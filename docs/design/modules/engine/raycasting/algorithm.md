# raycasting アルゴリズム

## 概要

DDA（Digital Differential Analyzer）を使った壁検出と描画。

## アルゴリズムの説明

### 入力

- プレイヤー位置 (pos_x, pos_y)
- プレイヤー方向 (dir_x, dir_y)
- カメラ平面 (plane_x, plane_y)
- マップ world_map[8][8]

### 出力

- 画面への3D描画（天井・壁・床）

### 処理手順

1. 画面の各x座標（0〜799）について以下を実行
2. レイの方向を計算（camera_x = 2*x/width - 1）
3. DDAの初期値設定（delta_dist, side_dist, step）
4. グリッドを進んで壁を検出
5. 壁までの垂直距離を計算（魚眼補正）
6. 壁の高さと描画範囲を計算
7. 天井（空色）→壁（灰色）→床（緑色）を描画

### 擬似コード

```
for x = 0 to WINDOW_WIDTH:
  camera_x = 2 * x / WINDOW_WIDTH - 1
  ray_dir = player.dir + player.plane * camera_x

  // DDA準備
  map_x = int(player.pos_x)
  map_y = int(player.pos_y)
  delta_dist = abs(1 / ray_dir)

  // ステップ方向と初期距離
  if ray_dir.x < 0:
    step_x = -1
    side_dist_x = (player.pos_x - map_x) * delta_dist_x
  else:
    step_x = 1
    side_dist_x = (map_x + 1 - player.pos_x) * delta_dist_x

  // 同様にY方向も計算

  // 壁を探す
  while not hit:
    if side_dist_x < side_dist_y:
      side_dist_x += delta_dist_x
      map_x += step_x
      side = 0
    else:
      side_dist_y += delta_dist_y
      map_y += step_y
      side = 1
    if world_map[map_y][map_x] > 0:
      hit = 1

  // 壁の距離と高さを計算
  perp_dist = (map - player.pos + offset) / ray_dir
  line_height = WINDOW_HEIGHT / perp_dist

  // 描画
  draw_ceiling(x, 0, draw_start)
  draw_wall(x, draw_start, draw_end)
  draw_floor(x, draw_end, WINDOW_HEIGHT)
```

## 計算量

- 時間計算量: O(W × D)
  - W = 画面幅（800）
  - D = 平均DDAステップ数（マップサイズ依存、最大8）
- 空間計算量: O(1)（画像バッファは別途必要）

## 参照

- [Lode's Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [設計](./design.md)
