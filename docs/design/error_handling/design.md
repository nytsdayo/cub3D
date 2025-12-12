# エラーハンドリング設計 / Error Handling Design

## 目的 / Purpose

全てのエラーを統一的に処理し、一貫したエラーメッセージ出力と適切なリソースクリーンアップを保証する。

Uniformly handle all errors, ensuring consistent error message output and proper resource cleanup.

---

## 設計原則 / Design Principles

1. **単一エラーハンドラ / Single Error Handler**
   - 全てのエラーは最終的に一つの関数に集約される
   - All errors ultimately converge to a single function

2. **一貫したエラー形式 / Consistent Error Format**
   - Subject 要件に準拠: `Error\n<specific message>`
   - Compliant with subject requirements: `Error\n<specific message>`

3. **適切なクリーンアップ / Proper Cleanup**
   - エラー発生時に確保済みリソースを全て解放
   - Release all allocated resources on error

4. **明確なエラーメッセージ / Clear Error Messages**
   - ユーザーが問題を理解できる具体的なメッセージ
   - Specific messages that users can understand

---

## アーキテクチャ / Architecture

### フロー図 / Flow Diagram

```
┌─────────────────┐
│  Any Module     │
│  (Parse/Engine) │
└────────┬────────┘
         │ Error Detected
         ↓
┌─────────────────────────┐
│  error_exit()           │
│  ┌───────────────────┐  │
│  │ 1. Print Error    │  │
│  │ 2. Cleanup        │  │
│  │ 3. Exit           │  │
│  └───────────────────┘  │
└─────────────────────────┘
         │
         ↓
┌─────────────────┐
│  exit(1)        │
└─────────────────┘
```

---

## 公開関数 / Public Functions

### 1. `error_exit()` - メインエラーハンドラ

```c
/**
 * @brief 統一エラーハンドリング関数
 * 
 * 全てのエラー発生時にこの関数を呼び出す。
 * エラーメッセージを標準エラー出力に表示し、
 * リソースをクリーンアップした後、プログラムを終了する。
 * 
 * @param error_code エラーコード (列挙型)
 * @param context エラーコンテキスト情報 (オプション、行番号など)
 * @param cleanup_data クリーンアップ対象のデータ構造へのポインタ
 * 
 * @note この関数は戻ることはない (noreturn)
 */
void error_exit(t_error_code error_code, const char *context, void *cleanup_data);
```

### 2. `error_exit_simple()` - シンプル版

```c
/**
 * @brief シンプルなエラー終了関数
 * 
 * コンテキスト情報やクリーンアップが不要な場合に使用。
 * 主にプログラム初期段階でのエラーに使用。
 * 
 * @param error_code エラーコード (列挙型)
 * 
 * @note この関数は戻ることはない (noreturn)
 */
void error_exit_simple(t_error_code error_code);
```

### 3. `error_warning()` - 警告表示

```c
/**
 * @brief 警告メッセージを表示 (プログラムは継続)
 * 
 * 到達不可能な領域など、致命的ではない問題を報告する。
 * 
 * @param warning_code 警告コード (列挙型)
 * @param context 警告コンテキスト情報
 */
void error_warning(t_warning_code warning_code, const char *context);
```

---

## データ構造 / Data Structures

### エラーコード列挙型 / Error Code Enumeration

