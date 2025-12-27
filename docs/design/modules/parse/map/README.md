# map サブモジュール

## 概要

マップパーサーは.cubファイルからマップデータを読み込み、検証する機能を提供します。

### マップ文字

- `0`: 空きスペース
- `1`: 壁
- `N`, `S`, `E`, `W`: プレイヤーの初期位置と向き
- ` ` (スペース): マップ内の有効なトークン

### 検証ルール

- マップは壁（`1`）で完全に囲まれている必要がある
- プレイヤーの開始位置は必ず1つだけ
- 最小サイズ: 3x3
- 有効な文字のみを含む

## 機能

### `load_map()`

```c
int load_map(char **input_data, size_t line_index, t_map_data *map_data);
```

マップデータをメモリに読み込み、検証を行います。

**パラメータ**:
- `input_data`: 入力データの行配列
- `line_index`: マップの開始行インデックス
- `map_data`: マップデータを格納する構造体

**戻り値**:
- `0`: 成功
- `-1`: 失敗（エラーメッセージを標準エラー出力に出力）

### `validate_map()`

```c
int validate_map(char **input_data, size_t line_index);
```

マップの構文を検証します（メモリ確保は行いません）。

## テスト

マップパーサーのテストはC++で実装されています。

### テストの実行

```bash
make test_parse_map
```

### テストファイル

テストファイルは`tests/parse/map/`に配置されています：

**有効なマップ**:
- `valid_simple.cub`: 基本的な有効なマップ
- `valid_medium.cub`: 中規模の有効なマップ
- `valid_with_spaces.cub`: スペースを含む有効なマップ

**無効なマップ**:
- `invalid_no_player.cub`: プレイヤーがいない
- `invalid_two_players.cub`: プレイヤーが複数いる
- `invalid_no_wall.cub`: 壁が閉じていない
- `invalid_too_small.cub`: サイズが小さすぎる
- `invalid_bad_char.cub`: 不正な文字を含む

詳細は[テストガイド](../../../../development/testing.md)を参照してください。

## 実装ファイル

- `srcs/parse/map/parse_map.c`: メイン実装
- `includes/parse/parse.h`: ヘッダーファイル
- `tests/parse/map/`: テストコード（C++）

## 参照

- [parse モジュール](../README.md)
- [テストガイド](../../../../development/testing.md)
- [データ構造](../../../data/structure.md)
