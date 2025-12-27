# Parser Test Suite / パーサーテストスイート

このディレクトリにはcub3Dプロジェクトのパーサーをテストするためのスクリプトとツールが含まれています。

## ファイル構成

- `Makefile` - ユニットテスト、パーサーテスト、リークチェックをまとめて実行
- `run_parser_tests.sh` - 成功/失敗マップを使ったパーサーテスト一式
- `run_leak_check.sh` - Valgrind を使ったリークチェック
- `test_data/` - ユニットテスト用のミニマルな .cub サンプル

## 使い方

### ローカルでまとめて実行

```bash
# プロジェクトルートから
make test
```

もしくは個別に実行:
```bash
cd tests
make unit          # C++ユニットテスト（設定・マップ）
make parser-tests  # assets/maps を使った総合パーサーテスト
make leak-check    # Valgrindリークチェック
```

## テストの内容

`make test` は以下を順に実行します：

1. **ユニットテスト** (`tests/test_data/`を使用)
   - 設定パース: 重複・RGBフォーマット・境界値(0/255)など
   - マップパース: 最小サイズ、壁囲み、スペース、プレイヤー数など

2. **パーサーテスト** (`assets/maps/` を対象)
   - 成功ケースは終了コード0、失敗ケースは非0を期待

3. **リークチェック** (`tests/run_leak_check.sh`)
   - Valgrind による良いマップ群のリーク確認

## 出力

各ステージで以下を表示します：

- 各テストケースの結果（PASSED/FAILED/SKIPPED）
- テスト結果のサマリー（合計、成功、失敗の数）
- カラーコード付きの見やすい出力

## GitHub Actions

`make test` が CI のワークフロー（parser-test / memory-leak-check）でも実行されます。手動実行時も同じコマンドを使えば再現できます。

## テストケースの詳細

各テストケースの詳細については、`docs/development/parser-test-cases.md`を参照してください。

## 注意事項

- パーサーがまだ実装されていない場合、すべてのテストはSKIPPEDと表示されます
- これは正常な動作であり、パーサーの実装後に実際のテストが開始されます
