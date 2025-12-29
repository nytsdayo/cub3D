# エラーハンドリング実装と設計書のすりあわせ

## 日付: 2025-12-29

## 概要

`copilot/create-error-handling-structure`ブランチの設計書と、現在の`refactor/error-handling-system`ブランチの実装を比較し、差分と対応方針を明確化する。

---

## 1. 現在の実装状況（refactor/error-handling-systemブランチ）

### 1.1 ファイル構成

```
includes/error/
└── error_manage.h              - エラー関数宣言のみ

srcs/error/
└── error_msg.c          - シンプルなメッセージ出力関数
```

### 1.2 実装されている機能

```c
// includes/error/error_manage.h
int	error_msg(const char *msg);
```

```c
// srcs/error/error_msg.c
int	error_msg(const char *msg)
{
	size_t	len;

	len = ft_strlen(msg);
	write(2, msg, len);
	return (-1);
}
```

**特徴**:
- ✅ メッセージをstderrに出力
- ✅ 42 Norminetteに準拠
- ❌ プログラムを終了しない（戻り値-1のみ）
- ❌ エラーコード列挙型なし
- ❌ クリーンアップ機能なし
- ❌ 統一されたエラーハンドリングなし

---

## 2. 設計書の要件（copilot/create-error-handling-structureブランチ）

### 2.1 ファイル構成

```
includes/error_manage.h
├── t_error_code 列挙型（22種類のエラー）
├── t_warning_code 列挙型
├── t_cleanup_data 構造体
├── error_exit() 関数宣言
├── error_exit_simple() 関数宣言
└── error_warning() 関数宣言

srcs/error/
├── error_exit.c          - error_exit() 実装
├── error_cleanup.c       - cleanup_resources() 実装
├── error_messages.c      - メッセージテーブル定義
└── error_warning.c       - error_warning() 実装
```

### 2.2 必要な機能

#### エラーコード列挙型
```c
typedef enum e_error_code
{
    /* Command Line Errors (100-199) */
    ERR_INVALID_ARGC = 100,
    ERR_INVALID_ARGV,

    /* Parse/Config Errors (200-299) */
    ERR_UNKNOWN_IDENTIFIER = 200,
    ERR_DUPLICATE_IDENTIFIER,
    ERR_SYNTAX_TEXTURE,
    ERR_SYNTAX_RGB,
    ERR_MISSING_IDENTIFIER,
    ERR_CONFIG_AFTER_MAP,

    /* Parse/Map Errors (300-399) */
    ERR_MINIMUM_MAP_SIZE = 300,
    ERR_MAXIMUM_MAP_SIZE,
    ERR_WALL_ENCLOSURE,
    ERR_PLAYER_COUNT_ZERO,
    ERR_PLAYER_COUNT_MULTIPLE,
    ERR_ROW_LENGTH_INCONSISTENT,
    ERR_INVALID_CHARACTER,
    ERR_SPACE_VOID_CONTACT,

    /* File/Path Errors (400-499) */
    ERR_FILE_NOT_FOUND = 400,
    ERR_FILE_READ_PERMISSION,
    ERR_INVALID_FILE_EXTENSION,
    ERR_INVALID_PATH,

    /* Memory Errors (500-599) */
    ERR_MALLOC_FAILURE = 500,
    ERR_BUFFER_OVERFLOW,

    /* Engine/MLX Errors (600-699) */
    ERR_MLX_INIT_FAILURE = 600,
    ERR_WINDOW_CREATION_FAILURE,
    ERR_IMAGE_CREATION_FAILURE,
    ERR_TEXTURE_LOAD_FAILURE,

    /* Engine/Runtime Errors (700-799) */
    ERR_DDA_OUT_OF_BOUNDS = 700,
    ERR_DRAW_COORD_OUT_OF_RANGE,

    /* Generic Errors (900-999) */
    ERR_GENERIC = 900,

} t_error_code;
```

#### エラーハンドラ関数
```c
void error_exit(t_error_code error_code, const char *context, void *cleanup_data);
void error_exit_simple(t_error_code error_code);
void error_warning(t_warning_code warning_code, const char *context);
```

