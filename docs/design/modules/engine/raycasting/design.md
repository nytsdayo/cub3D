# raycasting サブモジュール設計

## 目的

パーサー完成前の独立動作可能な3D描画エンジンの実装。

## 責務

- ハードコードマップの管理
- プレイヤー状態の管理
- レイキャスティングによる描画

## インターフェース

### 公開関数

| 関数名 | 説明 | 引数 | 戻り値 |
|--------|------|------|--------|
| `init_hardcoded_map` | 8x8マップを初期化 | `t_game *game` | void |
| `init_player` | プレイヤーを初期化 | `t_game *game` | void |
| `cast_rays` | レイを飛ばして描画 | `t_game *game` | void |

## 内部設計

### データ構造

```c
typedef struct s_ray {
  double camera_x;
  double ray_dir_x, ray_dir_y;
  int map_x, map_y;
  double side_dist_x, side_dist_y;
  double delta_dist_x, delta_dist_y;
  double perp_wall_dist;
  int step_x, step_y;
  int hit, side;
  int line_height, draw_start, draw_end;
} t_ray;
```

### ファイル構成

```
srcs/engine/raycasting/
├── init.c           - init_hardcoded_map(), init_player()
└── raycasting.c     - cast_rays() とヘルパー関数
```

### 色定義

- 天井: `0x87CEEB`
- 壁（X側）: `0x999999`
- 壁（Y側）: `0x666666`
- 床: `0x228B22`

## エラーハンドリング

- DDA中のマップ範囲外アクセスチェック
- 画像バッファへの描画時の座標範囲チェック

## 参照

- [README](./README.md)
- [algorithm](./algorithm.md)
- [engine モジュール](../README.md)
