# Parser Test Cases / パーサーテストケース

このドキュメントでは、`.cub`ファイルのパーサーをテストするために使用するテストケースについて説明します。

## 成功ケース (Success Cases)

### 1. 基本的な有効なマップ
**path:** `assets/maps/Success/valid_basic.cub`  
**detail:** 最も基本的な有効なマップ。すべての必須設定要素（NO, SO, WE, EA, F, C）が含まれ、プレイヤーが1人、壁で囲まれた有効なマップレイアウト。成功ケース。

### 2. 複雑なレイアウトの有効なマップ
**path:** `assets/maps/Success/valid_complex.cub`  
**detail:** より複雑な形状のマップレイアウト。空白スペースを含み、不規則な形状でも壁で適切に閉じられている。成功ケース。

#### 2-1. 複雑なマップ - ジグザグパターン
**path:** `assets/maps/Success/valid_complex/zigzag_horizontal.cub`  
**detail:** 水平方向にジグザグな通路を持つ複雑なマップ。成功ケース。

**path:** `assets/maps/Success/valid_complex/zigzag_vertical.cub`  
**detail:** 垂直方向にジグザグな通路を持つ複雑なマップ。成功ケース。

#### 2-2. 複雑なマップ - とげとげな外壁パターン
**path:** `assets/maps/Success/valid_complex/spiky_edges_1.cub`  
**detail:** 外側の壁が不規則でとげとげした形状のマップ。成功ケース。

**path:** `assets/maps/Success/valid_complex/spiky_edges_2.cub`  
**detail:** 外側の壁が段々になっているとげとげした形状のマップ。成功ケース。

### 3. 最小限の有効なマップ
**path:** `assets/maps/Success/valid_minimal.cub`  
**detail:** 最小限のサイズで有効なマップ（3x3）。必須要素のみを含む。成功ケース。

### 4. すべての方向を含むマップ
**path:** `assets/maps/Success/valid_player_south.cub`  
**detail:** プレイヤーが南向き（S）のマップ。成功ケース。

**path:** `assets/maps/Success/valid_player_east.cub`  
**detail:** プレイヤーが東向き（E）のマップ。成功ケース。

**path:** `assets/maps/Success/valid_player_west.cub`  
**detail:** プレイヤーが西向き（W）のマップ。成功ケース。

**注記:** プレイヤーが北向き（N）のマップは、`valid_random_order/order_01_NO_SO_WE_EA_F_C.cub`が同じ内容のため、重複削除されました。

### 5. 設定要素の順序が異なるマップ
**path:** `assets/maps/Success/valid_random_order/`  
**detail:** 設定要素（NO, SO, WE, EA, F, C）の順序が様々に異なる24パターンのマップファイル。どの順序でも有効であることを確認。成功ケース。order_01ファイルは北向きプレイヤーのケースも兼ねています。

### 6. 空行を含む有効なマップ
**path:** `assets/maps/Success/valid_with_empty_lines.cub`  
**detail:** 設定セクションとマップセクションの間に複数の空行がある。成功ケース。

### 7. 大きなマップ（1024文字以上）
**path:** `assets/maps/Success/valid_bigmap/large_open_space.cub`  
**detail:** 大きなオープンスペースを持つマップ（1024文字以上）。成功ケース。

**path:** `assets/maps/Success/valid_bigmap/maze_pattern.cub`  
**detail:** 迷路のようなパターンを持つ大きなマップ（1024文字以上）。成功ケース。

**path:** `assets/maps/Success/valid_bigmap/spiral_pattern.cub`  
**detail:** スパイラル（渦巻き）パターンを持つ大きなマップ（1024文字以上）。成功ケース。

## 失敗ケース (Failed Cases)

### 1. プレイヤーが複数いる
**path:** `assets/maps/Failed/invalid_multiple_players/`  
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
**path:** `assets/maps/Failed/invalid_no_player.cub`  
**detail:** マップ内にプレイヤー（N, S, E, W）が1つも存在しない。失敗ケース。

### 3. マップが壁で囲まれていない
**path:** `assets/maps/Failed/invalid_not_closed.cub`  
**detail:** マップの境界が壁（1）で完全に囲まれていない。失敗ケース。

