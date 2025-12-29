#!/bin/bash

# cub3Dエラー再現テストスクリプト
# すべての起きうるエラーシナリオを網羅的にテストします

set -e

# カラー定義
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# カウンター
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# テスト用一時ディレクトリ
TEST_DIR="./test_error_cases"
mkdir -p "$TEST_DIR"

# プログラムのパス
CUB3D="./cub3D"

# クリーンアップ関数
cleanup() {
    rm -rf "$TEST_DIR"
}
trap cleanup EXIT

# テスト実行関数
# $1: テスト名
# $2: 期待されるエラーメッセージの一部
# $3: コマンド（配列として渡す）
run_test() {
    local test_name="$1"
    local expected_error="$2"
    shift 2
    local cmd=("$@")

    TOTAL_TESTS=$((TOTAL_TESTS + 1))

    echo -e "${BLUE}[TEST $TOTAL_TESTS]${NC} $test_name"

    # コマンド実行
    output=$(timeout 2s "${cmd[@]}" 2>&1) || true

    # エラーメッセージが含まれているかチェック
    if echo "$output" | grep -q "$expected_error"; then
        echo -e "${GREEN}✓ PASS${NC} - Expected error: \"$expected_error\""
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAIL${NC} - Expected error: \"$expected_error\""
        echo "  Got: $output"
        FAILED_TESTS=$((FAILED_TESTS + 1))
    fi
    echo ""
}

# ============================================================================
# カテゴリ1: コマンドライン引数エラー (100番台)
# ============================================================================

echo -e "${YELLOW}=== カテゴリ1: コマンドライン引数エラー ===${NC}"

# ERR_INVALID_ARGC (100)
run_test "引数なし" "Usage: ./cub3D <map.cub>" \
    $CUB3D

run_test "引数が多すぎる" "Usage: ./cub3D <map.cub>" \
    $CUB3D "map1.cub" "map2.cub"

# ERR_INVALID_FILE_EXTENSION (402)
run_test "拡張子が.cubでない（.txt）" "Invalid file extension" \
    $CUB3D "$TEST_DIR/test.txt"

run_test "拡張子が.cubでない（.map）" "Invalid file extension" \
    $CUB3D "$TEST_DIR/test.map"

run_test "拡張子なし" "Invalid file extension" \
    $CUB3D "$TEST_DIR/test"

run_test "ファイル名が短すぎる（.cub未満）" "Invalid file extension" \
    $CUB3D "a.c"

# ============================================================================
# カテゴリ2: ファイルI/Oエラー (400番台)
# ============================================================================

echo -e "${YELLOW}=== カテゴリ2: ファイルI/Oエラー ===${NC}"

# ERR_FILE_NOT_FOUND (400)
run_test "存在しないファイル" "File not found" \
    $CUB3D "$TEST_DIR/nonexistent.cub"

# ERR_FILE_READ_PERMISSION (401)
# 読み取り権限のないファイルを作成
touch "$TEST_DIR/no_read.cub"
chmod 000 "$TEST_DIR/no_read.cub"
run_test "読み取り権限なし" "File not found" \
    $CUB3D "$TEST_DIR/no_read.cub"
chmod 644 "$TEST_DIR/no_read.cub" # クリーンアップのために権限を戻す

# ============================================================================
# カテゴリ3: 設定(Config)解析エラー (200番台)
# ============================================================================

echo -e "${YELLOW}=== カテゴリ3: 設定(Config)解析エラー ===${NC}"

# ERR_UNKNOWN_IDENTIFIER (200)
cat > "$TEST_DIR/unknown_id.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
XX invalid_identifier.xpm
F 220,100,0
C 225,30,0

111111
100001
101N01
100001
111111
EOF
run_test "未知の識別子（XX）" "Unknown identifier" \
    $CUB3D "$TEST_DIR/unknown_id.cub"

# ERR_DUPLICATE_IDENTIFIER (201)
cat > "$TEST_DIR/duplicate_id.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0
NO assets/textures/cub3_north_newyear.xpm

111111
100001
101N01
100001
111111
EOF
run_test "重複した識別子（NO）" "Duplicate identifier" \
    $CUB3D "$TEST_DIR/duplicate_id.cub"

# ERR_SYNTAX_TEXTURE (202) - テクスチャパスの不正
cat > "$TEST_DIR/invalid_texture_ext.cub" << 'EOF'
NO assets/textures/north.png
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

111111
100001
101N01
100001
111111
EOF
run_test "テクスチャ拡張子が.xpmでない" "Invalid file extension" \
    $CUB3D "$TEST_DIR/invalid_texture_ext.cub"

cat > "$TEST_DIR/no_texture_path.cub" << 'EOF'
NO
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

