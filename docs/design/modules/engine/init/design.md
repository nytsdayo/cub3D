# init サブモジュール設計

## 目的

ゲームの初期化処理を担当するサブモジュール。
MinilibXの初期化、ウィンドウ生成、画像バッファの作成、テクスチャの読み込み、ゲーム状態の初期設定を行う。

## 責務

- **MLXの初期化**: MinilibXライブラリの初期化とウィンドウ生成
- **画像バッファの初期化**: レンダリング用の画像バッファを作成
- **ゲーム状態の初期化**: ゲーム構造体のメンバーをゼロクリア・初期化
- **テクスチャの初期化**: 4方向のテクスチャファイルを読み込み
- **色の初期化**: 床・天井の色を設定
- **エラーハンドリング**: 初期化失敗時の適切なエラー報告

## インターフェース

### 公開関数

| 関数名 | 説明 | 引数 | 戻り値 |
|--------|------|------|--------|
| `init_game` | ゲーム全体を初期化する（メインエントリーポイント） | `t_game *game` | `int` (0: 成功, 1: 失敗) |

### 内部関数

| 関数名 | 説明 | 引数 | 戻り値 |
|--------|------|------|--------|
| `init_mlx` | MinilibXとウィンドウを初期化 (static) | `t_game *game` | `int` (0: 成功, 1: 失敗) |
| `init_image` | レンダリング用画像バッファを初期化 (static) | `t_game *game` | `void` |

## 内部設計

### init_game() の処理フロー

`init_game()` は以下の順序で初期化を実行する：

```
1. ゲーム構造体のクリア
   ├─ game->mlx = NULL
   ├─ game->win = NULL
   └─ game->keys[KEY_STATE_SIZE] をゼロクリア

2. MLXとウィンドウの初期化
   └─ init_mlx(game) ← 失敗時は return 1

3. 画像バッファの初期化
   └─ init_image(game)

4. テクスチャの初期化
   └─ init_textures(game)  // texture モジュール

5. 色の初期化
   └─ init_colors(game)    // texture モジュール

6. マップの初期化 (暫定)
   └─ init_hardcoded_map(game)  // TODO: パーサー統合後に削除

7. プレイヤーの初期化 (暫定)
   └─ init_player(game)         // TODO: パーサー統合後に削除

8. 成功を返す
   └─ return 0
```

### init_mlx() の処理

MinilibXライブラリを初期化し、ウィンドウを生成する。

**処理フロー:**
```c
1. mlx_init() を呼び出し
   - 失敗時: エラーメッセージ出力 + return 1

2. mlx_new_window() でウィンドウ生成
   - サイズ: WINDOW_WIDTH x WINDOW_HEIGHT
   - タイトル: TITLE
   - 失敗時: エラーメッセージ出力 + return 1

3. 成功: return 0
```

**定数:**
- `WINDOW_WIDTH`: 800 (cub3d.h)
- `WINDOW_HEIGHT`: 600 (cub3d.h)
- `TITLE`: "cub3D" (cub3d.h)

### init_image() の処理

レンダリング用の画像バッファを作成する。

**処理フロー:**
```c
1. mlx_new_image() で画像を作成
   - サイズ: WINDOW_WIDTH x WINDOW_HEIGHT
   - 失敗時: エラーメッセージ出力 + exit(EXIT_FAILURE)

2. mlx_get_data_addr() でピクセルデータのアドレスを取得
   - game->img.addr にポインタを保存
   - bits_per_pixel, line_length, endian の情報を取得
```

**画像構造体:**
```c
typedef struct s_img
{
    void  *img;              // MLX画像ポインタ
    char  *addr;             // ピクセルデータのアドレス
    int   bits_per_pixel;    // 1ピクセルのビット数
    int   line_length;       // 1行のバイト数
    int   endian;            // エンディアン情報
} t_img;
```

### キー状態配列の初期化

`game->keys[KEY_STATE_SIZE]` 配列をゼロクリアする。

**目的:**
- すべてのキーを「解放状態」に初期化
- 未初期化メモリによる誤動作を防止

**サイズ:**
- `KEY_STATE_SIZE`: 70000（X11 KeySym値対応）

## ファイル構成

```
srcs/engine/init/
└── init_game.c
    ├── init_game()      # 公開関数
    ├── init_mlx()       # 内部関数 (static)
    └── init_image()     # 内部関数 (static)

includes/engine/
└── engine.h            # init_game() のプロトタイプ宣言
```

## エラーハンドリング

### MLX初期化失敗

```c
if (!game->mlx)
{
    write(2, "Error\nMLX init failed\n", 22);
    return (1);
}
```

- **原因**: MinilibXライブラリの初期化失敗（稀）
- **対処**: エラーメッセージを標準エラー出力に書き込み、呼び出し元に失敗を通知

