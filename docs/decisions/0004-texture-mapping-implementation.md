# ADR-0004: テクスチャマッピングの実装方針

## ステータス

**承認済み** (2025-12-19)

## コンテキスト

cub3Dプロジェクトで壁面にテクスチャマッピングを実装し、床・天井にRGB色を適用する必要がある。以下の要件を満たす必要がある：

1. 東西南北4方向の壁にそれぞれ異なるテクスチャを適用
2. 床・天井はRGB値で色を指定
3. 2048x2048ピクセルの大型XPMテクスチャを処理
4. 42 Norm 準拠（5関数/ファイル、25行/関数など）
5. パフォーマンス（毎フレーム800x600ピクセルを描画）
6. パーサー未実装のため、一時的にハードコーディング

## 検討した選択肢

### 選択肢 1: 既存のray_draw.cにすべての処理を追加（不採用）

**利点:**
- ファイル数が増えない
- シンプルな構造

**欠点:**
- ray_draw.cが肥大化し、Norm違反のリスク（5関数制限超過）
- テクスチャ読み込み、サンプリング、座標計算が混在
- 責務の分離ができない
- テストが困難

### 選択肢 2: textureモジュールとして分離（採用）

**利点:**
- 単一責任原則に従う
- テクスチャ関連の処理が1箇所に集約
- Norm準拠しやすい（機能ごとにファイル分割）
- 拡張性が高い（スプライト、スカイボックスなど追加可能）
- テストが容易

**欠点:**
- ファイル数が増える
- モジュール間の依存関係が発生

### 選択肢 3: テクスチャファイルの扱い

#### 方式A: パーサーから受け取る（将来の実装）

**メリット:**
- .cubファイルで柔軟にテクスチャを指定可能
- 複数のマップで異なるテクスチャを使用可能

**デメリット:**
- パーサーが未実装

#### 方式B: ハードコーディング（暫定実装・採用）

**メリット:**
- パーサー完成を待たずに実装・テスト可能
- 独立して動作確認できる

**デメリット:**
- 後でパーサー統合時に修正が必要

**決定:** 方式Bを暫定実装とし、パーサー完成後に方式Aに移行

### 選択肢 4: テクスチャ座標計算の配置

#### 方式A: texture_coords.cをtextureディレクトリに配置（不採用）

**デメリット:**
- レイキャスティングロジックと分離される
- 依存関係が複雑になる

#### 方式B: texture_coords.cをraycastingディレクトリに配置（採用）

**メリット:**
- レイキャスティングパイプラインの一部として扱える
- t_ray構造体への依存が明確
- calc_wall_distance(), calc_line_height()と同じ階層

## 決定

以下の方針を採用：
- **選択肢 2**: `texture` モジュールとして独立させる
- **選択肢 3B**: テクスチャパスとRGB値を一時的にハードコーディング
- **選択肢 4B**: texture_coords.cをraycastingディレクトリに配置

### 実装詳細

#### ファイル構成

```
srcs/engine/
├── texture/
│   ├── texture_init.c       # テクスチャ読み込み（3関数）
│   │   ├── load_texture()
│   │   ├── init_textures()
│   │   └── init_colors()
│   ├── texture_utils.c      # テクスチャサンプリング（2関数）
│   │   ├── get_texture_pixel()
│   │   └── select_wall_texture()
│   └── texture_cleanup.c    # テクスチャ破棄（1関数）
│       └── cleanup_textures()
└── raycasting/
    └── texture_coords.c     # テクスチャ座標計算（1関数）
        └── calc_texture_coords()

includes/engine/
└── texture.h                # テクスチャ関数プロトタイプ
```

#### データ構造

```c
// テクスチャ構造体
typedef struct s_texture {
    t_img   north;
    t_img   south;
    t_img   east;
    t_img   west;
    int     width;
    int     height;
} t_texture;

// 色構造体（床・天井）
typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

// t_gameに追加
typedef struct s_game {
    // ... 既存フィールド
    t_texture   textures;
    t_color     floor_color;
    t_color     ceiling_color;
} t_game;

// t_rayに追加
typedef struct s_ray {
    // ... 既存フィールド
    double  wall_x;  // テクスチャX座標（0.0-1.0）
    int     tex_x;   // テクスチャピクセルX
} t_ray;
```

#### テクスチャ読み込み

- **MLX関数**: `mlx_xpm_file_to_image()`を使用
- **タイミング**: `init_game()`内、`init_image()`の直後
- **エラー処理**: ファイルが見つからない場合はエラーメッセージを出力して終了

#### テクスチャ座標計算

```c
void calc_texture_coords(t_game *game, t_ray *ray)
{
    // 壁のどこに当たったか計算（0.0-1.0）
    if (ray->side == 0)  // X側の壁
        ray->wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else                 // Y側の壁
        ray->wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;

    ray->wall_x -= floor(ray->wall_x);  // 小数部分のみ取得

    // テクスチャピクセル座標に変換
    ray->tex_x = (int)(ray->wall_x * TEX_WIDTH);

    // 向きによってミラーリング
    if ((ray->side == 0 && ray->ray_dir_x > 0) ||
        (ray->side == 1 && ray->ray_dir_y < 0))
        ray->tex_x = TEX_WIDTH - ray->tex_x - 1;
}
```

#### テクスチャサンプリング

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

#### 壁の向き検出とテクスチャ選択

