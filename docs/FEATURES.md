# cub3D 追加機能ドキュメント

## 概要

このドキュメントでは、cub3Dプロジェクトに実装された追加機能について説明します。

---

## 1. ミニマップ機能

### 概要
画面左上に150x150ピクセルのミニマップを表示し、プレイヤーの現在位置とマップ全体を一目で確認できます。

### 表示内容

| 要素 | 色 | 説明 |
|------|-----|------|
| 壁 | 白 (`0xFFFFFF`) | マップ上の壁 |
| 床 | 黒 (`0x000000`) | 通行可能な床 |
| 閉じたドア | 茶色 (`0x8B4513`) | 通行不可のドア |
| 開いたドア | 緑 (`0x00FF00`) | 通行可能なドア |
| プレイヤー | 赤 (`0xFF0000`) | 現在のプレイヤー位置（7x7ピクセル） |

### 技術的詳細

#### ファイル構成
- **実装**: `srcs/engine/renderer/minimap.c`
- **ヘッダー**: `includes/engine/minimap.h`
- **レンダリング**: `render_frame()` 内で `render_minimap()` を呼び出し

#### 動的スケーリング
マップのサイズに応じて自動的にタイルサイズを調整します。

```c
static int calculate_tile_size(t_game *game)
{
    int tile_w = MINIMAP_SIZE / game->map_width;
    int tile_h = MINIMAP_SIZE / game->map_height;
    return (tile_w < tile_h) ? tile_w : tile_h;
}
```

#### 定数
- `MINIMAP_SIZE`: 150 (ミニマップのサイズ)
- `MINIMAP_OFFSET`: 10 (画面左上からのオフセット)
- プレイヤードット半径: 3ピクセル（7x7の正方形）

### 使用方法
ミニマップは自動的に表示され、プレイヤーの移動に合わせてリアルタイムで更新されます。

---

## 2. ドア機能

### 概要
マップ内にドアを設置し、プレイヤーがEキーで開閉できる機能を提供します。

### マップファイルでの定義

#### 文字指定
マップファイルで `D` 文字を使用してドアを配置します。

```
1111111111111
1000000000001
1000000D00001  ← 'D' がドア
1000000000001
1000000N00001  ← 'N' がプレイヤー
1000000000001
1111111111111
```

#### 例: test_door.cub
```
NO assets/textures/nyan/north.xpm
SO assets/textures/nyan/south.xpm
WE assets/textures/nyan/west.xpm
EA assets/textures/nyan/east.xpm

F 255 , 255 , 255
C 0 , 100 , 200

1111111111111
1000000000001
1000000D00001
1000000000001
1000000N00001
1000000000001
1111111111111
```

### 操作方法

| キー | 動作 |
|------|------|
| E | プレイヤー前方のドアを開閉（範囲: 0.5～2.0マス） |

### ドアの挙動

#### 状態
- **閉じた状態（初期状態）**
  - プレイヤーの移動をブロック
  - レイキャスティングで壁として描画（茶色 `0x8B4513`）
  - ミニマップで茶色表示

- **開いた状態**
  - プレイヤーが通過可能
  - レイキャスティングで透過（描画しない）
  - ミニマップで緑色表示

#### 安全機能
**ドア閉じ込め防止**: プレイヤーがドアのセル内にいる場合、ドアを閉じることができません。

```c
// プレイヤーがドア内にいるかチェック
static int is_player_in_door(t_game *game, int door_x, int door_y)
{
    int player_map_x = (int)game->player.pos_x;
    int player_map_y = (int)game->player.pos_y;
    return (player_map_x == door_x && player_map_y == door_y);
}
```

### 技術的詳細

#### ファイル構成
- **実装**: `srcs/engine/door/door_manager.c`
- **ヘッダー**: `includes/engine/door.h`
- **パース**: `srcs/parse/map/parse_map_utils.c` で 'D' を有効文字として認識

#### データ構造

**t_game 構造体への追加**
```c
typedef struct s_game
{
    // ... 既存のフィールド
    bool    **door_state;   // ドアの開閉状態 [y][x]
    // ...
}   t_game;
```

**セルタイプの定義**
```c
typedef enum e_cell_type
{
    FLOOR = 0,
    WALL = 1,
    DOOR = 2
}   t_cell_type;
```

#### 主要関数

| 関数 | 説明 |
|------|------|
| `init_door_state()` | ドア状態配列を初期化（すべて閉じた状態） |
| `free_door_state()` | ドア状態配列のメモリを解放 |
| `toggle_door()` | ドアの開閉を切り替え（安全チェック付き） |
| `interact_door()` | プレイヤー前方のドアを検出して開閉 |

#### ドア検出アルゴリズム
プレイヤーの視線方向に0.5マス刻みで最大2.0マスまで検索し、最初に見つかったドアを開閉します。

```c
void interact_door(t_game *game)
{
    double distance = 0.5;
    while (distance <= 2.0)
    {
        check_x = game->player.pos_x + game->player.dir_x * distance;
        check_y = game->player.pos_y + game->player.dir_y * distance;
        map_x = (int)check_x;
        map_y = (int)check_y;

        if (is_valid_position && is_door)
        {
            toggle_door(game, map_x, map_y);
            return;
        }
        distance += 0.5;
    }
}
```

