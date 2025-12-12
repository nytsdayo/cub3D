# Parser Test Cases / パーサーテストケース

このドキュメントでは、`.cub`ファイルのパーサーをテストするために使用するテストケースについて説明します。

## 成功ケース (Success Cases)

### 1. 基本的な有効なマップ
**path:** `assets/maps/success/valid_basic.cub`  
**detail:** 最も基本的な有効なマップ。すべての必須設定要素（NO, SO, WE, EA, F, C）が含まれ、プレイヤーが1人、壁で囲まれた有効なマップレイアウト。成功ケース。

### 2. 複雑なレイアウトの有効なマップ
**path:** `assets/maps/success/valid_complex.cub`  
**detail:** より複雑な形状のマップレイアウト。空白スペースを含み、不規則な形状でも壁で適切に閉じられている。成功ケース。

### 3. 最小限の有効なマップ
**path:** `assets/maps/success/valid_minimal.cub`  
**detail:** 最小限のサイズで有効なマップ（3x3）。必須要素のみを含む。成功ケース。

### 4. すべての方向を含むマップ
**path:** `assets/maps/success/valid_all_directions.cub`  
**detail:** 各プレイヤー方向（N, S, E, W）のテスト用に、それぞれ個別のマップファイルを用意。成功ケース。

### 5. 設定要素の順序が異なるマップ
**path:** `assets/maps/success/valid_random_order.cub`  
**detail:** 設定要素（NO, SO, WE, EA, F, C）の順序が仕様に定められた順序と異なるが有効。成功ケース。

### 6. 空行を含む有効なマップ
**path:** `assets/maps/success/valid_with_empty_lines.cub`  
**detail:** 設定セクションとマップセクションの間に複数の空行がある。成功ケース。

## 失敗ケース (Failed Cases)

### 1. プレイヤーが複数いる
**path:** `assets/maps/failed/invalid_multiple_players.cub`  
**detail:** マップ内に複数のプレイヤー（N, S, E, Wの組み合わせ）が存在する。失敗ケース。

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
**path:** `assets/maps/failed/invalid_rgb_format.cub`  
**detail:** RGB値のフォーマットが不正（カンマ区切りでない、数値でないなど）。失敗ケース。

## テスト実行方法

### シェルスクリプトでの実行
```bash
./test/run_parser_tests.sh
```

### GitHub Actionsでの実行
手動トリガーで実行可能：
1. GitHubリポジトリの "Actions" タブに移動
2. "Parser Test" ワークフローを選択
3. "Run workflow" ボタンをクリック

## 注意事項

- パーサーはまだ実装中のため、これらのテストケースは将来の実装のための準備です。
- テストケースは実装の進捗に応じて追加・修正される可能性があります。
- 各テストケースは明確な目的を持ち、特定の検証ポイントをテストします。
