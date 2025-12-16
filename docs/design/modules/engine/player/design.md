# player サブモジュール設計

## 目的

プレイヤーの移動、回転、衝突判定を担当するサブモジュール。
キーボード入力に応じてプレイヤーの位置と向きを更新し、壁との衝突を検出して不正な移動を防ぐ。

## 責務

- **移動処理**: WASD キーによる前後左右の移動
- **回転処理**: 矢印キーによる視点の回転（左右）
- **衝突判定**: マップの壁チェックと移動可能位置の検証

## インターフェース

### 公開関数

| 関数名 | 説明 | 引数 | 戻り値 |
|--------|------|------|--------|
| `move_forward` | プレイヤーを前方に移動（方向ベクトルに沿って） | `t_game *game` | `void` |
| `move_backward` | プレイヤーを後方に移動 | `t_game *game` | `void` |
| `move_left` | プレイヤーを左に移動（カメラ平面の逆方向、ストレイフ） | `t_game *game` | `void` |
| `move_right` | プレイヤーを右に移動（カメラ平面方向、ストレイフ） | `t_game *game` | `void` |
| `rotate_left` | プレイヤーを左に回転（反時計回り） | `t_game *game` | `void` |
| `rotate_right` | プレイヤーを右に回転（時計回り） | `t_game *game` | `void` |

### 内部関数

| 関数名 | 説明 | 引数 | 戻り値 |
|--------|------|------|--------|
| `is_wall` | 指定された位置が壁かどうかをチェック（バウンディングボックス4コーナー） | `t_game *game, double x, double y` | `int` (1: 壁, 0: 通行可能) |

## 内部設計

### 移動処理

各移動関数は以下の流れで処理を行う：

```
1. 新しい位置を計算（現在位置 + 方向ベクトル * 移動速度）
2. X軸とY軸を個別に is_wall() で衝突判定
3. 各軸が通行可能な場合のみその軸の位置を更新
```

**X/Y軸分離チェックの利点：**
- 斜めに壁に当たった際も壁に沿ってスライドできる
- より自然な移動感覚

#### 移動方向の計算

- **前進/後進**: 方向ベクトル (`dir_x`, `dir_y`) に沿って移動
  ```c
  new_x = pos_x ± dir_x * MOVE_SPEED
  new_y = pos_y ± dir_y * MOVE_SPEED
  // X軸とY軸を個別にチェック
  if (!is_wall(game, new_x, pos_y))
      pos_x = new_x;
  if (!is_wall(game, pos_x, new_y))
      pos_y = new_y;
  ```

- **左右移動（ストレイフ）**: カメラ平面 (`plane_x`, `plane_y`) に沿って移動
  ```c
  new_x = pos_x ± plane_x * MOVE_SPEED
  new_y = pos_y ± plane_y * MOVE_SPEED
  // X軸とY軸を個別にチェック
  if (!is_wall(game, new_x, pos_y))
      pos_x = new_x;
  if (!is_wall(game, pos_x, new_y))
      pos_y = new_y;
  ```

### 回転処理

回転行列を使用して方向ベクトルとカメラ平面を変換：

```
回転行列（角度θ）:
| cos(θ)  -sin(θ) |
| sin(θ)   cos(θ) |

新しい方向ベクトル:
new_dir_x = dir_x * cos(θ) - dir_y * sin(θ)
new_dir_y = dir_x * sin(θ) + dir_y * cos(θ)

新しいカメラ平面:
new_plane_x = plane_x * cos(θ) - plane_y * sin(θ)
new_plane_y = plane_x * sin(θ) + plane_y * cos(θ)
```

- **左回転**: `θ = ROT_SPEED` （正の角度、反時計回り）
- **右回転**: `θ = -ROT_SPEED` （負の角度、時計回り）

### 衝突判定

`is_wall(game, x, y)` の処理：

**バウンディングボックス4コーナーチェック方式**

```
1. プレイヤーのバウンディングボックス4コーナーの座標を計算
   x1 = (int)(x - COLLISION_MARGIN)  // 左上
   x2 = (int)(x + COLLISION_MARGIN)  // 右上
   y1 = (int)(y - COLLISION_MARGIN)  // 左下
   y2 = (int)(y + COLLISION_MARGIN)  // 右下

2. マップ範囲外チェック
   if (x1 < 0 || x2 >= MAP_WIDTH || y1 < 0 || y2 >= MAP_HEIGHT)
       return 1  // 壁扱い

3. 4コーナーすべてが壁でないかチェック
   if (game->world_map[y1][x1] != 0) return 1
   if (game->world_map[y1][x2] != 0) return 1
   if (game->world_map[y2][x1] != 0) return 1
   if (game->world_map[y2][x2] != 0) return 1

4. すべて通行可能
   return 0
```

**利点：**
- プレイヤーの当たり判定が点ではなく矩形となり、壁へのクリッピングを防止
- より現実的な衝突判定

### 定数

```c
#define MOVE_SPEED 0.1           // 移動速度（1フレームあたりの移動量）
#define ROT_SPEED 0.05           // 回転速度（ラジアン、約2.86度）
#define COLLISION_MARGIN 0.2     // プレイヤーの当たり判定マージン（半径）
```

## ファイル構成

```
srcs/engine/player/
├── player_movement.c   # 移動処理（前後左右）
└── player_rotation.c   # 回転処理（左右）

includes/engine/
└── player.h            # プレイヤー操作の関数プロトタイプ
```

## 使用方法

キーボード入力は `key_handler.c` で処理され、連続キー押下に対応：

**キー状態の管理：**
```c
// handle_keypress() - キーを押したときに呼ばれる
int handle_keypress(int keycode, t_game *game)
{
    if (keycode >= 0 && keycode < 256)
        game->keys[keycode] = 1;  // キー押下状態を記録
    return (0);
}

// handle_keyrelease() - キーを離したときに呼ばれる
int handle_keyrelease(int keycode, t_game *game)
{
    if (keycode >= 0 && keycode < 256)
        game->keys[keycode] = 0;  // キー解放状態を記録
    return (0);
}
```

**毎フレーム処理：**
```c
// process_held_keys() - render_frame() で毎フレーム呼ばれる
void process_held_keys(t_game *game)
{
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

この方式により、キーを押し続けることでスムーズな連続移動が可能になる。

## キーバインド

| キー | 動作 |
|------|------|
| W | 前進 |
| S | 後退 |
| A | 左移動（ストレイフ） |
| D | 右移動（ストレイフ） |
| 左矢印 | 左回転 |
| 右矢印 | 右回転 |
| ESC | 終了 |

## エラーハンドリング

- **範囲外チェック**: マップの境界を超える移動は `is_wall()` で拒否
- **壁衝突**: 壁のマスへの移動は拒否（4コーナーのいずれかが壁の場合）
- **無効な移動**: 移動が拒否された場合、プレイヤーの位置は更新されない（安全）
- **軸ごとの判定**: X軸とY軸を個別にチェックするため、片方が壁でももう片方に移動可能

## パフォーマンス考慮

- 移動・回転は1フレームごとに呼ばれるため、計算は最小限に抑える
- `cos()` と `sin()` の計算は回転時のみ（移動時は不要）
- 衝突判定は単純な配列アクセスのみ（高速）

## 将来の拡張

- マウスによる視点回転
- ジャンプ・しゃがみ（ボーナス）
- スプリント（移動速度の変更）
- より高度な衝突判定（壁との距離を考慮）

## 参照

- [README](./README.md)
- [engine モジュール](../README.md)
- [Lode's Raycasting Tutorial - Input and Collision](https://lodev.org/cgtutor/raycasting.html)