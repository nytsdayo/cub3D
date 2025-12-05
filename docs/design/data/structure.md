# データ構造設計

## 概要

<!-- データ構造の概要を記述してください -->

## 主要データ構造

### マップ関連データ
* config_data : config部分の内容を格納した構造体
* map_data : map部分を抽出した構造体

### 構造体名

```c
typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_config_data
{
    char                *north_texture_path;
    char                *south_texture_path;
    char                *west_texture_path;
    char                *east_texture_path;
    t_color             floor_color;
    t_color             ceiling_color;
} t_config_data;

typedef struct s_map_data
{
    char    **map;
} t_map_data;

typedef struct s_game_data
{
    t_config_data   config;
    t_map_data      map;
} t_game_data;
```

#### フィールド説明

| フィールド名 | 型 | 説明 |
|-------------|-----|------|
|`north_texture_path`| char* | 北方向のテクスチャファイルのパス |  
|`south_texture_path`| char* | 南方向のテクスチャファイルのパス |  
|`west_texture_path`| char* | 西方向のテクスチャファイルのパス |  
|`east_texture_path`| char* | 東方向のテクスチャファイルのパス |  

|`floor_color`| t_color | 床のRGBカラー値 |
|`ceiling_color`| t_color | 天井のRGBカラー値 |
|`map`| char** | 2次元配列として表現されたマップデータ |
#### 使用箇所

<!-- この構造体が使用される箇所を記述してください -->

- 

## データフロー

<!-- データがどのように流れるかを記述してください -->

```
入力データ → パース → 内部データ構造 → 処理 → 出力
```

## メモリ管理

<!-- メモリの確保・解放方針を記述してください -->

### 確保タイミング

- 

### 解放タイミング

- 

## 参照

<!-- 参照ドキュメントへのリンクを記述してください -->

- [アーキテクチャ](../architecture.md)