### 4. 無効な文字を含む
**path:** `assets/maps/Failed/invalid_characters.cub`  
**detail:** マップセクションに有効でない文字（0, 1, N, S, E, W, スペース以外）が含まれる。失敗ケース。

### 5. 設定が不完全
**path:** `assets/maps/Failed/invalid_incomplete_config.cub`  
**detail:** 必須の設定要素（NO, SO, WE, EA, F, C）のいずれかが欠けている。失敗ケース。

### 6. 重複する設定
**path:** `assets/maps/Failed/invalid_duplicate_config.cub`  
**detail:** 同じ設定要素（例：NOが2回）が重複して定義されている。失敗ケース。

### 7. 無効なRGB値
**path:** `assets/maps/Failed/invalid_rgb_values.cub`  
**detail:** Floor（F）またはCeiling（C）のRGB値が範囲外（0-255以外）または不正な形式。失敗ケース。

### 8. 空のマップ
**path:** `assets/maps/Failed/invalid_empty_map.cub`  
**detail:** 設定セクションのみがあり、マップセクションが存在しない。失敗ケース。

### 9. テクスチャパスが存在しない
**path:** `assets/maps/Failed/invalid_missing_texture.cub`  
**detail:** 設定で指定されたテクスチャファイルのパスが存在しない。失敗ケース。

### 10. マップの途中に空行
**path:** `assets/maps/Failed/invalid_map_with_empty_line.cub`  
**detail:** マップセクション内に空行が含まれている。失敗ケース。

### 11. 無効なRGBフォーマット
**path:** `assets/maps/Failed/invalid_rgb_format/`  
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

### 成功ケース (Success Cases)
- 基本マップ: 1ファイル
- 複雑なマップ: 5ファイル（オリジナル1 + ジグザグ2 + とげとげ2）
- 最小マップ: 1ファイル
- プレイヤー方向: 3ファイル（S, E, W）※Nはランダム順序のorder_01と同一のため削除
- ランダム順序: 25ファイル（オリジナル1 + 新規24、order_01は北向きプレイヤーケースを兼ねる）
- 空行含む: 1ファイル
- 大きなマップ: 3ファイル（>1024文字）
- 既存マップ（good/から移動）: 17ファイル（cheese_maze, creepy, dungeon等）
- **合計: 56ファイル**

### 失敗ケース (Failed Cases)
- 複数プレイヤー: 11ファイル（全組み合わせ）※親ファイルは削除（N_S.cubと同一）
- プレイヤーなし: 1ファイル
- 未閉鎖マップ: 1ファイル
- 無効文字: 1ファイル
- 不完全設定: 1ファイル
- 重複設定: 1ファイル
- RGB範囲外: 1ファイル
- 空マップ: 1ファイル
- 存在しないテクスチャ: 1ファイル
- マップ内空行: 1ファイル
- RGBフォーマット不正: 6ファイル※親ファイルは削除（floor_space_separated.cubと同一）
- 既存マップ（bad/から移動）: 28ファイル
- **合計: 54ファイル**

### 総計
**全テストケース: 110ファイル**

### 重複削除の詳細
整理の際に以下の重複ファイルを削除しました：
1. `valid_player_north.cub` - `valid_random_order/order_01_NO_SO_WE_EA_F_C.cub`と同一
2. `invalid_multiple_players.cub` - `invalid_multiple_players/N_S.cub`と同一
3. `invalid_rgb_format.cub` - `invalid_rgb_format/floor_space_separated.cub`と同一

### ディレクトリ構造
```
assets/maps/
├── Success/          # 有効なマップ（56ファイル）
│   ├── valid_bigmap/
│   ├── valid_complex/
│   └── valid_random_order/
└── Failed/           # 無効なマップ（54ファイル）
    ├── invalid_multiple_players/
    └── invalid_rgb_format/
```

## 注意事項

- パーサーはまだ実装中のため、これらのテストケースは将来の実装のための準備です。
- テストケースは実装の進捗に応じて追加・修正される可能性があります。
- 各テストケースは明確な目的を持ち、特定の検証ポイントをテストします。
- ディレクトリ構造は `Success/` と `Failed/` の2つに統一され、関連するテストケースをサブディレクトリでグループ化しています。
- 旧来の `good/`, `bad/`, `success/`, `failed/`, `test/` ディレクトリは統合・削除されました。
