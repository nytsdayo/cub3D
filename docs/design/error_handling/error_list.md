# エラー一覧 / Error List

## 概要 / Overview

- `docs/design` 配下の設計ドキュメントから抽出したエラー要件のまとめ
- Implementation へ渡すためのカタログ（エラー名・条件・方針を即参照できる形）
- 各テーブルの行番号は参照元設計の目安位置

---

## 1. Parse モジュール / Parse Module

### 1.0 Parse 共通入口エラー / Parse Entry Errors

| エラーID<br>Error ID | 発生条件<br>Trigger Condition | 対応<br>Action | 行番号<br>Line Ref |
|----------|----------|------|--------|
| `INVALID_EXTENSION` | 入力ファイル拡張子が `.cub` 以外<br>Input file extension is not `.cub` | 即時エラー返却、以降の処理を行わない<br>Return error immediately, skip further processing | design.md:?? |
| `FILE_NOT_FOUND` | 指定した `.cub` ファイルが存在しない<br>Specified `.cub` file does not exist | エラーメッセージを出力し終了<br>Print error and exit | design.md:?? |
| `FILE_PERMISSION_DENIED` | 読み込み権限が無い<br>No read permission for `.cub` file | エラーメッセージを出力し終了<br>Print error and exit | design.md:?? |

### 1.1 Config サブモジュール / Config Submodule

**参照元 / Reference**: `docs/design/modules/parse/config/design.md`

| エラーID<br>Error ID | 発生条件<br>Trigger Condition | 対応<br>Action | 行番号<br>Line Ref |
|----------|----------|------|--------|
| `UNKNOWN_IDENTIFIER` | `NO`, `SO`, `WE`, `EA`, `F`, `C` 以外の識別子が行に出現<br>Identifier other than `NO`, `SO`, `WE`, `EA`, `F`, `C` appears | 行番号つきで報告し config 処理を即終了<br>Report with line number and immediately terminate config processing | design.md:160 |
| `DUPLICATE_IDENTIFIER` | `seen_flags[idx]` が 1 の識別子が再出現<br>Identifier with `seen_flags[idx]` = 1 appears again | 既存値を保持し、新しい値は破棄してエラー返却<br>Keep existing value, discard new value, return error | design.md:161 |
| `SYNTAX_TEXTURE` | 識別子後に1つ以上の空白が無い / パスが無い / `.xpm` 以外の拡張子 / パスに空白や許可外文字を含む<br>No space after identifier / no path / extension other than `.xpm` / path contains spaces or invalid chars | 問題行を指摘<br>Point out problematic line | design.md:162 |
| `SYNTAX_RGB` | 識別子後に1つ以上の空白が無い / RGB が3要素でない / 非整数 / 0-255範囲外 / カンマ前後に空白を含む / 余剰トークンがある<br>No space after identifier / RGB not 3 elements / non-integer / outside 0-255 / spaces around commas / trailing tokens present | F/C 共通のバリデーションとして扱う<br>Handle as common validation for F/C | design.md:163 |
| `MISSING_IDENTIFIER` | 入力終端 or map 行到達時点で `seen_flags` に 0 が残る<br>`seen_flags` contains 0 when reaching input end or map lines | 欠けている識別子名を列挙<br>List missing identifier names | design.md:164 |
| `CONFIG_AFTER_MAP` | map 開始後に config 識別子行が出現 / config 行が 7 行以上存在<br>Config identifier line appears after map starts, or more than 6 config lines are present | フォーマットエラーとして即時エラー返却<br>Treat as format error, return immediately | design.md:?? |

**セマンティック制約 / Semantic Constraints**:
- 各識別子は正確に1回のみ出現 (design.md:67-69)
- RGB 値は 0-255 範囲内 (design.md:71-73)
- テクスチャパスは `.xpm` 拡張子必須 (design.md:75-77)

---

### 1.2 Map サブモジュール / Map Submodule

**参照元 / Reference**: `docs/design/modules/parse/map/design.md`

