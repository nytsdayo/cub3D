# cub3D Test Cases

This document provides a comprehensive list of all test cases for the cub3D parser.

## Test Statistics

- **Total Tests**: 111
- **Success Cases**: 57
- **Failure Cases**: 54

## Success Test Cases (57)

These test cases should pass validation and parsing.

| # | Test File | Category | Description |
|---|-----------|----------|-------------|
| 1 | `cheese_maze.cub` | Complex Map | Cheese-themed maze layout |
| 2 | `creepy.cub` | Themed Map | Creepy atmosphere themed map |
| 3 | `diamond.cub` | Shape Test | Symmetrical diamond-shaped map |
| 4 | `dungeon.cub` | Themed Map | Dungeon-style map |
| 5 | `library.cub` | Themed Map | Library-themed environment |
| 6 | `matrix.cub` | Themed Map | Matrix-inspired map |
| 7 | `sad_face.cub` | Shape Test | Sad face shaped map |
| 8 | `square_map.cub` | Basic Shape | Standard square map with various features |
| 9 | `subject_map.cub` | Reference | Map from project subject |
| 10 | `test_map.cub` | Basic Test | General test map |
| 11 | `test_map_hole.cub` | Edge Case | Map with hole in the middle |
| 12 | `test_pos_bottom.cub` | Player Position | Player at bottom of map |
| 13 | `test_pos_left.cub` | Player Position | Player at left side of map |
| 14 | `test_pos_right.cub` | Player Position | Player at right side of map |
| 15 | `test_pos_top.cub` | Player Position | Player at top of map |
| 16 | `test_textures.cub` | Texture Test | Various texture configurations |
| 17 | `test_whitespace.cub` | Format Test | Map with extra whitespace |
| 18 | `valid_basic.cub` | Basic | Minimal valid configuration |
| 19 | `valid_bigmap/large_open_space.cub` | Large Map | Large open area |
| 20 | `valid_bigmap/maze_pattern.cub` | Large Map | Maze pattern in large map |
| 21 | `valid_bigmap/spiral_pattern.cub` | Large Map | Spiral pattern layout |
| 22 | `valid_complex.cub` | Complex | Complex map structure |
| 23 | `valid_complex/spiky_edges_1.cub` | Complex Shape | Map with spiky edges (variant 1) |
| 24 | `valid_complex/spiky_edges_2.cub` | Complex Shape | Map with spiky edges (variant 2) |
| 25 | `valid_complex/zigzag_horizontal.cub` | Complex Shape | Horizontal zigzag pattern |
| 26 | `valid_complex/zigzag_vertical.cub` | Complex Shape | Vertical zigzag pattern |
| 27 | `valid_minimal.cub` | Minimal | Smallest valid map (3x3) |
| 28 | `valid_player_east.cub` | Player Direction | Player facing East |
| 29 | `valid_player_south.cub` | Player Direction | Player facing South |
| 30 | `valid_player_west.cub` | Player Direction | Player facing West |
| 31 | `valid_random_order.cub` | Config Order | Random identifier order |
| 32-55 | `valid_random_order/order_*.cub` | Config Order | 24 permutations of identifier order |
| 56 | `valid_with_empty_lines.cub` | Format Test | Valid map with empty lines in config |
| 57 | `works.cub` | General | General working example |

### Identifier Order Tests (24 cases)

Tests all valid permutations of configuration identifiers (NO, SO, WE, EA, F, C).

| # | File | Order |
|---|------|-------|
| 1 | `order_01_NO_SO_WE_EA_F_C.cub` | NO → SO → WE → EA → F → C |
| 2 | `order_02_NO_WE_EA_SO_F_C.cub` | NO → WE → EA → SO → F → C |
| 3 | `order_03_NO_EA_F_SO_WE_C.cub` | NO → EA → F → SO → WE → C |
| 4 | `order_04_NO_F_C_SO_WE_EA.cub` | NO → F → C → SO → WE → EA |
| 5-24 | ... | (20 more permutations) |

## Failure Test Cases (54)

These test cases should fail validation with specific error codes.

### Color/RGB Tests (9 cases)

| # | Test File | Error Type | Description |
|---|-----------|------------|-------------|
| 1 | `color_invalid_rgb.cub` | Invalid RGB | RGB values out of range (0-255) |
| 2 | `color_missing_ceiling_rgb.cub` | Missing Config | Missing ceiling color |
| 3 | `color_missing.cub` | Missing Config | Missing both colors |
| 4 | `color_missing_floor_rgb.cub` | Missing Config | Missing floor color |
| 5 | `color_none.cub` | Missing Config | No color definitions |
| 6 | `invalid_rgb_format/ceiling_missing_value.cub` | RGB Format | Missing value in ceiling RGB |
| 7 | `invalid_rgb_format/ceiling_non_numeric.cub` | RGB Format | Non-numeric ceiling RGB |
| 8 | `invalid_rgb_format/floor_missing_value.cub` | RGB Format | Missing value in floor RGB |
| 9 | `invalid_rgb_format/floor_non_numeric.cub` | RGB Format | Non-numeric floor RGB |

### File Format Tests (3 cases)

| # | Test File | Error Type | Description |
|---|-----------|------------|-------------|
| 1 | `empty.cub` | Empty File | Completely empty file |
| 2 | `file_letter_end.cub` | Invalid Extension | Wrong file extension |
| 3 | `forbidden.cub` | Permission | No read permission (auto-generated) |

### Configuration Tests (7 cases)

