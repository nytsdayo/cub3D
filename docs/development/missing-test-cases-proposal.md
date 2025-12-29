# 追加すべきテストケースの提案 / Missing Test Cases Proposal

このドキュメントでは、現在のテストスイートに不足している可能性のあるテストケースを提案します。

## 提案の背景

現在のテストケース：
- **成功ケース**: 56ファイル
- **失敗ケース**: 54ファイル
- **合計**: 110ファイル

以下のカテゴリで追加のテストケースが必要と考えられます。

---

## 1. 境界値テスト (Boundary Value Tests)

### 1.1 RGB値の境界値
**目的**: RGB値の有効範囲（0-255）の境界値を確実にテストする

**提案するテストケース**:
- `Success/valid_rgb_boundary_min.cub` - F 0,0,0 と C 0,0,0（最小値）
- `Success/valid_rgb_boundary_max.cub` - F 255,255,255 と C 255,255,255（最大値）
- `Success/valid_rgb_boundary_mixed.cub` - F 0,128,255 と C 255,128,0（境界値混合）
- `Failed/invalid_rgb_negative.cub` - F -1,0,0（負の値）
- `Failed/invalid_rgb_overflow.cub` - C 256,0,0（範囲外）
- `Failed/invalid_rgb_overflow_large.cub` - F 999,999,999（大きく範囲外）

**優先度**: 高 - RGB値の検証は必須機能

---

## 2. マップサイズのエッジケース (Map Size Edge Cases)

### 2.1 最小・最大サイズ
**目的**: マップのサイズ制限を正しく処理できるか確認

**提案するテストケース**:
- `Success/valid_map_3x3.cub` - 最小の有効なマップ（既存のvalid_minimalと重複の可能性あり、確認が必要）
- `Success/valid_map_rectangular.cub` - 長方形のマップ（横長：例 3x20）
- `Success/valid_map_tall.cub` - 縦長のマップ（例 20x3）
- `Failed/invalid_map_too_small_1x1.cub` - 1x1マップ（小さすぎる）
- `Failed/invalid_map_too_small_2x2.cub` - 2x2マップ（プレイヤーを囲めない）

**優先度**: 中 - エッジケースの処理確認

---

## 3. 空白文字とフォーマット (Whitespace and Format)

### 3.1 様々な空白パターン
**目的**: パーサーが様々な空白の扱いに対応できるか確認

**提案するテストケース**:
- `Success/valid_tabs_in_config.cub` - 設定部分にタブ文字が含まれる
- `Success/valid_trailing_spaces.cub` - 各行の末尾にスペースがある
- `Success/valid_multiple_spaces_between_elements.cub` - 設定要素間に複数のスペース
- `Failed/invalid_tab_in_map.cub` - マップ内にタブ文字がある（スペースのみ許可の場合）
- `Failed/invalid_leading_spaces_in_config.cub` - 設定行の先頭に不適切なスペース（実装依存）

**優先度**: 中 - フォーマット処理の堅牢性確認

---

## 4. テクスチャパスのエッジケース (Texture Path Edge Cases)

### 4.1 パス形式のバリエーション
**目的**: 様々なパス形式を正しく処理できるか確認

**提案するテストケース**:
- `Success/valid_relative_path_dotdot.cub` - 相対パス（../textures/file.xpm）
- `Success/valid_path_with_spaces.cub` - スペースを含むパス（要エスケープ確認）
- `Failed/invalid_texture_empty_path.cub` - テクスチャパスが空
- `Failed/invalid_texture_directory.cub` - ディレクトリパスが指定されている（既存のtextures_dir.cubで対応済みの可能性）
- `Failed/invalid_texture_special_chars.cub` - 不正な特殊文字を含むパス

**優先度**: 中 - ファイルパス処理の堅牢性

---

## 5. 設定要素の形式 (Configuration Element Format)

### 5.1 大文字小文字の扱い
**目的**: 設定要素の大文字小文字の扱いを確認

**提案するテストケース**:
- `Failed/invalid_lowercase_config.cub` - 小文字の設定（no, so, we, ea, f, c）
- `Failed/invalid_mixed_case_config.cub` - 大文字小文字混合（No, So, We, Ea）

**優先度**: 低 - 仕様が明確な場合のみ

### 5.2 設定値の形式
**提案するテストケース**:
- `Failed/invalid_rgb_with_spaces.cub` - RGB値内にスペース（例：10, 20 , 30）
- `Failed/invalid_rgb_comma_format.cub` - カンマの位置が不正（例：10,,20,30 や 10,20,30,）
- `Failed/invalid_extra_config_params.cub` - 余分なパラメータ（例：NO path1.xpm path2.xpm）

**優先度**: 中 - パーサーのエラーハンドリング確認

---

## 6. マップ形状の複雑なケース (Complex Map Shapes)

### 6.1 特殊な形状
**目的**: 様々な複雑な形状のマップを処理できるか確認

**提案するテストケース**:
- `Success/valid_map_inner_walls.cub` - 内部に孤立した壁のある部屋
- `Success/valid_map_thin_corridors.cub` - 1マス幅の細い通路
- `Success/valid_map_irregular_perimeter.cub` - 非常に不規則な外周
- `Failed/invalid_map_space_leak.cub` - スペース（' '）を通じて外部に抜けられる
- `Failed/invalid_map_diagonal_leak.cub` - 対角線方向で壁が不完全（実装依存）

**優先度**: 高 - マップ検証の正確性確認

---

## 7. ファイル形式とエンコーディング (File Format and Encoding)

### 7.1 ファイル形式
**目的**: ファイル形式の堅牢性を確認