#### 衝突判定
閉じたドアは壁として扱い、開いたドアは床として扱います。

```c
static int is_blocked_cell(t_game *game, int map_x, int map_y)
{
    int cell_type = game->world_map[map_y][map_x];
    if (cell_type == WALL)
        return (1);
    if (cell_type == DOOR && !game->door_state[map_y][map_x])
        return (1);  // 閉じたドアは通行不可
    return (0);
}
```

#### レンダリング
閉じたドアは茶色の単色壁として描画されます。

```c
static void draw_door(t_game *game, t_ray *ray, int x)
{
    int door_color = 0x8B4513;  // 茶色
    // 天井、ドア、床を描画
}
```

---

## 3. 統合とビルド

### Makefile への追加
```makefile
SRCS = ... \
       $(SRC_DIR)/engine/door/door_manager.c \
       $(SRC_DIR)/engine/renderer/minimap.c \
       ...
```

### 初期化とクリーンアップ

**初期化順序** (`init_game.c`):
1. MLX初期化
2. 画像バッファ初期化
3. テクスチャ読み込み
4. 色設定
5. ワールドマップ変換
6. **ドア状態初期化** ← 追加
7. プレイヤー初期化

**クリーンアップ** (`cleanup.c`):
- `free_door_state(game)` を追加してメモリリークを防止

---

## 4. キーバインディング

### 追加されたキー

| OS | キーコード | 定数 | 機能 |
|----|----------|------|------|
| Linux | `XK_e` | `KEY_E` | ドア開閉 |
| macOS | `14` | `KEY_E` | ドア開閉 |

### 実装 (`key_handler.c`)
```c
int handle_keypress(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        close_window(game);
    else if (keycode == KEY_E)
        interact_door(game);  // ← 追加
    // ...
}
```

---

## 5. テストとデバッグ

### テストマップ
`assets/maps/Success/test_door.cub` を使用してドア機能をテストできます。

### メモリリーク確認
```bash
valgrind --leak-check=full --show-leak-kinds=all ./cub3D assets/maps/Success/test_door.cub
```

**結果**: メモリリークなし（definitely lost: 0 bytes）

### 動作確認項目
- [x] ミニマップが正しく表示される
- [x] プレイヤー位置がリアルタイムで更新される
- [x] ドアをEキーで開閉できる
- [x] 閉じたドアが移動をブロックする
- [x] 開いたドアを通過できる
- [x] ドア内でドアを閉じられない（閉じ込め防止）
- [x] ミニマップでドアの状態が色分けされる
- [x] メモリリークがない

---

## 6. 制限事項と既知の問題

### 制限事項
- ドアは単色（茶色）で描画され、テクスチャは使用しません
- 1つのマップに複数のドアを配置できますが、同時に操作できるのは1つのみです
- ドアのアニメーション（開閉中の動き）は実装されていません

### パフォーマンス
- ミニマップは毎フレーム再描画されますが、マップサイズが150x150以下の場合、パフォーマンスへの影響は最小限です

---

## 7. 今後の拡張案

### ミニマップ
- [ ] ミニマップの表示/非表示切り替え（Mキーなど）
- [ ] ミニマップサイズの調整機能
- [ ] プレイヤーの向きを矢印で表示
- [ ] 敵やアイテムの表示

### ドア
- [ ] ドアテクスチャの対応
- [ ] ドアの開閉アニメーション
- [ ] 自動ドア（近づくと自動で開く）
- [ ] ロックされたドア（鍵が必要）
- [ ] ドアの開閉音効果
- [ ] 複数タイプのドア（スライドドア、回転ドアなど）

---

## 8. 実装者向けノート

### コーディング規約
- 42 Normに準拠
- 関数は25行以内
- 1行80文字以内
- 適切な日本語コメント

### デバッグ用定義
開発中にデバッグ出力が必要な場合:
```c
#include <stdio.h>  // door_manager.c に追加
printf("Door toggled at (%d, %d), state: %d\n", map_x, map_y, state);
```

本番環境では削除してください。

---

## 9. 参考資料

### 関連ファイル一覧

#### 実装ファイル
- `srcs/engine/door/door_manager.c` - ドア管理
- `srcs/engine/renderer/minimap.c` - ミニマップ描画
- `srcs/engine/raycasting/ray_dda.c` - ドアのレイキャスティング対応
- `srcs/engine/raycasting/ray_draw.c` - ドアの描画
- `srcs/engine/player/player_movement.c` - ドアの衝突判定
- `srcs/engine/key_handler/key_handler.c` - Eキーハンドリング
- `srcs/engine/init/init_game.c` - ドア初期化
- `srcs/engine/init/init_map.c` - ワールドマップ変換
- `srcs/utils/cleanup.c` - ドアメモリ解放
- `srcs/parse/map/parse_map_utils.c` - 'D'文字の検証

#### ヘッダーファイル
- `includes/engine/door.h` - ドア関数宣言
- `includes/engine/minimap.h` - ミニマップ関数宣言
- `includes/cub3d.h` - 構造体定義

### Git コミット履歴
- `1eb877e` - feat: add minimap and door system
- `33c9fd3` - fix: prevent door trap bug and improve minimap

---

**最終更新**: 2026年1月5日
**バージョン**: 1.0.0
