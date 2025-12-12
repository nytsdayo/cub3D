# map サブモジュール設計

## 目的

- Parse exactly as rendered in the file; must support any valid layout.
- Spaces inside the map are meaningful tokens.

## EBNF 文法定義

```ebnf
(* Map Section Grammar *)

map_section = map_lines ;

map_lines = map_line, { map_line } ;
(* Minimum 3 lines required, semantic constraint *)

map_line = [ map_content ], newline ;
(* Empty lines within map are allowed *)

map_content = map_char, { map_char } ;
(* All rows must have consistent length when normalized, semantic constraint *)

map_char = wall | empty | player | space ;

wall = "1" ;

empty = "0" ;

player = north_player | south_player | east_player | west_player ;

north_player = "N" ;

south_player = "S" ;

east_player = "E" ;

west_player = "W" ;

space = " " ;
(* Spaces are significant within the map *)

newline = "\n" ;
```

### 文法の補足と制約

#### セマンティック制約 (構文では表現できない制約)

1. **最小マップサイズ**: マップは最低 3×3 のサイズが必要
   - 実装: 行数と各行の長さを検証
   - 違反時: マップ拒否

2. **最大マップサイズ**: マップは最大許容サイズを超えてはならない
   - 実装: 行数と列数の上限チェック
   - 違反時: マップ拒否

3. **壁による囲い込み**: マップは全ての辺が壁 (`1`) で囲まれている必要がある
   - 実装: 外周の全セルが壁であることを検証
   - 空白 (` `) が void/境界外に接してはならない
   - 違反時: マップ拒否

4. **プレイヤー開始位置**: プレイヤー (`N`, `S`, `E`, `W`) は正確に1つだけ存在する必要がある
   - 0個または2個以上の場合はエラー
   - 違反時: マップ拒否

5. **行の長さの一貫性**: 全ての行は同じ長さでなければならない
   - 短い行は暗黙的に空白でパディングされる
   - 実装: 最大行長を基準に正規化
   - 違反時: 長さ不一致の場合は拒否

6. **有効な文字のみ**: マップには `0`, `1`, `N`, `S`, `E`, `W`, ` ` (空白) のみが許可される
   - 実装: `is_valid_char` ヘルパー関数で検証
   - 違反時: マップ拒否

7. **到達可能性 (オプション)**: 全ての開放領域がプレイヤーから到達可能であるべき
   - 実装: フラッドフィル アルゴリズムで検証
   - 違反時: 警告または拒否

#### 文法の特性

- **空白の意味**: マップ内の空白文字 (` `) は意味を持つトークンであり、無視されない
- **行末処理**: 各行は改行文字 (`\n`) で終了
- **空行の扱い**: マップセクション内の空行は許容される（ただし有効なマップデータとしては扱わない）

#### 実装上の注意点

1. **正規化プロセス**:
   - 全行の長さを取得
   - 最長行の長さを基準として設定
   - 短い行は右側に空白を追加してパディング

2. **検証順序**:
   ```
   1. 文字検証 (is_valid_char)
   2. サイズ検証 (最小/最大)
   3. プレイヤー数検証 (exactly 1)
   4. 行長さ一貫性検証
   5. 壁囲い込み検証
   6. 空白-境界接触検証
   7. (オプション) 到達可能性検証
   ```

#### 曖昧性に関する明記事項

1. **空白の扱い**: 
   - マップ内の空白は有効なトークン
   - 行末の空白は意味を持つ（短い行のパディングに使用）
   - ファイル内でそのまま表現される通りにパース

2. **到達不可能な空領域**: 
   - 基本仕様では明記されていない
   - 実装方針: オプションで警告またはエラーとする

3. **マップ境界の定義**:
   - 最初の非空行から最後の非空行までをマップとして扱う
   - config セクションとの境界は親 parse モジュールで管理

4. **ドア記号の扱い**:
   - 基本仕様には含まれない
   - ボーナス機能として追加する場合は EBNF を拡張:
     ```ebnf
     door = "D" ;  (* ボーナス: ドア *)
     map_char = wall | empty | player | space | door ;
     ```

## 責務

<!-- このサブモジュールの責務を記述してください -->

- 

## インターフェース

### 公開関数

<!-- 公開関数の一覧を記述してください -->

| 関数名 | 説明 | 引数 | 戻り値 |
|--------|------|------|--------|
|`map_parser`        |map部分のパース処理      |char **input_data      |   int    |

## 内部設計

<!-- 内部の設計方針を記述してください -->

## エラーハンドリング

<!-- エラー処理の方針を記述してください -->

### Map content validation & format validation  

| Validation Rule | Description | Handling Policy |  
|----------------|-------------|-----------------|  
| Minimum map size | Map must be at least 3x3 in size | Reject map if too small |  
| Maximum map size guard | Map must not exceed maximum allowed size | Reject map if too large |  
| Surrounded-by-walls validation | Map must be enclosed by walls on all sides | Reject map if not enclosed |  
| Exactly one player start | Only one player start position (N/S/E/W) allowed | Reject map if zero or multiple starts |  
| Row length consistency | All rows must have the same length | Reject map if inconsistent |  
| Invalid character detection | Only valid characters allowed (`is_valid_char` helper) | Reject map if invalid character found |  
| Reachability via flood fill (optional) | All open areas must be reachable | Warn or reject if unreachable areas found |  
| Spaces touching void/out-of-bounds | Spaces must not touch void or out-of-bounds areas | Reject map if violation detected |  

## 参照

- [README](./README.md)
- [parse モジュール](../README.md)
