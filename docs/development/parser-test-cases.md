# Parser Test Cases / パーサーテストケース

このドキュメントでは、`.cub`ファイルのパーサーをテストするために使用するテストケースについて説明します。

## 成功ケース (Success Cases)

### 1. 基本的な有効なマップ
**path:** `assets/maps/success/valid_basic.cub`  
**detail:** 最も基本的な有効なマップ。すべての必須設定要素（NO, SO, WE, EA, F, C）が含まれ、プレイヤーが1人、壁で囲まれた有効なマップレイアウト。成功ケース。

### 2. 複雑なレイアウトの有効なマップ
**path:** `assets/maps/success/valid_complex.cub`  
**detail:** より複雑な形状のマップレイアウト。空白スペースを含み、不規則な形状でも壁で適切に閉じられている。成功ケース。

#### 2-1. 複雑なマップ - ジグザグパターン
**path:** `assets/maps/success/valid_complex/zigzag_horizontal.cub`  
**detail:** 水平方向にジグザグな通路を持つ複雑なマップ。成功ケース。

**path:** `assets/maps/success/valid_complex/zigzag_vertical.cub`  
**detail:** 垂直方向にジグザグな通路を持つ複雑なマップ。成功ケース。

#### 2-2. 複雑なマップ - とげとげな外壁パターン
**path:** `assets/maps/success/valid_complex/spiky_edges_1.cub`  
**detail:** 外側の壁が不規則でとげとげした形状のマップ。成功ケース。

**path:** `assets/maps/success/valid_complex/spiky_edges_2.cub`  
**detail:** 外側の壁が段々になっているとげとげした形状のマップ。成功ケース。

### 3. 最小限の有効なマップ
**path:** `assets/maps/success/valid_minimal.cub`  
**detail:** 最小限のサイズで有効なマップ（3x3）。必須要素のみを含む。成功ケース。

### 4. すべての方向を含むマップ
**path:** `assets/maps/success/valid_player_north.cub`  
**detail:** プレイヤーが北向き（N）のマップ。成功ケース。

**path:** `assets/maps/success/valid_player_south.cub`  
**detail:** プレイヤーが南向き（S）のマップ。成功ケース。

**path:** `assets/maps/success/valid_player_east.cub`  
**detail:** プレイヤーが東向き（E）のマップ。成功ケース。

**path:** `assets/maps/success/valid_player_west.cub`  
**detail:** プレイヤーが西向き（W）のマップ。成功ケース。

### 5. 設定要素の順序が異なるマップ
**path:** `assets/maps/success/valid_random_order/`  
**detail:** 設定要素（NO, SO, WE, EA, F, C）の順序が様々に異なる24パターンのマップファイル。どの順序でも有効であることを確認。成功ケース。

### 6. 空行を含む有効なマップ
**path:** `assets/maps/success/valid_with_empty_lines.cub`  
**detail:** 設定セクションとマップセクションの間に複数の空行がある。成功ケース。

### 7. 大きなマップ（1024文字以上）
**path:** `assets/maps/success/valid_bigmap/large_open_space.cub`  
**detail:** 大きなオープンスペースを持つマップ（1024文字以上）。成功ケース。

**path:** `assets/maps/success/valid_bigmap/maze_pattern.cub`  
**detail:** 迷路のようなパターンを持つ大きなマップ（1024文字以上）。成功ケース。

**path:** `assets/maps/success/valid_bigmap/spiral_pattern.cub`  
**detail:** スパイラル（渦巻き）パターンを持つ大きなマップ（1024文字以上）。成功ケース。

## 失敗ケース (Failed Cases)

### 1. プレイヤーが複数いる
**path:** `assets/maps/failed/invalid_multiple_players/`  
**detail:** マップ内に複数のプレイヤー（N, S, E, Wの組み合わせ）が存在する全11パターン。失敗ケース。
- N_S.cub - 北と南向きプレイヤー
- N_E.cub - 北と東向きプレイヤー
- N_W.cub - 北と西向きプレイヤー
- S_E.cub - 南と東向きプレイヤー
- S_W.cub - 南と西向きプレイヤー
- E_W.cub - 東と西向きプレイヤー
- N_S_E.cub - 3人のプレイヤー（北、南、東）
- N_S_W.cub - 3人のプレイヤー（北、南、西）
- N_E_W.cub - 3人のプレイヤー（北、東、西）
- S_E_W.cub - 3人のプレイヤー（南、東、西）
- N_S_E_W.cub - 4人のプレイヤー（全方向）