**提案するテストケース**:
- `Failed/invalid_utf8_bom.cub` - UTF-8 BOMが含まれるファイル
- `Failed/invalid_crlf_endings.cub` - Windows改行（\r\n）形式（実装依存）
- `Failed/invalid_no_newline_at_eof.cub` - ファイル末尾に改行がない
- `Failed/invalid_binary_content.cub` - バイナリデータが含まれる

**優先度**: 低 - プラットフォーム依存性が高い

---

## 8. コメント機能（仕様による）(Comments - if supported)

### 8.1 コメントの扱い
**目的**: コメント機能がサポートされている場合のテスト

**提案するテストケース**:
- `Success/valid_with_comments.cub` - #コメントを含むファイル（仕様による）
- `Failed/invalid_comment_in_map.cub` - マップ内にコメント（許可されない場合）

**優先度**: 低 - 仕様に明示的にコメント機能がない場合は不要

---

## 9. パフォーマンステスト (Performance Tests)

### 9.1 大規模マップ
**目的**: パーサーのパフォーマンスと制限を確認

**提案するテストケース**:
- `Success/valid_huge_map_100x100.cub` - 100×100サイズのマップ
- `Success/valid_huge_map_200x200.cub` - 200×200サイズのマップ
- `Success/valid_deep_nesting.cub` - 複雑にネストされた構造
- `Failed/invalid_too_many_config_lines.cub` - 不正に多数の設定行

**優先度**: 低 - 基本機能実装後

---

## 10. 特殊な壁の配置 (Special Wall Placements)

### 10.1 エッジケース
**目的**: 壁の配置パターンのエッジケースを確認

**提案するテストケース**:
- `Success/valid_player_surrounded_by_walls.cub` - プレイヤーが壁で囲まれているが抜け道がある
- `Failed/invalid_player_in_wall.cub` - プレイヤーが壁（1）の位置にいる
- `Failed/invalid_all_walls.cub` - マップが全て壁（移動可能スペースがない）
- `Failed/invalid_no_walls.cub` - 壁が1つもない（全て0とスペース）

**優先度**: 中 - ゲームロジックの妥当性確認

---

## 11. 行の長さのバリエーション (Line Length Variations)

### 11.1 不揃いな行長
**目的**: マップの各行の長さが異なる場合の処理を確認

**提案するテストケース**:
- `Success/valid_uneven_line_lengths.cub` - 各行の長さが異なる有効なマップ
- `Success/valid_short_first_line.cub` - 最初の行が短いマップ
- `Success/valid_short_last_line.cub` - 最後の行が短いマップ

**優先度**: 高 - マップパース処理の堅牢性

---

## 12. 設定の順序と重複の組み合わせ (Config Order and Duplication)

### 12.1 複雑な設定パターン
**目的**: 設定要素の順序と重複の様々な組み合わせを確認

**提案するテストケース**:
- `Failed/invalid_duplicate_NO.cub` - NO要素が2回（特定要素の重複）
- `Failed/invalid_duplicate_F.cub` - F要素が2回
- `Failed/invalid_duplicate_C.cub` - C要素が2回
- `Failed/invalid_all_duplicated.cub` - 全ての設定要素が重複

**優先度**: 中 - エラー検出の正確性

---

## 実装の優先順位まとめ

### 優先度：高
1. **RGB値の境界値テスト** - 必須機能の検証
2. **マップ形状の複雑なケース** - コア機能の正確性
3. **行の長さのバリエーション** - パース処理の堅牢性

### 優先度：中
4. **マップサイズのエッジケース**
5. **空白文字とフォーマット**
6. **テクスチャパスのエッジケース**
7. **設定値の形式**
8. **特殊な壁の配置**
9. **設定の順序と重複の組み合わせ**

### 優先度：低
10. **大文字小文字の扱い** - 仕様明確な場合のみ
11. **ファイル形式とエンコーディング** - プラットフォーム依存
12. **コメント機能** - 仕様次第
13. **パフォーマンステスト** - 基本機能実装後

---

## 推奨実装計画

### フェーズ1: 必須テストケース（優先度：高）
- RGB境界値テスト（6ケース）
- 複雑なマップ形状（5ケース）
- 行長バリエーション（3ケース）
- **小計: 14ケース**

### フェーズ2: 重要なエッジケース（優先度：中）
- マップサイズ（5ケース）
- 空白文字処理（5ケース）
- テクスチャパス（5ケース）
- 設定値形式（3ケース）
- 壁配置（4ケース）
- 設定重複（4ケース）
- **小計: 26ケース**

### フェーズ3: 追加の堅牢性テスト（優先度：低）
- 大文字小文字（2ケース）
- ファイル形式（4ケース）
- コメント（2ケース）
- パフォーマンス（4ケース）
- **小計: 12ケース**

### 総追加予定
**合計: 52ケースの追加を提案**

現在110ケース → 実装後162ケース

---

## 注意事項

1. **仕様との整合性**: これらのテストケースは、プロジェクトの仕様書（cub3D subject）に基づいて実装してください。
2. **優先順位**: まずは優先度が高いものから実装し、基本機能が安定してから低優先度のケースに取り組むことを推奨します。
3. **重複確認**: 既存のテストケースと重複していないか、実装前に必ず確認してください。
4. **段階的な実装**: 一度に全てを実装する必要はなく、パーサーの実装進捗に合わせて段階的に追加することを推奨します。

---

## 参考資料

- 現在のテストケース詳細: `docs/development/parser-test-cases.md`
- テスト実行方法: `tests/README.md`
- テストスクリプト: `tests/run_parser_tests.sh`
