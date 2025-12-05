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

### Map content validation & format validation  

| Validation Rule | Description | Handling Policy |  
|----------------|-------------|-----------------|  
| Minimum map size | Map must be at least 3x3 in size | Reject map if too small |  
| Maximum map size guard | Map must not exceed maximum allowed size | Reject map if too large |  
| Surrounded-by-walls validation | Map must be enclosed by walls on all sides | Reject map if not enclosed |  
| Exactly one player start | Only one player start position (N/S/E/W) allowed | Reject map if zero or multiple starts |  
| Row length consistency | All rows must have the same length | Reject map if inconsistent |  
| Invalid character detection | Only valid characters allowed (`is_valid_char` helper) | Reject map if invalid character found |  
| Reachability via flood fill (optional) | All open areas must be reachable | Warn or reject if unreachable areas found |  
| Spaces touching void/out-of-bounds | Spaces must not touch void or out-of-bounds areas | Reject map if violation detected |  

## 参照

- [README](./README.md)
- [parse モジュール](../README.md)