### 2. プレイヤーがいない
**path:** `assets/maps/failed/invalid_no_player.cub`  
**detail:** マップ内にプレイヤー（N, S, E, W）が1つも存在しない。失敗ケース。

### 3. マップが壁で囲まれていない
**path:** `assets/maps/failed/invalid_not_closed.cub`  
**detail:** マップの境界が壁（1）で完全に囲まれていない。失敗ケース。

### 4. 無効な文字を含む
**path:** `assets/maps/failed/invalid_characters.cub`  
**detail:** マップセクションに有効でない文字（0, 1, N, S, E, W, スペース以外）が含まれる。失敗ケース。

### 5. 設定が不完全
**path:** `assets/maps/failed/invalid_incomplete_config.cub`  
**detail:** 必須の設定要素（NO, SO, WE, EA, F, C）のいずれかが欠けている。失敗ケース。

### 6. 重複する設定
**path:** `assets/maps/failed/invalid_duplicate_config.cub`  
**detail:** 同じ設定要素（例：NOが2回）が重複して定義されている。失敗ケース。

### 7. 無効なRGB値
**path:** `assets/maps/failed/invalid_rgb_values.cub`  
**detail:** Floor（F）またはCeiling（C）のRGB値が範囲外（0-255以外）または不正な形式。失敗ケース。

### 8. 空のマップ
**path:** `assets/maps/failed/invalid_empty_map.cub`  
**detail:** 設定セクションのみがあり、マップセクションが存在しない。失敗ケース。

### 9. テクスチャパスが存在しない
**path:** `assets/maps/failed/invalid_missing_texture.cub`  
**detail:** 設定で指定されたテクスチャファイルのパスが存在しない。失敗ケース。

### 10. マップの途中に空行
**path:** `assets/maps/failed/invalid_map_with_empty_line.cub`  
**detail:** マップセクション内に空行が含まれている。失敗ケース。

### 11. 無効なRGBフォーマット
**path:** `assets/maps/failed/invalid_rgb_format/`  
**detail:** RGB値のフォーマットが不正（カンマ区切りでない、数値でないなど）な6パターン。失敗ケース。
- floor_space_separated.cub - フロアのRGB値がスペース区切り
- ceiling_space_separated.cub - 天井のRGB値がスペース区切り
- floor_missing_value.cub - フロアのRGB値が不足（2つだけ）
- ceiling_missing_value.cub - 天井のRGB値が不足（2つだけ）
- floor_non_numeric.cub - フロアのRGB値が数値でない
- ceiling_non_numeric.cub - 天井のRGB値が数値でない

## テスト実行方法

### シェルスクリプトでの実行
```bash
bash ./test/run_parser_tests.sh
```

### GitHub Actionsでの実行
手動トリガーで実行可能：
1. GitHubリポジトリの "Actions" タブに移動
2. "Parser Test" ワークフローを選択
3. "Run workflow" ボタンをクリック

## テストケースの統計

### 成功ケース
- 基本マップ: 1ファイル
- 複雑なマップ: 5ファイル（オリジナル1 + ジグザグ2 + とげとげ2）
- 最小マップ: 1ファイル
- プレイヤー方向: 4ファイル（N, S, E, W）
- ランダム順序: 25ファイル（オリジナル1 + 新規24）
- 空行含む: 1ファイル
- 大きなマップ: 3ファイル（>1024文字）
- **合計: 40ファイル**

### 失敗ケース
- 複数プレイヤー: 12ファイル（オリジナル1 + 全組み合わせ11）
- プレイヤーなし: 1ファイル
- 未閉鎖マップ: 1ファイル
- 無効文字: 1ファイル
- 不完全設定: 1ファイル
- 重複設定: 1ファイル
- RGB範囲外: 1ファイル
- 空マップ: 1ファイル
- 存在しないテクスチャ: 1ファイル
- マップ内空行: 1ファイル
- RGBフォーマット不正: 7ファイル（オリジナル1 + 新規6）
- **合計: 28ファイル**

### 総計
**全テストケース: 68ファイル**

## 注意事項

- パーサーはまだ実装中のため、これらのテストケースは将来の実装のための準備です。
- テストケースは実装の進捗に応じて追加・修正される可能性があります。
- 各テストケースは明確な目的を持ち、特定の検証ポイントをテストします。
- ディレクトリ構造を使って、関連するテストケースをグループ化しています。