| # | Test File | Error Type | Description |
|---|-----------|------------|-------------|
| 1 | `invalid_duplicate_config.cub` | Duplicate ID | Duplicate identifier |
| 2 | `invalid_incomplete_config.cub` | Missing ID | Incomplete configuration |
| 3 | `textures_duplicates.cub` | Duplicate | Duplicate texture definitions |
| 4 | `textures_missing.cub` | Missing Texture | Missing texture file |
| 5 | `textures_none.cub` | Missing Config | No texture definitions |
| 6 | `textures_not_xpm.cub` | Invalid Format | Non-XPM texture file |
| 7 | `textures_invalid.cub` | Invalid Path | Invalid texture path |

### Texture File Tests (3 cases)

| # | Test File | Error Type | Description |
|---|-----------|------------|-------------|
| 1 | `textures_dir.cub` | Invalid Path | Texture path is directory |
| 2 | `textures_forbidden.cub` | Permission | Texture file not readable |
| 3 | `invalid_missing_texture.cub` | Missing File | Referenced texture doesn't exist |

### Map Structure Tests (5 cases)

| # | Test File | Error Type | Description |
|---|-----------|------------|-------------|
| 1 | `invalid_empty_map.cub` | Empty Map | Map section is empty |
| 2 | `map_missing.cub` | Missing Map | No map section |
| 3 | `map_only.cub` | Missing Config | Map without configuration |
| 4 | `map_too_small.cub` | Size Error | Map smaller than 3x3 |
| 5 | `invalid_map_with_empty_line.cub` | Format Error | Empty line in map |

### Map Order Tests (2 cases)

| # | Test File | Error Type | Description |
|---|-----------|------------|-------------|
| 1 | `map_first.cub` | Config Order | Map before configuration |
| 2 | `map_middle.cub` | Config Order | Map in middle of config |

### Player Tests (15 cases)

| # | Test File | Error Type | Description |
|---|-----------|------------|-------------|
| 1 | `invalid_no_player.cub` | No Player | No player start position |
| 2 | `player_none.cub` | No Player | Missing player |
| 3 | `player_multiple.cub` | Multiple Players | Multiple player positions |
| 4 | `player_on_edge.cub` | Invalid Position | Player on map edge |
| 5-15 | `invalid_multiple_players/*.cub` | Multiple Players | 11 combinations of multiple players |

### Multiple Player Combinations (11 cases)

| # | File | Players |
|---|------|---------|
| 1 | `E_W.cub` | East + West |
| 2 | `N_E.cub` | North + East |
| 3 | `N_E_W.cub` | North + East + West |
| 4 | `N_S.cub` | North + South |
| 5 | `N_S_E.cub` | North + South + East |
| 6 | `N_S_E_W.cub` | North + South + East + West |
| 7 | `N_S_W.cub` | North + South + West |
| 8 | `N_W.cub` | North + West |
| 9 | `S_E.cub` | South + East |
| 10 | `S_E_W.cub` | South + East + West |
| 11 | `S_W.cub` | South + West |

### Wall Validation Tests (9 cases)

| # | Test File | Error Type | Description |
|---|-----------|------------|-------------|
| 1 | `invalid_not_closed.cub` | Wall Error | Map not enclosed by walls |
| 2 | `wall_none.cub` | Wall Error | No walls |
| 3 | `wall_hole_east.cub` | Wall Hole | Hole on east side |
| 4 | `wall_hole_north.cub` | Wall Hole | Hole on north side |
| 5 | `wall_hole_south.cub` | Wall Hole | Hole on south side |
| 6 | `wall_hole_west.cub` | Wall Hole | Hole on west side |
| 7-9 | `invalid_rgb_format/*_space_separated.cub` | Format Error | Space-separated RGB values |

### Character Validation Tests (1 case)

| # | Test File | Error Type | Description |
|---|-----------|------------|-------------|
| 1 | `invalid_characters.cub` | Invalid Char | Invalid characters in map |

## Test Execution

Tests are automatically run using:

```bash
make test                    # Run all tests
make -C tests parser-tests  # Run parser tests only
make -C tests leak-check    # Run memory leak tests
```

### Test Script

- Location: `tests/run_parser_tests.sh`
- Success cases: Expected to pass (exit code 0)
- Failure cases: Expected to fail (non-zero exit code)

### Special Cases

#### Auto-generated Tests

- **forbidden.cub**: Created during test execution with 000 permissions, automatically cleaned up afterward

#### Dynamic Tests

The test suite automatically discovers all `.cub` files in:
- `assets/maps/Success/` - Should pass
- `assets/maps/Failed/` - Should fail

## Error Code Coverage

The test cases cover all defined error codes:

- `ERR_INVALID_ARGC` (100)
- `ERR_INVALID_FILE_EXTENSION` (101)
- `ERR_UNKNOWN_IDENTIFIER` (200)
- `ERR_DUPLICATE_IDENTIFIER` (201)
- `ERR_SYNTAX_TEXTURE` (202)
- `ERR_SYNTAX_RGB` (203)
- `ERR_MISSING_IDENTIFIER` (204)
- `ERR_MINIMUM_MAP_SIZE` (300)
- `ERR_MAXIMUM_MAP_SIZE` (301)
- `ERR_PLAYER_COUNT_ZERO` (303)
- `ERR_PLAYER_COUNT_MULTIPLE` (304)
- `ERR_INVALID_CHARACTER` (306)
- `ERR_FILE_NOT_FOUND` (400)
- `ERR_MLX_INIT_FAILURE` (600)

## Adding New Test Cases

1. Create `.cub` file in appropriate directory:
   - Success cases: `assets/maps/Success/`
   - Failure cases: `assets/maps/Failed/`

2. Run tests to verify:
   ```bash
   make -C tests parser-tests
   ```

3. Update this documentation if adding new categories