| 検証ルール<br>Validation Rule | 説明<br>Description | 対応方針<br>Handling Policy | 行番号<br>Line Ref |
|----------------|-------------|-----------------|--------|
| `MINIMUM_MAP_SIZE` | マップは最低 3×3 のサイズが必要<br>Map must be at least 3×3 in size | サイズ不足の場合はマップを拒否<br>Reject map if too small | design.md:50-52 |
| `MAXIMUM_MAP_SIZE` | マップは 1024×1024 を超えてはならない（実装しきい値）<br>Map must not exceed 1024×1024 (implementation limit) | サイズ超過の場合はマップを拒否<br>Reject map if too large | design.md:54-56 |
| `WALL_ENCLOSURE` | マップは全ての辺が壁 (`1`) で囲まれている必要<br>Map must be enclosed by walls (`1`) on all sides | 囲まれていない場合はマップを拒否<br>Reject map if not enclosed | design.md:58-61 |
| `PLAYER_COUNT` | プレイヤー (`N`, `S`, `E`, `W`) は正確に1つだけ存在<br>Exactly one player (`N`, `S`, `E`, `W`) must exist | 0個または2個以上の場合はマップを拒否<br>Reject map if zero or multiple players | design.md:63-65 |
| `ROW_LENGTH_CONSISTENCY` | 全ての行は同じ長さでなければならない<br>All rows must have the same length | 長さ不一致の場合は拒否<br>Reject map if inconsistent | design.md:67-70 |
| `INVALID_CHARACTER` | マップには `0`, `1`, `N`, `S`, `E`, `W`, ` ` (空白) のみ許可<br>Only `0`, `1`, `N`, `S`, `E`, `W`, ` ` (space) allowed | 無効な文字が見つかった場合はマップを拒否<br>Reject map if invalid character found | design.md:72-74 |
| `SPACE_VOID_CONTACT` | 空白 (` `) が void/境界外に接してはならない<br>Spaces must not touch void or out-of-bounds areas | 違反が検出された場合はマップを拒否<br>Reject map if violation detected | design.md:162 |
| `UNREACHABLE_AREA` | 全ての開放領域がプレイヤーから到達可能であるべき<br>All open areas should be reachable from player | **WARNING を表示（エラーではない）**<br>**Display WARNING (not an error)** | design.md:76-78 |

**検証順序 / Validation Order** (design.md:94-102):
1. 文字検証 (is_valid_char)
2. サイズ検証 (最小/最大)
3. プレイヤー数検証 (exactly 1)
4. 行長さ一貫性検証
5. 壁囲い込み検証
6. 空白-境界接触検証
7. (オプション) 到達可能性検証

---

### 1.3 Parse 共通 / Parse Common

**参照元 / Reference**: `docs/design/modules/parse/README.md`

- 任意の設定ミス時に正常終了<br>Exit gracefully on any misconfiguration (README.md:58)
- `Error\n` の後に正確なエラーメッセージを表示<br>Print `Error\n` followed by precise error message (README.md:59)

---

## 2. Engine モジュール / Engine Module

### 2.1 Engine 共通 / Engine Common

**参照元 / Reference**: `docs/design/modules/engine/design.md`

| エラー種別<br>Error Type | 発生条件<br>Trigger Condition | 対応<br>Action | 行番号<br>Line Ref |
|----------|----------|------|--------|
| `MLX_INIT_FAILURE` | `init_mlx()` で MLX 初期化失敗<br>MLX initialization fails in `init_mlx()` | エラーメッセージを標準エラー出力に書き込み、`exit(EXIT_FAILURE)` で終了<br>Write error message to stderr, exit with `EXIT_FAILURE` | design.md:68-69 |
| `WINDOW_CREATION_FAILURE` | `init_mlx()` でウィンドウ生成失敗<br>Window creation fails in `init_mlx()` | エラーメッセージを標準エラー出力に書き込み、`exit(EXIT_FAILURE)` で終了<br>Write error message to stderr, exit with `EXIT_FAILURE` | design.md:68-69 |
| `RUNTIME_ERROR` | ゲームループ中のエラー<br>Error during game loop | 適切なクリーンアップを行った上で `close_window()` を通じてループを終了<br>Perform appropriate cleanup, exit loop via `close_window()` | design.md:71-72 |

**クロスプラットフォーム対応 / Cross-platform Support**:
- macOS/Linux で異なる MLX 実装に対応 (design.md:74-76)
- `#ifdef __linux__` で条件分岐（例: `mlx_destroy_display()`）

---

### 2.2 Raycasting サブモジュール / Raycasting Submodule

**参照元 / Reference**: `docs/design/modules/engine/raycasting/design.md`

| エラー種別<br>Error Type | 説明<br>Description | 行番号<br>Line Ref |
|----------|-------------|--------|
| `DDA_OUT_OF_BOUNDS` | DDA中のマップ範囲外アクセス<br>Out-of-bounds access during DDA | design.md:61 |
| `DRAW_COORD_OUT_OF_RANGE` | 画像バッファへの描画時の座標範囲外<br>Coordinate out of range when drawing to image buffer | design.md:62 |

---

## 3. データ構造 / Data Structure

### 3.1 メモリ管理 / Memory Management

**参照元 / Reference**: `docs/design/data/structure.md`

現在の設計では明示的なメモリエラーは定義されていませんが、以下の考慮が必要です：

While not explicitly defined in current design, the following considerations are needed:

