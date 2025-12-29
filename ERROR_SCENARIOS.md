# cub3D エラーシナリオ一覧

このドキュメントは、`srcs`ディレクトリ内のコードを分析して特定した、すべての起きうるエラーシナリオを網羅的に列挙したものです。

## エラーコード体系

エラーコードは以下のカテゴリに分類されています（[error_manage.h](includes/error/error_manage.h)より）：

- **100番台**: コマンドライン引数・検証エラー
- **200番台**: 設定(Config)解析エラー
- **300番台**: マップ検証エラー
- **400番台**: ファイルI/Oエラー
- **500番台**: メモリ割り当てエラー
- **600番台**: MLX/グラフィックスエラー
- **700番台**: レイキャスティングエラー
- **900番台**: 汎用エラー

---

## カテゴリ1: コマンドライン引数エラー (100番台)

### ERR_INVALID_ARGC (100)
**エラーメッセージ**: "Usage: ./cub3D <map.cub>"

**発生条件**:
- コマンドライン引数の数が2でない場合

**再現方法**:
```bash
./cub3D                           # 引数なし
./cub3D map1.cub map2.cub         # 引数が多すぎる
```

**ソースコード**: [main.c:59](srcs/main.c#L59)

---

### ERR_INVALID_ARGV (101)
**エラーメッセージ**: "Invalid argument"

**発生条件**:
- 引数が無効な場合（現在のコードでは未使用だが定義されている）

**ソースコード**: [error_manage.h:22](includes/error/error_manage.h#L22)

---

### ERR_INVALID_FILE_EXTENSION (402)
**エラーメッセージ**: "Invalid file extension"

**発生条件**:
- ファイル名が4文字未満
- ファイル名の末尾が`.cub`でない

**再現方法**:
```bash
./cub3D test.txt                  # .cub以外の拡張子
./cub3D test.map
./cub3D test                      # 拡張子なし
./cub3D a.c                       # ファイル名が短すぎる
```

**ソースコード**: [main.c:61-62](srcs/main.c#L61-62)

---

## カテゴリ2: ファイルI/Oエラー (400番台)

### ERR_FILE_NOT_FOUND (400)
**エラーメッセージ**: "File not found"

**発生条件**:
- 指定されたファイルが存在しない
- ファイルを開けない（権限不足含む）

**再現方法**:
```bash
./cub3D nonexistent.cub           # 存在しないファイル
chmod 000 test.cub && ./cub3D test.cub  # 読み取り権限なし
```

**ソースコード**: [read_map.c:28](srcs/utils/read_map.c#L28)

---

### ERR_FILE_READ_PERMISSION (401)
**エラーメッセージ**: "Permission denied reading file"

**発生条件**:
- ファイル読み取り中にエラーが発生
- 空のファイル（mapがNULL）

**再現方法**:
```bash
# ファイル読み取り中に権限を変更するなど
```

**ソースコード**:
- [read_map.c:66](srcs/utils/read_map.c#L66)
- [read_map.c:92](srcs/utils/read_map.c#L92)

---

### ERR_INVALID_PATH (403)
**エラーメッセージ**: "Invalid file path"

**発生条件**:
- 無効なファイルパス（現在のコードでは未使用だが定義されている）

**ソースコード**: [error_manage.h:40](includes/error/error_manage.h#L40)

---

## カテゴリ3: 設定(Config)解析エラー (200番台)

### ERR_UNKNOWN_IDENTIFIER (200)
**エラーメッセージ**: "Unknown identifier in config section"

**発生条件**:
- 設定セクションで未知の識別子が検出された
- 有効な識別子: `NO`, `SO`, `WE`, `EA`, `F`, `C`

**再現方法**:
.cubファイル内に以下を記述:
```
XX invalid_identifier.xpm
```

**ソースコード**: [parse_config.c:53](srcs/parse/config/parse_config.c#L53)

---

### ERR_DUPLICATE_IDENTIFIER (201)
**エラーメッセージ**: "Duplicate identifier found"

**発生条件**:
- 同じ識別子が2回以上出現した場合

**再現方法**:
.cubファイル内に以下を記述:
```
NO assets/textures/north.xpm
NO assets/textures/north2.xpm    # 重複
```

**ソースコード**: [parse_config.c:117](srcs/parse/config/parse_config.c#L117)

---

### ERR_SYNTAX_TEXTURE (202)
**エラーメッセージ**: "Invalid texture path syntax"

**発生条件**:
- テクスチャパスの拡張子が`.xpm`でない
- テクスチャパスが4文字未満
- テクスチャパスが空

**再現方法**:
.cubファイル内に以下を記述:
```
NO assets/textures/north.png     # .xpm以外
NO                                # パスなし
NO te.x                           # 短すぎる
```

**ソースコード**: [validate_format.c:19-40](srcs/parse/config/validate_format.c#L19-40)

---

### ERR_SYNTAX_RGB (203)
**エラーメッセージ**: "Invalid RGB color format or range"

**発生条件**:
- RGB値が0-255の範囲外
- RGB値が数値でない
- RGB形式が`R,G,B`でない
- カンマが欠けている
- 要素が3つでない

**再現方法**:
.cubファイル内に以下を記述:
```
F 256,100,0                       # 範囲外（>255）
F -1,100,0                        # 負の数
F abc,100,0                       # 文字列
F 220,100                         # 要素不足
F 220 100 0                       # カンマなし
```

**ソースコード**: [validate_format.c:69-85](srcs/parse/config/validate_format.c#L69-85)

---

### ERR_MISSING_IDENTIFIER (204)
**エラーメッセージ**: "Missing required identifier"

**発生条件**:
- 必須の識別子（NO, SO, WE, EA, F, C）のいずれかが欠けている

**再現方法**:
.cubファイルで以下のいずれかを省略:
```
# NOを省略した場合など
SO assets/textures/south.xpm
WE assets/textures/west.xpm
EA assets/textures/east.xpm
F 220,100,0
C 225,30,0
```

**ソースコード**: [parse_config.c:61](srcs/parse/config/parse_config.c#L61)

---

### ERR_CONFIG_AFTER_MAP (205)
**エラーメッセージ**: "Config line appeared after map section"

**発生条件**:
- マップセクションの後に設定行が出現した場合

**再現方法**:
.cubファイル内でマップの後に設定を記述:
```
NO assets/textures/north.xpm
...
111111
100N01
111111

F 220,100,0     # マップの後に設定が出現
```

**ソースコード**: [error_messages.c:34](srcs/error/error_messages.c#L34)

---

## カテゴリ4: マップ検証エラー (300番台)

### ERR_MINIMUM_MAP_SIZE (300)
**エラーメッセージ**: "Map is too small (minimum 3x3 required)"

**発生条件**:
- マップの行数が3未満
- マップの最大列数が3未満
- マップセクションが存在しない

**再現方法**:
.cubファイル内に以下のようなマップを記述:
```
11
1N
```
または
```
# 設定のみでマップなし
```

**ソースコード**:
- [parse_map.c:83](srcs/parse/map/parse_map.c#L83)
- [parse_map_validate.c:36-41](srcs/parse/map/parse_map_validate.c#L36-41)

---

### ERR_MAXIMUM_MAP_SIZE (301)
**エラーメッセージ**: "Map exceeds maximum allowed size"

**発生条件**:
- マップの行数が1000を超える
- マップの列数が1000を超える

**再現方法**:
1001行または1001列のマップを作成

**ソースコード**: [parse_map_validate.c:38](srcs/parse/map/parse_map_validate.c#L38)

---

### ERR_WALL_ENCLOSURE (301)
**エラーメッセージ**: "Map is not enclosed by walls"

**発生条件**:
- マップの外周が壁（'1'）で完全に囲まれていない
- マップ内の空きスペース（'0', 'N', 'S', 'E', 'W'）が外部に接触している

**再現方法**:
.cubファイル内に以下のようなマップを記述:
```
111111
100001
101N01
100001
111110      # 右下が開いている
```
または
```
101111      # 左上が開いている
100001
101N01
100001
111111
```

**ソースコード**: [parse_map_walls.c](srcs/parse/map/parse_map_walls.c)

---

### ERR_PLAYER_COUNT_ZERO (302)
**エラーメッセージ**: "No player start position found"

**発生条件**:
- マップ内にプレイヤー開始位置（N, S, E, W）が1つも存在しない

**再現方法**:
.cubファイル内に以下のようなマップを記述:
```
111111
100001
100001      # プレイヤー位置なし
100001
111111
```

**ソースコード**: [parse_map_validate.c:84](srcs/parse/map/parse_map_validate.c#L84)

---

### ERR_PLAYER_COUNT_MULTIPLE (303)
**エラーメッセージ**: "Multiple player start positions found"

**発生条件**:
- マップ内にプレイヤー開始位置が2つ以上存在する

**再現方法**:
.cubファイル内に以下のようなマップを記述:
```
111111
1N0001      # プレイヤー1
100S01      # プレイヤー2
100001
111111
```

**ソースコード**: [parse_map_validate.c:86](srcs/parse/map/parse_map_validate.c#L86)

---

### ERR_ROW_LENGTH_INCONSISTENT (304)
**エラーメッセージ**: "Inconsistent row lengths in map"

**発生条件**:
- （現在のコードでは未使用だが定義されている）

**ソースコード**: [error_manage.h:35](includes/error/error_manage.h#L35)

---

### ERR_INVALID_CHARACTER (305)
**エラーメッセージ**: "Invalid character in map"

**発生条件**:
- マップ内に無効な文字が含まれている
- 有効な文字: `0`, `1`, `N`, `S`, `E`, `W`, ` `（スペース）
- マップ内に空行（blank line）が含まれている

**再現方法**:
.cubファイル内に以下のようなマップを記述:
```
111111
1X0001      # 'X'は無効
101N01
100001
111111
```
または
```
111111
120001      # '2'は無効
101N01
100001
111111
```
または
```
111111
100001

101N01      # 空行がある
111111
```

**ソースコード**:
- [parse_map_validate.c:112](srcs/parse/map/parse_map_validate.c#L112)
- [parse_map.c:57](srcs/parse/map/parse_map.c#L57)

---

### ERR_SPACE_VOID_CONTACT (306)
**エラーメッセージ**: "Space character touches void area"

**発生条件**:
- マップ内のスペース文字が、マップ外（void領域）に隣接している
- 行の長さが不揃いな場合、短い行の末尾がvoidとなり、その隣接するスペースが検出される

**再現方法**:
.cubファイル内に以下のようなマップを記述:
```
1111111
1000001
10N0001
1000001
111111      # 最終行が短い -> 右端がvoid -> 上の行のスペースがvoidに接触
```
または
```
  1111      # 左側にスペース -> voidに接触
  1001
1110N1
1000 1      # 内部スペースがvoidに接触
111111
```

**ソースコード**: [parse_map_spaces.c](srcs/parse/map/parse_map_spaces.c)

---

## カテゴリ5: メモリ割り当てエラー (500番台)

### ERR_MALLOC_FAILURE (500)
**エラーメッセージ**: "Memory allocation failed"

**発生条件**:
- `malloc`が失敗した場合（メモリ不足）

**再現方法**:
- システムメモリを大量に消費した状態でプログラムを実行
- メモリリークテストツールでシミュレート

**ソースコード**: [read_map.c:51](srcs/utils/read_map.c#L51)

---

### ERR_BUFFER_OVERFLOW (501)
**エラーメッセージ**: "Buffer overflow detected"

**発生条件**:
- （現在のコードでは未使用だが定義されている）

**ソースコード**: [error_manage.h:42](includes/error/error_manage.h#L42)

---

## カテゴリ6: MLX/グラフィックスエラー (600番台)

### ERR_MLX_INIT_FAILURE (600)
**エラーメッセージ**: "Failed to initialize MLX"

**発生条件**:
- `mlx_init()`が失敗した場合
- X11サーバーが利用できない場合

**再現方法**:
```bash
# DISPLAY環境変数を無効化
unset DISPLAY
./cub3D valid_map.cub
```

**ソースコード**: [init_game.c](srcs/engine/init/init_game.c)

---

### ERR_WINDOW_CREATION_FAILURE (601)
**エラーメッセージ**: "Failed to create window"

**発生条件**:
- `mlx_new_window()`が失敗した場合

**ソースコード**: [init_game.c](srcs/engine/init/init_game.c)

---

### ERR_IMAGE_CREATION_FAILURE (602)
**エラーメッセージ**: "Failed to create image"

**発生条件**:
- `mlx_new_image()`が失敗した場合

**ソースコード**: [init_game.c](srcs/engine/init/init_game.c)

---

### ERR_TEXTURE_LOAD_FAILURE (603)
**エラーメッセージ**: "Failed to load texture"

**発生条件**:
- `mlx_xpm_file_to_image()`が失敗した場合
- テクスチャファイルが存在しない
- テクスチャファイルの形式が不正

**再現方法**:
.cubファイル内に存在しないテクスチャパスを指定:
```
NO assets/textures/nonexistent.xpm
```

**ソースコード**: [texture_init.c](srcs/engine/texture/texture_init.c)

---

## カテゴリ7: レイキャスティングエラー (700番台)

### ERR_DDA_OUT_OF_BOUNDS (700)
**エラーメッセージ**: "DDA algorithm accessed out of bounds"

**発生条件**:
- DDAアルゴリズムがマップ境界外にアクセスしようとした場合
- （現在のコードでは未使用だが定義されている）

**ソースコード**: [error_manage.h:47](includes/error/error_manage.h#L47)

---

### ERR_DRAW_COORD_OUT_OF_RANGE (701)
**エラーメッセージ**: "Drawing coordinate out of range"

**発生条件**:
- 描画座標がウィンドウ範囲外になった場合
- （現在のコードでは未使用だが定義されている）

**ソースコード**: [error_manage.h:48](includes/error/error_manage.h#L48)

---

## カテゴリ8: 汎用エラー (900番台)

### ERR_GENERIC (900)
**エラーメッセージ**: "An error occurred"

**発生条件**:
- その他の分類されないエラー

**ソースコード**: [error_manage.h:49](includes/error/error_manage.h#L49)

---

## エッジケース・境界値テスト

### RGB境界値
**正常動作する境界値**:
- 最小値: `F 0,0,0` / `C 0,0,0`
- 最大値: `F 255,255,255` / `C 255,255,255`

**エラーになる境界値**:
- `F 256,100,0` -> ERR_SYNTAX_RGB
- `F -1,100,0` -> ERR_SYNTAX_RGB

---

### マップサイズ境界値
**正常動作する境界値**:
- 最小サイズ: 3x3マップ

**エラーになる境界値**:
- 2x2マップ -> ERR_MINIMUM_MAP_SIZE
- 1001x1001マップ -> ERR_MAXIMUM_MAP_SIZE

---

### プレイヤー向き
**すべての方向が正常に動作する**:
- `N` (北向き)
- `S` (南向き)
- `E` (東向き)
- `W` (西向き)

---

### スペースとRGB値
**スペースを含むRGB値は許容される**（実装に依存）:
```
F  220 , 100 , 0
C  225 , 30 , 0
```

---

## テストスクリプト

すべてのエラーシナリオを自動的にテストするスクリプト: [test_errors.sh](test_errors.sh)

実行方法:
```bash
chmod +x test_errors.sh
./test_errors.sh
```

---

## まとめ

### 実装済みエラー検証
現在のコードで実装されている主なエラー検証:
1. ✅ コマンドライン引数検証
2. ✅ ファイル存在・読み取り検証
3. ✅ 設定識別子の検証（重複、欠落、未知）
4. ✅ テクスチャパス形式検証（.xpm拡張子）
5. ✅ RGB値の検証（範囲、形式）
6. ✅ マップサイズ検証（最小/最大）
7. ✅ プレイヤー位置検証（0個、複数）
8. ✅ 無効文字検証
9. ✅ 壁囲み検証
10. ✅ スペース-void接触検証

### 未使用だが定義されているエラー
以下のエラーコードは定義されているが、現在のコードでは使用されていません:
- ERR_INVALID_ARGV (101)
- ERR_INVALID_PATH (403)
- ERR_ROW_LENGTH_INCONSISTENT (304)
- ERR_BUFFER_OVERFLOW (501)
- ERR_DDA_OUT_OF_BOUNDS (700)
- ERR_DRAW_COORD_OUT_OF_RANGE (701)

これらは将来の拡張や、より詳細なエラーハンドリングのために予約されている可能性があります。

---

## 参照ファイル
- エラー定義: [includes/error/error_manage.h](includes/error/error_manage.h)
- エラーメッセージ: [srcs/error/error_messages.c](srcs/error/error_messages.c)
- メイン処理: [srcs/main.c](srcs/main.c)
- パース処理: [srcs/parse/parse.c](srcs/parse/parse.c)
- 設定検証: [srcs/parse/config/parse_config.c](srcs/parse/config/parse_config.c)
- マップ検証: [srcs/parse/map/parse_map.c](srcs/parse/map/parse_map.c)
