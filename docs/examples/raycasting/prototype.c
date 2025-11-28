/* ************************************************************************** */
/*   raycasting_prototype.c - Minimal raycasting example                     */
/*   Based on Lode's raycasting tutorial: https://lodev.org/cgtutor/raycasting.html */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 8
#define MAP_HEIGHT 8

// Simple 8x8 map (1 = wall, 0 = empty)
int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
  {1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,1,1,0,0,1},
  {1,0,0,1,1,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1}
};

/*
** cast_single_ray
** 1本のレイをキャストして、壁までの距離を計算
**
** Parameters:
**   posX, posY: プレイヤーの位置
**   dirX, dirY: プレイヤーの向いている方向
**   planeX, planeY: カメラ平面（FOV定義）
**   x: スクリーン上のx座標（0 to SCREEN_WIDTH-1）
**
** Returns: 壁までの垂直距離（perpendicular distance）
*/
double cast_single_ray(double posX, double posY,
                       double dirX, double dirY,
                       double planeX, double planeY,
                       int x)
{
  // カメラX座標（-1 to 1の範囲）
  double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;

  // レイの方向ベクトル
  double rayDirX = dirX + planeX * cameraX;
  double rayDirY = dirY + planeY * cameraX;

  // 現在のマップ座標
  int mapX = (int)posX;
  int mapY = (int)posY;

  // 次のマップ境界までの距離（X方向、Y方向）
  double sideDistX;
  double sideDistY;

  // 1マップ単位進むのに必要なレイの長さ
  double deltaDistX = fabs(1 / rayDirX);
  double deltaDistY = fabs(1 / rayDirY);

  // レイの進む方向（-1 or 1）
  int stepX;
  int stepY;

  // 壁に当たったか
  int hit = 0;

  // 垂直な壁（NS）か水平な壁（EW）か
  int side;

  // ステップ方向と初期のsideDistを計算
  if (rayDirX < 0) {
    stepX = -1;
    sideDistX = (posX - mapX) * deltaDistX;
  } else {
    stepX = 1;
    sideDistX = (mapX + 1.0 - posX) * deltaDistX;
  }

  if (rayDirY < 0) {
    stepY = -1;
    sideDistY = (posY - mapY) * deltaDistY;
  } else {
    stepY = 1;
    sideDistY = (mapY + 1.0 - posY) * deltaDistY;
  }

  // DDA (Digital Differential Analysis) アルゴリズム
  // 壁に当たるまでマップをステップ
  while (hit == 0) {
    // X方向またはY方向に1マス進む
    if (sideDistX < sideDistY) {
      sideDistX += deltaDistX;
      mapX += stepX;
      side = 0; // X方向の壁
    } else {
      sideDistY += deltaDistY;
      mapY += stepY;
      side = 1; // Y方向の壁
    }

    // 壁をチェック
    if (worldMap[mapX][mapY] > 0)
      hit = 1;
  }

  // 壁までの垂直距離を計算（魚眼効果を防ぐ）
  double perpWallDist;
  if (side == 0)
    perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
  else
    perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

  return perpWallDist;
}

/*
** demo_raycasting
** レイキャスティングのデモ
** スクリーンの中央列（x=400）のレイをキャストして結果を表示
*/
void demo_raycasting(void)
{
  // プレイヤーの初期位置
  double posX = 4.5;  // マップ中央
  double posY = 4.5;

  // プレイヤーの向き（北を向いている）
  double dirX = -1.0;
  double dirY = 0.0;

  // カメラ平面（FOV = 66度くらい）
  double planeX = 0.0;
  double planeY = 0.66;

  printf("=== Raycasting Demo ===\n");
  printf("Player position: (%.1f, %.1f)\n", posX, posY);
  printf("Player direction: (%.1f, %.1f)\n\n", dirX, dirY);

  // スクリーンの中央列でレイをキャスト
  int x = SCREEN_WIDTH / 2;
  double distance = cast_single_ray(posX, posY, dirX, dirY, planeX, planeY, x);

  // 壁の高さを計算（距離が遠いほど低く見える）
  int lineHeight = (int)(SCREEN_HEIGHT / distance);

  printf("Screen column x=%d:\n", x);
  printf("  Distance to wall: %.2f\n", distance);
  printf("  Wall height on screen: %d pixels\n", lineHeight);
  printf("\n");

  // 複数のレイをキャスト（左・中央・右）
  printf("=== Multiple rays ===\n");
  int test_positions[] = {0, SCREEN_WIDTH/4, SCREEN_WIDTH/2, 3*SCREEN_WIDTH/4, SCREEN_WIDTH-1};

  for (int i = 0; i < 5; i++) {
    x = test_positions[i];
    distance = cast_single_ray(posX, posY, dirX, dirY, planeX, planeY, x);
    lineHeight = (int)(SCREEN_HEIGHT / distance);
    printf("x=%4d -> distance=%.2f, height=%3d\n", x, distance, lineHeight);
  }
}

int main(void)
{
  demo_raycasting();
  return 0;
}