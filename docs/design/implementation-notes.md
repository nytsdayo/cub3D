# 実装時の注意事項 / Implementation Notes

## 概要 / Overview

このドキュメントは cub3D プロジェクト全体の実装において注意すべき事項をまとめたものです。

This document summarizes important considerations for implementing the cub3D project.

---

## 1. スレッドセーフティ / Thread Safety

- 現在の cub3D はシングルスレッドで動作するため、スレッドセーフティは考慮不要
- Currently single-threaded, thread safety not required

---

## 2. メモリリーク防止 / Memory Leak Prevention

- Valgrind でのメモリリークチェック必須
- Valgrind memory leak check required
- エラー処理パスでもリークが無いことを確認
- Verify no leaks in error handling paths

### 推奨チェックコマンド / Recommended Check Commands

```bash
valgrind --leak-check=full --show-leak-kinds=all ./cub3D map.cub
```

---

## 3. 42 Norminette 準拠 / 42 Norminette Compliance

### 関数の制約 / Function Constraints

- 関数は25行以内
- Functions must be within 25 lines
- 行は80文字以内
- Lines must be within 80 characters
- 関数は5個以内のパラメータ
- Functions must have at most 5 parameters

### チェック方法 / How to Check

```bash
norminette srcs/ includes/
```

---

## 4. エラーメッセージの言語 / Error Message Language

- 英語でメッセージを記述（国際的な標準）
- Error messages in English (international standard)
- 明確で簡潔な表現を心がける
- Keep messages clear and concise

### 例 / Examples

✅ Good:
```
Error
Invalid map: not enclosed by walls
```

❌ Bad:
```
エラー：マップが壁で囲まれていません
```

---

## 5. デバッグモード / Debug Mode

将来的に実装を検討：
Consider implementing in the future:

```c
#ifdef DEBUG
    fprintf(stderr, "Debug: Error occurred at %s:%d\n", __FILE__, __LINE__);
#endif
```

### ビルド方法 / Build Instructions

```bash
# デバッグモードでビルド / Build with debug mode
make DEBUG=1

# リリースモード / Release mode
make
```

---

## 6. コード品質 / Code Quality

### 静的解析 / Static Analysis

プロジェクトの品質を保つため、以下のツールの使用を推奨：
Recommended tools to maintain project quality:

- **norminette**: 42スクール規約チェック / 42 school coding standard
- **valgrind**: メモリリーク検出 / Memory leak detection
- **gcc -Wall -Wextra -Werror**: コンパイル時警告 / Compile-time warnings

### コードレビュー / Code Review

- プルリクエストは必ずレビューを受ける
- Pull requests must be reviewed
- 単一責任の原則を守る
- Follow single responsibility principle
- 適切なコメントを残す（特に複雑なロジック）
- Add appropriate comments (especially for complex logic)

---

## 7. テスト / Testing

### 必須テスト / Required Tests

各実装後に以下を確認：
Verify the following after each implementation:

1. **正常系テスト / Normal Case Tests**
   - 期待通りの動作をするか
   - Does it work as expected?

2. **異常系テスト / Error Case Tests**
   - エラーハンドリングが適切か
   - Is error handling appropriate?
   - メモリリークは無いか
   - Are there any memory leaks?

3. **境界値テスト / Boundary Tests**
   - エッジケースでクラッシュしないか
   - Does it handle edge cases without crashing?

---

## 8. ドキュメント / Documentation

### 更新が必要な場合 / When to Update

- 新しいモジュールを追加した時
- When adding a new module
- APIや関数シグネチャを変更した時
- When changing APIs or function signatures
- 重要な設計判断を行った時
- When making important design decisions

### ドキュメントの場所 / Document Locations

- `docs/design/`: 設計ドキュメント / Design documents
- `docs/development/`: 開発ガイド / Development guides
- `docs/decisions/`: 設計判断記録 (ADR) / Architectural Decision Records

---

## 参照 / References

- [プロジェクト概要](./overview.md)
- [アーキテクチャ](./architecture.md)
- [エラーハンドリング設計](./error_handling/design.md)
- [コーディング規約](../development/coding-standards.md)
