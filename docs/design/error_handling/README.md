# エラーハンドリング / Error Handling

## 概要 / Overview

このディレクトリには cub3D プロジェクトのエラー処理に関する設計ドキュメントが格納されています。

This directory contains design documents for error handling in the cub3D project.

---

## ファイル構成 / File Structure

```
docs/design/error_handling/
├── README.md           # このファイル / This file
├── error_list.md       # エラー要件一覧 / Error requirements list
└── design.md           # エラーハンドリング詳細設計 / Error handling detailed design
```

---

## ドキュメントの使い分け / Document Usage

### `error_list.md` - エラー要件一覧

**対象読者 / Target Audience**: 
- 全ての開発者 / All developers
- テスターやレビュアー / Testers and reviewers

**記載内容 / Contents**:
- `docs/design` 内の全設計ドキュメントから抽出したエラー要件
- Error requirements extracted from all design documents in `docs/design`
- モジュール別に分類されたエラーカタログ
- Error catalog organized by module
- エラーの発生条件と対応方針
- Error trigger conditions and handling policies
- 統計情報とサマリ
- Statistics and summary

**用途 / Use Cases**:
- エラー処理の全体像を把握する
- Understand overall error handling
- 特定のエラーを素早く検索する
- Quickly search for specific errors
- エラーハンドリングのテストケース作成
- Create test cases for error handling

---

### `design.md` - エラーハンドリング詳細設計

**対象読者 / Target Audience**:
- エラーハンドリング実装者 / Error handling implementers
- コードレビュアー / Code reviewers

**記載内容 / Contents**:
- 統一エラーハンドラの設計
- Unified error handler design
- エラーコード列挙型の定義
- Error code enumeration definition
- クリーンアップ処理の実装方針
- Cleanup process implementation strategy
- 使用例とコードサンプル
- Usage examples and code samples
- テスト戦略
- Testing strategy

**用途 / Use Cases**:
- エラーハンドリング機能を実装する
- Implement error handling functionality
- エラー処理のコードレビューを行う
- Conduct error handling code review
- 新しいエラー種別を追加する
- Add new error types

---

## 設計方針 / Design Policy

### 1. 単一責任の原則 / Single Responsibility Principle

全てのエラーは最終的に `error_exit()` 関数に集約されます。

All errors ultimately converge to the `error_exit()` function.

```
各モジュール → error_exit() → クリーンアップ → 終了
Each module  → error_exit() → Cleanup      → Exit
```

### 2. 一貫性 / Consistency

エラー出力形式は Subject 要件に準拠：

Error output format complies with subject requirements:

```
Error
<specific error message>
```

### 3. 拡張性 / Extensibility

新しいエラー種別は列挙型に追加するだけで対応可能。

New error types can be added simply by extending the enumeration.

### 4. 保守性 / Maintainability

エラーメッセージは一箇所で管理され、変更が容易。

Error messages are managed in one place, easy to modify.

---

## 実装の進め方 / Implementation Approach

### フェーズ 1: 基盤構築 / Phase 1: Foundation

1. `includes/error.h` の作成
   - Create `includes/error.h`
   - エラーコード列挙型の定義
   - Define error code enumeration
   - クリーンアップデータ構造の定義
   - Define cleanup data structure

2. `srcs/error/` ディレクトリの作成
   - Create `srcs/error/` directory
   - 基本的なエラーハンドラの実装
   - Implement basic error handler

3. ユニットテストの作成
   - Create unit tests
   - 各エラーコードの動作確認
   - Verify behavior of each error code

### フェーズ 2: 統合 / Phase 2: Integration

1. Parse モジュールとの統合
   - Integration with Parse module
   - Config/Map エラーの実装
   - Implement Config/Map errors

2. Engine モジュールとの統合
   - Integration with Engine module
   - MLX/Runtime エラーの実装
   - Implement MLX/Runtime errors

3. 統合テストの実施
   - Conduct integration tests
   - エンドツーエンドのエラーフロー確認
   - Verify end-to-end error flow

### フェーズ 3: 最適化 / Phase 3: Optimization

1. メモリリークの確認と修正
   - Check and fix memory leaks
   - Valgrind でのテスト
   - Test with Valgrind