```c
/**
 * @brief エラーコード定義
 * 
 * 全てのエラー種別を列挙型で定義。
 * 各エラーに対応するメッセージはエラーハンドラ内部で管理。
 */
typedef enum e_error_code
{
    /* Parse/Config Errors (100-199) */
    ERR_UNKNOWN_IDENTIFIER = 100,
    ERR_DUPLICATE_IDENTIFIER,
    ERR_SYNTAX_TEXTURE,
    ERR_SYNTAX_RGB,
    ERR_MISSING_IDENTIFIER,
    
    /* Parse/Map Errors (200-299) */
    ERR_MINIMUM_MAP_SIZE = 200,
    ERR_MAXIMUM_MAP_SIZE,
    ERR_WALL_ENCLOSURE,
    ERR_PLAYER_COUNT_ZERO,
    ERR_PLAYER_COUNT_MULTIPLE,
    ERR_ROW_LENGTH_INCONSISTENT,
    ERR_INVALID_CHARACTER,
    ERR_SPACE_VOID_CONTACT,
    
    /* File/Path Errors (300-399) */
    ERR_FILE_NOT_FOUND = 300,
    ERR_FILE_READ_PERMISSION,
    ERR_INVALID_FILE_EXTENSION,
    ERR_INVALID_PATH,
    
    /* Memory Errors (400-499) */
    ERR_MALLOC_FAILURE = 400,
    ERR_BUFFER_OVERFLOW,
    
    /* Engine/MLX Errors (500-599) */
    ERR_MLX_INIT_FAILURE = 500,
    ERR_WINDOW_CREATION_FAILURE,
    ERR_IMAGE_CREATION_FAILURE,
    ERR_TEXTURE_LOAD_FAILURE,
    
    /* Engine/Runtime Errors (600-699) */
    ERR_DDA_OUT_OF_BOUNDS = 600,
    ERR_DRAW_COORD_OUT_OF_RANGE,
    
    /* Command Line Errors (700-799) */
    ERR_INVALID_ARGC = 700,
    ERR_INVALID_ARGV,
    
    /* Generic Errors (900-999) */
    ERR_GENERIC = 900,
    
} t_error_code;
```

### 警告コード列挙型 / Warning Code Enumeration

```c
/**
 * @brief 警告コード定義
 * 
 * 致命的ではないが報告すべき問題を定義。
 */
typedef enum e_warning_code
{
    WARN_UNREACHABLE_AREA = 1,
    WARN_PERFORMANCE_ISSUE,
    
} t_warning_code;
```

### クリーンアップデータ構造 / Cleanup Data Structure

```c
/**
 * @brief クリーンアップ対象データ構造
 * 
 * エラー発生時に解放すべきリソースを一元管理。
 */
typedef struct s_cleanup_data
{
    void            *mlx;
    void            *win;
    void            *img;
    char            **map;
    t_config_data   *config;
    int             mlx_initialized;
    int             window_created;
    
} t_cleanup_data;
```

---

## 内部実装詳細 / Internal Implementation Details

### エラーメッセージテーブル / Error Message Table

```c
/**
 * @brief エラーメッセージマッピング
 * 
 * 各エラーコードに対応するメッセージを定義。
 * 実装時に static const として定義。
 */
static const char *g_error_messages[] = {
    /* Parse/Config Errors */
    [ERR_UNKNOWN_IDENTIFIER] = "Unknown identifier in config section",
    [ERR_DUPLICATE_IDENTIFIER] = "Duplicate identifier found",
    [ERR_SYNTAX_TEXTURE] = "Invalid texture path syntax",
    [ERR_SYNTAX_RGB] = "Invalid RGB color format or range",
    [ERR_MISSING_IDENTIFIER] = "Missing required identifier",
    
    /* Parse/Map Errors */
    [ERR_MINIMUM_MAP_SIZE] = "Map is too small (minimum 3x3 required)",
    [ERR_MAXIMUM_MAP_SIZE] = "Map exceeds maximum allowed size",
    [ERR_WALL_ENCLOSURE] = "Map is not enclosed by walls",
    [ERR_PLAYER_COUNT_ZERO] = "No player start position found",
    [ERR_PLAYER_COUNT_MULTIPLE] = "Multiple player start positions found",
    [ERR_ROW_LENGTH_INCONSISTENT] = "Inconsistent row lengths in map",
    [ERR_INVALID_CHARACTER] = "Invalid character in map",
    [ERR_SPACE_VOID_CONTACT] = "Space character touches void area",
    
    /* File/Path Errors */
    [ERR_FILE_NOT_FOUND] = "File not found",
    [ERR_FILE_READ_PERMISSION] = "Permission denied reading file",
    [ERR_INVALID_FILE_EXTENSION] = "Invalid file extension",
    [ERR_INVALID_PATH] = "Invalid file path",
    
    /* Memory Errors */
    [ERR_MALLOC_FAILURE] = "Memory allocation failed",
    [ERR_BUFFER_OVERFLOW] = "Buffer overflow detected",
    
    /* Engine/MLX Errors */
    [ERR_MLX_INIT_FAILURE] = "Failed to initialize MLX",
    [ERR_WINDOW_CREATION_FAILURE] = "Failed to create window",
    [ERR_IMAGE_CREATION_FAILURE] = "Failed to create image",
    [ERR_TEXTURE_LOAD_FAILURE] = "Failed to load texture",
    
    /* Engine/Runtime Errors */
    [ERR_DDA_OUT_OF_BOUNDS] = "DDA algorithm accessed out of bounds",
    [ERR_DRAW_COORD_OUT_OF_RANGE] = "Drawing coordinate out of range",
    
    /* Command Line Errors */
    [ERR_INVALID_ARGC] = "Invalid number of arguments",
    [ERR_INVALID_ARGV] = "Invalid argument",
    
    /* Generic */
    [ERR_GENERIC] = "An error occurred",
};
```

