# texture サブモジュール

## 概要

壁面へのテクスチャマッピングと床・天井へのRGB色適用を担当するモジュール。

## 責務

- XPMテクスチャファイルの読み込みと管理
- テクスチャピクセルのサンプリング
- 壁の向きに応じたテクスチャ選択
- 床・天井色の管理

## 主な機能

### テクスチャ読み込み
- 4方向（北・南・東・西）のXPMテクスチャを読み込み
- MLXの`mlx_xpm_file_to_image()`を使用
- エラー時はメッセージを出力して終了

### テクスチャサンプリング
- 指定座標のピクセル色を取得
- 範囲外アクセスは黒（0）を返す

### テクスチャ選択
- レイの向き（`ray->side`, `ray->step_x/y`）に基づいて適切なテクスチャを選択

### 色管理
- 床・天井のRGB色を管理
- RGB構造体から0xRRGGBB形式に変換

## ファイル構成

```
srcs/engine/texture/
├── texture_init.c      - テクスチャ読み込み（3関数）
├── texture_utils.c     - テクスチャサンプリング（2関数）
└── texture_cleanup.c   - テクスチャ破棄（1関数）

srcs/engine/raycasting/
└── texture_coords.c    - テクスチャ座標計算（1関数）

includes/engine/
└── texture.h           - 公開関数宣言
```

## 使用方法

### 初期化

```c
// ゲーム初期化時（init_game.c内）
init_textures(game);  // テクスチャ読み込み
init_colors(game);    // 床・天井色設定
```

### レイキャスティングでの使用

```c
// レイキャスティングループ内（raycasting.c内）
calc_texture_coords(game, &ray);  // テクスチャ座標計算

// 描画時（ray_draw.c内）
t_img *texture = select_wall_texture(game, ray);
int color = get_texture_pixel(texture, ray->tex_x, tex_y);
```

### クリーンアップ

```c
// ゲーム終了時（cleanup.c内）
cleanup_textures(game);  // テクスチャ解放
```

## データ構造

### t_texture
```c
typedef struct s_texture {
    t_img   north;   // 北向き壁
    t_img   south;   // 南向き壁
    t_img   east;    // 東向き壁
    t_img   west;    // 西向き壁
    int     width;   // 2048
    int     height;  // 2048
} t_texture;
```

### t_color
```c
typedef struct s_color {
    int r;  // 赤（0-255）
    int g;  // 緑（0-255）
    int b;  // 青（0-255）
} t_color;
```

## 暫定実装

現在はパーサー未実装のため、テクスチャパスとRGB値をハードコーディングしています。

```c
// cub3d.hで定義
#define TEX_NORTH_PATH "assets/textures/cub3_North.xpm"
#define TEX_SOUTH_PATH "assets/textures/cub3_South.xpm"
#define TEX_EAST_PATH "assets/textures/cub3_East.xpm"
#define TEX_WEST_PATH "assets/textures/cub3_West.xpm"

#define CEILING_R 10   // 暗い青紫
#define CEILING_G 15
#define CEILING_B 35
#define FLOOR_R 230    // 青白い雪面
#define FLOOR_G 240
#define FLOOR_B 250
```

**パーサー統合後**: これらの定数は削除され、.cubファイルから値を取得します。

## テクスチャファイル

- **場所**: `assets/textures/`
- **有効ファイル**: `cub3_North.xpm`, `cub3_South.xpm`, `cub3_East.xpm`, `cub3_West.xpm`
- **サイズ**: 2048x2048ピクセル
- **フォーマット**: XPM（256色）
- **ファイルサイズ**: 約8MB/ファイル

## 関連ドキュメント

- [設計書](./design.md) - 詳細設計
- [ADR-0004](../../../../decisions/0004-texture-mapping-implementation.md) - 実装方針
- [raycasting モジュール](../raycasting/README.md) - レイキャスティング
- [engine モジュール](../README.md) - エンジン全体