- メモリ確保失敗時のエラーハンドリング (`MALLOC_FAILURE` として扱う)<br>Error handling for memory allocation failures (treat as `MALLOC_FAILURE`)
- メモリリーク防止のための解放タイミング<br>Proper deallocation timing to prevent memory leaks
- 二重解放防止<br>Prevention of double-free

---

## 4. エラー処理の方針 / Error Handling Policy

### 4.1 統一されたエラー出力形式 / Unified Error Output Format

Subject 要件に基づき：<br>Based on subject requirements:

```
Error\n<specific error message>
```

### 4.2 エラー発生時の終了戦略 / Exit Strategy on Error

1. **Parse 段階のエラー**<br>**Parse Phase Errors**
   - 即座にプログラムを終了 (`exit(EXIT_FAILURE)`)
   - リソースのクリーンアップを実施
   
2. **Engine 初期化段階のエラー**<br>**Engine Initialization Phase Errors**
   - MLX リソースのクリーンアップ
   - 確保済みメモリの解放
   - `exit(EXIT_FAILURE)` で終了
   
3. **Runtime エラー**<br>**Runtime Errors**
   - ゲームループの正常終了
   - 全リソースのクリーンアップ
   - `close_window()` 経由での終了

### 4.3 エラーの優先度 / Error Priority

**HIGH (即座に終了)**:
- メモリ確保失敗
- MLX 初期化失敗
- 必須設定の欠落
- 無効なマップ構造

**MEDIUM (リカバリ可能)**:
- ファイル読み込みエラー（代替パスの試行）
- 到達不可能領域（WARNING 表示のみ）

**LOW (無視可能)**:
- パフォーマンス警告
- デバッグ情報

---

## 5. エラーカタログサマリ / Error Catalog Summary

### 5.1 エラー数の統計 / Error Statistics

| モジュール<br>Module | エラー種別数<br>Error Types | 警告種別数<br>Warning Types |
|----------|----------|----------|
| Parse/Entry | 3 | 0 |
| Parse/Config | 6 | 0 |
| Parse/Map | 7 | 1 |
| Engine/Common | 3 | 0 |
| Engine/Raycasting | 2 | 0 |
| Data/Memory | 1 | 0 |
| **合計 / Total** | **22** | **1** |

### 5.2 エラーID一覧 / Error ID List

**Parse Module**:
- `UNKNOWN_IDENTIFIER`
- `DUPLICATE_IDENTIFIER`
- `SYNTAX_TEXTURE`
- `SYNTAX_RGB`
- `MISSING_IDENTIFIER`
- `CONFIG_AFTER_MAP`
- `INVALID_EXTENSION`
- `FILE_NOT_FOUND`
- `FILE_PERMISSION_DENIED`
- `MINIMUM_MAP_SIZE`
- `MAXIMUM_MAP_SIZE`
- `WALL_ENCLOSURE`
- `PLAYER_COUNT`
- `ROW_LENGTH_CONSISTENCY`
- `INVALID_CHARACTER`
- `SPACE_VOID_CONTACT`

**Engine Module**:
- `MLX_INIT_FAILURE`
- `WINDOW_CREATION_FAILURE`
- `RUNTIME_ERROR`
- `DDA_OUT_OF_BOUNDS`
- `DRAW_COORD_OUT_OF_RANGE`

**Data/Memory**:
- `MALLOC_FAILURE`

**Warnings**:
- `UNREACHABLE_AREA` (WARNING のみ)

---

## 6. 今後の拡張 / Future Extensions

以下のエラー種別は実装時に追加が必要になる可能性があります：

The following error types may need to be added during implementation:

1. **ファイルシステムエラー / Filesystem Errors**
   - ファイルが存在しない / File not found
   - 読み込み権限がない / Read permission denied
   - パスが無効 / Invalid path

2. **メモリエラー / Memory Errors**
   - malloc 失敗 / malloc failure
   - メモリリーク検出 / Memory leak detection
   - バッファオーバーフロー / Buffer overflow

3. **入力検証エラー / Input Validation Errors**
   - 無効なコマンドライン引数 / Invalid command line arguments
   - ファイル拡張子の不一致 / File extension mismatch

4. **ボーナス機能のエラー / Bonus Feature Errors**
   - ドア処理エラー / Door handling errors
   - ミニマップ描画エラー / Minimap rendering errors
   - マウス操作エラー / Mouse operation errors

---

## 参照 / References

- [Parse/Config 設計](../modules/parse/config/design.md)
- [Parse/Map 設計](../modules/parse/map/design.md)
- [Parse モジュール README](../modules/parse/README.md)
- [Engine 設計](../modules/engine/design.md)
- [Raycasting 設計](../modules/engine/raycasting/design.md)
- [データ構造](../data/structure.md)
