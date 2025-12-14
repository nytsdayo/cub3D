# input サブモジュール設計

## 目的

キーボード入力の処理を担当するサブモジュール。
キーの押下・解放イベントを監視し、連続キー押下に対応することで、スムーズなプレイヤー操作を実現する。

## 責務

- **キー状態管理**: キーの押下・解放状態を追跡
- **イベントハンドリング**: MinilibXのキーイベントを処理
- **フレームごとの入力処理**: 押されているキーに応じてプレイヤー操作関数を呼び出し
- **ウィンドウ制御**: ウィンドウを閉じる処理

## インターフェース

### 公開関数

| 関数名 | 説明 | 引数 | 戻り値 |
|--------|------|------|--------|
| `handle_keypress` | キーが押されたときのイベントハンドラ | `int keycode, t_game *game` | `int` (0) |
| `handle_keyrelease` | キーが離されたときのイベントハンドラ | `int keycode, t_game *game` | `int` (0) |
| `process_held_keys` | 押されているキーを処理してプレイヤーを操作 | `t_game *game` | `void` |
| `close_window` | ウィンドウを閉じる | `t_game *game` | `int` (0) |

### 内部関数

| 関数名 | 説明 | 引数 | 戻り値 |
|--------|------|------|--------|
| `platform_close` | プラットフォーム固有のウィンドウクローズ処理 (static) | `t_game *game` | `void` |

## 内部設計

### キー状態管理

**データ構造:**
```c
// t_game 構造体内
int keys[256];  // キーの押下状態 (0: 解放, 1: 押下)
```

**イベントハンドリング:**
```c
int handle_keypress(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        close_window(game);  // ESCは即座に終了
    else if (keycode >= 0 && keycode < 256)
        game->keys[keycode] = 1;  // キー押下を記録
    return (0);
}

int handle_keyrelease(int keycode, t_game *game)
{
    if (keycode >= 0 && keycode < 256)
        game->keys[keycode] = 0;  // キー解放を記録
    return (0);
}
```

### フレームごとの処理

`process_held_keys()` は `render_frame()` から毎フレーム呼び出される：

```c
void process_held_keys(t_game *game)
{
    // 押されているキーをチェックして対応する処理を実行
    if (game->keys[KEY_W])
        move_forward(game);
    if (game->keys[KEY_S])
        move_backward(game);
    if (game->keys[KEY_A])
        move_left(game);
    if (game->keys[KEY_D])
        move_right(game);
    if (game->keys[KEY_LEFT])
        rotate_left(game);
    if (game->keys[KEY_RIGHT])
        rotate_right(game);
}
```

**利点:**
- 複数キーの同時押しに対応
- フレームレートに同期した安定した動作
- OSのキーリピート設定に依存しない

### ウィンドウクローズ処理

プラットフォームごとに異なる終了処理を実装：

```c
#ifdef __linux__
static void platform_close(t_game *game)
{
    mlx_loop_end(game->mlx);  // Linuxはループを終了
}
#else
static void platform_close(t_game *game)
{
    cleanup_game(game);  // macOSはクリーンアップして終了
    exit(0);
}
#endif
```

## ファイル構成

```
srcs/engine/input/
└── input.c              # 入力処理（4関数 + 1内部関数）
    ├── handle_keypress()
    ├── handle_keyrelease()
    ├── process_held_keys()
    ├── close_window()
    └── platform_close() (static)

includes/engine/
└── input.h              # 入力処理の関数プロトタイプ
```

## 使用方法

### ゲームループでの設定

`game_loop.c` でイベントフックを設定：

```c
void setup_event_hooks(t_game *game)
{
    mlx_hook(game->win, ON_KEYDOWN, 1L<<0, handle_keypress, game);
    mlx_hook(game->win, ON_KEYUP, 1L<<1, handle_keyrelease, game);
    mlx_hook(game->win, ON_DESTROY, 0, close_window, game);
    mlx_loop_hook(game->mlx, render_frame, game);
}
```

### レンダーフレームでの呼び出し

`render_frame.c` で毎フレーム `process_held_keys()` を呼び出す：

```c
int render_frame(t_game *game)
{
    process_held_keys(game);  // 入力処理
    // レイキャスティング + 描画処理
    // ...
    return (0);
}
```

## キーコード定義

```c
// cub3d.h で定義
#ifdef __linux__
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
#else
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
#endif
```

## エラーハンドリング

- **範囲外チェック**: キーコードが 0-255 の範囲内かチェック
- **ESC特別処理**: ESCキーは即座にウィンドウを閉じる
- **プラットフォーム対応**: Linux/macOSで異なる終了処理を実装

## パフォーマンス考慮

- キー状態配列のアクセスは O(1) （高速）
- 毎フレーム最大6つのキーチェック（定数時間）
- プレイヤー操作関数は押されているキーの場合のみ呼び出し

## 将来の拡張

- マウス入力のサポート
- キーバインドのカスタマイズ機能
- ゲームパッドのサポート
- 入力リプレイ機能（デバッグ用）

## 参照

- [engine モジュール設計](../design.md)
- [player モジュール設計](../player/design.md)
- [ADR-0003: プレイヤー移動・回転の実装方針](../../../../decisions/0003-player-movement-implementation.md)