```c
t_img *select_wall_texture(t_game *game, t_ray *ray)
{
    if (ray->side == 0)  // X側（東西）
    {
        if (ray->step_x > 0)
            return (&game->textures.east);
        else
            return (&game->textures.west);
    }
    else  // Y側（南北）
    {
        if (ray->step_y > 0)
            return (&game->textures.south);
        else
            return (&game->textures.north);
    }
}
```

#### 描画処理の更新

```c
void draw_vertical_line(t_game *game, t_ray *ray, int x)
{
    int     y, tex_y;
    double  step, tex_pos;
    t_img   *texture;

    // 天井（RGB色）
    y = 0;
    while (y < ray->draw_start)
        put_pixel(game, x, y++, create_rgb_color(game->ceiling_color));

    // 壁（テクスチャ）
    texture = select_wall_texture(game, ray);
    step = (double)TEX_HEIGHT / ray->line_height;
    tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2
               + ray->line_height / 2) * step;

    while (y <= ray->draw_end)
    {
        tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
        tex_pos += step;
        put_pixel(game, x, y++, get_texture_pixel(texture, ray->tex_x, tex_y));
    }

    // 床（RGB色）
    while (y < WINDOW_HEIGHT)
        put_pixel(game, x, y++, create_rgb_color(game->floor_color));
}
```

#### 定数

```c
// テクスチャサイズ
#define TEX_WIDTH 2048
#define TEX_HEIGHT 2048

// テクスチャパス（暫定）
#define TEX_NORTH_PATH "assets/textures/cub3_North.xpm"
#define TEX_SOUTH_PATH "assets/textures/cub3_South.xpm"
#define TEX_EAST_PATH "assets/textures/cub3_East.xpm"
#define TEX_WEST_PATH "assets/textures/cub3_West.xpm"

// RGB値（暫定）
#define CEILING_R 10
#define CEILING_G 15
#define CEILING_B 35
#define FLOOR_R 230
#define FLOOR_G 240
#define FLOOR_B 250
```

#### レイキャスティングパイプライン統合

```c
void cast_rays(t_game *game)
{
    t_ray ray;
    int x = 0;

    while (x < WINDOW_WIDTH)
    {
        init_ray(game, &ray, x);
        calc_step_and_side_dist(game, &ray);
        perform_dda(game, &ray);
        calc_wall_distance(game, &ray);
        calc_line_height(&ray);
        calc_texture_coords(game, &ray);  // ← 追加
        draw_vertical_line(game, &ray, x);
        x++;
    }
}
```

## 結果

### 正の影響

1. **Norm準拠**:
   - 各ファイルは5関数以下
   - 各関数は25行以下
   - Norminette チェック合格

2. **視覚的改善**:
   - 壁面に詳細なテクスチャが表示され、没入感が向上
   - 方向ごとに異なるテクスチャで空間認識が容易
   - 床・天井の色をカスタマイズ可能

3. **保守性向上**:
   - テクスチャ関連の処理が texture モジュールに集約
   - 各ファイルの責務が明確
   - テストが容易

4. **拡張性**:
   - スプライト（敵、アイテム）の追加が容易
   - スカイボックスの実装が可能
   - アニメーションテクスチャの追加が可能

5. **パフォーマンス**:
   - テクスチャサンプリングは単純なメモリアクセス
   - ビット演算による高速なY座標計算（`& (TEX_HEIGHT - 1)`）
   - MLXがXPM読み込みとキャッシュを処理

### 負の影響

1. **メモリ使用量増加**:
   - 4つのテクスチャで約32MB（8MB × 4）
   - 対処: 42スクールのマシンでは問題なし

2. **ファイル数増加**:
   - texture モジュールで4ファイル追加
   - 対処: ディレクトリ構造で整理

3. **暫定実装の技術的負債**:
   - ハードコーディングされたパスとRGB値
   - 対処: パーサー統合時に置き換え

### 対処策

- **パーサー統合時の修正手順**:
  1. `TEX_*_PATH` 定数を削除
  2. `CEILING_R/G/B`, `FLOOR_R/G/B` 定数を削除
  3. `init_textures()`, `init_colors()` をパーサー呼び出しに置き換え
  4. パーサーが `game->textures` と `game->*_color` を設定

## 関連決定

- [ADR-0002: main.cのリファクタリング](./0002-main-refactoring-separation-of-concerns.md)
  - エンジンモジュールの分離方針に従う
- [ADR-0003: プレイヤー移動・回転の実装方針](./0003-player-movement-implementation.md)
  - モジュール分離の設計パターンを踏襲

## 参照

- [texture モジュール設計](../design/modules/engine/texture/design.md)
- [raycasting モジュール設計](../design/modules/engine/raycasting/design.md)
- [Lode's Raycasting Tutorial - Textures](https://lodev.org/cgtutor/raycasting.html)
- [42 Norm](https://github.com/42School/norminette)

## メモ

- テクスチャファイルは2048x2048ピクセル、256色のXPM形式
- パーサー統合後は.cubファイルで指定されたパスから読み込む予定
- 床・天井のテクスチャマッピングは将来の拡張として検討可能

### 実装後の改善履歴

- **2025-12-19**: テクスチャマッピング実装完了
  - 4方向の壁テクスチャ対応
  - 床・天井RGB色対応
  - Norm準拠、ビルド成功
