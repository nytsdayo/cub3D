#!/usr/bin/env bash

# Memory Leak Check Script for cub3D
# This script checks for memory leaks using Valgrind

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

# Paths
CUB3D_BIN="${PROJECT_ROOT}/cub3D"
GOOD_MAPS_DIR="${PROJECT_ROOT}/assets/maps/good"

echo "=========================================="
echo "cub3D Memory Leak Check with Valgrind"
echo "=========================================="
echo ""

# Check if Valgrind is installed
if ! command -v valgrind &> /dev/null; then
    echo -e "${RED}Error: Valgrind is not installed${NC}"
    echo "Please install Valgrind first:"
    echo "  Ubuntu/Debian: sudo apt-get install valgrind"
    echo "  macOS: brew install valgrind"
    exit 1
fi

# Check if cub3D binary exists
if [ ! -f "$CUB3D_BIN" ]; then
    echo -e "${RED}Error: cub3D binary not found at $CUB3D_BIN${NC}"
    echo "Please build the project first with 'make'"
    exit 1
fi

# Check if good maps directory exists
if [ ! -d "$GOOD_MAPS_DIR" ]; then
    echo -e "${RED}Error: Good maps directory not found: $GOOD_MAPS_DIR${NC}"
    exit 1
fi

echo "Testing good maps for memory leaks..."
echo "----------------------------------------"
echo ""

# Find all .cub files in good maps directory
while IFS= read -r -d '' map_file; do
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    map_name=$(basename "$map_file")

    echo -e "${BLUE}Testing: $map_name${NC}"

    # Create temporary file for Valgrind output
    VALGRIND_OUTPUT=$(mktemp)

    # Run Valgrind with proper options
    # --leak-check=full: detailed leak information
    # --show-leak-kinds=all: show all types of leaks
    # Don't use --error-exitcode because we only care about leaks, not program errors
    timeout 5s valgrind \
        --leak-check=full \
        --show-leak-kinds=all \
        --log-file="$VALGRIND_OUTPUT" \
        "$CUB3D_BIN" "$map_file" &> /dev/null

    # Always check the leak summary from Valgrind output
    # Exit code doesn't matter - we only care about actual memory leaks
    LEAK_BYTES=$(grep "definitely lost:" "$VALGRIND_OUTPUT" | awk '{print $4}' | sed 's/,//g')
    POSSIBLY_LOST=$(grep "possibly lost:" "$VALGRIND_OUTPUT" | awk '{print $4}' | sed 's/,//g')

    # Check if there are no leaks
    if [ -z "$LEAK_BYTES" ]; then
        LEAK_BYTES=0
    fi
    if [ -z "$POSSIBLY_LOST" ]; then
        POSSIBLY_LOST=0
    fi

    if [ "$LEAK_BYTES" -eq 0 ] && [ "$POSSIBLY_LOST" -eq 0 ]; then
        echo -e "  ${GREEN}✓ PASSED - No memory leaks detected${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "  ${RED}✗ FAILED - Memory leak detected${NC}"
        if [ "$LEAK_BYTES" -gt 0 ]; then
            echo -e "    Definitely lost: ${RED}$LEAK_BYTES bytes${NC}"
        fi
        if [ "$POSSIBLY_LOST" -gt 0 ]; then
            echo -e "    Possibly lost: ${YELLOW}$POSSIBLY_LOST bytes${NC}"
        fi
        echo -e "  ${YELLOW}Valgrind output:${NC}"
        grep -A 8 "LEAK SUMMARY" "$VALGRIND_OUTPUT" | sed 's/^/    /'
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi

    # Clean up temporary file
    rm -f "$VALGRIND_OUTPUT"
    echo ""

done < <(find "$GOOD_MAPS_DIR" -maxdepth 1 -name "*.cub" -type f -print0 | sort -z)

echo ""
echo "=========================================="
echo "Leak Check Results Summary"
echo "=========================================="
echo "Total tests: $TOTAL_TESTS"
echo -e "Passed: ${GREEN}$PASSED_TESTS${NC}"
echo -e "Failed: ${RED}$FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo ""
    echo -e "${GREEN}All leak checks passed! 🎉${NC}"
    exit 0
else
    echo ""
    echo -e "${RED}Some leak checks failed.${NC}"
    exit 1
fi