2. エラーメッセージの改善
   - Improve error messages
   - より具体的で分かりやすい表現に
   - Make more specific and understandable

3. パフォーマンステスト
   - Performance testing
   - エラー処理のオーバーヘッド確認
   - Verify error handling overhead

---

## クイックリファレンス / Quick Reference

### よくあるエラー / Common Errors

| エラー<br>Error | コード<br>Code | 対処法<br>Solution |
|---------|------|--------|
| 重複する識別子<br>Duplicate identifier | `ERR_DUPLICATE_IDENTIFIER` | 設定ファイルで同じ識別子が複数回出現していないか確認<br>Check if same identifier appears multiple times in config |
| マップが小さすぎる<br>Map too small | `ERR_MINIMUM_MAP_SIZE` | マップを 3×3 以上にする<br>Make map at least 3×3 |
| プレイヤー不在<br>No player | `ERR_PLAYER_COUNT_ZERO` | N/S/E/W のいずれかを1つ配置<br>Place one of N/S/E/W |
| 壁で囲まれていない<br>Not enclosed | `ERR_WALL_ENCLOSURE` | マップの外周を全て `1` にする<br>Make all outer edges `1` |
| MLX 初期化失敗<br>MLX init failure | `ERR_MLX_INIT_FAILURE` | システム環境を確認（X11など）<br>Check system environment (X11, etc.) |

### 警告 / Warnings

| 警告<br>Warning | コード<br>Code | 意味<br>Meaning |
|---------|------|--------|
| 到達不可能な領域<br>Unreachable area | `WARN_UNREACHABLE_AREA` | プレイヤーから到達できない空き領域が存在<br>Empty areas exist that player cannot reach |

---

## 関連ドキュメント / Related Documents

### 設計ドキュメント / Design Documents

- [Parse モジュール設計](../modules/parse/design.md)
- [Parse/Config 設計](../modules/parse/config/design.md)
- [Parse/Map 設計](../modules/parse/map/design.md)
- [Engine モジュール設計](../modules/engine/design.md)

### データ構造 / Data Structures

- [データ構造設計](../data/structure.md)

### アーキテクチャ / Architecture

- [アーキテクチャ設計](../architecture.md)
- [プロジェクト概要](../overview.md)

---

## 貢献ガイドライン / Contribution Guidelines

### 新しいエラーを追加する場合 / Adding New Errors

1. **エラーコードを定義**
   - `includes/error.h` の `t_error_code` に追加
   - Add to `t_error_code` in `includes/error.h`

2. **エラーメッセージを追加**
   - `srcs/error/error_messages.c` のテーブルに追加
   - Add to table in `srcs/error/error_messages.c`

3. **ドキュメントを更新**
   - `error_list.md` に追加
   - Add to `error_list.md`
   - 該当モジュールの設計書にも記載
   - Also document in relevant module design

4. **テストを追加**
   - 新しいエラーのテストケースを追加
   - Add test case for new error

### コーディング規約 / Coding Conventions

- 42 Norminette に準拠
- Follow 42 Norminette
- エラーメッセージは英語で記述
- Write error messages in English
- エラーコードは意味のある名前を使用
- Use meaningful names for error codes
- 関数は単一責任の原則に従う
- Functions follow single responsibility principle

---

## FAQ

### Q1: エラーハンドラを呼ぶタイミングは？

A: エラーが検出された時点で即座に `error_exit()` を呼び出してください。リカバリ処理は現在サポートしていません。

When to call error handler?

A: Call `error_exit()` immediately when error is detected. Recovery processing is not currently supported.

---

### Q2: 警告とエラーの違いは？

A: エラーはプログラムを終了させますが、警告は継続します。例：到達不可能な領域は警告として報告されますが、プログラムは実行されます。

What's the difference between warnings and errors?

A: Errors terminate the program, warnings continue. Example: Unreachable areas are reported as warnings but program continues.

---

### Q3: クリーンアップデータは必須？

A: 初期段階（MLX初期化前など）では NULL を渡しても構いません。リソースが確保されている場合は必ず渡してください。

Is cleanup data mandatory?

A: In early stages (before MLX init, etc.) you can pass NULL. If resources are allocated, always pass cleanup data.

---

## ライセンス / License

このドキュメントは cub3D プロジェクトの一部です。

This document is part of the cub3D project.
