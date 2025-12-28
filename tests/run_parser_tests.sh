#!/usr/bin/env bash

# Parser Test Script for cub3D
# This script tests the parser with various map files
#
# Directory structure:
#   - assets/maps/good/    -> Valid maps (should pass)
#   - assets/maps/success/ -> Valid maps (should pass)
#   - assets/maps/bad/     -> Invalid maps (should fail)
#   - assets/maps/failed/  -> Invalid maps (should fail)
#   - assets/maps/test/    -> Incomplete test maps (not tested)
#   - assets/maps/Failed/  -> Empty directory (not tested)

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Counters
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

# Paths
if [ -n "$PARSER_BIN" ]; then
    CUB3D_BIN="$PARSER_BIN"
else
    CUB3D_BIN="${PROJECT_ROOT}/cub3D"
fi
# Success case directories (should pass)
SUCCESS_DIRS=(
    "${PROJECT_ROOT}/assets/maps/success"
    "${PROJECT_ROOT}/assets/maps/good"
)
# Failure case directories (should fail)
FAILED_DIRS=(
    "${PROJECT_ROOT}/assets/maps/failed"
    "${PROJECT_ROOT}/assets/maps/bad"
)

echo "=========================================="
echo "cub3D Parser Test Suite"
echo "=========================================="
echo ""

# Check if cub3D binary exists
if [ ! -f "$CUB3D_BIN" ]; then
    echo -e "${YELLOW}Warning: cub3D binary not found at $CUB3D_BIN${NC}"
    echo -e "${YELLOW}Please build the project first with 'make'${NC}"
    echo -e "${YELLOW}Note: Parser is not yet implemented, this is a dry run${NC}"
    echo ""
fi

# Test success cases
echo "----------------------------------------"
echo "Testing SUCCESS cases (should pass):"
echo "----------------------------------------"
for SUCCESS_DIR in "${SUCCESS_DIRS[@]}"; do
    if [ -d "$SUCCESS_DIR" ]; then
        DIR_NAME=$(basename "$SUCCESS_DIR")
        echo ""
        echo "Testing directory: $DIR_NAME"
        echo "---"
        while IFS= read -r -d '' map_file; do
            TOTAL_TESTS=$((TOTAL_TESTS + 1))
            map_name="${map_file#$SUCCESS_DIR/}"
            echo -n "  $map_name ... "

            if [ -x "$CUB3D_BIN" ]; then
                # Run the parser only (skip rendering) with timeout, from project root
                if timeout 10s sh -c "cd '$PROJECT_ROOT' && '$CUB3D_BIN' '$map_file'" &> /dev/null; then
                    echo -e "${GREEN}✓ PASSED${NC}"
                    PASSED_TESTS=$((PASSED_TESTS + 1))
                else
                    echo -e "${RED}✗ FAILED (should have succeeded)${NC}"
                    FAILED_TESTS=$((FAILED_TESTS + 1))
                fi
            else
                echo -e "${YELLOW}SKIPPED (binary not found)${NC}"
            fi
        done < <(find "$SUCCESS_DIR" -name "*.cub" -type f -print0 | sort -z)
    else
        echo "Success maps directory not found: $SUCCESS_DIR"
    fi
done

echo ""

# Test failure cases
echo "----------------------------------------"
echo "Testing FAILURE cases (should fail):"
echo "----------------------------------------"
for FAILED_DIR in "${FAILED_DIRS[@]}"; do
    if [ -d "$FAILED_DIR" ]; then
        DIR_NAME=$(basename "$FAILED_DIR")
        echo ""
        echo "Testing directory: $DIR_NAME"
        echo "---"
        while IFS= read -r -d '' map_file; do
            TOTAL_TESTS=$((TOTAL_TESTS + 1))
            map_name="${map_file#$FAILED_DIR/}"
            echo -n "  $map_name ... "

            if [ -x "$CUB3D_BIN" ]; then
                # Run the parser only (skip rendering) - should fail (timeout also counts as failure)
                if timeout 10s sh -c "cd '$PROJECT_ROOT' && '$CUB3D_BIN' '$map_file'" &> /dev/null; then
                    echo -e "${RED}✗ FAILED (should have failed)${NC}"
                    FAILED_TESTS=$((FAILED_TESTS + 1))
                else
                    echo -e "${GREEN}✓ PASSED${NC}"
                    PASSED_TESTS=$((PASSED_TESTS + 1))
                fi
            else
                echo -e "${YELLOW}SKIPPED (binary not found)${NC}"
            fi
        done < <(find "$FAILED_DIR" -name "*.cub" -type f -print0 | sort -z)
    else
        echo "Failed maps directory not found: $FAILED_DIR"
    fi
done

echo ""
echo "=========================================="
echo "Test Results Summary"
echo "=========================================="
echo "Total tests: $TOTAL_TESTS"
echo -e "Passed: ${GREEN}$PASSED_TESTS${NC}"
echo -e "Failed: ${RED}$FAILED_TESTS${NC}"

if [ -f "$CUB3D_BIN" ]; then
    if [ $FAILED_TESTS -eq 0 ]; then
        echo ""
        echo -e "${GREEN}All tests passed! 🎉${NC}"
        exit 0
    else
        echo ""
        echo -e "${RED}Some tests failed.${NC}"
        exit 1
    fi
else
    echo ""
    echo -e "${YELLOW}Tests skipped - parser not yet implemented${NC}"
    echo "This is expected at this stage of development."
    exit 0
fi
