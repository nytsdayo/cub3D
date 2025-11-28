# レイキャスティング実装ガイド

## 概要
このガイドは、cub3Dでレイキャスティングを実装するための最小限の説明です。

## コアコンセプト

### 1. レイキャスティングとは
スクリーンの各列ごとに1本の「レイ（光線）」を飛ばし、壁に当たるまでの距離を計算する。
距離が近い → 壁は大きく表示
距離が遠い → 壁は小さく表示

```
プレイヤー
    |
    | レイ
    |
    ↓
   壁
```

### 2. アルゴリズムの流れ

```
for (各スクリーン列 x = 0 to SCREEN_WIDTH) {
  1. レイの方向を計算
  2. DDAアルゴリズムで壁を探す
  3. 壁までの距離を計算
  4. 壁の高さを計算: height = SCREEN_HEIGHT / distance
  5. 壁を描画
}
```

### 3. 重要な変数

| 変数 | 説明 |
|------|------|
| `posX, posY` | プレイヤーの位置 |
| `dirX, dirY` | プレイヤーの向き（方向ベクトル） |
| `planeX, planeY` | カメラ平面（視野角を定義） |
| `rayDirX, rayDirY` | 個々のレイの方向 |
| `perpWallDist` | 壁までの垂直距離（魚眼効果を防ぐ） |

### 4. DDA (Digital Differential Analysis)

マップをマス目ごとにステップしながら壁を探すアルゴリズム。

```
while (壁に当たっていない) {
  if (X方向の次のマスが近い)
    X方向に1マス進む
  else
    Y方向に1マス進む

  現在のマスが壁かチェック
}
```

## サンプルコードの使い方

`raycasting_prototype.c`をコンパイル・実行：

```bash
cc -o raycast_demo ai_work/raycasting_prototype.c -lm
./raycast_demo
```

出力例：
```
=== Raycasting Demo ===
Player position: (4.5, 4.5)
Player direction: (-1.0, 0.0)

Screen column x=400:
  Distance to wall: 2.50
  Wall height on screen: 240 pixels
```

## 次のステップ

1. **理解フェーズ**（今ここ）
   - サンプルコードを読む
   - DDAアルゴリズムを理解

2. **実装フェーズ**
   - `srcs/engine/raycasting/cast_rays.c`を作成
   - `render_frame()`から呼び出す

3. **統合フェーズ**
   - パースされたマップデータを使用
   - テクスチャ描画を追加

## 参考資料
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- プロジェクト内: `docs/design/modules/engine/raycasting/`