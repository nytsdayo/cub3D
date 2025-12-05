#!/bin/bash
# fix_norminette.sh
# Applies safe formatting fixes to C and header files for Norminette compliance.
# This script performs the following fixes:
#   a) Convert leading spaces to tabs (Norminette requires tabs for indentation)
#   b) Remove trailing whitespace
#   c) Ensure a newline at EOF
#   d) Apply clang-format (use repo .clang-format if present, otherwise default)

set -euo pipefail

# Skip execution if triggered by github-actions[bot]
if [ "${GITHUB_ACTOR:-}" = "github-actions[bot]" ]; then
    echo "Skipping auto-fix: triggered by github-actions[bot] to avoid loops."
    exit 0
fi

# Find all tracked .c and .h files in srcs/ and includes/ (matching norminette.yml)
FILES=$(git ls-files 'srcs/*.c' 'srcs/**/*.c' 'srcs/*.h' 'srcs/**/*.h' 'includes/*.c' 'includes/**/*.c' 'includes/*.h' 'includes/**/*.h' 2>/dev/null || true)

if [ -z "$FILES" ]; then
    echo "No .c or .h files found in the repository."
    exit 0
fi

echo "Processing the following files:"
echo "$FILES"
echo ""

for file in $FILES; do
    if [ -f "$file" ]; then
        echo "Fixing: $file"

        # a) Convert leading 4 spaces to tabs (Norminette requires tabs for indentation)
        # First, normalize any existing leading spaces to tabs
        perl -i -pe 's/^(    )+/"\t" x (length($&)\/4)/ge' "$file"

        # b) Remove trailing whitespace
        sed -i 's/[[:space:]]*$//' "$file"

        # c) Ensure a newline at EOF
        if [ -s "$file" ] && [ "$(tail -c 1 "$file" | wc -l)" -eq 0 ]; then
            echo "" >> "$file"
        fi

        # d) Apply clang-format
        if command -v clang-format &> /dev/null; then
            clang-format -i "$file"
        else
            echo "Warning: clang-format not found, skipping clang-format step for $file"
        fi
    fi
done

echo ""
echo "Formatting fixes applied successfully."
