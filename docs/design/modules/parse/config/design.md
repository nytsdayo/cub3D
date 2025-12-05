# config サブモジュール設計

## 目的

- 親 `parse()` が取得した入力行列から config セクション (テクスチャ ×4 + RGB ×2) を切り出して正規化する。
- map セクションへ制御を渡す前に、全6要素が一度ずつ揃っていることを保証する。

## 入力と前提

- 入力：`char **input_data, size_t *line_index` (NULL 終端の行配列)。
- 先頭およびセクション途中に空行が混在する。
- 空行/空白のみの行は config 処理では無視する。
- 行の順序は任意。識別子 `NO|SO|WE|EA|F|C` の出現回数は最大1回。

## 成果物

- テクスチャ4種: そのままの相対/絶対パス文字列を保持。
	- 存在確認は後段 (読み込み時) に行う。
	- 拡張子 `.xpm` であることだけここで検知する。
- `F` / `C`: `R,G,B` 形式の3整数を抽出し、0-255 範囲を保証したデータ (例: `{ int[3]  { r,g,b; }`) へ格納。
- 6要素すべて揃ったら次のモジュールへ `config_result` 構造体を返す。

## パースフロー

```text
1. skip_reading_blank_lines()
2. while (!all_identifiers_consumed)
	* 現在行の状態をチェック
		2.1 NULL line -> MISSING_IDENTIFIER エラー
		2.2 empty line -> skip
		2.3 detect_identifier(line)
			 - unknown/duplicate -> ERROR
		2.4 dispatch(line_after_id)
			 - texture_handler: check `.xpm` extension, save trimmed path
			 - rgb_handler: split(',') -> 3-element int conversion -> range check
		2.5 increment corresponding flag.
			- if already 1, DUPLICATE error.	 
	* 次行へ進む(line_index++)
3. 次の非空行まで進み、line_indexを更新する。
```

### ヘルパー関数メモ

- `bool is_blank_line(const char *line)`
- `t_identifier detect_identifier(const char *line)`
	- 先頭トークンのみ比較 (`NO`, `SO`, `WE`, `EA`, `F`, `C`). それ以外は即エラー。
- `char *extract_path(const char *line)`
	- 先頭識別子の後ろの空白を1個以上許可。`.xpm` 拡張子必須。ここではファイルを開かず、文字列コピーのみ。
- `t_color parse_rgb(const char *line)`
	- `split(',')` で3トークン。各トークンは `ft_isdigit` で検査し `ft_atoi`。0-255 以外はエラー。
- `bool all_identifiers_consumed(int flags[6])`
	- `NO,SO,WE,EA,F,C` をインデックス化した配列で進捗を管理。

## 状態管理

```c
typedef struct s_config_state {
		char *textures[4];   // NO, SO, WE, EA
		t_rgb floor;
		t_rgb ceiling;
		int  seen_flags[6];        // 各識別子の消費回数
		size_t line_idx;     // input_data 上の現在位置
}   t_config_state;
```
```
	
- `seen_flags` は初期化 0。対応識別子を処理するたびに `seen_flags[idx]++`。
- `seen_flags[idx] > 1` を検出したらただちに `DUPLICATE_IDENTIFIER` を返す。
- ループ終了条件は `min(seen_flags[]) == 1`。1つでも 0 が残っている状態で NULL 行に到達した場合は `MISSING_IDENTIFIER`。

## エラーハンドリング

| エラーID | 発生条件 | 対応 |
|----------|----------|------|
| `UNKNOWN_IDENTIFIER` | `NO|SO|WE|EA|F|C` 以外の行に遭遇 | 行番号つきで報告し config 処理を即終了 |
| `DUPLICATE_IDENTIFIER` | `seen_flags[idx]` が 1 の識別子が再出現 | 既存値を保持し、新しい値は破棄してエラー返却 |
| `SYNTAX_TEXTURE` | 識別子の後にパスが無い / `.xpm` 以外 | 問題行を指摘 |
| `SYNTAX_RGB` | RGB が3要素でない / 非整数 / 0-255外 | F/C 共通のバリデーションとして扱う |
| `MISSING_IDENTIFIER` | 入力終端 or map 行に到達した時点で `seen_flags` に 0 が残る | 欠けている識別子名を列挙 |

```
## 参照

- `docs/design/modules/parse/README.md`
- `docs/design/modules/parse/config/README.md`