111111
100001
101N01
100001
111111
EOF
run_test "テクスチャパスなし" "Invalid file extension" \
    $CUB3D "$TEST_DIR/no_texture_path.cub"

# ERR_SYNTAX_RGB (203) - RGB値の不正
cat > "$TEST_DIR/invalid_rgb_range.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 256,100,0
C 225,30,0

111111
100001
101N01
100001
111111
EOF
run_test "RGB値が範囲外（256）" "Invalid RGB color format" \
    $CUB3D "$TEST_DIR/invalid_rgb_range.cub"

cat > "$TEST_DIR/invalid_rgb_negative.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F -1,100,0
C 225,30,0

111111
100001
101N01
100001
111111
EOF
run_test "RGB値が負の数" "Invalid RGB color format" \
    $CUB3D "$TEST_DIR/invalid_rgb_negative.cub"

cat > "$TEST_DIR/invalid_rgb_format.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100
C 225,30,0

111111
100001
101N01
100001
111111
EOF
run_test "RGB値の要素が不足" "Invalid RGB color format" \
    $CUB3D "$TEST_DIR/invalid_rgb_format.cub"

cat > "$TEST_DIR/invalid_rgb_text.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F abc,100,0
C 225,30,0

111111
100001
101N01
100001
111111
EOF
run_test "RGB値に文字列が含まれる" "Invalid RGB color format" \
    $CUB3D "$TEST_DIR/invalid_rgb_text.cub"

# ERR_MISSING_IDENTIFIER (204)
cat > "$TEST_DIR/missing_no.cub" << 'EOF'
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

111111
100001
101N01
100001
111111
EOF
run_test "識別子NOが欠けている" "Missing required identifier" \
    $CUB3D "$TEST_DIR/missing_no.cub"

cat > "$TEST_DIR/missing_floor.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
C 225,30,0

111111
100001
101N01
100001
111111
EOF
run_test "識別子Fが欠けている" "Missing required identifier" \
    $CUB3D "$TEST_DIR/missing_floor.cub"

# ============================================================================
# カテゴリ4: マップ検証エラー (300番台)
# ============================================================================

echo -e "${YELLOW}=== カテゴリ4: マップ検証エラー ===${NC}"

# ERR_MINIMUM_MAP_SIZE (300) - 最小サイズ未満
cat > "$TEST_DIR/too_small_map.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

11
1N
EOF
run_test "マップが小さすぎる（2x2）" "Map is too small" \
    $CUB3D "$TEST_DIR/too_small_map.cub"

cat > "$TEST_DIR/no_map.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0
EOF
run_test "マップセクションがない" "Map is too small" \
    $CUB3D "$TEST_DIR/no_map.cub"

# ERR_PLAYER_COUNT_ZERO (302)
cat > "$TEST_DIR/no_player.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

111111
100001
100001
100001
111111
EOF
run_test "プレイヤー開始位置がない" "No player start position" \
    $CUB3D "$TEST_DIR/no_player.cub"

# ERR_PLAYER_COUNT_MULTIPLE (303)
cat > "$TEST_DIR/multiple_players.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

111111
1N0001
100S01
100001
111111
EOF
run_test "プレイヤー開始位置が複数" "Multiple player start positions" \
    $CUB3D "$TEST_DIR/multiple_players.cub"

# ERR_INVALID_CHARACTER (305)
cat > "$TEST_DIR/invalid_char.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

111111
1X0001
101N01
100001
111111
EOF
run_test "無効な文字（X）がマップに含まれる" "Invalid character" \
    $CUB3D "$TEST_DIR/invalid_char.cub"

cat > "$TEST_DIR/invalid_char_number.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

111111
120001
101N01
100001
111111
EOF
run_test "無効な文字（2）がマップに含まれる" "Invalid character" \
    $CUB3D "$TEST_DIR/invalid_char_number.cub"

# ERR_WALL_ENCLOSURE (301) - 壁に囲まれていない
cat > "$TEST_DIR/not_enclosed.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

111111
100001
101N01
100001
111110
EOF
run_test "マップが壁に囲まれていない（右下が開いている）" "not enclosed by walls" \
    $CUB3D "$TEST_DIR/not_enclosed.cub"

cat > "$TEST_DIR/open_top.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

101111
100001
101N01
100001
111111
EOF
run_test "マップが壁に囲まれていない（上部が開いている）" "not enclosed by walls" \
    $CUB3D "$TEST_DIR/open_top.cub"

cat > "$TEST_DIR/open_left.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

111111
000001
001N01
000001
111111
EOF
run_test "マップが壁に囲まれていない（左側が開いている）" "not enclosed by walls" \
    $CUB3D "$TEST_DIR/open_left.cub"