#### クリーンアップデータ構造
```c
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

## 3. 差分分析

### 3.1 欠けている機能

| 機能 | 設計書 | 現在の実装 | 優先度 |
|------|--------|------------|--------|
| エラーコード列挙型 | ✅ 22種類定義 | ❌ なし | **HIGH** |
| 統一エラーハンドラ | ✅ error_exit() | ❌ なし | **HIGH** |
| クリーンアップ機能 | ✅ cleanup_resources() | ❌ なし | **HIGH** |
| エラーメッセージテーブル | ✅ 静的配列で管理 | ❌ 呼び出し側で文字列指定 | **MEDIUM** |
| 警告機能 | ✅ error_warning() | ❌ なし | **MEDIUM** |
| プログラム終了 | ✅ exit(1) | ❌ return -1のみ | **HIGH** |
| コンテキスト情報 | ✅ 第2引数で渡す | ❌ なし | **LOW** |

### 3.2 アーキテクチャの違い

#### 現在の実装パターン
```c
// 各モジュールで個別にエラーメッセージを作成
if (error_condition)
{
    error_msg("Error\nSpecific error message\n");
    return (-1);  // 呼び出し側で処理が必要
}
```

#### 設計書のパターン
```c
// 統一されたエラーハンドラで一元管理
if (error_condition)
{
    error_exit(ERR_SPECIFIC_ERROR, "context info", cleanup_data);
    // ここには到達しない（プログラムが終了する）
}
```

---

## 4. 対応方針

### 4.1 Phase 1: 基盤構築（優先度: HIGH）

**目標**: 設計書の基本構造を実装

1. **エラーコード列挙型の追加**
   - `includes/error/error_manage.h` に `t_error_code` を追加
   - 全22種類のエラーコードを定義

2. **クリーンアップデータ構造の追加**
   - `t_cleanup_data` 構造体を定義

3. **統一エラーハンドラの実装**
   - `srcs/error/error_exit.c` を作成
   - `error_exit()` と `error_exit_simple()` を実装

4. **エラーメッセージテーブルの実装**
   - `srcs/error/error_messages.c` を作成
   - 静的配列で全エラーメッセージを管理

5. **クリーンアップ処理の実装**
   - `srcs/error/error_cleanup.c` を作成
   - `cleanup_resources()` を実装

### 4.2 Phase 2: 既存コードの移行（優先度: MEDIUM）

**目標**: 現在の `error_msg()` 呼び出しを `error_exit()` に置き換え

1. **Parse モジュールの移行**
   - `parse_config.c`, `parse_map.c` など
   - 各エラーメッセージを対応するエラーコードに置き換え

2. **Engine モジュールの移行**
   - MLX 初期化エラーを `ERR_MLX_INIT_FAILURE` に統一

3. **Makefile の更新**
   - 新しい `.c` ファイルをビルドに追加

### 4.3 Phase 3: 拡張機能（優先度: LOW）

1. **警告機能の実装**
   - `srcs/error/error_warning.c` を作成
   - 到達不可能領域などの警告に対応

2. **コンテキスト情報の追加**
   - 行番号や詳細情報を含むエラーメッセージ

---

## 5. 互換性の維持

### 5.1 移行戦略

既存の `error_msg()` 関数は、移行期間中も残しておく:

```c
// 互換性のための簡易ラッパー（deprecated）
int	error_msg(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (-1);
}
```

移行が完了したら、この関数を削除する。

### 5.2 段階的移行

```
Step 1: 新しいエラーシステムを実装（error_msg()と並行）
Step 2: 1つのモジュールずつ新システムに移行
Step 3: 全モジュール移行後、error_msg()を削除
```

---

## 6. テスト計画

### 6.1 ユニットテスト

各エラーコードに対して:
- [ ] エラーメッセージが正しく表示される
- [ ] プログラムが exit(1) で終了する
- [ ] クリーンアップが実行される

### 6.2 統合テスト

実際のエラーシナリオ:
- [ ] 不正な設定ファイル → `ERR_SYNTAX_RGB`
- [ ] マップが小さすぎる → `ERR_MINIMUM_MAP_SIZE`
- [ ] プレイヤー不在 → `ERR_PLAYER_COUNT_ZERO`
- [ ] MLX初期化失敗 → `ERR_MLX_INIT_FAILURE`

### 6.3 メモリリークテスト

```bash
valgrind --leak-check=full ./cub3D invalid_map.cub
```

エラー発生時でもリークが無いことを確認。

---

## 7. 実装時の注意点

### 7.1 42 Norminette 準拠

- 関数は25行以内
- 1行80文字以内
- 関数は1ファイル5個まで
- エラーメッセージテーブルは静的配列で管理

### 7.2 クロスプラットフォーム対応

```c
#ifdef __linux__
    if (cleanup_data->mlx && cleanup_data->mlx_initialized)
        mlx_destroy_display(cleanup_data->mlx);
#endif
```

### 7.3 NULL チェック

クリーンアップ時に必ず NULL チェックを実施:
```c
if (cleanup_data && cleanup_data->mlx)
    free(cleanup_data->mlx);
```

---

## 8. 次のステップ

1. ✅ 設計書と実装の差分を明確化（このドキュメント）
2. ⬜ Phase 1 の実装開始
   - エラーコード列挙型の追加
   - 基本的なエラーハンドラの実装
3. ⬜ ユニットテストの作成
4. ⬜ 既存コードの段階的移行

---

## 9. 参照ドキュメント

### 設計書（copilot/create-error-handling-structure ブランチ）
- `docs/design/error_handling/README.md`
- `docs/design/error_handling/design.md`
- `docs/design/error_handling/error_list.md`

### 現在の実装（refactor/error-handling-system ブランチ）
- `includes/error/error_manage.h`
- `srcs/error/error_msg.c`

---

## 10. まとめ

現在の実装は **シンプルなエラーメッセージ出力** のみで、設計書が求める **統一されたエラーハンドリングシステム** とは大きく異なる。

主な課題:
- エラーコードの体系化が必要
- プログラム終了機能の実装が必要
- リソースクリーンアップ機能の実装が必要
- エラーメッセージの一元管理が必要

推奨アプローチ:
1. 設計書に従って段階的に実装
2. 既存の `error_msg()` は移行期間中保持
3. モジュール単位で新システムに移行
4. 全移行完了後、旧システムを削除
