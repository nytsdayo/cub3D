# map サブモジュール設計

## 目的

- Parse exactly as rendered in the file; must support any valid layout.
- Spaces inside the map are meaningful tokens.

## 責務

<!-- このサブモジュールの責務を記述してください -->

- 

## インターフェース

### 公開関数

<!-- 公開関数の一覧を記述してください -->

| 関数名 | 説明 | 引数 | 戻り値 |
|--------|------|------|--------|
|`map_parser`        |map部分のパース処理      |char **input_data      |   int    |

## 内部設計

<!-- 内部の設計方針を記述してください -->

## エラーハンドリング

<!-- エラー処理の方針を記述してください -->
### Map content validation
- [ ] Minimum map size (e.g., ≥3x3)
- [ ] Maximum map size guard
### Map format validation
- [ ] Surrounded-by-walls validation
- [ ] Exactly one player start (only one of N/S/E/W)
- [ ] Row length consistency
- [ ] Invalid character detection (`is_valid_char` helper)
- [ ] (option: Reachability via flood fill)
- [ ] Policy for spaces touching void/out-of-bounds

## 参照

<!-- 参照ドキュメントへのリンクを記述してください -->

- [README](./README.md)
- [parse モジュール](../README.md)