### ウィンドウ生成失敗

```c
if (!game->win)
{
    write(2, "Error\nWindow creation failed\n", 29);
    return (1);
}
```

- **原因**: ウィンドウシステムへの接続失敗、ディスプレイなし（CIなど）
- **対処**: エラーメッセージを出力し、呼び出し元に失敗を通知

### 画像バッファ生成失敗

```c
if (!game->img.img)
{
    write(2, "Error\nImage creation failed\n", 28);
    exit(EXIT_FAILURE);
}
```

- **原因**: メモリ不足、MLXの内部エラー
- **対処**: エラーメッセージを出力し、プログラムを終了

### エラーハンドリングの改善 (PR #57)

**変更前:** `init_game()` の戻り値は `void`
**変更後:** `init_game()` の戻り値は `int` (0: 成功, 1: 失敗)

**利点:**
- 呼び出し元（main.c）でエラーをチェック可能
- 初期化失敗時に適切なクリーンアップが可能
- より堅牢なエラーハンドリング

**main.c での使用例:**
```c
if (init_game(&game) != 0)
{
    free_map((void **)game.map);
    return (EXIT_FAILURE);
}
```

## 暫定実装とパーサー統合

### 現在の暫定実装

以下の関数は**テスト用の仮実装**：

1. **init_hardcoded_map()** (raycasting/mock_world.c)
   - ハードコードされたマップデータを設定
   - `world_map[MAP_HEIGHT][MAP_WIDTH]` 配列を初期化

2. **init_player()** (raycasting/mock_world.c)
   - プレイヤーの初期位置と向きを設定
   - `player.pos_x`, `pos_y`, `dir_x`, `dir_y` などを初期化

### パーサー統合後の変更

**削除するもの:**
- `init_hardcoded_map()` の呼び出し
- `init_player()` の呼び出し
- `init_colors()` の呼び出し（パーサーが設定）
- `init_textures()` の呼び出し（パーサーが設定）

**パーサーが担当:**
- .cubファイルからマップデータを読み込み → `game->world_map` に設定
- .cubファイルからプレイヤー初期位置を取得 → `game->player` に設定
- .cubファイルからテクスチャパスを取得 → テクスチャを読み込み
- .cubファイルから床・天井の色を取得 → `game->floor_color`, `ceiling_color` に設定

**統合後の init_game():**
```c
int init_game(t_game *game)
{
    int i;

    game->mlx = NULL;
    game->win = NULL;
    i = 0;
    while (i < KEY_STATE_SIZE)
        game->keys[i++] = 0;
    if (init_mlx(game) != 0)
        return (1);
    init_image(game);
    // テクスチャ、マップ、プレイヤーはパーサーが設定済み
    return (0);
}
```

## 初期化順序の重要性

初期化の順序は依存関係を考慮して決定されている：

```
1. game->mlx, game->win のクリア
   ↓
2. init_mlx() → MLXとウィンドウを初期化
   ↓
3. init_image() → MLXを使用するため、MLX初期化後に実行
   ↓
4. init_textures() → MLXを使用してXPMファイルを読み込む
   ↓
5. init_colors() → 他に依存しない
   ↓
6. init_hardcoded_map() → 他に依存しない
   ↓
7. init_player() → マップ初期化後に実行（マップサイズを参照）
```

## メモリ初期化

### ゲーム構造体のゼロクリア

**main.c で実施:**
```c
t_game game;
memset(&game, 0, sizeof(t_game));
```

**理由:**
- すべてのポインタをNULLに初期化
- 数値フィールドを0に初期化
- 未初期化メモリによるバグを防止
- cleanup処理でのNULLチェックを可能にする

**PR #57 での改善:**
- メモリリーク修正の一環として追加
- 初期化が部分的に失敗した場合でも安全にクリーンアップ可能

## クロスプラットフォーム対応

現在の実装は **macOS** と **Linux** の両方に対応：

**ウィンドウ生成:**
- 両プラットフォームで同じコード（`mlx_new_window`）

**画像バッファ:**
- 両プラットフォームで同じコード（`mlx_new_image`, `mlx_get_data_addr`）

**クリーンアップ:**
- Linux: `mlx_destroy_display()` が必要（cleanup.c で実装）
- macOS: `mlx_destroy_display()` は不要

## パフォーマンス考慮

- 初期化は起動時に1回のみ実行されるため、パフォーマンスは重要でない
- エラーチェックを優先（堅牢性重視）

## 参照

- [README](./README.md)
- [engine モジュール](../design.md)
- [texture モジュール](../texture/design.md) - init_textures(), init_colors()
- [raycasting モジュール](../raycasting/design.md) - init_hardcoded_map(), init_player()
- [ADR-0002: main.cのリファクタリング](../../../../decisions/0002-main-refactoring-separation-of-concerns.md)
