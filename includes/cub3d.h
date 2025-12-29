/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:05:14 by mkawano           #+#    #+#             */
/*   Updated: 2025/12/27 05:49:34 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifdef __linux__
#  include <X11/X.h>
#  include <X11/keysym.h>
# endif

/* Window Configuration */
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define TITLE "cub3D"

/* Map Cell Types */
typedef enum e_cell_type
{
	FLOOR = 0,
	WALL = 1
}	t_cell_type;

/* Player Position Constants */
# define GRID_CENTER_OFFSET 0.5
# define DEFAULT_PLAYER_POS 3.5

/* Raycasting Constants */
/* - CAMERA_PLANE_LENGTH
 *   - カメラ平面ベクトルの長さ
 *   - FOVを決定: tan(FOV/2) ≈ 0.66 で FOV ≈ 66度
 *   - 値が大きい = 広角、小さい = 狭角
 * - MOVE_PER_FRAME:
 *   - Per-frame movement (in grid units)
 *   - フレームあたりの移動量/速度(グリッド単位/frame)
 * - ROT_PER_FRAME
 *   - Per-frame rotation (in radians)
 *   - フレームあたりの回転量/速度（ラジアン/frame）
 *  - COLLISION_MARGIN
 *   - 衝突判定の余白（壁衝突を防ぐ）
 */
# define CAMERA_PLANE_LENGTH 0.66
# define MOVE_PER_FRAME 0.1
# define ROT_PER_FRAME 0.05
# define COLLISION_MARGIN 0.2

/* Texture Constants */
# define TEX_WIDTH 2048
# define TEX_HEIGHT 2048
# define TEX_NORTH_PATH "assets/textures/cub3_north_newyear.xpm"
# define TEX_SOUTH_PATH "assets/textures/cub3_south_xmaswreath.xpm"
# define TEX_EAST_PATH "assets/textures/cub3_east_cookie.xpm"
# define TEX_WEST_PATH "assets/textures/cub3_west_snowflake.xpm"

/* Key State Array Size (large enough for X11 KeySym values) */
/* キー状態配列のサイズ(Linux X11 KeySym値の最大値約65000より大きく設定) */
/* メリット: シンプルで高速, デメリット: メモリ無駄遣い, 余力あれば: ハッシュマップを使う */
# define KEY_STATE_SIZE 70000

/* Key Codes (Cross-platform) */
/* 本来XK_Escape等コード内で使えるが、クロスプラットフォーム対応で抽象化している */
# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# else
#  define KEY_ESC XK_Escape
#  define KEY_W XK_w
#  define KEY_A XK_a
#  define KEY_S XK_s
#  define KEY_D XK_d
#  define KEY_LEFT XK_Left
#  define KEY_RIGHT XK_Right
# endif

/* Events */
/* X11/MLX standard event type values */
/* X11/MLX標準のイベントタイプ値 */
# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_DESTROY 17

/* Player Structure */
/* - pos
 *   - プレイヤーの現在位置座標
 * - dir
 *   - プレイヤーの向きベクトル（視線の中心方向）、長さは常に1
 *   - 懐中電灯で例えると
 *     - ライトを向けている中心方向（一番明るい真ん中の光軸）
 *     - FOV光の広がり具合（照射角度）、広いライトか狭いスポットライトか
 *       - 狭いスポットライトなのか、広いワイドライトなのか、という「性能」
 * - plan: dirに垂直な平面ベクトル(FOV実現のために必須)
 *   - Camera Plane Vector(カメラ平面)
 *   - dirに垂直なベクトル
 *   - FOVという性能を具体的に「ベクトルの長さ」として表現する
 *   - plane が長い＝ワイドライト（広角）、短い＝スポットライト（狭角）
*/
typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

/* Image Structure */
/* img: mlx_new_image()で作成したイメージオブジェクトへのポインタ
 * addr:  mlx_get_data_addr()で取得したピクセルバッファのアドレス
 * bits_per_pixel: 1ピクセルのビット数（32bit = RGBA各8bit）
 * line_length: メモリ上の1行のバイト数（幅x4とは限らないので）
 * endian: バイトオーダー（0=little, 1=big）
 */
typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

/* Texture Structure */
typedef struct s_texture
{
	t_img		north;
	t_img		south;
	t_img		east;
	t_img		west;
	int			width;
	int			height;
}				t_texture;

/* RGB Color Structure */
typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

/* Game Structure */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			**world_map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_img		img;
	t_texture	textures;
	t_rgb		floor_color;
	t_rgb		ceiling_color;
	int			keys[KEY_STATE_SIZE];
}				t_game;

#endif
