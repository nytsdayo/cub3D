#!/usr/bin/env bash

# Parser Test Script for cub3D
# This script tests the parser with various map files

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
CUB3D_BIN="${PROJECT_ROOT}/cub3D"
SUCCESS_MAPS_DIR="${PROJECT_ROOT}/assets/maps/success"
FAILED_MAPS_DIR="${PROJECT_ROOT}/assets/maps/failed"

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
if [ -d "$SUCCESS_MAPS_DIR" ]; then
    while IFS= read -r -d '' map_file; do
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        map_name=$(echo "$map_file" | sed "s|$SUCCESS_MAPS_DIR/||")
        echo -n "Testing $map_name ... "
        
        if [ -f "$CUB3D_BIN" ]; then
            # Run the parser with timeout to prevent hanging
            if timeout 10s "$CUB3D_BIN" "$map_file" &> /dev/null; then
                echo -e "${GREEN}✓ PASSED${NC}"
                PASSED_TESTS=$((PASSED_TESTS + 1))
            else
                echo -e "${RED}✗ FAILED (should have succeeded)${NC}"
                FAILED_TESTS=$((FAILED_TESTS + 1))
            fi
        else
            echo -e "${YELLOW}SKIPPED (binary not found)${NC}"
        fi
    done < <(find "$SUCCESS_MAPS_DIR" -name "*.cub" -type f -print0 | sort -z)
else
    echo "Success maps directory not found: $SUCCESS_MAPS_DIR"
fi

echo ""

# Test failure cases
echo "----------------------------------------"
echo "Testing FAILURE cases (should fail):"
echo "----------------------------------------"
if [ -d "$FAILED_MAPS_DIR" ]; then
    while IFS= read -r -d '' map_file; do
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        map_name=$(echo "$map_file" | sed "s|$FAILED_MAPS_DIR/||")
        echo -n "Testing $map_name ... "
        
        if [ -f "$CUB3D_BIN" ]; then
            # Run the parser - should fail (timeout also counts as failure)
            if timeout 10s "$CUB3D_BIN" "$map_file" &> /dev/null; then
                echo -e "${RED}✗ FAILED (should have failed)${NC}"
                FAILED_TESTS=$((FAILED_TESTS + 1))
            else
                echo -e "${GREEN}✓ PASSED${NC}"
                PASSED_TESTS=$((PASSED_TESTS + 1))
            fi
        else
            echo -e "${YELLOW}SKIPPED (binary not found)${NC}"
        fi
    done < <(find "$FAILED_MAPS_DIR" -name "*.cub" -type f -print0 | sort -z)
else
    echo "Failed maps directory not found: $FAILED_MAPS_DIR"
fi

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