### クリーンアップ処理の実装方針 / Cleanup Implementation Strategy

```c
/**
 * @brief リソースクリーンアップ処理
 * 
 * エラー発生時に呼び出され、確保済みリソースを順次解放。
 * NULL チェックを行い、既に解放済みのリソースは無視する。
 * 
 * @param cleanup_data クリーンアップ対象データ
 */
static void cleanup_resources(t_cleanup_data *cleanup_data)
{
    if (!cleanup_data)
        return;
    
    /* MLX resources cleanup */
    if (cleanup_data->img && cleanup_data->mlx)
        mlx_destroy_image(cleanup_data->mlx, cleanup_data->img);
    
    if (cleanup_data->win && cleanup_data->mlx)
        mlx_destroy_window(cleanup_data->mlx, cleanup_data->win);
    
#ifdef __linux__
    if (cleanup_data->mlx && cleanup_data->mlx_initialized)
        mlx_destroy_display(cleanup_data->mlx);
#endif
    
    if (cleanup_data->mlx)
        free(cleanup_data->mlx);
    
    /* Config data cleanup */
    if (cleanup_data->config)
        free_config_data(cleanup_data->config);
    
    /* Map data cleanup */
    if (cleanup_data->map)
        free_map_data(cleanup_data->map);
}
```

---

## 使用例 / Usage Examples

### 例1: Config パース中のエラー

```c
// Parse/config モジュール内
if (identifier_count[idx] > 0)
{
    // 重複識別子を検出
    error_exit(ERR_DUPLICATE_IDENTIFIER, "NO", cleanup_data);
}
```

### 例2: MLX 初期化失敗

```c
// Engine/init モジュール内
mlx = mlx_init();
if (!mlx)
{
    error_exit_simple(ERR_MLX_INIT_FAILURE);
}
```

### 例3: マップ検証でのエラー

```c
// Parse/map モジュール内
if (player_count == 0)
{
    error_exit(ERR_PLAYER_COUNT_ZERO, NULL, cleanup_data);
}
else if (player_count > 1)
{
    char context[64];
    snprintf(context, sizeof(context), "Found %d players", player_count);
    error_exit(ERR_PLAYER_COUNT_MULTIPLE, context, cleanup_data);
}
```

### 例4: 警告の表示

```c
// Parse/map モジュール内
if (unreachable_areas_detected)
{
    error_warning(WARN_UNREACHABLE_AREA, 
                  "Some areas are not reachable from player start");
    // プログラムは継続
}
```

---

## エラー出力フォーマット / Error Output Format

### 基本フォーマット / Basic Format

```
Error
<error_message>
```

### コンテキスト付きフォーマット / Format with Context

