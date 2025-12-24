# texture サブモジュール設計

## 目的

壁面へのテクスチャマッピングと床・天井へのRGB色適用を実現する。

## 責務

- XPMテクスチャファイルの読み込みと管理
- テクスチャピクセルのサンプリング
- 壁の向きに応じたテクスチャ選択
- 床・天井色の管理
- テクスチャリソースの解放

## インターフェース

### 公開関数

| 関数名 | 説明 | 引数 | 戻り値 |
|--------|------|------|--------|
| `init_textures` | 4方向のテクスチャを読み込む | `t_game *game` | void |
| `load_texture` | XPMファイルから1つのテクスチャを読み込む | `t_game *game, t_img *texture, char *path` | void |
| `init_colors` | 床・天井の色を初期化 | `t_game *game` | void |
| `get_texture_pixel` | テクスチャから指定座標のピクセル色を取得 | `t_img *texture, int x, int y` | int (color) |
| `select_wall_texture` | レイの向きに応じてテクスチャを選択 | `t_game *game, t_ray *ray` | t_img * |
| `cleanup_textures` | すべてのテクスチャを解放 | `t_game *game` | void |

## 内部設計

### データ構造

```c
// テクスチャ構造体
typedef struct s_texture
{
    t_img   north;   // 北向き壁のテクスチャ
    t_img   south;   // 南向き壁のテクスチャ
    t_img   east;    // 東向き壁のテクスチャ
    t_img   west;    // 西向き壁のテクスチャ
    int     width;   // テクスチャの幅（2048）
    int     height;  // テクスチャの高さ（2048）
} t_texture;

// 色構造体
typedef struct s_color
{
    int r;  // 赤成分（0-255）
    int g;  // 緑成分（0-255）
    int b;  // 青成分（0-255）
} t_color;
```

### ファイル構成

```
srcs/engine/texture/
├── texture_init.c      - init_textures(), load_texture(), init_colors()
├── texture_utils.c     - get_texture_pixel(), select_wall_texture()
└── texture_cleanup.c   - cleanup_textures()

srcs/engine/raycasting/
└── texture_coords.c    - calc_texture_coords()

includes/engine/
└── texture.h           - 公開関数のプロトタイプ
```

### テクスチャ読み込み処理

#### init_textures()

4方向のテクスチャを一括で読み込む。

```c
void init_textures(t_game *game)
{
    game->textures.width = TEX_WIDTH;
    game->textures.height = TEX_HEIGHT;
    load_texture(game, &game->textures.north, TEX_NORTH_PATH);
    load_texture(game, &game->textures.south, TEX_SOUTH_PATH);
    load_texture(game, &game->textures.east, TEX_EAST_PATH);
    load_texture(game, &game->textures.west, TEX_WEST_PATH);
}
```

#### load_texture()

MLXの`mlx_xpm_file_to_image()`を使用してXPMファイルを読み込む。

**処理フロー:**
1. `mlx_xpm_file_to_image()`でXPMファイルを読み込み
2. エラーチェック（ファイルが見つからない場合は終了）
3. `mlx_get_data_addr()`でピクセルデータのアドレスを取得
4. `t_img`構造体にすべての情報を格納

**エラーハンドリング:**
- ファイルが見つからない場合: エラーメッセージを出力して`exit(EXIT_FAILURE)`

### テクスチャサンプリング処理

#### get_texture_pixel()

テクスチャから指定座標のピクセル色を取得する。

**引数:**
- `texture`: テクスチャ画像
- `x`: テクスチャX座標（0 ~ TEX_WIDTH-1）
- `y`: テクスチャY座標（0 ~ TEX_HEIGHT-1）

**戻り値:**
- ピクセルの色（0xRRGGBB形式）
- 範囲外の場合は0（黒）

**実装:**
```c
int get_texture_pixel(t_img *texture, int x, int y)
{
    char *pixel;

    if (x < 0 || x >= TEX_WIDTH || y < 0 || y >= TEX_HEIGHT)
        return (0);
    pixel = texture->addr + (y * texture->line_length
            + x * (texture->bits_per_pixel / 8));
    return (*(unsigned int *)pixel);
}
```

#### select_wall_texture()

レイの向きに基づいて適切なテクスチャを選択する。

**判定ロジック:**
- `ray->side == 0 && ray->step_x > 0` → **東**壁
- `ray->side == 0 && ray->step_x < 0` → **西**壁
- `ray->side == 1 && ray->step_y > 0` → **南**壁
- `ray->side == 1 && ray->step_y < 0` → **北**壁

**戻り値:**
- 対応する方向のテクスチャへのポインタ

### テクスチャ座標計算

#### calc_texture_coords()

**配置**: `srcs/engine/raycasting/texture_coords.c`

レイが壁に当たった位置から、テクスチャのX座標を計算する。

**計算手順:**

1. **wall_x計算** - 壁のどこに当たったか（0.0 ~ 1.0）
   ```c
   if (ray->side == 0)  // X側の壁
       ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
   else                 // Y側の壁
       ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
   ray->wall_x -= floor(ray->wall_x);  // 小数部分のみ取得
   ```

2. **tex_x計算** - テクスチャピクセル座標に変換
   ```c
   ray->tex_x = (int)(ray->wall_x * TEX_WIDTH);
   ```

3. **ミラーリング** - 向きによって反転
   ```c
   if ((ray->side == 0 && ray->ray_dir_x > 0) ||
       (ray->side == 1 && ray->ray_dir_y < 0))
       ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
   ```

