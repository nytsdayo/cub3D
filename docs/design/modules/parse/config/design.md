# config サブモジュール設計

## 目的

- 親 `parse()` が読んだ行列から config セクション（テクスチャ×4 + RGB×2）を抽出・正規化
- map セクションへ渡す前に全6要素が1回ずつ出現していることを保証

## EBNF 文法定義

```ebnf
(* Config Section Grammar *)

config_section = { blank_line }, config_lines, { blank_line } ;

config_lines = config_line, config_line, config_line, 
               config_line, config_line, config_line ;
(* Exactly 6 config lines required, order-independent *)

config_line = ( texture_line | color_line ), newline ;

blank_line = [ whitespace ], newline ;

(* Texture Configuration *)
texture_line = texture_identifier, separator, texture_path ;

texture_identifier = "NO" | "SO" | "WE" | "EA" ;

texture_path = path_component, { path_separator, path_component }, ".xpm" ;

path_component = { path_char } ;

path_char = letter | digit | "_" | "-" | "." ;

path_separator = "/" ;

(* Color Configuration *)
color_line = color_identifier, separator, rgb_value ;

color_identifier = "F" | "C" ;

rgb_value = color_component, ",", color_component, ",", color_component ;

color_component = digit | digit, digit | digit, digit, digit ;
(* Must be in range 0-255, semantic constraint *)

(* Common Definitions *)
separator = whitespace, { whitespace } ;

whitespace = " " | "\t" ;

newline = "\n" ;

letter = "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | 
         "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | 
         "U" | "V" | "W" | "X" | "Y" | "Z" |
         "a" | "b" | "c" | "d" | "e" | "f" | "g" | "h" | "i" | "j" | 
         "k" | "l" | "m" | "n" | "o" | "p" | "q" | "r" | "s" | "t" | 
         "u" | "v" | "w" | "x" | "y" | "z" ;

digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
```

### 文法の補足と制約（箇条書き）

- 識別子の一意性: `NO|SO|WE|EA|F|C` は各1回のみ（`seen_flags[6]` で管理、違反時 `DUPLICATE_IDENTIFIER`）
- RGB 範囲: `color_component` は 0-255（構文は1-3桁、範囲は実行時チェック、違反時 `SYNTAX_RGB`）
- テクスチャパス: `.xpm` 拡張子のみを構文で強制、実在チェックは別モジュール
- 空白行: Config セクション前後と各行の間で任意数許容
- セクション境界: Config はちょうど6行のみ許可。map 開始後の config 行や7行目以降の config 行はフォーマットエラー

#### 実装上の注意点

- **順序非依存**: 6つの config 行は任意の順序で出現可能
- **空白の扱い**: 識別子とその値の間には1つ以上の空白文字 (スペースまたはタブ) が必要
- **行末**: 各行は改行文字 (`\n`) で終了する必要がある

#### 曖昧性に関する明記事項

1. **相対パス vs 絶対パス**: EBNF では両方を許容。`./` や `/` で始まるパスも有効。
2. **パス内の空白**: 現仕様では空白をパス区切り文字として扱うため、パス内に空白を含むことはできない。
3. **RGB のゼロパディング**: `001` のような先頭ゼロは許容される（値が範囲内であれば）。
4. **カンマ周辺の空白**: 現仕様では RGB 値のカンマの前後に空白は許容されない (`R,G,B` 形式)。

## 入力と前提

- 入力：`char **input_data, size_t *line_index` (NULL 終端の行配列)
- 先頭およびセクション途中に空行が混在する
- 空行/空白のみの行は config 処理では無視する
- 行の順序は任意。識別子 `NO|SO|WE|EA|F|C` の出現回数は最大1回

## 成果物（戻り値のみ）

このモジュールは**値を保持せず**、検証結果のみを返す:

- **成功時**: `0` を返す（構文が正しい）
- **失敗時**: `-1` を返す（標準エラー出力にメッセージ表示済み）

実際の値の確保は、別の`load`モジュールが行う。

## パースフロー（検証のみ）

```text
1. skip_reading_blank_lines()
2. while (!all_identifiers_found && line != NULL)
    2.1 empty line -> skip
    2.2 detect_identifier(line)
         - unknown -> ERROR (-1を返す)
         - duplicate -> ERROR (-1を返す)
    2.3 validate_format(line, identifier)
         - texture: `.xpm`拡張子チェックのみ
         - rgb: 形式チェック、0-255範囲チェック
    2.4 mark identifier as seen
    2.5 次行へ進む(line_index++)
3. all_identifiers_found? 
    - YES -> return 0
    - NO -> return -1 (MISSING_IDENTIFIER)
```

### ヘルパー関数（検証のみ）

- `bool is_blank_line(const char *line)`
- `t_identifier detect_identifier(const char *line)`
- `int validate_texture_format(const char *line)`
  - `.xpm`で終わるかのみチェック
  - **文字列のコピーはしない**
- `int validate_rgb_format(const char *line)`
  - `R,G,B`形式かチェック
  - 0-255範囲かチェック
  - **値の保存はしない**
- `bool all_identifiers_found(int flags[6])`

## 状態管理（検証用のみ）

```c
typedef struct s_validation_state {
    int  seen_flags[6];    // 各識別子を見つけたか（0 or 1）
    size_t line_idx;       // input_data 上の現在位置
} t_validation_state;
```

**注意**: この構造体は関数内のローカル変数として使用し、
テクスチャパスや RGB 値は保持しない。

## エラーハンドリング

| エラーID | 発生条件 | 対応 |
|----------|----------|------|
| `UNKNOWN_IDENTIFIER` | `NO|SO|WE|EA|F|C` 以外の行に遭遇 | 行番号つきで報告し config 処理を即終了 |
| `DUPLICATE_IDENTIFIER` | `seen_flags[idx]` が 1 の識別子が再出現 | 既存値を保持し、新しい値は破棄してエラー返却 |
| `SYNTAX_TEXTURE` | 識別子の後にパスが無い / `.xpm` 以外 | 問題行を指摘 |
| `SYNTAX_RGB` | RGB が3要素でない / 非整数 / 0-255外 | F/C 共通のバリデーションとして扱う |
| `MISSING_IDENTIFIER` | 入力終端 or map 行に到達した時点で `seen_flags` に 0 が残る | 欠けている識別子名を列挙 |

## 参照

- `docs/design/modules/parse/README.md`
- `docs/design/modules/parse/config/README.md`
