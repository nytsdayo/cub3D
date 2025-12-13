# parse モジュール設計

## 目的

.cubファイルの構文検証（validation）のみを行い、フォーマットが正しいことを保証する。
**値の確保（メモリ割り当て）は行わず**、構文チェックのみに責務を限定する。

## 責務

### パースモジュールが行うこと

- ✅ .cubファイルの構文検証
- ✅ 識別子の存在チェック（NO, SO, WE, EA, F, C）
- ✅ 識別子の重複チェック
- ✅ RGB値の範囲チェック（0-255）
- ✅ テクスチャパスの拡張子チェック（.xpm）
- ✅ マップ形式の検証（壁で囲まれているか、プレイヤー位置など）

### パースモジュールが行わないこと

- ❌ メモリの動的確保（malloc/strdup等）
- ❌ テクスチャファイルの実在確認
- ❌ テクスチャファイルの読み込み
- ❌ マップデータの複製や保持

## 設計原則

### 単一責任の原則

```
Parse Module (構文検証のみ)
    ↓ OK
Load Module (値の確保・リソース読み込み)
    ↓ OK
Game Module (ゲーム実行)
```

- **parse**: 構文が正しいかのみを判定（戻り値: 0=成功, -1=失敗）
- **load**: パース済みデータから実際のリソースを読み込み、メモリ確保
- **game**: 読み込まれたデータでゲームを実行

## インターフェース

### 公開関数

| 関数名 | 説明 | 引数 | 戻り値 |
|--------|------|------|--------|
| `validate_cub_file` | .cubファイル全体の構文検証 | `char **lines` | `int` (0=成功, -1=失敗) |
| `validate_config_section` | config部分の構文検証 | `char **lines, size_t *idx` | `int` |
| `validate_map_section` | map部分の構文検証 | `char **lines, size_t idx` | `int` |

### 戻り値の意味

- `0`: 構文が正しい（次の処理に進める）
- `-1`: 構文エラー（標準エラー出力にメッセージ表示済み）

## 内部設計

### フェーズ分離

#### Phase 1: Parse（構文検証）
```c
int validate_cub_file(char **lines)
{
    size_t idx = 0;
    
    // Config部分の構文検証（メモリ確保なし）
    if (validate_config_section(lines, &idx) != 0)
        return (-1);
    
    // Map部分の構文検証（メモリ確保なし）
    if (validate_map_section(lines, idx) != 0)
        return (-1);
    
    return (0);  // 構文OK
}
```

#### Phase 2: Load（値の確保・リソース読み込み）
```c
// 別モジュール（load.c等）で実装
int load_game_resources(char **lines, t_game *game)
{
    size_t idx = 0;
    
    // Config値を読み込み、メモリ確保
    if (load_config_data(lines, &idx, &game->config) != 0)
        return (-1);
    
    // テクスチャファイルを実際に読み込み
    if (load_textures(&game->config, game->mlx) != 0)
        return (-1);
    
    // Map値を読み込み、メモリ確保
    if (load_map_data(lines, idx, &game->map) != 0)
        return (-1);
    
    return (0);
}
```

### 検証のみを行う理由

1. **責務の明確化**: パーサーは「正しいか」を判定するだけ
2. **テスト容易性**: 構文チェックのみなので単体テストが簡単
3. **エラーハンドリング**: パース失敗時にメモリリークの心配がない
4. **再利用性**: 検証ロジックと読み込みロジックを独立して使える

## エラーハンドリング

パースモジュールは検証のみを行うため、エラー時は：

1. 標準エラー出力にメッセージを表示
2. `-1`を返す
3. **メモリ解放は不要**（確保していないため）

### エラーメッセージ形式

```
Error
<具体的なエラー内容>
```

例:
```
Error
Unknown identifier at line 5
```

## 参照

- [README](./README.md)
- [config設計](./config/design.md)
- [map設計](./map/design.md)