**理由:**
- レイキャスティングパイプラインの一部として扱う
- `t_ray`構造体に直接書き込む
- `calc_wall_distance()`, `calc_line_height()`と同じ階層

### 色管理

#### init_colors()

床と天井の色を初期化する。

**暫定実装:**
```c
void init_colors(t_game *game)
{
    game->ceiling_color.r = CEILING_R;  // 10
    game->ceiling_color.g = CEILING_G;  // 15
    game->ceiling_color.b = CEILING_B;  // 35
    game->floor_color.r = FLOOR_R;      // 230
    game->floor_color.g = FLOOR_G;      // 240
    game->floor_color.b = FLOOR_B;      // 250
}
```

**パーサー統合後:**
- パーサーが.cubファイルから`F`（床）と`C`（天井）のRGB値を読み込む
- `init_colors()`は削除し、パーサーが直接`game->*_color`を設定

#### create_rgb_color()

RGB構造体から0xRRGGBB形式の色を作成する。

**実装:**
```c
static int create_rgb_color(t_color color)
{
    return ((color.r << 16) | (color.g << 8) | color.b);
}
```

**配置:** `ray_draw.c`内のstatic関数

### クリーンアップ処理

#### cleanup_textures()

すべてのテクスチャ画像を解放する。

**処理順序:**
1. 各テクスチャ（north, south, east, west）について：
   - `mlx_destroy_image()`でMLX画像を破棄
2. `cleanup_game()`の最初に呼び出される（MLX破棄の前）

**重要:** テクスチャは`game->mlx`を使用するため、MLX自体を破棄する前に解放する必要がある。

### レイキャスティングパイプラインとの統合

#### 統合ポイント

1. **初期化** (`init_game.c`)
   ```c
   init_image(game);
   init_textures(game);  // ← ここで追加
   init_colors(game);    // ← ここで追加
   ```

2. **レイキャスティング** (`raycasting.c`)
   ```c
   calc_line_height(&ray);
   calc_texture_coords(game, &ray);  // ← ここで追加
   draw_vertical_line(game, &ray, x);
   ```

3. **描画** (`ray_draw.c`)
   - 天井: `create_rgb_color(game->ceiling_color)`
   - 壁: `get_texture_pixel(texture, ray->tex_x, tex_y)`
   - 床: `create_rgb_color(game->floor_color)`

4. **クリーンアップ** (`cleanup.c`)
   ```c
   cleanup_textures(game);  // ← 最初に実行
   // ... 他のクリーンアップ
   ```

### 定数

```c
// テクスチャサイズ
#define TEX_WIDTH 2048
#define TEX_HEIGHT 2048

// テクスチャパス（暫定 - パーサー統合後に削除）
#define TEX_NORTH_PATH "assets/textures/cub3_North.xpm"
#define TEX_SOUTH_PATH "assets/textures/cub3_South.xpm"
#define TEX_EAST_PATH "assets/textures/cub3_East.xpm"
#define TEX_WEST_PATH "assets/textures/cub3_West.xpm"

// RGB値（暫定 - パーサー統合後に削除）
#define CEILING_R 10    // 暗い青紫
#define CEILING_G 15
#define CEILING_B 35
#define FLOOR_R 230     // 青白い雪面
#define FLOOR_G 240
#define FLOOR_B 250
```

## パフォーマンス考慮事項

### テクスチャサイズ

- **2048x2048ピクセル** = 4,194,304ピクセル
- **32ビット色** = 4バイト/ピクセル
- **1テクスチャ** = 約16MB
- **4テクスチャ** = 約64MB（実際のXPMファイルは8MB × 4 = 32MB）

### 最適化

1. **ビット演算によるY座標計算**
   ```c
   tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
   ```
   - `% TEX_HEIGHT`より高速（2048は2の累乗）

2. **MLXのキャッシング**
   - MLXが内部でテクスチャをキャッシュ
   - 同じテクスチャの繰り返しアクセスは高速

3. **メモリアクセスパターン**
   - テクスチャは連続したメモリ領域
   - キャッシュフレンドリー

## エラーハンドリング

### テクスチャ読み込みエラー

```c
if (!texture->img)
{
    write(2, "Error\nTexture loading failed: ", 30);
    write(2, path, ft_strlen(path));
    write(2, "\n", 1);
    exit(EXIT_FAILURE);
}
```

### 範囲外アクセス

```c
if (x < 0 || x >= TEX_WIDTH || y < 0 || y >= TEX_HEIGHT)
    return (0);  // 黒を返す
```

## 将来の拡張

### パーサー統合時の修正

1. **定数削除**
   - `TEX_*_PATH`定数を削除
   - `CEILING_R/G/B`, `FLOOR_R/G/B`定数を削除

2. **初期化の変更**
   - `init_textures()`, `init_colors()`を削除
   - パーサーが`game->textures`と`game->*_color`を設定

3. **インターフェース追加**
   - パーサーから呼び出すための`load_texture()`は公開関数として維持

### 将来の機能

- **スプライト**: 敵、アイテムのテクスチャマッピング
- **アニメーション**: 複数フレームのテクスチャ切り替え
- **スカイボックス**: 天井テクスチャマッピング
- **床テクスチャ**: 床面へのテクスチャマッピング

## 参照

- [README](./README.md)
- [raycasting サブモジュール](../raycasting/design.md)
- [engine モジュール](../design.md)
- [ADR-0004: テクスチャマッピングの実装方針](../../../../decisions/0004-texture-mapping-implementation.md)