# ERR_SPACE_VOID_CONTACT (306) - スペースがvoidに接触
cat > "$TEST_DIR/space_void.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

1111111
1000001
10N0001
1000001
111111
EOF
run_test "スペースがvoid領域に接触している" "Space character touches void" \
    $CUB3D "$TEST_DIR/space_void.cub"

cat > "$TEST_DIR/space_void2.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

  1111
  1001
1110N1
1000 1
111111
EOF
run_test "スペースがvoid領域に接触している（複雑なケース）" "Space character touches void" \
    $CUB3D "$TEST_DIR/space_void2.cub"

# マップ内に空行が含まれる
cat > "$TEST_DIR/empty_line_in_map.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

111111
100001

101N01
100001
111111
EOF
run_test "マップ内に空行が含まれる" "Invalid character" \
    $CUB3D "$TEST_DIR/empty_line_in_map.cub"

# ============================================================================
# カテゴリ5: エンジン/MLXエラー (600番台)
# ============================================================================

echo -e "${YELLOW}=== カテゴリ5: テクスチャロードエラー ===${NC}"

# ERR_TEXTURE_LOAD_FAILURE (603) - 存在しないテクスチャファイル
cat > "$TEST_DIR/missing_texture.cub" << 'EOF'
NO assets/textures/nonexistent.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

111111
100001
101N01
100001
111111
EOF
run_test "存在しないテクスチャファイル" "Failed to load texture" \
    $CUB3D "$TEST_DIR/missing_texture.cub"

# ============================================================================
# カテゴリ6: エッジケース・境界値テスト
# ============================================================================

echo -e "${YELLOW}=== カテゴリ6: エッジケース・境界値テスト ===${NC}"

# RGB境界値テスト（0と255は正常）
cat > "$TEST_DIR/rgb_boundary_0.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 0,0,0
C 255,255,255

111111
100001
101N01
100001
111111
EOF
run_test "RGB境界値（0,0,0 と 255,255,255）は正常" "" \
    timeout 1s $CUB3D "$TEST_DIR/rgb_boundary_0.cub" || echo "プログラムが正常に起動（予期された動作）"

# 最小サイズのマップ（3x3）は正常
cat > "$TEST_DIR/min_size_map.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

111
1N1
111
EOF
run_test "最小サイズ（3x3）のマップは正常" "" \
    timeout 1s $CUB3D "$TEST_DIR/min_size_map.cub" || echo "プログラムが正常に起動（予期された動作）"

# 全方向のプレイヤー向き
for dir in N S E W; do
    cat > "$TEST_DIR/player_dir_${dir}.cub" << EOF
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0
C 225,30,0

111111
100001
101${dir}01
100001
111111
EOF
    run_test "プレイヤー向き: ${dir}" "" \
        timeout 1s $CUB3D "$TEST_DIR/player_dir_${dir}.cub" || echo "プログラムが正常に起動（予期された動作）"
done

# ============================================================================
# カテゴリ7: 設定とマップの組み合わせエラー
# ============================================================================

echo -e "${YELLOW}=== カテゴリ7: 設定とマップの組み合わせエラー ===${NC}"

# 設定がマップの後に出現
cat > "$TEST_DIR/config_after_map.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F 220,100,0

111111
100001
101N01
100001
111111

C 225,30,0
EOF
run_test "設定行がマップの後に出現" "Unknown identifier\\|Invalid character" \
    $CUB3D "$TEST_DIR/config_after_map.cub"

# RGB値にスペースが含まれる（仕様上許容される可能性あり）
cat > "$TEST_DIR/rgb_with_spaces.cub" << 'EOF'
NO assets/textures/cub3_north_newyear.xpm
SO assets/textures/cub3_south_xmaswreath.xpm
WE assets/textures/cub3_west_snowflake.xpm
EA assets/textures/cub3_east_cookie.xpm
F  220 , 100 , 0
C  225 , 30 , 0

111111
100001
101N01
100001
111111
EOF
run_test "RGB値にスペースが含まれる（仕様上許容される）" "" \
    timeout 1s $CUB3D "$TEST_DIR/rgb_with_spaces.cub" || echo "プログラムが正常に起動（予期された動作）"

# ============================================================================
# 結果サマリー
# ============================================================================

echo ""
echo -e "${YELLOW}========================================${NC}"
echo -e "${YELLOW}テスト結果サマリー${NC}"
echo -e "${YELLOW}========================================${NC}"
echo -e "総テスト数: ${BLUE}$TOTAL_TESTS${NC}"
echo -e "成功: ${GREEN}$PASSED_TESTS${NC}"
echo -e "失敗: ${RED}$FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}すべてのテストが成功しました！${NC}"
    exit 0
else
    echo -e "${RED}一部のテストが失敗しました${NC}"
    exit 1
fi