```
Error
<error_message>: <context>
```

### 例 / Examples

```
Error
Duplicate identifier found: NO
```

```
Error
Map is not enclosed by walls
```

```
Error
Invalid RGB color format or range: line 3
```

---

## ファイル構成 / File Structure

### ヘッダーファイル / Header File

```
includes/error.h
├── t_error_code 列挙型
├── t_warning_code 列挙型
├── t_cleanup_data 構造体
├── error_exit() 関数宣言
├── error_exit_simple() 関数宣言
└── error_warning() 関数宣言
```

### ソースファイル / Source Files

```
srcs/error/
├── error_exit.c          - error_exit() 実装
├── error_cleanup.c       - cleanup_resources() 実装
├── error_messages.c      - メッセージテーブル定義
└── error_warning.c       - error_warning() 実装
```

---

## 実装時の注意事項 / Implementation Notes

### 1. スレッドセーフティ / Thread Safety

- 現在の cub3D はシングルスレッドで動作するため、スレッドセーフティは考慮不要
- Currently single-threaded, thread safety not required

### 2. メモリリーク防止 / Memory Leak Prevention

- Valgrind でのメモリリークチェック必須
- Valgrind memory leak check required
- エラー処理パスでもリークが無いことを確認
- Verify no leaks in error handling paths

### 3. 42 Norminette 準拠 / 42 Norminette Compliance

- 関数は25行以内
- Functions must be within 25 lines
- 行は80文字以内
- Lines must be within 80 characters
- 関数は5個以内のパラメータ
- Functions must have at most 5 parameters

### 4. エラーメッセージの言語 / Error Message Language

- 英語でメッセージを記述（国際的な標準）
- Error messages in English (international standard)
- 明確で簡潔な表現を心がける
- Keep messages clear and concise

### 5. デバッグモード / Debug Mode

将来的に実装を検討：
Consider implementing in the future:

```c
#ifdef DEBUG
    fprintf(stderr, "Debug: Error occurred at %s:%d\n", __FILE__, __LINE__);
#endif
```

---

## テスト戦略 / Testing Strategy

### 1. ユニットテスト / Unit Tests

各エラーコードに対して：
For each error code:
- エラーメッセージが正しく表示されるか
- Verify error message is displayed correctly
- クリーンアップが適切に実行されるか
- Verify cleanup is executed properly
- プログラムが正しく終了するか (exit code = 1)
- Verify program exits correctly (exit code = 1)

### 2. 統合テスト / Integration Tests

実際のエラーシナリオ：
Real error scenarios:
- 不正な設定ファイル
- Invalid config file
- 無効なマップ
- Invalid map
- 存在しないテクスチャファイル
- Non-existent texture file
- MLX 初期化失敗のシミュレーション
- MLX initialization failure simulation

### 3. メモリリークテスト / Memory Leak Tests

```bash
valgrind --leak-check=full ./cub3D invalid_map.cub
```

エラー発生時でもリークが無いことを確認。
Verify no leaks even when errors occur.

---

## 参照 / References

- [エラー一覧](./error_list.md)
- [Parse/Config 設計](../modules/parse/config/design.md)
- [Parse/Map 設計](../modules/parse/map/design.md)
- [Engine 設計](../modules/engine/design.md)

---

## 変更履歴 / Change History

| 日付<br>Date | バージョン<br>Version | 変更内容<br>Changes |
|---------|---------|---------|
| 2025-12-12 | 1.0.0 | 初版作成<br>Initial version |

---

## 今後の拡張予定 / Future Extensions

1. **ログファイル出力**
   - エラーをログファイルにも記録
   - Log errors to file

2. **多言語対応**
   - エラーメッセージの多言語化
   - Multilingual error messages

3. **エラーリカバリ**
   - 一部のエラーでリカバリを試行
   - Attempt recovery for some errors

4. **スタックトレース**
   - デバッグモードでスタックトレースを表示
   - Display stack trace in debug mode
