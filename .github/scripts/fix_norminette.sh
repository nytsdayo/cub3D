#!/bin/bash
# fix_norminette.sh
# Applies basic formatting fixes to C and header files for Norminette compliance.
# This script performs the following fixes:
#   a) Remove trailing whitespace
#   b) Convert leading spaces to tabs
#   c) Align tabs and convert remaining spaces to tabs
#   d) Preprocessor directives: .h files use "# define", .c files use "#define"
#   e) Add newline before opening brace in struct definitions
#   f) Ensure a newline at EOF
# 
# Note: This script does NOT fix structural issues like:
#   - Incorrect indentation levels
#   - Function length violations (25 lines)
#   - Argument count violations (4 max)
#   - Line length violations (80 chars)
# These require manual fixes.

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

        # a) Remove trailing whitespace
        sed -i 's/[[:space:]]*$//' "$file"

        # b) Convert leading spaces to tabs (4 spaces = 1 tab)
        perl -i -pe 's/^[ ]+/"\t" x (length($&)\/4)/ge' "$file"

        # c) Align tabs - convert multiple spaces to single tab in indentation
        perl -i -pe 's/^(\t*)[ ]{2,}/"\1\t"/ge' "$file"

        # c-2) Convert all remaining spaces to tabs (for struct members, function declarations)
        perl -i -pe 's/^([\t ]*)\t([ ]+)/"\1\t" . ("\t" x (length($2)\/4))/ge' "$file"

        # d) Add space after # in preprocessor directives for .h files only
        # For .h files: # define, # include, etc. (but #ifndef, #endif no space)
        # For .c files: #define, #include, etc. (no space)
        if [[ "$file" == *.h ]]; then
            # .h files: Add space for define, include, etc.
            sed -i 's/^#[ ]*\(define\|include\|pragma\|undef\|warning\|error\|ifdef\|else\|elif\)\>/# \1/g' "$file"
            # Remove space for ifndef, endif
            sed -i 's/^#[ ]*\(ifndef\|endif\)\>/#\1/g' "$file"
            # Remove indentation before # directives
            sed -i 's/^[ \t]*\(#[ ]*\(ifdef\|ifndef\|endif\|else\|elif\|define\|include\|pragma\|undef\|warning\|error\)\)/\1/g' "$file"
        else
            # .c files: Remove space after # if present
            sed -i 's/^# \(define\|include\|pragma\|undef\|warning\|error\)\>/#\1/g' "$file"
        fi

        # e) Add newline before opening brace in struct/typedef definitions
        sed -i 's/^\(typedef struct [^{]*\){/\1\n{/g' "$file"
        sed -i 's/^\(struct [^{]*\){/\1\n{/g' "$file"

        # f) Ensure a newline at EOF
        if [ -s "$file" ] && [ "$(tail -c 1 "$file" | wc -l)" -eq 0 ]; then
            echo "" >> "$file"
        fi
    fi
done

echo ""
echo "Formatting fixes applied successfully."
