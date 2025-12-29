# 正常起動トレース（関数呼び出し順）

本資料は正常起動を前提に、関数の呼び出し順で全コードを再構成した教材です。
関数に属さない行（コメント、include、プロトタイプ、マクロなど）は、当該ファイルが
最初に登場する位置でまとめて説明します。

前提:
- 有効な .cub が渡される（正常起動）
- __linux__ を想定（#else ブランチも行単位で説明）
- utils 配下の実装は対象外（呼び出し行のみ記述）
- 設定識別子の順序は NO/SO/WE/EA/F/C を想定（一般的な .cub）
- イベント/フレームの順序は代表例として並べる（実行時は前後しうる）

表記:
- `<path>:<line> <code>` — ...。...
- コメント/空行/プリプロセッサ行は『実行なし』として明記

## 呼び出し順（正常起動）

## main（srcs/main.c）

- srcs/main.c:22 `int	main(int argc, char *argv[])` — 関数定義開始。関数 main の実装が始まる。
- srcs/main.c:23 `{`
- srcs/main.c:24 `	t_game		game;` — 変数宣言。ローカル変数を用意する。
- srcs/main.c:25 `	t_game_data	game_data;` — 変数宣言。ローカル変数を用意する。
- srcs/main.c:26 `	int			ret;` — 変数宣言。ローカル変数を用意する。
- srcs/main.c:27 ``
- srcs/main.c:28 `	init_structs(&game, &game_data);` — 関数呼び出し。init_structs を呼び出し、構造体を初期化する。
- srcs/main.c:29 `	valid_args(argc, argv);` — 関数呼び出し。valid_args を呼び出し、引数を検証する。
- srcs/main.c:30 `	ret = parse(argv[1], &game_data);` — 代入。ret に parse(argv[1], &game_data) を設定する。
- srcs/main.c:31 `	if (ret != 0)` — 条件評価。条件を評価して分岐する。
- srcs/main.c:32 `		error_exit_simple(get_error_status());` — 関数呼び出し。error_exit_simple を呼び出し、エラーで終了する。
- srcs/main.c:33 `	game.map = game_data.map.map;` — 代入。game.map に game_data.map.map を設定する。
- srcs/main.c:34 `	if (init_game(&game, &game_data.config) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/main.c:35 `	{`
- srcs/main.c:36 `		free_map((void **)game.map);` — 関数呼び出し。free_map を呼び出し、マップを解放する。
- srcs/main.c:37 `		free_config_data(&game_data.config);` — 関数呼び出し。free_config_data を呼び出し、設定データを解放する。
- srcs/main.c:38 `		error_exit_simple(ERR_MLX_INIT_FAILURE);` — 関数呼び出し。error_exit_simple を呼び出し、エラーで終了する。
- srcs/main.c:39 `	}`
- srcs/main.c:40 `	run_game_loop(&game);` — 関数呼び出し。run_game_loop を呼び出し、ゲームループを実行する。
- srcs/main.c:41 `	free_config_data(&game_data.config);` — 関数呼び出し。free_config_data を呼び出し、設定データを解放する。
- srcs/main.c:42 `	return (EXIT_SUCCESS);` — 戻り値として EXIT_SUCCESS を返す。
- srcs/main.c:43 `}`

## init_structs（srcs/main.c）

- srcs/main.c:45 `static void	init_structs(t_game *game, t_game_data *game_data)` — 関数定義開始。関数 init_structs の実装が始まる。
- srcs/main.c:46 `{`
- srcs/main.c:47 `	int	i;` — 変数宣言。ローカル変数を用意する。
- srcs/main.c:48 ``
- srcs/main.c:49 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/main.c:50 `	while (i < (int) sizeof(t_game))` — ループ評価。条件が真の間ループする。
- srcs/main.c:51 `		((char *)game)[i++] = 0;` — 代入。((char *)game)[i++] に 0 を設定する。
- srcs/main.c:52 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/main.c:53 `	while (i < (int) sizeof(t_game_data))` — ループ評価。条件が真の間ループする。
- srcs/main.c:54 `		((char *)game_data)[i++] = 0;` — 代入。((char *)game_data)[i++] に 0 を設定する。
- srcs/main.c:55 `}`

## valid_args（srcs/main.c）

- srcs/main.c:57 `static int	valid_args(int argc, char *argv[])` — 関数定義開始。関数 valid_args の実装が始まる。
- srcs/main.c:58 `{`
- srcs/main.c:59 `	if (argc != 2)` — 条件評価。条件を評価して分岐する。
- srcs/main.c:60 `		error_exit_simple(ERR_INVALID_ARGC);` — 関数呼び出し。error_exit_simple を呼び出し、エラーで終了する。
- srcs/main.c:61 `	if (ft_strlen(argv[1]) < 4` — 条件評価。条件を評価して分岐する。
- srcs/main.c:62 `		|| ft_strcmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub") != 0)` — 式の継続。前後の行と合わせて評価する。
- srcs/main.c:63 `		error_exit_simple(ERR_INVALID_FILE_EXTENSION);` — 関数呼び出し。error_exit_simple を呼び出し、エラーで終了する。
- srcs/main.c:64 `	return (0);` — 戻り値として 0 を返す。
- srcs/main.c:65 `}`

## parse（srcs/parse/parse.c）

- srcs/parse/parse.c:29 `int	parse(const char *filepath, t_game_data *game_data)` — 関数定義開始。関数 parse の実装が始まる。
- srcs/parse/parse.c:30 `{`
- srcs/parse/parse.c:31 `	char	**input_data;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/parse.c:32 `	size_t	line_index;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/parse.c:33 `	int		ret;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/parse.c:34 ``
- srcs/parse/parse.c:35 `	(void)game_data;` — 文の評価。未使用変数の警告を抑止する。
- srcs/parse/parse.c:36 `	line_index = 0;` — 代入。line_index に 0 を設定する。
- srcs/parse/parse.c:37 `	input_data = read_map(filepath);` — 代入。input_data に read_map(filepath) を設定する。
- srcs/parse/parse.c:38 `	if (input_data == NULL)` — 条件評価。条件を評価して分岐する。
- srcs/parse/parse.c:39 `	{`
- srcs/parse/parse.c:40 `		set_error_status(ERR_FILE_NOT_FOUND);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/parse.c:41 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/parse.c:42 `	}`
- srcs/parse/parse.c:43 `	ret = validate_config(input_data, &line_index);` — 代入。ret に validate_config(input_data, &line_index) を設定する。
- srcs/parse/parse.c:44 `	if (ret != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/parse.c:45 `	{`
- srcs/parse/parse.c:46 `		free_map((void **)input_data);` — 関数呼び出し。free_map を呼び出し、マップを解放する。
- srcs/parse/parse.c:47 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/parse.c:48 `	}`
- srcs/parse/parse.c:49 `	ret = validate_map(input_data, line_index);` — 代入。ret に validate_map(input_data, line_index) を設定する。
- srcs/parse/parse.c:50 `	if (ret != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/parse.c:51 `	{`
- srcs/parse/parse.c:52 `		free_map((void **)input_data);` — 関数呼び出し。free_map を呼び出し、マップを解放する。
- srcs/parse/parse.c:53 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/parse.c:54 `	}`
- srcs/parse/parse.c:55 `	ret = load_data((const char **)input_data, game_data);` — 代入。ret に load_data((const char **)input_data, game_data) を設定する。
- srcs/parse/parse.c:56 `	free_map((void **)input_data);` — 関数呼び出し。free_map を呼び出し、マップを解放する。
- srcs/parse/parse.c:57 `	return (ret);` — 戻り値として ret を返す。
- srcs/parse/parse.c:58 `}`

## validate_config（srcs/parse/config/parse_config.c）

- srcs/parse/config/parse_config.c:37 `int	validate_config(char **input_data, size_t *line_index)` — 関数定義開始。関数 validate_config の実装が始まる。
- srcs/parse/config/parse_config.c:38 `{`
- srcs/parse/config/parse_config.c:39 `	t_seen_flags	seen_flags;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/parse_config.c:40 `	t_identifier	id;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/parse_config.c:41 `	int				result;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/parse_config.c:42 ``
- srcs/parse/config/parse_config.c:43 `	init_seen_flags(seen_flags);` — 関数呼び出し。init_seen_flags を呼び出し、既出フラグを初期化する。
- srcs/parse/config/parse_config.c:44 `	while (input_data[*line_index] != NULL` — ループ評価。条件が真の間ループする。
- srcs/parse/config/parse_config.c:45 `		&& !all_identifiers_found(seen_flags))` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/config/parse_config.c:46 `	{`
- srcs/parse/config/parse_config.c:47 `		if (is_blank_line(input_data[*line_index]))` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/parse_config.c:48 `		{`
- srcs/parse/config/parse_config.c:49 `			(*line_index)++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/parse_config.c:50 `			continue ;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/parse_config.c:51 `		}`
- srcs/parse/config/parse_config.c:52 `		id = detect_identifier(input_data[*line_index]);` — 代入。id に detect_identifier(input_data[*line_index]) を設定する。
- srcs/parse/config/parse_config.c:53 `		if (id == ID_UNKNOWN)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/parse_config.c:54 `		{`
- srcs/parse/config/parse_config.c:55 `			set_error_status(ERR_UNKNOWN_IDENTIFIER);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/config/parse_config.c:56 `			return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/parse_config.c:57 `		}`
- srcs/parse/config/parse_config.c:58 `		result = validate_identifier_line(input_data[*line_index],` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/config/parse_config.c:59 `				seen_flags, id);` — 文の評価。式または宣言を処理する。
- srcs/parse/config/parse_config.c:60 `		if (result != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/parse_config.c:61 `			return (result);` — 戻り値として result を返す。
- srcs/parse/config/parse_config.c:62 `		(*line_index)++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/parse_config.c:63 `	}`
- srcs/parse/config/parse_config.c:64 `	if (!all_identifiers_found(seen_flags))` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/parse_config.c:65 `	{`
- srcs/parse/config/parse_config.c:66 `		set_error_status(ERR_MISSING_IDENTIFIER);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/config/parse_config.c:67 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/parse_config.c:68 `	}`
- srcs/parse/config/parse_config.c:69 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/config/parse_config.c:70 `}`

## init_seen_flags（srcs/parse/config/parse_config.c）

- srcs/parse/config/parse_config.c:74 `static void	init_seen_flags(t_seen_flags seen_flags)` — 関数定義開始。関数 init_seen_flags の実装が始まる。
- srcs/parse/config/parse_config.c:75 `{`
- srcs/parse/config/parse_config.c:76 `	int	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/parse_config.c:77 ``
- srcs/parse/config/parse_config.c:78 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/config/parse_config.c:79 `	while (i < 6)` — ループ評価。条件が真の間ループする。
- srcs/parse/config/parse_config.c:80 `	{`
- srcs/parse/config/parse_config.c:81 `		seen_flags[i] = 0;` — 代入。seen_flags[i] に 0 を設定する。
- srcs/parse/config/parse_config.c:82 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/parse_config.c:83 `	}`
- srcs/parse/config/parse_config.c:84 `}`

## detect_identifier（srcs/parse/config/detect_identifier.c）

- srcs/parse/config/detect_identifier.c:16 `t_identifier	detect_identifier(const char *line)` — 関数定義開始。関数 detect_identifier の実装が始まる。
- srcs/parse/config/detect_identifier.c:17 `{`
- srcs/parse/config/detect_identifier.c:18 `	int	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/detect_identifier.c:19 ``
- srcs/parse/config/detect_identifier.c:20 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/config/detect_identifier.c:21 `	while (ft_isspace(line[i]))` — ループ評価。条件が真の間ループする。
- srcs/parse/config/detect_identifier.c:22 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/detect_identifier.c:23 `	if (ft_strncmp(&line[i], "NO", 2) == 0 && ft_isspace(line[i + 2]))` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/detect_identifier.c:24 `		return (ID_NO);` — 戻り値として ID_NO を返す。
- srcs/parse/config/detect_identifier.c:25 `	if (ft_strncmp(&line[i], "SO", 2) == 0 && ft_isspace(line[i + 2]))` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/detect_identifier.c:26 `		return (ID_SO);` — 戻り値として ID_SO を返す。
- srcs/parse/config/detect_identifier.c:27 `	if (ft_strncmp(&line[i], "WE", 2) == 0 && ft_isspace(line[i + 2]))` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/detect_identifier.c:28 `		return (ID_WE);` — 戻り値として ID_WE を返す。
- srcs/parse/config/detect_identifier.c:29 `	if (ft_strncmp(&line[i], "EA", 2) == 0 && ft_isspace(line[i + 2]))` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/detect_identifier.c:30 `		return (ID_EA);` — 戻り値として ID_EA を返す。
- srcs/parse/config/detect_identifier.c:31 `	if (line[i] == 'F' && line[i + 1] && ft_isspace(line[i + 1]))` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/detect_identifier.c:32 `		return (ID_F);` — 戻り値として ID_F を返す。
- srcs/parse/config/detect_identifier.c:33 `	if (line[i] == 'C' && line[i + 1] && ft_isspace(line[i + 1]))` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/detect_identifier.c:34 `		return (ID_C);` — 戻り値として ID_C を返す。
- srcs/parse/config/detect_identifier.c:35 `	return (ID_UNKNOWN);` — 戻り値として ID_UNKNOWN を返す。
- srcs/parse/config/detect_identifier.c:36 `}`

## validate_identifier_line（srcs/parse/config/parse_config.c）

- srcs/parse/config/parse_config.c:117 `static int	validate_identifier_line(const char *line,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/config/parse_config.c:118 `		t_seen_flags seen_flags, t_identifier id)` — 文の評価。式/制御構文を処理する。
- srcs/parse/config/parse_config.c:119 `{`
- srcs/parse/config/parse_config.c:120 `	int	idx;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/parse_config.c:121 ``
- srcs/parse/config/parse_config.c:122 `	idx = get_identifier_index(id);` — 代入。idx に get_identifier_index(id) を設定する。
- srcs/parse/config/parse_config.c:123 `	if (seen_flags[idx] > 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/parse_config.c:124 `	{`
- srcs/parse/config/parse_config.c:125 `		set_error_status(ERR_DUPLICATE_IDENTIFIER);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/config/parse_config.c:126 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/parse_config.c:127 `	}`
- srcs/parse/config/parse_config.c:128 `	while (ft_isspace(*line))` — ループ評価。条件が真の間ループする。
- srcs/parse/config/parse_config.c:129 `		line++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/parse_config.c:130 `	if (id >= ID_NO && id <= ID_EA)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/parse_config.c:131 `	{`
- srcs/parse/config/parse_config.c:132 `		if (validate_texture_format(line + 2, id) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/parse_config.c:133 `		{`
- srcs/parse/config/parse_config.c:134 `			set_error_status(ERR_SYNTAX_TEXTURE);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/config/parse_config.c:135 `			return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/parse_config.c:136 `		}`
- srcs/parse/config/parse_config.c:137 `	}`
- srcs/parse/config/parse_config.c:138 `	else` — 分岐。前条件が偽のときの分岐。
- srcs/parse/config/parse_config.c:139 `	{`
- srcs/parse/config/parse_config.c:140 `		if (validate_rgb_format(line + 1) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/parse_config.c:141 `		{`
- srcs/parse/config/parse_config.c:142 `			set_error_status(ERR_SYNTAX_RGB);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/config/parse_config.c:143 `			return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/parse_config.c:144 `		}`
- srcs/parse/config/parse_config.c:145 `	}`
- srcs/parse/config/parse_config.c:146 `	seen_flags[idx]++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/parse_config.c:147 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/config/parse_config.c:148 `}`

## get_identifier_index（srcs/parse/config/parse_config.c）

- srcs/parse/config/parse_config.c:86 `static int	get_identifier_index(t_identifier id)` — 関数定義開始。関数 get_identifier_index の実装が始まる。
- srcs/parse/config/parse_config.c:87 `{`
- srcs/parse/config/parse_config.c:88 `	if (id == ID_NO)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/parse_config.c:89 `		return (0);` — 戻り値として 0 を返す。
- srcs/parse/config/parse_config.c:90 `	else if (id == ID_SO)` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/parse/config/parse_config.c:91 `		return (1);` — 戻り値として 1 を返す。
- srcs/parse/config/parse_config.c:92 `	else if (id == ID_WE)` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/parse/config/parse_config.c:93 `		return (2);` — 戻り値として 2 を返す。
- srcs/parse/config/parse_config.c:94 `	else if (id == ID_EA)` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/parse/config/parse_config.c:95 `		return (3);` — 戻り値として 3 を返す。
- srcs/parse/config/parse_config.c:96 `	else if (id == ID_F)` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/parse/config/parse_config.c:97 `		return (4);` — 戻り値として 4 を返す。
- srcs/parse/config/parse_config.c:98 `	else if (id == ID_C)` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/parse/config/parse_config.c:99 `		return (5);` — 戻り値として 5 を返す。
- srcs/parse/config/parse_config.c:100 `	return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/parse_config.c:101 `}`

## validate_texture_format（srcs/parse/config/validate_format.c）

- srcs/parse/config/validate_format.c:19 `int	validate_texture_format(const char *line, t_identifier id)` — 関数定義開始。関数 validate_texture_format の実装が始まる。
- srcs/parse/config/validate_format.c:20 `{`
- srcs/parse/config/validate_format.c:21 `	int	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/validate_format.c:22 `	int	start;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/validate_format.c:23 `	int	len;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/validate_format.c:24 ``
- srcs/parse/config/validate_format.c:25 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/config/validate_format.c:26 `	if (id >= ID_NO && id <= ID_EA)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/validate_format.c:27 `		i += 2;` — 代入。i に 2 を加算して設定する。
- srcs/parse/config/validate_format.c:28 `	else` — 分岐。前条件が偽のときの分岐。
- srcs/parse/config/validate_format.c:29 `		i += 1;` — 代入。i に 1 を加算して設定する。
- srcs/parse/config/validate_format.c:30 `	while (ft_isspace(line[i]))` — ループ評価。条件が真の間ループする。
- srcs/parse/config/validate_format.c:31 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/validate_format.c:32 `	start = i;` — 代入。start に i を設定する。
- srcs/parse/config/validate_format.c:33 `	while (line[i] && !ft_isspace(line[i]) && line[i] != '\n')` — ループ評価。条件が真の間ループする。
- srcs/parse/config/validate_format.c:34 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/validate_format.c:35 `	len = i - start;` — 代入。len に i - start を設定する。
- srcs/parse/config/validate_format.c:36 `	if (len < 4)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/validate_format.c:37 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/validate_format.c:38 `	if (ft_strncmp(&line[start + len - 4], ".xpm", 4) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/validate_format.c:39 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/validate_format.c:40 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/config/validate_format.c:41 `}`

## validate_rgb_format（srcs/parse/config/validate_format.c）

- srcs/parse/config/validate_format.c:69 `int	validate_rgb_format(const char *line)` — 関数定義開始。関数 validate_rgb_format の実装が始まる。
- srcs/parse/config/validate_format.c:70 `{`
- srcs/parse/config/validate_format.c:71 `	int	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/validate_format.c:72 ``
- srcs/parse/config/validate_format.c:73 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/config/validate_format.c:74 `	if (parse_component_with_spaces(line, &i) < 0` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/validate_format.c:75 `		|| expect_comma(line, &i) < 0` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/config/validate_format.c:76 `		|| parse_component_with_spaces(line, &i) < 0` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/config/validate_format.c:77 `		|| expect_comma(line, &i) < 0` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/config/validate_format.c:78 `		|| parse_component_with_spaces(line, &i) < 0)` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/config/validate_format.c:79 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/validate_format.c:80 `	while (ft_isspace(line[i]))` — ループ評価。条件が真の間ループする。
- srcs/parse/config/validate_format.c:81 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/validate_format.c:82 `	if (line[i] != '\0')` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/validate_format.c:83 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/validate_format.c:84 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/config/validate_format.c:85 `}`

## parse_component_with_spaces（srcs/parse/config/validate_format.c）

- srcs/parse/config/validate_format.c:43 `static int	parse_component_with_spaces(const char *line, int *idx)` — 関数定義開始。関数 parse_component_with_spaces の実装が始まる。
- srcs/parse/config/validate_format.c:44 `{`
- srcs/parse/config/validate_format.c:45 `	int	value;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/validate_format.c:46 ``
- srcs/parse/config/validate_format.c:47 `	while (ft_isspace(line[*idx]))` — ループ評価。条件が真の間ループする。
- srcs/parse/config/validate_format.c:48 `		(*idx)++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/validate_format.c:49 `	value = parse_rgb_component(line, idx);` — 代入。value に parse_rgb_component(line, idx) を設定する。
- srcs/parse/config/validate_format.c:50 `	if (value < 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/validate_format.c:51 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/validate_format.c:52 `	while (ft_isspace(line[*idx]))` — ループ評価。条件が真の間ループする。
- srcs/parse/config/validate_format.c:53 `		(*idx)++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/validate_format.c:54 `	return (value);` — 戻り値として value を返す。
- srcs/parse/config/validate_format.c:55 `}`

## parse_rgb_component（srcs/parse/config/load_config_utils.c）

- srcs/parse/config/load_config_utils.c:69 `int	parse_rgb_component(const char *str, int *idx)` — 関数定義開始。関数 parse_rgb_component の実装が始まる。
- srcs/parse/config/load_config_utils.c:70 `{`
- srcs/parse/config/load_config_utils.c:71 `	int	value;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config_utils.c:72 `	int	digits;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config_utils.c:73 ``
- srcs/parse/config/load_config_utils.c:74 `	value = 0;` — 代入。value に 0 を設定する。
- srcs/parse/config/load_config_utils.c:75 `	digits = 0;` — 代入。digits に 0 を設定する。
- srcs/parse/config/load_config_utils.c:76 `	while (ft_isdigit(str[*idx]) && digits < 3)` — ループ評価。条件が真の間ループする。
- srcs/parse/config/load_config_utils.c:77 `	{`
- srcs/parse/config/load_config_utils.c:78 `		value = value * 10 + (str[*idx] - '0');` — 代入。value に value * 10 + (str[*idx] - '0') を設定する。
- srcs/parse/config/load_config_utils.c:79 `		(*idx)++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config_utils.c:80 `		digits++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config_utils.c:81 `	}`
- srcs/parse/config/load_config_utils.c:82 `	if (digits == NON_NUM || value > RGB_MAX)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config_utils.c:83 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/load_config_utils.c:84 `	return (value);` — 戻り値として value を返す。
- srcs/parse/config/load_config_utils.c:85 `}`

## expect_comma（srcs/parse/config/validate_format.c）

- srcs/parse/config/validate_format.c:57 `static int	expect_comma(const char *line, int *idx)` — 関数定義開始。関数 expect_comma の実装が始まる。
- srcs/parse/config/validate_format.c:58 `{`
- srcs/parse/config/validate_format.c:59 `	if (line[*idx] != ',')` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/validate_format.c:60 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/validate_format.c:61 `	(*idx)++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/validate_format.c:62 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/config/validate_format.c:63 `}`

## all_identifiers_found（srcs/parse/config/parse_config.c）

- srcs/parse/config/parse_config.c:103 `static bool	all_identifiers_found(t_seen_flags seen_flags)` — 関数定義開始。関数 all_identifiers_found の実装が始まる。
- srcs/parse/config/parse_config.c:104 `{`
- srcs/parse/config/parse_config.c:105 `	int	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/parse_config.c:106 ``
- srcs/parse/config/parse_config.c:107 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/config/parse_config.c:108 `	while (i < 6)` — ループ評価。条件が真の間ループする。
- srcs/parse/config/parse_config.c:109 `	{`
- srcs/parse/config/parse_config.c:110 `		if (seen_flags[i] == 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/parse_config.c:111 `			return (false);` — 戻り値として false を返す。
- srcs/parse/config/parse_config.c:112 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/parse_config.c:113 `	}`
- srcs/parse/config/parse_config.c:114 `	return (true);` — 戻り値として true を返す。
- srcs/parse/config/parse_config.c:115 `}`

## validate_map（srcs/parse/map/parse_map.c）

- srcs/parse/map/parse_map.c:62 `int	validate_map(char **input_data, size_t line_index)` — 関数定義開始。関数 validate_map の実装が始まる。
- srcs/parse/map/parse_map.c:63 `{`
- srcs/parse/map/parse_map.c:64 `	size_t	map_lines;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map.c:65 `	size_t	max_len;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map.c:66 ``
- srcs/parse/map/parse_map.c:67 `	if (!input_data)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map.c:68 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map.c:69 `	while (input_data[line_index] && is_blank_line(input_data[line_index]))` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map.c:70 `		line_index++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map.c:71 `	if (!input_data[line_index])` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map.c:72 `	{`
- srcs/parse/map/parse_map.c:73 `		set_error_status(ERR_MINIMUM_MAP_SIZE);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map.c:74 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map.c:75 `	}`
- srcs/parse/map/parse_map.c:76 `	map_lines = count_map_lines(input_data, line_index);` — 代入。map_lines に count_map_lines(input_data, line_index) を設定する。
- srcs/parse/map/parse_map.c:77 `	if (map_lines < MIN_MAP_SIZE)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map.c:78 `	{`
- srcs/parse/map/parse_map.c:79 `		set_error_status(ERR_MINIMUM_MAP_SIZE);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map.c:80 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map.c:81 `	}`
- srcs/parse/map/parse_map.c:82 `	if (validate_no_empty_lines(input_data, line_index, map_lines) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map.c:83 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map.c:84 `	max_len = get_max_line_length(input_data, line_index, map_lines);` — 代入。max_len に get_max_line_length(input_data, line_index, map_lines) を設定する。
- srcs/parse/map/parse_map.c:85 `	return (run_validations(input_data, line_index, map_lines, max_len));` — 戻り値として run_validations(input_data, line_index, map_lines, max_len) を返す。
- srcs/parse/map/parse_map.c:86 `}`

## count_map_lines（srcs/parse/map/parse_map_utils.c）

- srcs/parse/map/parse_map_utils.c:35 `size_t	count_map_lines(char **input_data, size_t line_index)` — 関数定義開始。関数 count_map_lines の実装が始まる。
- srcs/parse/map/parse_map_utils.c:36 `{`
- srcs/parse/map/parse_map_utils.c:37 `	size_t	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_utils.c:38 `	size_t	last_content;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_utils.c:39 `	int		found_content;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_utils.c:40 ``
- srcs/parse/map/parse_map_utils.c:41 `	i = line_index;` — 代入。i に line_index を設定する。
- srcs/parse/map/parse_map_utils.c:42 `	last_content = line_index;` — 代入。last_content に line_index を設定する。
- srcs/parse/map/parse_map_utils.c:43 `	found_content = 0;` — 代入。found_content に 0 を設定する。
- srcs/parse/map/parse_map_utils.c:44 `	while (input_data[i])` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map_utils.c:45 `	{`
- srcs/parse/map/parse_map_utils.c:46 `		if (!is_blank_line(input_data[i]))` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_utils.c:47 `		{`
- srcs/parse/map/parse_map_utils.c:48 `			last_content = i;` — 代入。last_content に i を設定する。
- srcs/parse/map/parse_map_utils.c:49 `			found_content = 1;` — 代入。found_content に 1 を設定する。
- srcs/parse/map/parse_map_utils.c:50 `		}`
- srcs/parse/map/parse_map_utils.c:51 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_utils.c:52 `	}`
- srcs/parse/map/parse_map_utils.c:53 `	if (!found_content)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_utils.c:54 `		return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/parse_map_utils.c:55 `	return (last_content - line_index + 1);` — 戻り値として last_content - line_index + 1 を返す。
- srcs/parse/map/parse_map_utils.c:56 `}`

## validate_no_empty_lines（srcs/parse/map/parse_map.c）

- srcs/parse/map/parse_map.c:38 `static int	validate_no_empty_lines(char **input_data, size_t line_index,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map.c:39 `		size_t map_lines)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map.c:40 `{`
- srcs/parse/map/parse_map.c:41 `	size_t	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map.c:42 ``
- srcs/parse/map/parse_map.c:43 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/map/parse_map.c:44 `	while (i < map_lines)` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map.c:45 `	{`
- srcs/parse/map/parse_map.c:46 `		if (is_blank_line(input_data[line_index + i]))` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map.c:47 `		{`
- srcs/parse/map/parse_map.c:48 `			set_error_status(ERR_INVALID_CHARACTER);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map.c:49 `			return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map.c:50 `		}`
- srcs/parse/map/parse_map.c:51 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map.c:52 `	}`
- srcs/parse/map/parse_map.c:53 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/parse_map.c:54 `}`

## get_max_line_length（srcs/parse/map/parse_map_utils.c）

- srcs/parse/map/parse_map_utils.c:65 `size_t	get_max_line_length(char **input_data, size_t line_index,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map_utils.c:66 `		size_t map_lines)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map_utils.c:67 `{`
- srcs/parse/map/parse_map_utils.c:68 `	size_t	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_utils.c:69 `	size_t	max_len;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_utils.c:70 `	size_t	current_len;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_utils.c:71 ``
- srcs/parse/map/parse_map_utils.c:72 `	max_len = 0;` — 代入。max_len に 0 を設定する。
- srcs/parse/map/parse_map_utils.c:73 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/map/parse_map_utils.c:74 `	while (i < map_lines)` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map_utils.c:75 `	{`
- srcs/parse/map/parse_map_utils.c:76 `		current_len = ft_strlen(input_data[line_index + i]);` — 代入。current_len に ft_strlen(input_data[line_index + i]) を設定する。
- srcs/parse/map/parse_map_utils.c:77 `		if (current_len > max_len)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_utils.c:78 `			max_len = current_len;` — 代入。max_len に current_len を設定する。
- srcs/parse/map/parse_map_utils.c:79 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_utils.c:80 `	}`
- srcs/parse/map/parse_map_utils.c:81 `	return (max_len);` — 戻り値として max_len を返す。
- srcs/parse/map/parse_map_utils.c:82 `}`

## run_validations（srcs/parse/map/parse_map.c）

- srcs/parse/map/parse_map.c:21 `static int	run_validations(char **input_data, size_t line_index,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map.c:22 `				size_t map_lines, size_t max_len)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map.c:23 `{`
- srcs/parse/map/parse_map.c:24 `	if (validate_invalid_chars(input_data, line_index, map_lines) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map.c:25 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map.c:26 `	if (validate_map_size(input_data, line_index, map_lines, max_len) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map.c:27 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map.c:28 `	if (validate_player_start(input_data, line_index, map_lines) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map.c:29 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map.c:30 `	if (validate_surrounded_by_walls(input_data, line_index, map_lines,` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map.c:31 `			max_len) != 0)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map.c:32 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map.c:33 `	if (validate_spaces(input_data, line_index, map_lines, max_len) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map.c:34 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map.c:35 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/parse_map.c:36 `}`

## validate_invalid_chars（srcs/parse/map/parse_map_validate.c）

- srcs/parse/map/parse_map_validate.c:112 `int	validate_invalid_chars(char **input_data, size_t line_index,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map_validate.c:113 `		size_t map_lines)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map_validate.c:114 `{`
- srcs/parse/map/parse_map_validate.c:115 `	size_t	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_validate.c:116 `	size_t	j;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_validate.c:117 `	char	c;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_validate.c:118 ``
- srcs/parse/map/parse_map_validate.c:119 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/map/parse_map_validate.c:120 `	while (i < map_lines)` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map_validate.c:121 `	{`
- srcs/parse/map/parse_map_validate.c:122 `		j = 0;` — 代入。j に 0 を設定する。
- srcs/parse/map/parse_map_validate.c:123 `		while (input_data[line_index + i][j])` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map_validate.c:124 `		{`
- srcs/parse/map/parse_map_validate.c:125 `			c = input_data[line_index + i][j];` — 代入。c に input_data[line_index + i][j] を設定する。
- srcs/parse/map/parse_map_validate.c:126 `			if (!is_valid_char(c))` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_validate.c:127 `			{`
- srcs/parse/map/parse_map_validate.c:128 `				set_error_status(ERR_INVALID_CHARACTER);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map_validate.c:129 `				return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_validate.c:130 `			}`
- srcs/parse/map/parse_map_validate.c:131 `			j++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_validate.c:132 `		}`
- srcs/parse/map/parse_map_validate.c:133 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_validate.c:134 `	}`
- srcs/parse/map/parse_map_validate.c:135 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/parse_map_validate.c:136 `}`

## is_valid_char（srcs/parse/map/parse_map_utils.c）

- srcs/parse/map/parse_map_utils.c:23 `bool	is_valid_char(char c)` — 関数定義開始。関数 is_valid_char の実装が始まる。
- srcs/parse/map/parse_map_utils.c:24 `{`
- srcs/parse/map/parse_map_utils.c:25 `	return (c == '0' || c == '1' || c == 'N' || c == 'S'` — 戻り値として (c == '0' || c == '1' || c == 'N' || c == 'S' を返す。
- srcs/parse/map/parse_map_utils.c:26 `		|| c == 'E' || c == 'W' || c == ' ');` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map_utils.c:27 `}`

## validate_map_size（srcs/parse/map/parse_map_validate.c）

- srcs/parse/map/parse_map_validate.c:31 `int	validate_map_size(char **input_data, size_t line_index,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map_validate.c:32 `		size_t map_lines, size_t max_len)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map_validate.c:33 `{`
- srcs/parse/map/parse_map_validate.c:34 `	(void)input_data;` — 文の評価。未使用変数の警告を抑止する。
- srcs/parse/map/parse_map_validate.c:35 `	(void)line_index;` — 文の評価。未使用変数の警告を抑止する。
- srcs/parse/map/parse_map_validate.c:36 `	if (map_lines < MIN_MAP_SIZE)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_validate.c:37 `	{`
- srcs/parse/map/parse_map_validate.c:38 `		set_error_status(ERR_MINIMUM_MAP_SIZE);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map_validate.c:39 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_validate.c:40 `	}`
- srcs/parse/map/parse_map_validate.c:41 `	if (map_lines > MAX_MAP_SIZE || max_len > MAX_MAP_SIZE)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_validate.c:42 `	{`
- srcs/parse/map/parse_map_validate.c:43 `		set_error_status(ERR_MAXIMUM_MAP_SIZE);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map_validate.c:44 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_validate.c:45 `	}`
- srcs/parse/map/parse_map_validate.c:46 `	if (max_len < MIN_MAP_SIZE)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_validate.c:47 `	{`
- srcs/parse/map/parse_map_validate.c:48 `		set_error_status(ERR_MINIMUM_MAP_SIZE);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map_validate.c:49 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_validate.c:50 `	}`
- srcs/parse/map/parse_map_validate.c:51 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/parse_map_validate.c:52 `}`

## validate_player_start（srcs/parse/map/parse_map_validate.c）

- srcs/parse/map/parse_map_validate.c:86 `int	validate_player_start(char **input_data, size_t line_index,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map_validate.c:87 `		size_t map_lines)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map_validate.c:88 `{`
- srcs/parse/map/parse_map_validate.c:89 `	int	player_count;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_validate.c:90 ``
- srcs/parse/map/parse_map_validate.c:91 `	player_count = count_players(input_data, line_index, map_lines);` — 代入。player_count に count_players(input_data, line_index, map_lines) を設定する。
- srcs/parse/map/parse_map_validate.c:92 `	if (player_count == 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_validate.c:93 `	{`
- srcs/parse/map/parse_map_validate.c:94 `		set_error_status(ERR_PLAYER_COUNT_ZERO);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map_validate.c:95 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_validate.c:96 `	}`
- srcs/parse/map/parse_map_validate.c:97 `	if (player_count > 1)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_validate.c:98 `	{`
- srcs/parse/map/parse_map_validate.c:99 `		set_error_status(ERR_PLAYER_COUNT_MULTIPLE);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map_validate.c:100 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_validate.c:101 `	}`
- srcs/parse/map/parse_map_validate.c:102 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/parse_map_validate.c:103 `}`

## count_players（srcs/parse/map/parse_map_validate.c）

- srcs/parse/map/parse_map_validate.c:54 `static int	count_players(char **input_data, size_t line_index,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map_validate.c:55 `				size_t map_lines)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map_validate.c:56 `{`
- srcs/parse/map/parse_map_validate.c:57 `	size_t	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_validate.c:58 `	size_t	j;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_validate.c:59 `	int		count;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_validate.c:60 `	char	c;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_validate.c:61 ``
- srcs/parse/map/parse_map_validate.c:62 `	count = 0;` — 代入。count に 0 を設定する。
- srcs/parse/map/parse_map_validate.c:63 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/map/parse_map_validate.c:64 `	while (i < map_lines)` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map_validate.c:65 `	{`
- srcs/parse/map/parse_map_validate.c:66 `		j = 0;` — 代入。j に 0 を設定する。
- srcs/parse/map/parse_map_validate.c:67 `		while (input_data[line_index + i][j])` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map_validate.c:68 `		{`
- srcs/parse/map/parse_map_validate.c:69 `			c = input_data[line_index + i][j];` — 代入。c に input_data[line_index + i][j] を設定する。
- srcs/parse/map/parse_map_validate.c:70 `			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_validate.c:71 `				count++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_validate.c:72 `			j++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_validate.c:73 `		}`
- srcs/parse/map/parse_map_validate.c:74 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_validate.c:75 `	}`
- srcs/parse/map/parse_map_validate.c:76 `	return (count);` — 戻り値として count を返す。
- srcs/parse/map/parse_map_validate.c:77 `}`

## validate_surrounded_by_walls（srcs/parse/map/parse_map_walls.c）

- srcs/parse/map/parse_map_walls.c:29 `int	validate_surrounded_by_walls(char **input_data, size_t line_index,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map_walls.c:30 `		size_t map_lines, size_t max_len)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map_walls.c:31 `{`
- srcs/parse/map/parse_map_walls.c:32 `	size_t	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_walls.c:33 `	char	c;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_walls.c:34 ``
- srcs/parse/map/parse_map_walls.c:35 `	(void)max_len;` — 文の評価。未使用変数の警告を抑止する。
- srcs/parse/map/parse_map_walls.c:36 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/map/parse_map_walls.c:37 `	while (input_data[line_index][i])` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map_walls.c:38 `	{`
- srcs/parse/map/parse_map_walls.c:39 `		c = input_data[line_index][i];` — 代入。c に input_data[line_index][i] を設定する。
- srcs/parse/map/parse_map_walls.c:40 `		if (c != ' ' && c != '1')` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_walls.c:41 `		{`
- srcs/parse/map/parse_map_walls.c:42 `			set_error_status(ERR_WALL_ENCLOSURE);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map_walls.c:43 `			return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_walls.c:44 `		}`
- srcs/parse/map/parse_map_walls.c:45 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_walls.c:46 `	}`
- srcs/parse/map/parse_map_walls.c:47 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/map/parse_map_walls.c:48 `	while (input_data[line_index + map_lines - 1][i])` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map_walls.c:49 `	{`
- srcs/parse/map/parse_map_walls.c:50 `		c = input_data[line_index + map_lines - 1][i];` — 代入。c に input_data[line_index + map_lines - 1][i] を設定する。
- srcs/parse/map/parse_map_walls.c:51 `		if (c != ' ' && c != '1')` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_walls.c:52 `		{`
- srcs/parse/map/parse_map_walls.c:53 `			set_error_status(ERR_WALL_ENCLOSURE);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map_walls.c:54 `			return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_walls.c:55 `		}`
- srcs/parse/map/parse_map_walls.c:56 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_walls.c:57 `	}`
- srcs/parse/map/parse_map_walls.c:58 `	return (check_side_borders(input_data, line_index, map_lines));` — 戻り値として check_side_borders(input_data, line_index, map_lines) を返す。
- srcs/parse/map/parse_map_walls.c:59 `}`

## check_side_borders（srcs/parse/map/parse_map_walls.c）

- srcs/parse/map/parse_map_walls.c:95 `static int	check_side_borders(char **input_data, size_t line_index,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map_walls.c:96 `		size_t map_lines)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map_walls.c:97 `{`
- srcs/parse/map/parse_map_walls.c:98 `	size_t	j;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_walls.c:99 `	int		result;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_walls.c:100 ``
- srcs/parse/map/parse_map_walls.c:101 `	j = 0;` — 代入。j に 0 を設定する。
- srcs/parse/map/parse_map_walls.c:102 `	while (j < map_lines)` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map_walls.c:103 `	{`
- srcs/parse/map/parse_map_walls.c:104 `		result = check_row_borders(input_data, line_index, j);` — 代入。result に check_row_borders(input_data, line_index, j) を設定する。
- srcs/parse/map/parse_map_walls.c:105 `		if (result < 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_walls.c:106 `			return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_walls.c:107 `		j++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_walls.c:108 `	}`
- srcs/parse/map/parse_map_walls.c:109 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/parse_map_walls.c:110 `}`

## check_row_borders（srcs/parse/map/parse_map_walls.c）

- srcs/parse/map/parse_map_walls.c:61 `static int	check_row_borders(char **input_data, size_t line_index, size_t j)` — 関数定義開始。関数 check_row_borders の実装が始まる。
- srcs/parse/map/parse_map_walls.c:62 `{`
- srcs/parse/map/parse_map_walls.c:63 `	size_t	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_walls.c:64 `	size_t	left_idx;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_walls.c:65 `	size_t	right_idx;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_walls.c:66 `	size_t	row_len;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_walls.c:67 ``
- srcs/parse/map/parse_map_walls.c:68 `	row_len = ft_strlen(input_data[line_index + j]);` — 代入。row_len に ft_strlen(input_data[line_index + j]) を設定する。
- srcs/parse/map/parse_map_walls.c:69 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/map/parse_map_walls.c:70 `	while (i < row_len && input_data[line_index + j][i] == ' ')` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map_walls.c:71 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_walls.c:72 `	left_idx = i;` — 代入。left_idx に i を設定する。
- srcs/parse/map/parse_map_walls.c:73 `	if (row_len == 0 || left_idx == row_len)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_walls.c:74 `		return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/parse_map_walls.c:75 `	i = row_len;` — 代入。i に row_len を設定する。
- srcs/parse/map/parse_map_walls.c:76 `	while (i > left_idx && input_data[line_index + j][i - 1] == ' ')` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map_walls.c:77 `		i--;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_walls.c:78 `	if (i == 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_walls.c:79 `		right_idx = 0;` — 代入。right_idx に 0 を設定する。
- srcs/parse/map/parse_map_walls.c:80 `	else` — 分岐。前条件が偽のときの分岐。
- srcs/parse/map/parse_map_walls.c:81 `		right_idx = i - 1;` — 代入。right_idx に i - 1 を設定する。
- srcs/parse/map/parse_map_walls.c:82 `	if (input_data[line_index + j][left_idx] != '1')` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_walls.c:83 `	{`
- srcs/parse/map/parse_map_walls.c:84 `		set_error_status(ERR_WALL_ENCLOSURE);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map_walls.c:85 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_walls.c:86 `	}`
- srcs/parse/map/parse_map_walls.c:87 `	if (input_data[line_index + j][right_idx] != '1')` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_walls.c:88 `	{`
- srcs/parse/map/parse_map_walls.c:89 `		set_error_status(ERR_WALL_ENCLOSURE);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map_walls.c:90 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_walls.c:91 `	}`
- srcs/parse/map/parse_map_walls.c:92 `	return (1);` — 戻り値として 1 を返す。
- srcs/parse/map/parse_map_walls.c:93 `}`

## validate_spaces（srcs/parse/map/parse_map_spaces.c）

- srcs/parse/map/parse_map_spaces.c:29 `int	validate_spaces(char **input_data, size_t line_index,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map_spaces.c:30 `		size_t map_lines, size_t max_len_param)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map_spaces.c:31 `{`
- srcs/parse/map/parse_map_spaces.c:32 `	size_t	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_spaces.c:33 `	size_t	j;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_spaces.c:34 `	size_t	max_len;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_spaces.c:35 `	char	c;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_spaces.c:36 ``
- srcs/parse/map/parse_map_spaces.c:37 `	max_len = max_len_param;` — 代入。max_len に max_len_param を設定する。
- srcs/parse/map/parse_map_spaces.c:38 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/map/parse_map_spaces.c:39 `	while (i < map_lines)` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map_spaces.c:40 `	{`
- srcs/parse/map/parse_map_spaces.c:41 `		j = 0;` — 代入。j に 0 を設定する。
- srcs/parse/map/parse_map_spaces.c:42 `		while (j < max_len)` — ループ評価。条件が真の間ループする。
- srcs/parse/map/parse_map_spaces.c:43 `		{`
- srcs/parse/map/parse_map_spaces.c:44 `			c = get_char_at(input_data, line_index, i, j);` — 代入。c に get_char_at(input_data, line_index, i, j) を設定する。
- srcs/parse/map/parse_map_spaces.c:45 `			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_spaces.c:46 `			{`
- srcs/parse/map/parse_map_spaces.c:47 `				if (check_all_adjacent(input_data, line_index,` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_spaces.c:48 `						map_lines, i, j) != 0)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map_spaces.c:49 `					return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_spaces.c:50 `			}`
- srcs/parse/map/parse_map_spaces.c:51 `			j++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_spaces.c:52 `		}`
- srcs/parse/map/parse_map_spaces.c:53 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/parse_map_spaces.c:54 `	}`
- srcs/parse/map/parse_map_spaces.c:55 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/parse_map_spaces.c:56 `}`

## get_char_at（srcs/parse/map/parse_map_utils.c）

- srcs/parse/map/parse_map_utils.c:92 `char	get_char_at(char **input_data, size_t line_index,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map_utils.c:93 `		size_t row, size_t col)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map_utils.c:94 `{`
- srcs/parse/map/parse_map_utils.c:95 `	size_t	line_len;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_utils.c:96 ``
- srcs/parse/map/parse_map_utils.c:97 `	if (!input_data[line_index + row])` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_utils.c:98 `		return (' ');` — 戻り値として ' ' を返す。
- srcs/parse/map/parse_map_utils.c:99 `	line_len = ft_strlen(input_data[line_index + row]);` — 代入。line_len に ft_strlen(input_data[line_index + row]) を設定する。
- srcs/parse/map/parse_map_utils.c:100 `	if (col >= line_len)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_utils.c:101 `		return (' ');` — 戻り値として ' ' を返す。
- srcs/parse/map/parse_map_utils.c:102 `	return (input_data[line_index + row][col]);` — 戻り値として input_data[line_index + row][col] を返す。
- srcs/parse/map/parse_map_utils.c:103 `}`

## check_all_adjacent（srcs/parse/map/parse_map_spaces.c）

- srcs/parse/map/parse_map_spaces.c:81 `static int	check_all_adjacent(char **input_data, size_t line_index,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map_spaces.c:82 `		size_t map_lines, size_t i, size_t j)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map_spaces.c:83 `{`
- srcs/parse/map/parse_map_spaces.c:84 `	if (i > 0 && check_dir(input_data, line_index, map_lines, i - 1, j) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_spaces.c:85 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_spaces.c:86 `	if (j > 0 && check_dir(input_data, line_index, map_lines, i, j - 1) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_spaces.c:87 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_spaces.c:88 `	if (check_dir(input_data, line_index, map_lines, i + 1, j) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_spaces.c:89 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_spaces.c:90 `	if (check_dir(input_data, line_index, map_lines, i, j + 1) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_spaces.c:91 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_spaces.c:92 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/parse_map_spaces.c:93 `}`

## check_dir（srcs/parse/map/parse_map_spaces.c）

- srcs/parse/map/parse_map_spaces.c:58 `static int	check_dir(char **input_data, size_t line_index,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/map/parse_map_spaces.c:59 `				size_t map_lines, size_t i, size_t j)` — 文の評価。式/制御構文を処理する。
- srcs/parse/map/parse_map_spaces.c:60 `{`
- srcs/parse/map/parse_map_spaces.c:61 `	size_t	row_len;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_spaces.c:62 `	char	adj;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/parse_map_spaces.c:63 ``
- srcs/parse/map/parse_map_spaces.c:64 `	if (i >= map_lines)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_spaces.c:65 `	{`
- srcs/parse/map/parse_map_spaces.c:66 `		set_error_status(ERR_SPACE_VOID_CONTACT);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map_spaces.c:67 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_spaces.c:68 `	}`
- srcs/parse/map/parse_map_spaces.c:69 `	row_len = ft_strlen(input_data[line_index + i]);` — 代入。row_len に ft_strlen(input_data[line_index + i]) を設定する。
- srcs/parse/map/parse_map_spaces.c:70 `	if (j >= row_len)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_spaces.c:71 `	{`
- srcs/parse/map/parse_map_spaces.c:72 `		set_error_status(ERR_SPACE_VOID_CONTACT);` — 関数呼び出し。set_error_status を呼び出し、エラーステータスを設定する。
- srcs/parse/map/parse_map_spaces.c:73 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/parse_map_spaces.c:74 `	}`
- srcs/parse/map/parse_map_spaces.c:75 `	adj = input_data[line_index + i][j];` — 代入。adj に input_data[line_index + i][j] を設定する。
- srcs/parse/map/parse_map_spaces.c:76 `	if (adj == ' ')` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/parse_map_spaces.c:77 `		return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/parse_map_spaces.c:78 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/parse_map_spaces.c:79 `}`

## load_data（srcs/parse/load_data.c）

- srcs/parse/load_data.c:20 `int	load_data(const char **input_data, void *data)` — 関数定義開始。関数 load_data の実装が始まる。
- srcs/parse/load_data.c:21 `{`
- srcs/parse/load_data.c:22 `	t_game_data	*game_data;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/load_data.c:23 `	size_t		line_index;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/load_data.c:24 ``
- srcs/parse/load_data.c:25 `	game_data = (t_game_data *)data;` — 代入。game_data に (t_game_data *)data を設定する。
- srcs/parse/load_data.c:26 `	if (load_config(input_data, &game_data->config) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/load_data.c:27 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/load_data.c:28 `	line_index = 0;` — 代入。line_index に 0 を設定する。
- srcs/parse/load_data.c:29 `	if (skip_config_lines(input_data, &line_index) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/load_data.c:30 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/load_data.c:31 `	if (load_map((char **)input_data, line_index, &game_data->map) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/load_data.c:32 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/load_data.c:33 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/load_data.c:34 `}`

## load_config（srcs/parse/config/load_config.c）

- srcs/parse/config/load_config.c:79 `int	load_config(const char **input_data, t_config_data *config)` — 関数定義開始。関数 load_config の実装が始まる。
- srcs/parse/config/load_config.c:80 `{`
- srcs/parse/config/load_config.c:81 `	size_t	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config.c:82 `	int		loaded_count;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config.c:83 ``
- srcs/parse/config/load_config.c:84 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/config/load_config.c:85 `	loaded_count = 0;` — 代入。loaded_count に 0 を設定する。
- srcs/parse/config/load_config.c:86 `	while (input_data[i] && loaded_count < 6)` — ループ評価。条件が真の間ループする。
- srcs/parse/config/load_config.c:87 `	{`
- srcs/parse/config/load_config.c:88 `		if (is_blank_line(input_data[i]))` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config.c:89 `		{`
- srcs/parse/config/load_config.c:90 `			i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config.c:91 `			continue ;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config.c:92 `		}`
- srcs/parse/config/load_config.c:93 `		if (process_config_line(input_data[i], config) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config.c:94 `			return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/load_config.c:95 `		loaded_count++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config.c:96 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config.c:97 `	}`
- srcs/parse/config/load_config.c:98 `	if (loaded_count != 6)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config.c:99 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/load_config.c:100 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/config/load_config.c:101 `}`

## process_config_line（srcs/parse/config/load_config.c）

- srcs/parse/config/load_config.c:67 `static int	process_config_line(const char *line, t_config_data *config)` — 関数定義開始。関数 process_config_line の実装が始まる。
- srcs/parse/config/load_config.c:68 `{`
- srcs/parse/config/load_config.c:69 `	t_identifier	id;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config.c:70 ``
- srcs/parse/config/load_config.c:71 `	id = detect_identifier(line);` — 代入。id に detect_identifier(line) を設定する。
- srcs/parse/config/load_config.c:72 `	if (id == ID_UNKNOWN)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config.c:73 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/load_config.c:74 `	if (store_config_value(id, line, config) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config.c:75 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/load_config.c:76 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/config/load_config.c:77 `}`

## store_config_value（srcs/parse/config/load_config.c）

- srcs/parse/config/load_config.c:53 `static int	store_config_value(t_identifier id, const char *line,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/config/load_config.c:54 `				t_config_data *config)` — 文の評価。式/制御構文を処理する。
- srcs/parse/config/load_config.c:55 `{`
- srcs/parse/config/load_config.c:56 `	if (id >= ID_NO && id <= ID_EA)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config.c:57 `		return (store_texture_path(id, line, config));` — 戻り値として store_texture_path(id, line, config) を返す。
- srcs/parse/config/load_config.c:58 `	else if (id == ID_F)` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/parse/config/load_config.c:59 `		return (parse_rgb_color(get_value_ptr(line, id),` — 戻り値として (parse_rgb_color(get_value_ptr(line, id), を返す。
- srcs/parse/config/load_config.c:60 `				&config->floor_color));` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config.c:61 `	else if (id == ID_C)` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/parse/config/load_config.c:62 `		return (parse_rgb_color(get_value_ptr(line, id),` — 戻り値として (parse_rgb_color(get_value_ptr(line, id), を返す。
- srcs/parse/config/load_config.c:63 `				&config->ceiling_color));` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config.c:64 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/config/load_config.c:65 `}`

## store_texture_path（srcs/parse/config/load_config.c）

- srcs/parse/config/load_config.c:34 `static int	store_texture_path(t_identifier id, const char *line,` — 式の継続。前後の行と合わせて評価する。
- srcs/parse/config/load_config.c:35 `				t_config_data *config)` — 文の評価。式/制御構文を処理する。
- srcs/parse/config/load_config.c:36 `{`
- srcs/parse/config/load_config.c:37 `	char	*path;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config.c:38 ``
- srcs/parse/config/load_config.c:39 `	path = extract_texture_path(line, id);` — 代入。path に extract_texture_path(line, id) を設定する。
- srcs/parse/config/load_config.c:40 `	if (!path || access(path, R_OK) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config.c:41 `		return (free(path), -1);` — 戻り値として free(path), -1 を返す。
- srcs/parse/config/load_config.c:42 `	if (id == ID_NO)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config.c:43 `		config->north_texture_path = path;` — 代入。config->north_texture_path に path を設定する。
- srcs/parse/config/load_config.c:44 `	else if (id == ID_SO)` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/parse/config/load_config.c:45 `		config->south_texture_path = path;` — 代入。config->south_texture_path に path を設定する。
- srcs/parse/config/load_config.c:46 `	else if (id == ID_WE)` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/parse/config/load_config.c:47 `		config->west_texture_path = path;` — 代入。config->west_texture_path に path を設定する。
- srcs/parse/config/load_config.c:48 `	else if (id == ID_EA)` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/parse/config/load_config.c:49 `		config->east_texture_path = path;` — 代入。config->east_texture_path に path を設定する。
- srcs/parse/config/load_config.c:50 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/config/load_config.c:51 `}`

## extract_texture_path（srcs/parse/config/load_config_utils.c）

- srcs/parse/config/load_config_utils.c:55 `char	*extract_texture_path(const char *line, t_identifier id)` — 関数定義開始。関数 extract_texture_path の実装が始まる。
- srcs/parse/config/load_config_utils.c:56 `{`
- srcs/parse/config/load_config_utils.c:57 `	int		i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config_utils.c:58 `	int		start;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config_utils.c:59 `	int		len;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config_utils.c:60 ``
- srcs/parse/config/load_config_utils.c:61 `	i = skip_to_value_start(line, id);` — 代入。i に skip_to_value_start(line, id) を設定する。
- srcs/parse/config/load_config_utils.c:62 `	start = i;` — 代入。start に i を設定する。
- srcs/parse/config/load_config_utils.c:63 `	while (line[i] && !ft_isspace(line[i]) && line[i] != '\n')` — ループ評価。条件が真の間ループする。
- srcs/parse/config/load_config_utils.c:64 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config_utils.c:65 `	len = i - start;` — 代入。len に i - start を設定する。
- srcs/parse/config/load_config_utils.c:66 `	return (ft_strndup(&line[start], len));` — 戻り値として ft_strndup(&line[start], len) を返す。
- srcs/parse/config/load_config_utils.c:67 `}`

## skip_to_value_start（srcs/parse/config/load_config_utils.c）

- srcs/parse/config/load_config_utils.c:17 `static int	skip_to_value_start(const char *line, t_identifier id)` — 関数定義開始。関数 skip_to_value_start の実装が始まる。
- srcs/parse/config/load_config_utils.c:18 `{`
- srcs/parse/config/load_config_utils.c:19 `	int	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config_utils.c:20 ``
- srcs/parse/config/load_config_utils.c:21 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/config/load_config_utils.c:22 `	while (ft_isspace(line[i]))` — ループ評価。条件が真の間ループする。
- srcs/parse/config/load_config_utils.c:23 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config_utils.c:24 `	if (id >= ID_NO && id <= ID_EA)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config_utils.c:25 `		i += 2;` — 代入。i に 2 を加算して設定する。
- srcs/parse/config/load_config_utils.c:26 `	else` — 分岐。前条件が偽のときの分岐。
- srcs/parse/config/load_config_utils.c:27 `		i += 1;` — 代入。i に 1 を加算して設定する。
- srcs/parse/config/load_config_utils.c:28 `	while (ft_isspace(line[i]))` — ループ評価。条件が真の間ループする。
- srcs/parse/config/load_config_utils.c:29 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config_utils.c:30 `	return (i);` — 戻り値として i を返す。
- srcs/parse/config/load_config_utils.c:31 `}`

## get_value_ptr（srcs/parse/config/load_config.c）

- srcs/parse/config/load_config.c:18 `static const char	*get_value_ptr(const char *line, t_identifier id)` — 関数定義開始。関数 get_value_ptr の実装が始まる。
- srcs/parse/config/load_config.c:19 `{`
- srcs/parse/config/load_config.c:20 `	int	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config.c:21 ``
- srcs/parse/config/load_config.c:22 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/config/load_config.c:23 `	while (ft_isspace(line[i]))` — ループ評価。条件が真の間ループする。
- srcs/parse/config/load_config.c:24 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config.c:25 `	if (id >= ID_NO && id <= ID_EA)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config.c:26 `		i += 2;` — 代入。i に 2 を加算して設定する。
- srcs/parse/config/load_config.c:27 `	else` — 分岐。前条件が偽のときの分岐。
- srcs/parse/config/load_config.c:28 `		i += 1;` — 代入。i に 1 を加算して設定する。
- srcs/parse/config/load_config.c:29 `	while (ft_isspace(line[i]))` — ループ評価。条件が真の間ループする。
- srcs/parse/config/load_config.c:30 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config.c:31 `	return (line + i);` — 戻り値として line + i を返す。
- srcs/parse/config/load_config.c:32 `}`

## parse_rgb_color（srcs/parse/config/load_config_utils.c）

- srcs/parse/config/load_config_utils.c:87 `int	parse_rgb_color(const char *line, t_color *color)` — 関数定義開始。関数 parse_rgb_color の実装が始まる。
- srcs/parse/config/load_config_utils.c:88 `{`
- srcs/parse/config/load_config_utils.c:89 `	int	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config_utils.c:90 `	int	r;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config_utils.c:91 `	int	g;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config_utils.c:92 `	int	b;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config_utils.c:93 ``
- srcs/parse/config/load_config_utils.c:94 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/config/load_config_utils.c:95 `	r = parse_component_with_spaces(line, &i);` — 代入。r に parse_component_with_spaces(line, &i) を設定する。
- srcs/parse/config/load_config_utils.c:96 `	if (r == -1 || expect_comma(line, &i) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config_utils.c:97 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/load_config_utils.c:98 `	g = parse_component_with_spaces(line, &i);` — 代入。g に parse_component_with_spaces(line, &i) を設定する。
- srcs/parse/config/load_config_utils.c:99 `	if (g == -1 || expect_comma(line, &i) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config_utils.c:100 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/load_config_utils.c:101 `	b = parse_component_with_spaces(line, &i);` — 代入。b に parse_component_with_spaces(line, &i) を設定する。
- srcs/parse/config/load_config_utils.c:102 `	if (b == -1)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config_utils.c:103 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/load_config_utils.c:104 `	while (ft_isspace(line[i]))` — ループ評価。条件が真の間ループする。
- srcs/parse/config/load_config_utils.c:105 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config_utils.c:106 `	if (line[i] != '\0')` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config_utils.c:107 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/load_config_utils.c:108 `	color->r = r;` — 代入。color->r に r を設定する。
- srcs/parse/config/load_config_utils.c:109 `	color->g = g;` — 代入。color->g に g を設定する。
- srcs/parse/config/load_config_utils.c:110 `	color->b = b;` — 代入。color->b に b を設定する。
- srcs/parse/config/load_config_utils.c:111 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/config/load_config_utils.c:112 `}`

## parse_component_with_spaces（srcs/parse/config/load_config_utils.c）

- srcs/parse/config/load_config_utils.c:33 `static int	parse_component_with_spaces(const char *line, int *idx)` — 関数定義開始。関数 parse_component_with_spaces の実装が始まる。
- srcs/parse/config/load_config_utils.c:34 `{`
- srcs/parse/config/load_config_utils.c:35 `	int	value;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/config/load_config_utils.c:36 ``
- srcs/parse/config/load_config_utils.c:37 `	while (ft_isspace(line[*idx]))` — ループ評価。条件が真の間ループする。
- srcs/parse/config/load_config_utils.c:38 `		(*idx)++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config_utils.c:39 `	value = parse_rgb_component(line, idx);` — 代入。value に parse_rgb_component(line, idx) を設定する。
- srcs/parse/config/load_config_utils.c:40 `	if (value < 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config_utils.c:41 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/load_config_utils.c:42 `	while (ft_isspace(line[*idx]))` — ループ評価。条件が真の間ループする。
- srcs/parse/config/load_config_utils.c:43 `		(*idx)++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config_utils.c:44 `	return (value);` — 戻り値として value を返す。
- srcs/parse/config/load_config_utils.c:45 `}`

## expect_comma（srcs/parse/config/load_config_utils.c）

- srcs/parse/config/load_config_utils.c:47 `static int	expect_comma(const char *line, int *idx)` — 関数定義開始。関数 expect_comma の実装が始まる。
- srcs/parse/config/load_config_utils.c:48 `{`
- srcs/parse/config/load_config_utils.c:49 `	if (line[*idx] != ',')` — 条件評価。条件を評価して分岐する。
- srcs/parse/config/load_config_utils.c:50 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/config/load_config_utils.c:51 `	(*idx)++;` — 文の評価。式または宣言を処理する。
- srcs/parse/config/load_config_utils.c:52 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/config/load_config_utils.c:53 `}`

## skip_config_lines（srcs/parse/load_data.c）

- srcs/parse/load_data.c:36 `static int	skip_config_lines(const char **input_data, size_t *line_index)` — 関数定義開始。関数 skip_config_lines の実装が始まる。
- srcs/parse/load_data.c:37 `{`
- srcs/parse/load_data.c:38 `	size_t	id_count;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/load_data.c:39 `	int		done;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/load_data.c:40 ``
- srcs/parse/load_data.c:41 `	id_count = 0;` — 代入。id_count に 0 を設定する。
- srcs/parse/load_data.c:42 `	done = 0;` — 代入。done に 0 を設定する。
- srcs/parse/load_data.c:43 `	while (input_data[*line_index] && !done)` — ループ評価。条件が真の間ループする。
- srcs/parse/load_data.c:44 `	{`
- srcs/parse/load_data.c:45 `		if (process_line(input_data[*line_index], &id_count, &done) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/load_data.c:46 `			return (-1);` — 戻り値として -1 を返す。
- srcs/parse/load_data.c:47 `		if (!done)` — 条件評価。条件を評価して分岐する。
- srcs/parse/load_data.c:48 `			(*line_index)++;` — 文の評価。式または宣言を処理する。
- srcs/parse/load_data.c:49 `	}`
- srcs/parse/load_data.c:50 `	if (id_count < 6)` — 条件評価。条件を評価して分岐する。
- srcs/parse/load_data.c:51 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/load_data.c:52 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/load_data.c:53 `}`

## process_line（srcs/parse/load_data.c）

- srcs/parse/load_data.c:55 `static int	process_line(const char *line, size_t *id_count, int *done)` — 関数定義開始。関数 process_line の実装が始まる。
- srcs/parse/load_data.c:56 `{`
- srcs/parse/load_data.c:57 `	t_identifier	id;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/load_data.c:58 ``
- srcs/parse/load_data.c:59 `	if (is_blank_line(line))` — 条件評価。条件を評価して分岐する。
- srcs/parse/load_data.c:60 `		return (0);` — 戻り値として 0 を返す。
- srcs/parse/load_data.c:61 `	id = detect_identifier(line);` — 代入。id に detect_identifier(line) を設定する。
- srcs/parse/load_data.c:62 `	if (id != ID_UNKNOWN)` — 条件評価。条件を評価して分岐する。
- srcs/parse/load_data.c:63 `	{`
- srcs/parse/load_data.c:64 `		if (*id_count >= 6)` — 条件評価。条件を評価して分岐する。
- srcs/parse/load_data.c:65 `			return (-1);` — 戻り値として -1 を返す。
- srcs/parse/load_data.c:66 `		(*id_count)++;` — 文の評価。式または宣言を処理する。
- srcs/parse/load_data.c:67 `		return (0);` — 戻り値として 0 を返す。
- srcs/parse/load_data.c:68 `	}`
- srcs/parse/load_data.c:69 `	if (*id_count < 6)` — 条件評価。条件を評価して分岐する。
- srcs/parse/load_data.c:70 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/load_data.c:71 `	*done = 1;` — なし。コメント。
- srcs/parse/load_data.c:72 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/load_data.c:73 `}`

## load_map（srcs/parse/map/load_map.c）

- srcs/parse/map/load_map.c:49 `int	load_map(char **input_data, size_t line_index, t_map_data *map_data)` — 関数定義開始。関数 load_map の実装が始まる。
- srcs/parse/map/load_map.c:50 `{`
- srcs/parse/map/load_map.c:51 `	size_t	map_lines;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/load_map.c:52 `	size_t	max_len;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/load_map.c:53 `	size_t	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/load_map.c:54 ``
- srcs/parse/map/load_map.c:55 `	if (!input_data || !map_data)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/load_map.c:56 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/load_map.c:57 `	if (validate_map(input_data, line_index) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/load_map.c:58 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/load_map.c:59 `	map_lines = count_map_lines(input_data, line_index);` — 代入。map_lines に count_map_lines(input_data, line_index) を設定する。
- srcs/parse/map/load_map.c:60 `	max_len = get_max_line_length(input_data, line_index, map_lines);` — 代入。max_len に get_max_line_length(input_data, line_index, map_lines) を設定する。
- srcs/parse/map/load_map.c:61 `	map_data->map = malloc(sizeof(char *) * (map_lines + 1));` — 代入。map_data->map に malloc(sizeof(char *) * (map_lines + 1)) を設定する。
- srcs/parse/map/load_map.c:62 `	if (!map_data->map)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/load_map.c:63 `		return (-1);` — 戻り値として -1 を返す。
- srcs/parse/map/load_map.c:64 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/map/load_map.c:65 `	while (i < map_lines)` — ループ評価。条件が真の間ループする。
- srcs/parse/map/load_map.c:66 `	{`
- srcs/parse/map/load_map.c:67 `		map_data->map[i] = malloc(sizeof(char) * (max_len + 1));` — 代入。map_data->map[i] に malloc(sizeof(char) * (max_len + 1)) を設定する。
- srcs/parse/map/load_map.c:68 `		if (!map_data->map[i])` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/load_map.c:69 `			return (free_partial_map(map_data->map, i), -1);` — 戻り値として free_partial_map(map_data->map, i), -1 を返す。
- srcs/parse/map/load_map.c:70 `		copy_map_line(map_data->map[i], input_data[line_index + i], max_len);` — 関数呼び出し。copy_map_line を呼び出し、マップの1行をコピーする。
- srcs/parse/map/load_map.c:71 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/load_map.c:72 `	}`
- srcs/parse/map/load_map.c:73 `	map_data->map[map_lines] = NULL;` — 代入。map_data->map[map_lines] に NULL を設定する。
- srcs/parse/map/load_map.c:74 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/load_map.c:75 `}`

## copy_map_line（srcs/parse/map/load_map.c）

- srcs/parse/map/load_map.c:30 `static int	copy_map_line(char *dest, const char *src, size_t max_len)` — 関数定義開始。関数 copy_map_line の実装が始まる。
- srcs/parse/map/load_map.c:31 `{`
- srcs/parse/map/load_map.c:32 `	size_t	j;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/load_map.c:33 `	size_t	src_len;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/load_map.c:34 ``
- srcs/parse/map/load_map.c:35 `	src_len = ft_strlen(src);` — 代入。src_len に ft_strlen(src) を設定する。
- srcs/parse/map/load_map.c:36 `	j = 0;` — 代入。j に 0 を設定する。
- srcs/parse/map/load_map.c:37 `	while (j < max_len)` — ループ評価。条件が真の間ループする。
- srcs/parse/map/load_map.c:38 `	{`
- srcs/parse/map/load_map.c:39 `		if (j < src_len)` — 条件評価。条件を評価して分岐する。
- srcs/parse/map/load_map.c:40 `			dest[j] = src[j];` — 代入。dest[j] に src[j] を設定する。
- srcs/parse/map/load_map.c:41 `		else` — 分岐。前条件が偽のときの分岐。
- srcs/parse/map/load_map.c:42 `			dest[j] = ' ';` — 代入。dest[j] に ' ' を設定する。
- srcs/parse/map/load_map.c:43 `		j++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/load_map.c:44 `	}`
- srcs/parse/map/load_map.c:45 `	dest[max_len] = '\0';` — 代入。dest[max_len] に '\0' を設定する。
- srcs/parse/map/load_map.c:46 `	return (0);` — 戻り値として 0 を返す。
- srcs/parse/map/load_map.c:47 `}`

## init_game（srcs/engine/init/init_game.c）

- srcs/engine/init/init_game.c:27 `int	init_game(t_game *game, t_config_data *config)` — 関数定義開始。関数 init_game の実装が始まる。
- srcs/engine/init/init_game.c:28 `{`
- srcs/engine/init/init_game.c:29 `	int	i;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/init/init_game.c:30 ``
- srcs/engine/init/init_game.c:31 `	game->mlx = NULL;` — 代入。game->mlx に NULL を設定する。
- srcs/engine/init/init_game.c:32 `	game->win = NULL;` — 代入。game->win に NULL を設定する。
- srcs/engine/init/init_game.c:33 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/engine/init/init_game.c:34 `	while (i < 256)` — ループ評価。条件が真の間ループする。
- srcs/engine/init/init_game.c:35 `		game->keys[i++] = 0;` — 代入。game->keys[i++] に 0 を設定する。
- srcs/engine/init/init_game.c:36 `	if (init_mlx(game) != 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/init/init_game.c:37 `		return (1);` — 戻り値として 1 を返す。
- srcs/engine/init/init_game.c:38 `	init_image(game);` — 関数呼び出し。init_image を呼び出し、画像を初期化する。
- srcs/engine/init/init_game.c:39 `	init_textures(game, config);` — 関数呼び出し。init_textures を呼び出し、テクスチャを初期化する。
- srcs/engine/init/init_game.c:40 `	init_colors(game, config);` — 関数呼び出し。init_colors を呼び出し、色設定を初期化する。
- srcs/engine/init/init_game.c:41 `	init_world_map(game);` — 関数呼び出し。init_world_map を呼び出し、ワールドマップを初期化する。
- srcs/engine/init/init_game.c:42 `	init_player(game);` — 関数呼び出し。init_player を呼び出し、プレイヤーを初期化する。
- srcs/engine/init/init_game.c:43 `	return (0);` — 戻り値として 0 を返す。
- srcs/engine/init/init_game.c:44 `}`

## init_mlx（srcs/engine/init/init_game.c）

- srcs/engine/init/init_game.c:46 `static int	init_mlx(t_game *game)` — 関数定義開始。関数 init_mlx の実装が始まる。
- srcs/engine/init/init_game.c:47 `{`
- srcs/engine/init/init_game.c:48 `	game->mlx = mlx_init();` — 代入。game->mlx に mlx_init() を設定する。
- srcs/engine/init/init_game.c:49 `	if (!game->mlx)` — 条件評価。条件を評価して分岐する。
- srcs/engine/init/init_game.c:50 `	{`
- srcs/engine/init/init_game.c:51 `		error_exit_simple(ERR_MLX_INIT_FAILURE);` — 関数呼び出し。error_exit_simple を呼び出し、エラーで終了する。
- srcs/engine/init/init_game.c:52 `		return (1);` — 戻り値として 1 を返す。
- srcs/engine/init/init_game.c:53 `	}`
- srcs/engine/init/init_game.c:54 `	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, TITLE);` — 代入。game->win に mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, TITLE) を設定する。
- srcs/engine/init/init_game.c:55 `	if (!game->win)` — 条件評価。条件を評価して分岐する。
- srcs/engine/init/init_game.c:56 `	{`
- srcs/engine/init/init_game.c:57 `		error_exit_simple(ERR_WINDOW_CREATION_FAILURE);` — 関数呼び出し。error_exit_simple を呼び出し、エラーで終了する。
- srcs/engine/init/init_game.c:58 `		return (1);` — 戻り値として 1 を返す。
- srcs/engine/init/init_game.c:59 `	}`
- srcs/engine/init/init_game.c:60 `	return (0);` — 戻り値として 0 を返す。
- srcs/engine/init/init_game.c:61 `}`

## init_image（srcs/engine/init/init_game.c）

- srcs/engine/init/init_game.c:63 `static void	init_image(t_game *game)` — 関数定義開始。関数 init_image の実装が始まる。
- srcs/engine/init/init_game.c:64 `{`
- srcs/engine/init/init_game.c:65 `	game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);` — 代入。game->img.img に mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT) を設定する。
- srcs/engine/init/init_game.c:66 `	if (!game->img.img)` — 条件評価。条件を評価して分岐する。
- srcs/engine/init/init_game.c:67 `		error_exit_simple(ERR_IMAGE_CREATION_FAILURE);` — 関数呼び出し。error_exit_simple を呼び出し、エラーで終了する。
- srcs/engine/init/init_game.c:68 `	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,` — 式の継続。前後の行と合わせて評価する。
- srcs/engine/init/init_game.c:69 `			&game->img.line_length, &game->img.endian);` — 文の評価。式または宣言を処理する。
- srcs/engine/init/init_game.c:70 `}`

## init_textures（srcs/engine/texture/texture_init.c）

- srcs/engine/texture/texture_init.c:28 `void	init_textures(t_game *game, t_config_data *config)` — 関数定義開始。関数 init_textures の実装が始まる。
- srcs/engine/texture/texture_init.c:29 `{`
- srcs/engine/texture/texture_init.c:30 `	game->textures.width = TEX_WIDTH;` — 代入。game->textures.width に TEX_WIDTH を設定する。
- srcs/engine/texture/texture_init.c:31 `	game->textures.height = TEX_HEIGHT;` — 代入。game->textures.height に TEX_HEIGHT を設定する。
- srcs/engine/texture/texture_init.c:32 `	load_texture(game, &game->textures.north, config->north_texture_path);` — 関数呼び出し。load_texture を呼び出し、テクスチャを読み込む。
- srcs/engine/texture/texture_init.c:33 `	load_texture(game, &game->textures.south, config->south_texture_path);` — 関数呼び出し。load_texture を呼び出し、テクスチャを読み込む。
- srcs/engine/texture/texture_init.c:34 `	load_texture(game, &game->textures.east, config->east_texture_path);` — 関数呼び出し。load_texture を呼び出し、テクスチャを読み込む。
- srcs/engine/texture/texture_init.c:35 `	load_texture(game, &game->textures.west, config->west_texture_path);` — 関数呼び出し。load_texture を呼び出し、テクスチャを読み込む。
- srcs/engine/texture/texture_init.c:36 `}`

## load_texture（srcs/engine/texture/texture_init.c）

- srcs/engine/texture/texture_init.c:17 `void	load_texture(t_game *game, t_img *texture, char *path)` — 関数定義開始。関数 load_texture の実装が始まる。
- srcs/engine/texture/texture_init.c:18 `{`
- srcs/engine/texture/texture_init.c:19 `	texture->img = mlx_xpm_file_to_image(game->mlx, path,` — 式の継続。前後の行と合わせて評価する。
- srcs/engine/texture/texture_init.c:20 `			&game->textures.width, &game->textures.height);` — 文の評価。式または宣言を処理する。
- srcs/engine/texture/texture_init.c:21 `	if (!texture->img)` — 条件評価。条件を評価して分岐する。
- srcs/engine/texture/texture_init.c:22 `		error_exit_simple(ERR_TEXTURE_LOAD_FAILURE);` — 関数呼び出し。error_exit_simple を呼び出し、エラーで終了する。
- srcs/engine/texture/texture_init.c:23 `	texture->addr = mlx_get_data_addr(texture->img,` — 式の継続。前後の行と合わせて評価する。
- srcs/engine/texture/texture_init.c:24 `			&texture->bits_per_pixel, &texture->line_length,` — 式の継続。前後の行と合わせて評価する。
- srcs/engine/texture/texture_init.c:25 `			&texture->endian);` — 文の評価。式または宣言を処理する。
- srcs/engine/texture/texture_init.c:26 `}`

## init_colors（srcs/engine/texture/texture_init.c）

- srcs/engine/texture/texture_init.c:38 `void	init_colors(t_game *game, t_config_data *config)` — 関数定義開始。関数 init_colors の実装が始まる。
- srcs/engine/texture/texture_init.c:39 `{`
- srcs/engine/texture/texture_init.c:40 `	game->ceiling_color.r = config->ceiling_color.r;` — 代入。game->ceiling_color.r に config->ceiling_color.r を設定する。
- srcs/engine/texture/texture_init.c:41 `	game->ceiling_color.g = config->ceiling_color.g;` — 代入。game->ceiling_color.g に config->ceiling_color.g を設定する。
- srcs/engine/texture/texture_init.c:42 `	game->ceiling_color.b = config->ceiling_color.b;` — 代入。game->ceiling_color.b に config->ceiling_color.b を設定する。
- srcs/engine/texture/texture_init.c:43 `	game->floor_color.r = config->floor_color.r;` — 代入。game->floor_color.r に config->floor_color.r を設定する。
- srcs/engine/texture/texture_init.c:44 `	game->floor_color.g = config->floor_color.g;` — 代入。game->floor_color.g に config->floor_color.g を設定する。
- srcs/engine/texture/texture_init.c:45 `	game->floor_color.b = config->floor_color.b;` — 代入。game->floor_color.b に config->floor_color.b を設定する。
- srcs/engine/texture/texture_init.c:46 `}`

## init_world_map（srcs/engine/init/init_map.c）

- srcs/engine/init/init_map.c:27 `void	init_world_map(t_game *game)` — 関数定義開始。関数 init_world_map の実装が始まる。
- srcs/engine/init/init_map.c:28 `{`
- srcs/engine/init/init_map.c:29 `	int	i;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/init/init_map.c:30 `	int	j;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/init/init_map.c:31 ``
- srcs/engine/init/init_map.c:32 `	get_map_dimensions(game->map, &game->map_width, &game->map_height);` — 関数呼び出し。get_map_dimensions を呼び出し、マップの寸法を取得する。
- srcs/engine/init/init_map.c:33 `	game->world_map = allocate_world_map(game->map_width, game->map_height);` — 代入。game->world_map に allocate_world_map(game->map_width, game->map_height) を設定する。
- srcs/engine/init/init_map.c:34 `	if (!game->world_map)` — 条件評価。条件を評価して分岐する。
- srcs/engine/init/init_map.c:35 `		return ;` — 戻り値を返さずに関数から戻る。
- srcs/engine/init/init_map.c:36 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/engine/init/init_map.c:37 `	while (i < game->map_height)` — ループ評価。条件が真の間ループする。
- srcs/engine/init/init_map.c:38 `	{`
- srcs/engine/init/init_map.c:39 `		j = 0;` — 代入。j に 0 を設定する。
- srcs/engine/init/init_map.c:40 `		while (j < game->map_width && game->map[i] && game->map[i][j])` — ループ評価。条件が真の間ループする。
- srcs/engine/init/init_map.c:41 `		{`
- srcs/engine/init/init_map.c:42 `			if (game->map[i][j] == '1')` — 条件評価。条件を評価して分岐する。
- srcs/engine/init/init_map.c:43 `				game->world_map[i][j] = 1;` — 代入。game->world_map[i][j] に 1 を設定する。
- srcs/engine/init/init_map.c:44 `			else` — 分岐。前条件が偽のときの分岐。
- srcs/engine/init/init_map.c:45 `				game->world_map[i][j] = 0;` — 代入。game->world_map[i][j] に 0 を設定する。
- srcs/engine/init/init_map.c:46 `			j++;` — 文の評価。式または宣言を処理する。
- srcs/engine/init/init_map.c:47 `		}`
- srcs/engine/init/init_map.c:48 `		while (j < game->map_width)` — ループ評価。条件が真の間ループする。
- srcs/engine/init/init_map.c:49 `			game->world_map[i][j++] = 0;` — 代入。game->world_map[i][j++] に 0 を設定する。
- srcs/engine/init/init_map.c:50 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/engine/init/init_map.c:51 `	}`
- srcs/engine/init/init_map.c:52 `}`

## get_map_dimensions（srcs/engine/init/init_map_utils.c）

- srcs/engine/init/init_map_utils.c:15 `void	get_map_dimensions(char **map, int *width, int *height)` — 関数定義開始。関数 get_map_dimensions の実装が始まる。
- srcs/engine/init/init_map_utils.c:16 `{`
- srcs/engine/init/init_map_utils.c:17 `	int	h;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/init/init_map_utils.c:18 `	int	w;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/init/init_map_utils.c:19 `	int	max_w;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/init/init_map_utils.c:20 ``
- srcs/engine/init/init_map_utils.c:21 `	h = 0;` — 代入。h に 0 を設定する。
- srcs/engine/init/init_map_utils.c:22 `	max_w = 0;` — 代入。max_w に 0 を設定する。
- srcs/engine/init/init_map_utils.c:23 `	while (map[h])` — ループ評価。条件が真の間ループする。
- srcs/engine/init/init_map_utils.c:24 `	{`
- srcs/engine/init/init_map_utils.c:25 `		w = 0;` — 代入。w に 0 を設定する。
- srcs/engine/init/init_map_utils.c:26 `		while (map[h][w])` — ループ評価。条件が真の間ループする。
- srcs/engine/init/init_map_utils.c:27 `			w++;` — 文の評価。式または宣言を処理する。
- srcs/engine/init/init_map_utils.c:28 `		if (w > max_w)` — 条件評価。条件を評価して分岐する。
- srcs/engine/init/init_map_utils.c:29 `			max_w = w;` — 代入。max_w に w を設定する。
- srcs/engine/init/init_map_utils.c:30 `		h++;` — 文の評価。式または宣言を処理する。
- srcs/engine/init/init_map_utils.c:31 `	}`
- srcs/engine/init/init_map_utils.c:32 `	*width = max_w;` — なし。コメント。
- srcs/engine/init/init_map_utils.c:33 `	*height = h;` — なし。コメント。
- srcs/engine/init/init_map_utils.c:34 `}`

## allocate_world_map（srcs/engine/init/init_map_utils.c）

- srcs/engine/init/init_map_utils.c:36 `int	**allocate_world_map(int width, int height)` — 関数定義開始。関数 allocate_world_map の実装が始まる。
- srcs/engine/init/init_map_utils.c:37 `{`
- srcs/engine/init/init_map_utils.c:38 `	int	**world_map;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/init/init_map_utils.c:39 `	int	i;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/init/init_map_utils.c:40 ``
- srcs/engine/init/init_map_utils.c:41 `	world_map = malloc(sizeof(int *) * height);` — 代入。world_map に malloc(sizeof(int *) * height) を設定する。
- srcs/engine/init/init_map_utils.c:42 `	if (!world_map)` — 条件評価。条件を評価して分岐する。
- srcs/engine/init/init_map_utils.c:43 `		return (NULL);` — 戻り値として NULL を返す。
- srcs/engine/init/init_map_utils.c:44 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/engine/init/init_map_utils.c:45 `	while (i < height)` — ループ評価。条件が真の間ループする。
- srcs/engine/init/init_map_utils.c:46 `	{`
- srcs/engine/init/init_map_utils.c:47 `		world_map[i] = malloc(sizeof(int) * width);` — 代入。world_map[i] に malloc(sizeof(int) * width) を設定する。
- srcs/engine/init/init_map_utils.c:48 `		if (!world_map[i])` — 条件評価。条件を評価して分岐する。
- srcs/engine/init/init_map_utils.c:49 `		{`
- srcs/engine/init/init_map_utils.c:50 `			while (i > 0)` — ループ評価。条件が真の間ループする。
- srcs/engine/init/init_map_utils.c:51 `				free(world_map[--i]);` — 関数呼び出し。free を呼び出し、メモリを解放する。
- srcs/engine/init/init_map_utils.c:52 `			free(world_map);` — 関数呼び出し。free を呼び出し、メモリを解放する。
- srcs/engine/init/init_map_utils.c:53 `			return (NULL);` — 戻り値として NULL を返す。
- srcs/engine/init/init_map_utils.c:54 `		}`
- srcs/engine/init/init_map_utils.c:55 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/engine/init/init_map_utils.c:56 `	}`
- srcs/engine/init/init_map_utils.c:57 `	return (world_map);` — 戻り値として world_map を返す。
- srcs/engine/init/init_map_utils.c:58 `}`

## init_player（srcs/engine/init/init_map.c）

- srcs/engine/init/init_map.c:57 `void	init_player(t_game *game)` — 関数定義開始。関数 init_player の実装が始まる。
- srcs/engine/init/init_map.c:58 `{`
- srcs/engine/init/init_map.c:59 `	int		player_x;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/init/init_map.c:60 `	int		player_y;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/init/init_map.c:61 `	char	direction;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/init/init_map.c:62 ``
- srcs/engine/init/init_map.c:63 `	if (find_player_position(game->map, &player_x, &player_y, &direction))` — 条件評価。条件を評価して分岐する。
- srcs/engine/init/init_map.c:64 `	{`
- srcs/engine/init/init_map.c:65 `		game->player.pos_x = (double)player_x + 0.5;` — 代入。game->player.pos_x に (double)player_x + 0.5 を設定する。
- srcs/engine/init/init_map.c:66 `		game->player.pos_y = (double)player_y + 0.5;` — 代入。game->player.pos_y に (double)player_y + 0.5 を設定する。
- srcs/engine/init/init_map.c:67 `		set_player_direction(&game->player, direction);` — 関数呼び出し。set_player_direction を呼び出し、プレイヤーの向きを設定する。
- srcs/engine/init/init_map.c:68 `	}`
- srcs/engine/init/init_map.c:69 `	else` — 分岐。前条件が偽のときの分岐。
- srcs/engine/init/init_map.c:70 `	{`
- srcs/engine/init/init_map.c:71 `		game->player.pos_x = 3.5;` — 代入。game->player.pos_x に 3.5 を設定する。
- srcs/engine/init/init_map.c:72 `		game->player.pos_y = 3.5;` — 代入。game->player.pos_y に 3.5 を設定する。
- srcs/engine/init/init_map.c:73 `		game->player.dir_x = -1.0;` — 代入。game->player.dir_x に -1.0 を設定する。
- srcs/engine/init/init_map.c:74 `		game->player.dir_y = 0.0;` — 代入。game->player.dir_y に 0.0 を設定する。
- srcs/engine/init/init_map.c:75 `		game->player.plane_x = 0.0;` — 代入。game->player.plane_x に 0.0 を設定する。
- srcs/engine/init/init_map.c:76 `		game->player.plane_y = 0.66;` — 代入。game->player.plane_y に 0.66 を設定する。
- srcs/engine/init/init_map.c:77 `	}`
- srcs/engine/init/init_map.c:78 `}`

## find_player_position（srcs/engine/init/init_map.c）

- srcs/engine/init/init_map.c:80 `static int	find_player_position(char **map, int *x, int *y, char *dir)` — 関数定義開始。関数 find_player_position の実装が始まる。
- srcs/engine/init/init_map.c:81 `{`
- srcs/engine/init/init_map.c:82 `	int	i;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/init/init_map.c:83 `	int	j;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/init/init_map.c:84 ``
- srcs/engine/init/init_map.c:85 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/engine/init/init_map.c:86 `	while (map[i])` — ループ評価。条件が真の間ループする。
- srcs/engine/init/init_map.c:87 `	{`
- srcs/engine/init/init_map.c:88 `		j = 0;` — 代入。j に 0 を設定する。
- srcs/engine/init/init_map.c:89 `		while (map[i][j])` — ループ評価。条件が真の間ループする。
- srcs/engine/init/init_map.c:90 `		{`
- srcs/engine/init/init_map.c:91 `			if (map[i][j] == 'N' || map[i][j] == 'S'` — 条件評価。条件を評価して分岐する。
- srcs/engine/init/init_map.c:92 `				|| map[i][j] == 'E' || map[i][j] == 'W')` — 式の継続。前後の行と合わせて評価する。
- srcs/engine/init/init_map.c:93 `			{`
- srcs/engine/init/init_map.c:94 `				*y = i;` — なし。コメント。
- srcs/engine/init/init_map.c:95 `				*x = j;` — なし。コメント。
- srcs/engine/init/init_map.c:96 `				*dir = map[i][j];` — なし。コメント。
- srcs/engine/init/init_map.c:97 `				return (1);` — 戻り値として 1 を返す。
- srcs/engine/init/init_map.c:98 `			}`
- srcs/engine/init/init_map.c:99 `			j++;` — 文の評価。式または宣言を処理する。
- srcs/engine/init/init_map.c:100 `		}`
- srcs/engine/init/init_map.c:101 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/engine/init/init_map.c:102 `	}`
- srcs/engine/init/init_map.c:103 `	return (0);` — 戻り値として 0 を返す。
- srcs/engine/init/init_map.c:104 `}`

## set_player_direction（srcs/engine/init/init_map.c）

- srcs/engine/init/init_map.c:106 `static void	set_player_direction(t_player *player, char direction)` — 関数定義開始。関数 set_player_direction の実装が始まる。
- srcs/engine/init/init_map.c:107 `{`
- srcs/engine/init/init_map.c:108 `	if (direction == 'N')` — 条件評価。条件を評価して分岐する。
- srcs/engine/init/init_map.c:109 `	{`
- srcs/engine/init/init_map.c:110 `		player->dir_x = -1.0;` — 代入。player->dir_x に -1.0 を設定する。
- srcs/engine/init/init_map.c:111 `		player->dir_y = 0.0;` — 代入。player->dir_y に 0.0 を設定する。
- srcs/engine/init/init_map.c:112 `		player->plane_x = 0.0;` — 代入。player->plane_x に 0.0 を設定する。
- srcs/engine/init/init_map.c:113 `		player->plane_y = 0.66;` — 代入。player->plane_y に 0.66 を設定する。
- srcs/engine/init/init_map.c:114 `	}`
- srcs/engine/init/init_map.c:115 `	else if (direction == 'S')` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/engine/init/init_map.c:116 `	{`
- srcs/engine/init/init_map.c:117 `		player->dir_x = 1.0;` — 代入。player->dir_x に 1.0 を設定する。
- srcs/engine/init/init_map.c:118 `		player->dir_y = 0.0;` — 代入。player->dir_y に 0.0 を設定する。
- srcs/engine/init/init_map.c:119 `		player->plane_x = 0.0;` — 代入。player->plane_x に 0.0 を設定する。
- srcs/engine/init/init_map.c:120 `		player->plane_y = -0.66;` — 代入。player->plane_y に -0.66 を設定する。
- srcs/engine/init/init_map.c:121 `	}`
- srcs/engine/init/init_map.c:122 `	else` — 分岐。前条件が偽のときの分岐。
- srcs/engine/init/init_map.c:123 `		set_player_dir_ew(player, direction);` — 関数呼び出し。set_player_dir_ew を呼び出し、プレイヤーの向きを東西で設定する。
- srcs/engine/init/init_map.c:124 `}`

## set_player_dir_ew（srcs/engine/init/init_map.c）

- srcs/engine/init/init_map.c:126 `static void	set_player_dir_ew(t_player *player, char direction)` — 関数定義開始。関数 set_player_dir_ew の実装が始まる。
- srcs/engine/init/init_map.c:127 `{`
- srcs/engine/init/init_map.c:128 `	if (direction == 'E')` — 条件評価。条件を評価して分岐する。
- srcs/engine/init/init_map.c:129 `	{`
- srcs/engine/init/init_map.c:130 `		player->dir_x = 0.0;` — 代入。player->dir_x に 0.0 を設定する。
- srcs/engine/init/init_map.c:131 `		player->dir_y = 1.0;` — 代入。player->dir_y に 1.0 を設定する。
- srcs/engine/init/init_map.c:132 `		player->plane_x = 0.66;` — 代入。player->plane_x に 0.66 を設定する。
- srcs/engine/init/init_map.c:133 `		player->plane_y = 0.0;` — 代入。player->plane_y に 0.0 を設定する。
- srcs/engine/init/init_map.c:134 `	}`
- srcs/engine/init/init_map.c:135 `	else if (direction == 'W')` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/engine/init/init_map.c:136 `	{`
- srcs/engine/init/init_map.c:137 `		player->dir_x = 0.0;` — 代入。player->dir_x に 0.0 を設定する。
- srcs/engine/init/init_map.c:138 `		player->dir_y = -1.0;` — 代入。player->dir_y に -1.0 を設定する。
- srcs/engine/init/init_map.c:139 `		player->plane_x = -0.66;` — 代入。player->plane_x に -0.66 を設定する。
- srcs/engine/init/init_map.c:140 `		player->plane_y = 0.0;` — 代入。player->plane_y に 0.0 を設定する。
- srcs/engine/init/init_map.c:141 `	}`
- srcs/engine/init/init_map.c:142 `}`

## run_game_loop（srcs/engine/game_loop.c）

- srcs/engine/game_loop.c:55 `void	run_game_loop(t_game *game)` — 関数定義開始。関数 run_game_loop の実装が始まる。
- srcs/engine/game_loop.c:56 `{`
- srcs/engine/game_loop.c:57 `	setup_event_hooks(game);` — 関数呼び出し。setup_event_hooks を呼び出し、イベントフックを設定する。
- srcs/engine/game_loop.c:58 `	mlx_loop(game->mlx);` — 関数呼び出し。mlx_loop を呼び出し、イベントループを開始する。
- srcs/engine/game_loop.c:59 `	cleanup_game(game);` — 関数呼び出し。cleanup_game を呼び出し、ゲームをクリーンアップする。
- srcs/engine/game_loop.c:60 `}`

## setup_event_hooks（srcs/engine/game_loop.c, 開始行:28）

- srcs/engine/game_loop.c:28 `static void	setup_event_hooks(t_game *game)` — 関数定義開始。関数 setup_event_hooks の実装が始まる。
- srcs/engine/game_loop.c:29 `{`
- srcs/engine/game_loop.c:30 `	mlx_hook(game->win, ON_KEYDOWN, KeyPressMask, handle_keypress, game);` — 関数呼び出し。mlx_hook を呼び出し、イベントフックを設定する。
- srcs/engine/game_loop.c:31 `	mlx_hook(game->win, ON_KEYUP, KeyReleaseMask, handle_keyrelease, game);` — 関数呼び出し。mlx_hook を呼び出し、イベントフックを設定する。
- srcs/engine/game_loop.c:32 `	mlx_hook(game->win, ON_DESTROY, StructureNotifyMask, close_window, game);` — 関数呼び出し。mlx_hook を呼び出し、イベントフックを設定する。
- srcs/engine/game_loop.c:33 `	mlx_loop_hook(game->mlx, render_frame, game);` — 関数呼び出し。mlx_loop_hook を呼び出し、ループフックを設定する。
- srcs/engine/game_loop.c:34 `}`

## render_frame（srcs/engine/renderer/render_frame.c）

- srcs/engine/renderer/render_frame.c:18 `int	render_frame(t_game *game)` — 関数定義開始。関数 render_frame の実装が始まる。
- srcs/engine/renderer/render_frame.c:19 `{`
- srcs/engine/renderer/render_frame.c:20 `	process_held_keys(game);` — 関数呼び出し。process_held_keys を呼び出し、押下中のキーを処理する。
- srcs/engine/renderer/render_frame.c:21 `	cast_rays(game);` — 関数呼び出し。cast_rays を呼び出し、レイを投射する。
- srcs/engine/renderer/render_frame.c:22 `	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);` — 関数呼び出し。mlx_put_image_to_window を呼び出し、画像をウィンドウに描画する。
- srcs/engine/renderer/render_frame.c:23 `	return (0);` — 戻り値として 0 を返す。
- srcs/engine/renderer/render_frame.c:24 `}`

## process_held_keys（srcs/engine/key_handler/key_handler.c）

- srcs/engine/key_handler/key_handler.c:53 `void	process_held_keys(t_game *game)` — 関数定義開始。関数 process_held_keys の実装が始まる。
- srcs/engine/key_handler/key_handler.c:54 `{`
- srcs/engine/key_handler/key_handler.c:55 `	if (game->keys[KEY_W])` — 条件評価。条件を評価して分岐する。
- srcs/engine/key_handler/key_handler.c:56 `		move_forward(game);` — 関数呼び出し。move_forward を呼び出し、前に移動する。
- srcs/engine/key_handler/key_handler.c:57 `	if (game->keys[KEY_S])` — 条件評価。条件を評価して分岐する。
- srcs/engine/key_handler/key_handler.c:58 `		move_backward(game);` — 関数呼び出し。move_backward を呼び出し、後ろに移動する。
- srcs/engine/key_handler/key_handler.c:59 `	if (game->keys[KEY_A])` — 条件評価。条件を評価して分岐する。
- srcs/engine/key_handler/key_handler.c:60 `		move_left(game);` — 関数呼び出し。move_left を呼び出し、左に移動する。
- srcs/engine/key_handler/key_handler.c:61 `	if (game->keys[KEY_D])` — 条件評価。条件を評価して分岐する。
- srcs/engine/key_handler/key_handler.c:62 `		move_right(game);` — 関数呼び出し。move_right を呼び出し、右に移動する。
- srcs/engine/key_handler/key_handler.c:63 `	if (game->keys[KEY_LEFT])` — 条件評価。条件を評価して分岐する。
- srcs/engine/key_handler/key_handler.c:64 `		rotate_left(game);` — 関数呼び出し。rotate_left を呼び出し、左に回転する。
- srcs/engine/key_handler/key_handler.c:65 `	if (game->keys[KEY_RIGHT])` — 条件評価。条件を評価して分岐する。
- srcs/engine/key_handler/key_handler.c:66 `		rotate_right(game);` — 関数呼び出し。rotate_right を呼び出し、右に回転する。
- srcs/engine/key_handler/key_handler.c:67 `}`

## move_forward（srcs/engine/player/player_movement.c）

- srcs/engine/player/player_movement.c:23 `void	move_forward(t_game *game)` — 関数定義開始。関数 move_forward の実装が始まる。
- srcs/engine/player/player_movement.c:24 `{`
- srcs/engine/player/player_movement.c:25 `	double	new_x;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:26 `	double	new_y;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:27 `	t_vec	move;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:28 ``
- srcs/engine/player/player_movement.c:29 `	new_x = game->player.pos_x + game->player.dir_x * MOVE_PER_FRAME;` — 代入。new_x に game->player.pos_x + game->player.dir_x * MOVE_PER_FRAME を設定する。
- srcs/engine/player/player_movement.c:30 `	new_y = game->player.pos_y + game->player.dir_y * MOVE_PER_FRAME;` — 代入。new_y に game->player.pos_y + game->player.dir_y * MOVE_PER_FRAME を設定する。
- srcs/engine/player/player_movement.c:31 `	if (!is_wall(game, new_x, new_y))` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_movement.c:32 `	{`
- srcs/engine/player/player_movement.c:33 `		game->player.pos_x = new_x;` — 代入。game->player.pos_x に new_x を設定する。
- srcs/engine/player/player_movement.c:34 `		game->player.pos_y = new_y;` — 代入。game->player.pos_y に new_y を設定する。
- srcs/engine/player/player_movement.c:35 `		return ;` — 戻り値を返さずに関数から戻る。
- srcs/engine/player/player_movement.c:36 `	}`
- srcs/engine/player/player_movement.c:37 `	move.x = game->player.dir_x;` — 代入。move.x に game->player.dir_x を設定する。
- srcs/engine/player/player_movement.c:38 `	move.y = game->player.dir_y;` — 代入。move.y に game->player.dir_y を設定する。
- srcs/engine/player/player_movement.c:39 `	try_wall_slide(game, new_x, new_y, move);` — 関数呼び出し。try_wall_slide を呼び出し、壁沿いスライドを試みる。
- srcs/engine/player/player_movement.c:40 `}`

## is_wall（srcs/engine/player/player_movement.c）

- srcs/engine/player/player_movement.c:120 `static int	is_wall(t_game *game, double x, double y)` — 関数定義開始。関数 is_wall の実装が始まる。
- srcs/engine/player/player_movement.c:121 `{`
- srcs/engine/player/player_movement.c:122 `	int	x1;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:123 `	int	x2;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:124 `	int	y1;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:125 `	int	y2;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:126 ``
- srcs/engine/player/player_movement.c:127 `	x1 = (int)(x - COLLISION_MARGIN);` — 代入。x1 に (int)(x - COLLISION_MARGIN) を設定する。
- srcs/engine/player/player_movement.c:128 `	x2 = (int)(x + COLLISION_MARGIN);` — 代入。x2 に (int)(x + COLLISION_MARGIN) を設定する。
- srcs/engine/player/player_movement.c:129 `	y1 = (int)(y - COLLISION_MARGIN);` — 代入。y1 に (int)(y - COLLISION_MARGIN) を設定する。
- srcs/engine/player/player_movement.c:130 `	y2 = (int)(y + COLLISION_MARGIN);` — 代入。y2 に (int)(y + COLLISION_MARGIN) を設定する。
- srcs/engine/player/player_movement.c:131 `	if (x1 < 0 || x2 >= game->map_width || y1 < 0 || y2 >= game->map_height)` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_movement.c:132 `		return (1);` — 戻り値として 1 を返す。
- srcs/engine/player/player_movement.c:133 `	if (game->world_map[y1][x1] != 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_movement.c:134 `		return (1);` — 戻り値として 1 を返す。
- srcs/engine/player/player_movement.c:135 `	if (game->world_map[y1][x2] != 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_movement.c:136 `		return (1);` — 戻り値として 1 を返す。
- srcs/engine/player/player_movement.c:137 `	if (game->world_map[y2][x1] != 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_movement.c:138 `		return (1);` — 戻り値として 1 を返す。
- srcs/engine/player/player_movement.c:139 `	if (game->world_map[y2][x2] != 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_movement.c:140 `		return (1);` — 戻り値として 1 を返す。
- srcs/engine/player/player_movement.c:141 `	return (0);` — 戻り値として 0 を返す。
- srcs/engine/player/player_movement.c:142 `}`

## try_wall_slide（srcs/engine/player/player_slide.c）

- srcs/engine/player/player_slide.c:23 `void	try_wall_slide(t_game *game, double new_x, double new_y, t_vec move)` — 関数定義開始。関数 try_wall_slide の実装が始まる。
- srcs/engine/player/player_slide.c:24 `{`
- srcs/engine/player/player_slide.c:25 `	t_slide	s;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_slide.c:26 ``
- srcs/engine/player/player_slide.c:27 `	s.new_x = new_x;` — 代入。s.new_x に new_x を設定する。
- srcs/engine/player/player_slide.c:28 `	s.new_y = new_y;` — 代入。s.new_y に new_y を設定する。
- srcs/engine/player/player_slide.c:29 `	s.dx = move.x * MOVE_PER_FRAME;` — 代入。s.dx に move.x * MOVE_PER_FRAME を設定する。
- srcs/engine/player/player_slide.c:30 `	s.dy = move.y * MOVE_PER_FRAME;` — 代入。s.dy に move.y * MOVE_PER_FRAME を設定する。
- srcs/engine/player/player_slide.c:31 `	if (s.dx < 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_slide.c:32 `		s.dx = -s.dx;` — 代入。s.dx に -s.dx を設定する。
- srcs/engine/player/player_slide.c:33 `	if (s.dy < 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_slide.c:34 `		s.dy = -s.dy;` — 代入。s.dy に -s.dy を設定する。
- srcs/engine/player/player_slide.c:35 `	s.total = s.dx + s.dy;` — 代入。s.total に s.dx + s.dy を設定する。
- srcs/engine/player/player_slide.c:36 `	try_slide(game, &s);` — 関数呼び出し。try_slide を呼び出し、スライド移動を試みる。
- srcs/engine/player/player_slide.c:37 `}`

## try_slide（srcs/engine/player/player_slide.c）

- srcs/engine/player/player_slide.c:43 `static void	try_slide(t_game *game, t_slide *s)` — 関数定義開始。関数 try_slide の実装が始まる。
- srcs/engine/player/player_slide.c:44 `{`
- srcs/engine/player/player_slide.c:45 `	if (s->dy / s->total >= 0.8 && !is_wall(game, game->player.pos_x, s->new_y))` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_slide.c:46 `		game->player.pos_y = s->new_y;` — 代入。game->player.pos_y に s->new_y を設定する。
- srcs/engine/player/player_slide.c:47 `	else if (s->dx / s->total >= 0.8` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/engine/player/player_slide.c:48 `		&& !is_wall(game, s->new_x, game->player.pos_y))` — 式の継続。前後の行と合わせて評価する。
- srcs/engine/player/player_slide.c:49 `		game->player.pos_x = s->new_x;` — 代入。game->player.pos_x に s->new_x を設定する。
- srcs/engine/player/player_slide.c:50 `	else if (s->dy / s->total < 0.8 && s->dx / s->total < 0.8)` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/engine/player/player_slide.c:51 `	{`
- srcs/engine/player/player_slide.c:52 `		if (!is_wall(game, s->new_x, game->player.pos_y)` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_slide.c:53 `			&& (s->new_x - game->player.pos_x) * game->player.dir_x >= 0)` — 式の継続。前後の行と合わせて評価する。
- srcs/engine/player/player_slide.c:54 `			game->player.pos_x = s->new_x;` — 代入。game->player.pos_x に s->new_x を設定する。
- srcs/engine/player/player_slide.c:55 `		else if (!is_wall(game, game->player.pos_x, s->new_y)` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/engine/player/player_slide.c:56 `			&& (s->new_y - game->player.pos_y) * game->player.dir_y >= 0)` — 式の継続。前後の行と合わせて評価する。
- srcs/engine/player/player_slide.c:57 `			game->player.pos_y = s->new_y;` — 代入。game->player.pos_y に s->new_y を設定する。
- srcs/engine/player/player_slide.c:58 `	}`
- srcs/engine/player/player_slide.c:59 `}`

## is_wall（srcs/engine/player/player_slide.c）

- srcs/engine/player/player_slide.c:66 `static int	is_wall(t_game *game, double x, double y)` — 関数定義開始。関数 is_wall の実装が始まる。
- srcs/engine/player/player_slide.c:67 `{`
- srcs/engine/player/player_slide.c:68 `	int	x1;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_slide.c:69 `	int	x2;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_slide.c:70 `	int	y1;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_slide.c:71 `	int	y2;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_slide.c:72 ``
- srcs/engine/player/player_slide.c:73 `	x1 = (int)(x - COLLISION_MARGIN);` — 代入。x1 に (int)(x - COLLISION_MARGIN) を設定する。
- srcs/engine/player/player_slide.c:74 `	x2 = (int)(x + COLLISION_MARGIN);` — 代入。x2 に (int)(x + COLLISION_MARGIN) を設定する。
- srcs/engine/player/player_slide.c:75 `	y1 = (int)(y - COLLISION_MARGIN);` — 代入。y1 に (int)(y - COLLISION_MARGIN) を設定する。
- srcs/engine/player/player_slide.c:76 `	y2 = (int)(y + COLLISION_MARGIN);` — 代入。y2 に (int)(y + COLLISION_MARGIN) を設定する。
- srcs/engine/player/player_slide.c:77 `	if (x1 < 0 || x2 >= game->map_width || y1 < 0 || y2 >= game->map_height)` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_slide.c:78 `		return (1);` — 戻り値として 1 を返す。
- srcs/engine/player/player_slide.c:79 `	if (game->world_map[y1][x1] != 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_slide.c:80 `		return (1);` — 戻り値として 1 を返す。
- srcs/engine/player/player_slide.c:81 `	if (game->world_map[y1][x2] != 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_slide.c:82 `		return (1);` — 戻り値として 1 を返す。
- srcs/engine/player/player_slide.c:83 `	if (game->world_map[y2][x1] != 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_slide.c:84 `		return (1);` — 戻り値として 1 を返す。
- srcs/engine/player/player_slide.c:85 `	if (game->world_map[y2][x2] != 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_slide.c:86 `		return (1);` — 戻り値として 1 を返す。
- srcs/engine/player/player_slide.c:87 `	return (0);` — 戻り値として 0 を返す。
- srcs/engine/player/player_slide.c:88 `}`

## move_backward（srcs/engine/player/player_movement.c）

- srcs/engine/player/player_movement.c:46 `void	move_backward(t_game *game)` — 関数定義開始。関数 move_backward の実装が始まる。
- srcs/engine/player/player_movement.c:47 `{`
- srcs/engine/player/player_movement.c:48 `	double	new_x;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:49 `	double	new_y;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:50 `	t_vec	move;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:51 ``
- srcs/engine/player/player_movement.c:52 `	new_x = game->player.pos_x - game->player.dir_x * MOVE_PER_FRAME;` — 代入。new_x に game->player.pos_x - game->player.dir_x * MOVE_PER_FRAME を設定する。
- srcs/engine/player/player_movement.c:53 `	new_y = game->player.pos_y - game->player.dir_y * MOVE_PER_FRAME;` — 代入。new_y に game->player.pos_y - game->player.dir_y * MOVE_PER_FRAME を設定する。
- srcs/engine/player/player_movement.c:54 `	if (!is_wall(game, new_x, new_y))` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_movement.c:55 `	{`
- srcs/engine/player/player_movement.c:56 `		game->player.pos_x = new_x;` — 代入。game->player.pos_x に new_x を設定する。
- srcs/engine/player/player_movement.c:57 `		game->player.pos_y = new_y;` — 代入。game->player.pos_y に new_y を設定する。
- srcs/engine/player/player_movement.c:58 `		return ;` — 戻り値を返さずに関数から戻る。
- srcs/engine/player/player_movement.c:59 `	}`
- srcs/engine/player/player_movement.c:60 `	move.x = game->player.dir_x;` — 代入。move.x に game->player.dir_x を設定する。
- srcs/engine/player/player_movement.c:61 `	move.y = game->player.dir_y;` — 代入。move.y に game->player.dir_y を設定する。
- srcs/engine/player/player_movement.c:62 `	try_wall_slide(game, new_x, new_y, move);` — 関数呼び出し。try_wall_slide を呼び出し、壁沿いスライドを試みる。
- srcs/engine/player/player_movement.c:63 `}`

## move_left（srcs/engine/player/player_movement.c）

- srcs/engine/player/player_movement.c:71 `void	move_left(t_game *game)` — 関数定義開始。関数 move_left の実装が始まる。
- srcs/engine/player/player_movement.c:72 `{`
- srcs/engine/player/player_movement.c:73 `	double	new_x;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:74 `	double	new_y;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:75 `	t_vec	move;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:76 ``
- srcs/engine/player/player_movement.c:77 `	new_x = game->player.pos_x - game->player.plane_x * MOVE_PER_FRAME;` — 代入。new_x に game->player.pos_x - game->player.plane_x * MOVE_PER_FRAME を設定する。
- srcs/engine/player/player_movement.c:78 `	new_y = game->player.pos_y - game->player.plane_y * MOVE_PER_FRAME;` — 代入。new_y に game->player.pos_y - game->player.plane_y * MOVE_PER_FRAME を設定する。
- srcs/engine/player/player_movement.c:79 `	if (!is_wall(game, new_x, new_y))` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_movement.c:80 `	{`
- srcs/engine/player/player_movement.c:81 `		game->player.pos_x = new_x;` — 代入。game->player.pos_x に new_x を設定する。
- srcs/engine/player/player_movement.c:82 `		game->player.pos_y = new_y;` — 代入。game->player.pos_y に new_y を設定する。
- srcs/engine/player/player_movement.c:83 `		return ;` — 戻り値を返さずに関数から戻る。
- srcs/engine/player/player_movement.c:84 `	}`
- srcs/engine/player/player_movement.c:85 `	move.x = game->player.plane_x;` — 代入。move.x に game->player.plane_x を設定する。
- srcs/engine/player/player_movement.c:86 `	move.y = game->player.plane_y;` — 代入。move.y に game->player.plane_y を設定する。
- srcs/engine/player/player_movement.c:87 `	try_wall_slide(game, new_x, new_y, move);` — 関数呼び出し。try_wall_slide を呼び出し、壁沿いスライドを試みる。
- srcs/engine/player/player_movement.c:88 `}`

## move_right（srcs/engine/player/player_movement.c）

- srcs/engine/player/player_movement.c:96 `void	move_right(t_game *game)` — 関数定義開始。関数 move_right の実装が始まる。
- srcs/engine/player/player_movement.c:97 `{`
- srcs/engine/player/player_movement.c:98 `	double	new_x;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:99 `	double	new_y;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:100 `	t_vec	move;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_movement.c:101 ``
- srcs/engine/player/player_movement.c:102 `	new_x = game->player.pos_x + game->player.plane_x * MOVE_PER_FRAME;` — 代入。new_x に game->player.pos_x + game->player.plane_x * MOVE_PER_FRAME を設定する。
- srcs/engine/player/player_movement.c:103 `	new_y = game->player.pos_y + game->player.plane_y * MOVE_PER_FRAME;` — 代入。new_y に game->player.pos_y + game->player.plane_y * MOVE_PER_FRAME を設定する。
- srcs/engine/player/player_movement.c:104 `	if (!is_wall(game, new_x, new_y))` — 条件評価。条件を評価して分岐する。
- srcs/engine/player/player_movement.c:105 `	{`
- srcs/engine/player/player_movement.c:106 `		game->player.pos_x = new_x;` — 代入。game->player.pos_x に new_x を設定する。
- srcs/engine/player/player_movement.c:107 `		game->player.pos_y = new_y;` — 代入。game->player.pos_y に new_y を設定する。
- srcs/engine/player/player_movement.c:108 `		return ;` — 戻り値を返さずに関数から戻る。
- srcs/engine/player/player_movement.c:109 `	}`
- srcs/engine/player/player_movement.c:110 `	move.x = game->player.plane_x;` — 代入。move.x に game->player.plane_x を設定する。
- srcs/engine/player/player_movement.c:111 `	move.y = game->player.plane_y;` — 代入。move.y に game->player.plane_y を設定する。
- srcs/engine/player/player_movement.c:112 `	try_wall_slide(game, new_x, new_y, move);` — 関数呼び出し。try_wall_slide を呼び出し、壁沿いスライドを試みる。
- srcs/engine/player/player_movement.c:113 `}`

## rotate_left（srcs/engine/player/player_rotation.c）

- srcs/engine/player/player_rotation.c:21 `void	rotate_left(t_game *game)` — 関数定義開始。関数 rotate_left の実装が始まる。
- srcs/engine/player/player_rotation.c:22 `{`
- srcs/engine/player/player_rotation.c:23 `	double	old_dir_x;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_rotation.c:24 `	double	old_plane_x;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_rotation.c:25 `	double	cos_rot;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_rotation.c:26 `	double	sin_rot;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_rotation.c:27 ``
- srcs/engine/player/player_rotation.c:28 `	cos_rot = cos(ROT_PER_FRAME);` — 代入。cos_rot に cos(ROT_PER_FRAME) を設定する。
- srcs/engine/player/player_rotation.c:29 `	sin_rot = sin(ROT_PER_FRAME);` — 代入。sin_rot に sin(ROT_PER_FRAME) を設定する。
- srcs/engine/player/player_rotation.c:30 `	old_dir_x = game->player.dir_x;` — 代入。old_dir_x に game->player.dir_x を設定する。
- srcs/engine/player/player_rotation.c:31 `	game->player.dir_x = game->player.dir_x * cos_rot` — 文の評価。式/制御構文を処理する。
- srcs/engine/player/player_rotation.c:32 `		- game->player.dir_y * sin_rot;` — 文の評価。式または宣言を処理する。
- srcs/engine/player/player_rotation.c:33 `	game->player.dir_y = old_dir_x * sin_rot` — 文の評価。式/制御構文を処理する。
- srcs/engine/player/player_rotation.c:34 `		+ game->player.dir_y * cos_rot;` — 文の評価。式または宣言を処理する。
- srcs/engine/player/player_rotation.c:35 `	old_plane_x = game->player.plane_x;` — 代入。old_plane_x に game->player.plane_x を設定する。
- srcs/engine/player/player_rotation.c:36 `	game->player.plane_x = game->player.plane_x * cos_rot` — 文の評価。式/制御構文を処理する。
- srcs/engine/player/player_rotation.c:37 `		- game->player.plane_y * sin_rot;` — 文の評価。式または宣言を処理する。
- srcs/engine/player/player_rotation.c:38 `	game->player.plane_y = old_plane_x * sin_rot` — 文の評価。式/制御構文を処理する。
- srcs/engine/player/player_rotation.c:39 `		+ game->player.plane_y * cos_rot;` — 文の評価。式または宣言を処理する。
- srcs/engine/player/player_rotation.c:40 `}`

## rotate_right（srcs/engine/player/player_rotation.c）

- srcs/engine/player/player_rotation.c:46 `void	rotate_right(t_game *game)` — 関数定義開始。関数 rotate_right の実装が始まる。
- srcs/engine/player/player_rotation.c:47 `{`
- srcs/engine/player/player_rotation.c:48 `	double	old_dir_x;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_rotation.c:49 `	double	old_plane_x;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_rotation.c:50 `	double	cos_rot;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_rotation.c:51 `	double	sin_rot;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/player/player_rotation.c:52 ``
- srcs/engine/player/player_rotation.c:53 `	cos_rot = cos(-ROT_PER_FRAME);` — 代入。cos_rot に cos(-ROT_PER_FRAME) を設定する。
- srcs/engine/player/player_rotation.c:54 `	sin_rot = sin(-ROT_PER_FRAME);` — 代入。sin_rot に sin(-ROT_PER_FRAME) を設定する。
- srcs/engine/player/player_rotation.c:55 `	old_dir_x = game->player.dir_x;` — 代入。old_dir_x に game->player.dir_x を設定する。
- srcs/engine/player/player_rotation.c:56 `	game->player.dir_x = game->player.dir_x * cos_rot` — 文の評価。式/制御構文を処理する。
- srcs/engine/player/player_rotation.c:57 `		- game->player.dir_y * sin_rot;` — 文の評価。式または宣言を処理する。
- srcs/engine/player/player_rotation.c:58 `	game->player.dir_y = old_dir_x * sin_rot` — 文の評価。式/制御構文を処理する。
- srcs/engine/player/player_rotation.c:59 `		+ game->player.dir_y * cos_rot;` — 文の評価。式または宣言を処理する。
- srcs/engine/player/player_rotation.c:60 `	old_plane_x = game->player.plane_x;` — 代入。old_plane_x に game->player.plane_x を設定する。
- srcs/engine/player/player_rotation.c:61 `	game->player.plane_x = game->player.plane_x * cos_rot` — 文の評価。式/制御構文を処理する。
- srcs/engine/player/player_rotation.c:62 `		- game->player.plane_y * sin_rot;` — 文の評価。式または宣言を処理する。
- srcs/engine/player/player_rotation.c:63 `	game->player.plane_y = old_plane_x * sin_rot` — 文の評価。式/制御構文を処理する。
- srcs/engine/player/player_rotation.c:64 `		+ game->player.plane_y * cos_rot;` — 文の評価。式または宣言を処理する。
- srcs/engine/player/player_rotation.c:65 `}`

## cast_rays（srcs/engine/raycasting/raycasting.c）

- srcs/engine/raycasting/raycasting.c:20 `void	cast_rays(t_game *game)` — 関数定義開始。関数 cast_rays の実装が始まる。
- srcs/engine/raycasting/raycasting.c:21 `{`
- srcs/engine/raycasting/raycasting.c:22 `	t_ray	ray;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/raycasting/raycasting.c:23 `	int		x;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/raycasting/raycasting.c:24 ``
- srcs/engine/raycasting/raycasting.c:25 `	x = 0;` — 代入。x に 0 を設定する。
- srcs/engine/raycasting/raycasting.c:26 `	while (x < WINDOW_WIDTH)` — ループ評価。条件が真の間ループする。
- srcs/engine/raycasting/raycasting.c:27 `	{`
- srcs/engine/raycasting/raycasting.c:28 `		init_ray(game, &ray, x);` — 関数呼び出し。init_ray を呼び出し、レイを初期化する。
- srcs/engine/raycasting/raycasting.c:29 `		calc_step_and_side_dist(game, &ray);` — 関数呼び出し。calc_step_and_side_dist を呼び出し、ステップとサイド距離を計算する。
- srcs/engine/raycasting/raycasting.c:30 `		perform_dda(game, &ray);` — 関数呼び出し。perform_dda を呼び出し、DDA を実行する。
- srcs/engine/raycasting/raycasting.c:31 `		calc_wall_distance(game, &ray);` — 関数呼び出し。calc_wall_distance を呼び出し、壁までの距離を計算する。
- srcs/engine/raycasting/raycasting.c:32 `		calc_line_height(&ray);` — 関数呼び出し。calc_line_height を呼び出し、ライン高さを計算する。
- srcs/engine/raycasting/raycasting.c:33 `		calc_texture_coords(game, &ray);` — 関数呼び出し。calc_texture_coords を呼び出し、テクスチャ座標を計算する。
- srcs/engine/raycasting/raycasting.c:34 `		draw_vertical_line(game, &ray, x);` — 関数呼び出し。draw_vertical_line を呼び出し、縦線を描画する。
- srcs/engine/raycasting/raycasting.c:35 `		x++;` — 文の評価。式または宣言を処理する。
- srcs/engine/raycasting/raycasting.c:36 `	}`
- srcs/engine/raycasting/raycasting.c:37 `}`

## init_ray（srcs/engine/raycasting/ray_init.c）

- srcs/engine/raycasting/ray_init.c:21 `void	init_ray(t_game *game, t_ray *ray, int x)` — 関数定義開始。関数 init_ray の実装が始まる。
- srcs/engine/raycasting/ray_init.c:22 `{`
- srcs/engine/raycasting/ray_init.c:23 `	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;` — 代入。ray->camera_x に 2 * x / (double)WINDOW_WIDTH - 1 を設定する。
- srcs/engine/raycasting/ray_init.c:24 `	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;` — 代入。ray->ray_dir_x に game->player.dir_x + game->player.plane_x * ray->camera_x を設定する。
- srcs/engine/raycasting/ray_init.c:25 `	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;` — 代入。ray->ray_dir_y に game->player.dir_y + game->player.plane_y * ray->camera_x を設定する。
- srcs/engine/raycasting/ray_init.c:26 `	ray->map_x = (int)game->player.pos_x;` — 代入。ray->map_x に (int)game->player.pos_x を設定する。
- srcs/engine/raycasting/ray_init.c:27 `	ray->map_y = (int)game->player.pos_y;` — 代入。ray->map_y に (int)game->player.pos_y を設定する。
- srcs/engine/raycasting/ray_init.c:28 `	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);` — 代入。ray->delta_dist_x に fabs(1 / ray->ray_dir_x) を設定する。
- srcs/engine/raycasting/ray_init.c:29 `	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);` — 代入。ray->delta_dist_y に fabs(1 / ray->ray_dir_y) を設定する。
- srcs/engine/raycasting/ray_init.c:30 `	ray->hit = 0;` — 代入。ray->hit に 0 を設定する。
- srcs/engine/raycasting/ray_init.c:31 `}`

## calc_step_and_side_dist（srcs/engine/raycasting/ray_init.c）

- srcs/engine/raycasting/ray_init.c:36 `void	calc_step_and_side_dist(t_game *game, t_ray *ray)` — 関数定義開始。関数 calc_step_and_side_dist の実装が始まる。
- srcs/engine/raycasting/ray_init.c:37 `{`
- srcs/engine/raycasting/ray_init.c:38 `	if (ray->ray_dir_x < 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/raycasting/ray_init.c:39 `	{`
- srcs/engine/raycasting/ray_init.c:40 `		ray->step_x = -1;` — 代入。ray->step_x に -1 を設定する。
- srcs/engine/raycasting/ray_init.c:41 `		ray->side_dist_x = (game->player.pos_x - ray->map_x)` — 文の評価。式/制御構文を処理する。
- srcs/engine/raycasting/ray_init.c:42 `			* ray->delta_dist_x;` — なし。コメント。
- srcs/engine/raycasting/ray_init.c:43 `	}`
- srcs/engine/raycasting/ray_init.c:44 `	else` — 分岐。前条件が偽のときの分岐。
- srcs/engine/raycasting/ray_init.c:45 `	{`
- srcs/engine/raycasting/ray_init.c:46 `		ray->step_x = 1;` — 代入。ray->step_x に 1 を設定する。
- srcs/engine/raycasting/ray_init.c:47 `		ray->side_dist_x = (ray->map_x + 1.0 - game->player.pos_x)` — 文の評価。式/制御構文を処理する。
- srcs/engine/raycasting/ray_init.c:48 `			* ray->delta_dist_x;` — なし。コメント。
- srcs/engine/raycasting/ray_init.c:49 `	}`
- srcs/engine/raycasting/ray_init.c:50 `	if (ray->ray_dir_y < 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/raycasting/ray_init.c:51 `	{`
- srcs/engine/raycasting/ray_init.c:52 `		ray->step_y = -1;` — 代入。ray->step_y に -1 を設定する。
- srcs/engine/raycasting/ray_init.c:53 `		ray->side_dist_y = (game->player.pos_y - ray->map_y)` — 文の評価。式/制御構文を処理する。
- srcs/engine/raycasting/ray_init.c:54 `			* ray->delta_dist_y;` — なし。コメント。
- srcs/engine/raycasting/ray_init.c:55 `	}`
- srcs/engine/raycasting/ray_init.c:56 `	else` — 分岐。前条件が偽のときの分岐。
- srcs/engine/raycasting/ray_init.c:57 `	{`
- srcs/engine/raycasting/ray_init.c:58 `		ray->step_y = 1;` — 代入。ray->step_y に 1 を設定する。
- srcs/engine/raycasting/ray_init.c:59 `		ray->side_dist_y = (ray->map_y + 1.0 - game->player.pos_y)` — 文の評価。式/制御構文を処理する。
- srcs/engine/raycasting/ray_init.c:60 `			* ray->delta_dist_y;` — なし。コメント。
- srcs/engine/raycasting/ray_init.c:61 `	}`
- srcs/engine/raycasting/ray_init.c:62 `}`

## perform_dda（srcs/engine/raycasting/ray_dda.c）

- srcs/engine/raycasting/ray_dda.c:19 `void	perform_dda(t_game *game, t_ray *ray)` — 関数定義開始。関数 perform_dda の実装が始まる。
- srcs/engine/raycasting/ray_dda.c:20 `{`
- srcs/engine/raycasting/ray_dda.c:21 `	while (ray->hit == 0)` — ループ評価。条件が真の間ループする。
- srcs/engine/raycasting/ray_dda.c:22 `	{`
- srcs/engine/raycasting/ray_dda.c:23 `		if (ray->side_dist_x < ray->side_dist_y)` — 条件評価。条件を評価して分岐する。
- srcs/engine/raycasting/ray_dda.c:24 `		{`
- srcs/engine/raycasting/ray_dda.c:25 `			ray->side_dist_x += ray->delta_dist_x;` — 代入。ray->side_dist_x に ray->delta_dist_x を加算して設定する。
- srcs/engine/raycasting/ray_dda.c:26 `			ray->map_x += ray->step_x;` — 代入。ray->map_x に ray->step_x を加算して設定する。
- srcs/engine/raycasting/ray_dda.c:27 `			ray->side = 0;` — 代入。ray->side に 0 を設定する。
- srcs/engine/raycasting/ray_dda.c:28 `		}`
- srcs/engine/raycasting/ray_dda.c:29 `		else` — 分岐。前条件が偽のときの分岐。
- srcs/engine/raycasting/ray_dda.c:30 `		{`
- srcs/engine/raycasting/ray_dda.c:31 `			ray->side_dist_y += ray->delta_dist_y;` — 代入。ray->side_dist_y に ray->delta_dist_y を加算して設定する。
- srcs/engine/raycasting/ray_dda.c:32 `			ray->map_y += ray->step_y;` — 代入。ray->map_y に ray->step_y を加算して設定する。
- srcs/engine/raycasting/ray_dda.c:33 `			ray->side = 1;` — 代入。ray->side に 1 を設定する。
- srcs/engine/raycasting/ray_dda.c:34 `		}`
- srcs/engine/raycasting/ray_dda.c:35 `		if (game->world_map[ray->map_y][ray->map_x] > 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/raycasting/ray_dda.c:36 `			ray->hit = 1;` — 代入。ray->hit に 1 を設定する。
- srcs/engine/raycasting/ray_dda.c:37 `	}`
- srcs/engine/raycasting/ray_dda.c:38 `}`

## calc_wall_distance（srcs/engine/raycasting/ray_dda.c）

- srcs/engine/raycasting/ray_dda.c:43 `void	calc_wall_distance(t_game *game, t_ray *ray)` — 関数定義開始。関数 calc_wall_distance の実装が始まる。
- srcs/engine/raycasting/ray_dda.c:44 `{`
- srcs/engine/raycasting/ray_dda.c:45 `	if (ray->side == 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/raycasting/ray_dda.c:46 `		ray->perp_wall_dist = (ray->map_x - game->player.pos_x + (1` — 文の評価。式/制御構文を処理する。
- srcs/engine/raycasting/ray_dda.c:47 `					- ray->step_x) / 2) / ray->ray_dir_x;` — 文の評価。式または宣言を処理する。
- srcs/engine/raycasting/ray_dda.c:48 `	else` — 分岐。前条件が偽のときの分岐。
- srcs/engine/raycasting/ray_dda.c:49 `		ray->perp_wall_dist = (ray->map_y - game->player.pos_y + (1` — 文の評価。式/制御構文を処理する。
- srcs/engine/raycasting/ray_dda.c:50 `					- ray->step_y) / 2) / ray->ray_dir_y;` — 文の評価。式または宣言を処理する。
- srcs/engine/raycasting/ray_dda.c:51 `}`

## calc_line_height（srcs/engine/raycasting/ray_dda.c）

- srcs/engine/raycasting/ray_dda.c:56 `void	calc_line_height(t_ray *ray)` — 関数定義開始。関数 calc_line_height の実装が始まる。
- srcs/engine/raycasting/ray_dda.c:57 `{`
- srcs/engine/raycasting/ray_dda.c:58 `	ray->line_height = (int)(WINDOW_HEIGHT / ray->perp_wall_dist);` — 代入。ray->line_height に (int)(WINDOW_HEIGHT / ray->perp_wall_dist) を設定する。
- srcs/engine/raycasting/ray_dda.c:59 `	ray->draw_start = -ray->line_height / 2 + WINDOW_HEIGHT / 2;` — 代入。ray->draw_start に -ray->line_height / 2 + WINDOW_HEIGHT / 2 を設定する。
- srcs/engine/raycasting/ray_dda.c:60 `	if (ray->draw_start < 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/raycasting/ray_dda.c:61 `		ray->draw_start = 0;` — 代入。ray->draw_start に 0 を設定する。
- srcs/engine/raycasting/ray_dda.c:62 `	ray->draw_end = ray->line_height / 2 + WINDOW_HEIGHT / 2;` — 代入。ray->draw_end に ray->line_height / 2 + WINDOW_HEIGHT / 2 を設定する。
- srcs/engine/raycasting/ray_dda.c:63 `	if (ray->draw_end >= WINDOW_HEIGHT)` — 条件評価。条件を評価して分岐する。
- srcs/engine/raycasting/ray_dda.c:64 `		ray->draw_end = WINDOW_HEIGHT - 1;` — 代入。ray->draw_end に WINDOW_HEIGHT - 1 を設定する。
- srcs/engine/raycasting/ray_dda.c:65 `}`

## calc_texture_coords（srcs/engine/raycasting/texture_coords.c）

- srcs/engine/raycasting/texture_coords.c:16 `void	calc_texture_coords(t_game *game, t_ray *ray)` — 関数定義開始。関数 calc_texture_coords の実装が始まる。
- srcs/engine/raycasting/texture_coords.c:17 `{`
- srcs/engine/raycasting/texture_coords.c:18 `	if (ray->side == 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/raycasting/texture_coords.c:19 `		ray->wall_x = game->player.pos_y + ray->perp_wall_dist` — 文の評価。式/制御構文を処理する。
- srcs/engine/raycasting/texture_coords.c:20 `			* ray->ray_dir_y;` — なし。コメント。
- srcs/engine/raycasting/texture_coords.c:21 `	else` — 分岐。前条件が偽のときの分岐。
- srcs/engine/raycasting/texture_coords.c:22 `		ray->wall_x = game->player.pos_x + ray->perp_wall_dist` — 文の評価。式/制御構文を処理する。
- srcs/engine/raycasting/texture_coords.c:23 `			* ray->ray_dir_x;` — なし。コメント。
- srcs/engine/raycasting/texture_coords.c:24 `	ray->wall_x -= floor(ray->wall_x);` — 代入。ray->wall_x から floor(ray->wall_x) を減算して設定する。
- srcs/engine/raycasting/texture_coords.c:25 `	ray->tex_x = (int)(ray->wall_x * (double)TEX_WIDTH);` — 代入。ray->tex_x に (int)(ray->wall_x * (double)TEX_WIDTH) を設定する。
- srcs/engine/raycasting/texture_coords.c:26 `	if (ray->side == 0 && ray->ray_dir_x > 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/raycasting/texture_coords.c:27 `		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;` — 代入。ray->tex_x に TEX_WIDTH - ray->tex_x - 1 を設定する。
- srcs/engine/raycasting/texture_coords.c:28 `	if (ray->side == 1 && ray->ray_dir_y < 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/raycasting/texture_coords.c:29 `		ray->tex_x = TEX_WIDTH - ray->tex_x - 1;` — 代入。ray->tex_x に TEX_WIDTH - ray->tex_x - 1 を設定する。
- srcs/engine/raycasting/texture_coords.c:30 `}`

## draw_vertical_line（srcs/engine/raycasting/ray_draw.c）

- srcs/engine/raycasting/ray_draw.c:42 `void	draw_vertical_line(t_game *game, t_ray *ray, int x)` — 関数定義開始。関数 draw_vertical_line の実装が始まる。
- srcs/engine/raycasting/ray_draw.c:43 `{`
- srcs/engine/raycasting/ray_draw.c:44 `	int		y;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/raycasting/ray_draw.c:45 `	int		tex_y;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/raycasting/ray_draw.c:46 `	double	step;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/raycasting/ray_draw.c:47 `	double	tex_pos;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/raycasting/ray_draw.c:48 `	t_img	*texture;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/raycasting/ray_draw.c:49 ``
- srcs/engine/raycasting/ray_draw.c:50 `	y = 0;` — 代入。y に 0 を設定する。
- srcs/engine/raycasting/ray_draw.c:51 `	while (y < ray->draw_start)` — ループ評価。条件が真の間ループする。
- srcs/engine/raycasting/ray_draw.c:52 `		put_pixel(game, x, y++, create_rgb_color(game->ceiling_color));` — 関数呼び出し。put_pixel を呼び出し、ピクセルを描画する。
- srcs/engine/raycasting/ray_draw.c:53 `	texture = select_wall_texture(game, ray);` — 代入。texture に select_wall_texture(game, ray) を設定する。
- srcs/engine/raycasting/ray_draw.c:54 `	step = (double)TEX_HEIGHT / ray->line_height;` — 代入。step に (double)TEX_HEIGHT / ray->line_height を設定する。
- srcs/engine/raycasting/ray_draw.c:55 `	tex_pos = (ray->draw_start - WINDOW_HEIGHT / 2` — 文の評価。式/制御構文を処理する。
- srcs/engine/raycasting/ray_draw.c:56 `			+ ray->line_height / 2) * step;` — 文の評価。式または宣言を処理する。
- srcs/engine/raycasting/ray_draw.c:57 `	while (y <= ray->draw_end)` — ループ評価。条件が真の間ループする。
- srcs/engine/raycasting/ray_draw.c:58 `	{`
- srcs/engine/raycasting/ray_draw.c:59 `		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);` — 代入。tex_y に (int)tex_pos & (TEX_HEIGHT - 1) を設定する。
- srcs/engine/raycasting/ray_draw.c:60 `		tex_pos += step;` — 代入。tex_pos に step を加算して設定する。
- srcs/engine/raycasting/ray_draw.c:61 `		put_pixel(game, x, y++, get_texture_pixel(texture,` — 式の継続。前後の行と合わせて評価する。
- srcs/engine/raycasting/ray_draw.c:62 `				ray->tex_x, tex_y));` — 文の評価。式または宣言を処理する。
- srcs/engine/raycasting/ray_draw.c:63 `	}`
- srcs/engine/raycasting/ray_draw.c:64 `	while (y < WINDOW_HEIGHT)` — ループ評価。条件が真の間ループする。
- srcs/engine/raycasting/ray_draw.c:65 `		put_pixel(game, x, y++, create_rgb_color(game->floor_color));` — 関数呼び出し。put_pixel を呼び出し、ピクセルを描画する。
- srcs/engine/raycasting/ray_draw.c:66 `}`

## put_pixel（srcs/engine/raycasting/ray_draw.c）

- srcs/engine/raycasting/ray_draw.c:20 `void	put_pixel(t_game *game, int x, int y, int color)` — 関数定義開始。関数 put_pixel の実装が始まる。
- srcs/engine/raycasting/ray_draw.c:21 `{`
- srcs/engine/raycasting/ray_draw.c:22 `	char	*dst;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/raycasting/ray_draw.c:23 ``
- srcs/engine/raycasting/ray_draw.c:24 `	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)` — 条件評価。条件を評価して分岐する。
- srcs/engine/raycasting/ray_draw.c:25 `		return ;` — 戻り値を返さずに関数から戻る。
- srcs/engine/raycasting/ray_draw.c:26 `	dst = game->img.addr + (y * game->img.line_length + x` — 文の評価。式/制御構文を処理する。
- srcs/engine/raycasting/ray_draw.c:27 `			* (game->img.bits_per_pixel / 8));` — なし。コメント。
- srcs/engine/raycasting/ray_draw.c:28 `	*(unsigned int *)dst = color;` — なし。コメント。
- srcs/engine/raycasting/ray_draw.c:29 `}`

## create_rgb_color（srcs/engine/raycasting/ray_draw.c）

- srcs/engine/raycasting/ray_draw.c:34 `static int	create_rgb_color(t_color color)` — 関数定義開始。関数 create_rgb_color の実装が始まる。
- srcs/engine/raycasting/ray_draw.c:35 `{`
- srcs/engine/raycasting/ray_draw.c:36 `	return ((color.r << 16) | (color.g << 8) | color.b);` — 戻り値として (color.r << 16) | (color.g << 8) | color.b を返す。
- srcs/engine/raycasting/ray_draw.c:37 `}`

## select_wall_texture（srcs/engine/texture/texture_utils.c）

- srcs/engine/texture/texture_utils.c:27 `t_img	*select_wall_texture(t_game *game, t_ray *ray)` — 関数定義開始。関数 select_wall_texture の実装が始まる。
- srcs/engine/texture/texture_utils.c:28 `{`
- srcs/engine/texture/texture_utils.c:29 `	if (ray->side == 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/texture/texture_utils.c:30 `	{`
- srcs/engine/texture/texture_utils.c:31 `		if (ray->step_x > 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/texture/texture_utils.c:32 `			return (&game->textures.east);` — 戻り値として &game->textures.east を返す。
- srcs/engine/texture/texture_utils.c:33 `		else` — 分岐。前条件が偽のときの分岐。
- srcs/engine/texture/texture_utils.c:34 `			return (&game->textures.west);` — 戻り値として &game->textures.west を返す。
- srcs/engine/texture/texture_utils.c:35 `	}`
- srcs/engine/texture/texture_utils.c:36 `	else` — 分岐。前条件が偽のときの分岐。
- srcs/engine/texture/texture_utils.c:37 `	{`
- srcs/engine/texture/texture_utils.c:38 `		if (ray->step_y > 0)` — 条件評価。条件を評価して分岐する。
- srcs/engine/texture/texture_utils.c:39 `			return (&game->textures.south);` — 戻り値として &game->textures.south を返す。
- srcs/engine/texture/texture_utils.c:40 `		else` — 分岐。前条件が偽のときの分岐。
- srcs/engine/texture/texture_utils.c:41 `			return (&game->textures.north);` — 戻り値として &game->textures.north を返す。
- srcs/engine/texture/texture_utils.c:42 `	}`
- srcs/engine/texture/texture_utils.c:43 `}`

## get_texture_pixel（srcs/engine/texture/texture_utils.c）

- srcs/engine/texture/texture_utils.c:16 `int	get_texture_pixel(t_img *texture, int x, int y)` — 関数定義開始。関数 get_texture_pixel の実装が始まる。
- srcs/engine/texture/texture_utils.c:17 `{`
- srcs/engine/texture/texture_utils.c:18 `	char	*pixel;` — 変数宣言。ローカル変数を用意する。
- srcs/engine/texture/texture_utils.c:19 ``
- srcs/engine/texture/texture_utils.c:20 `	if (x < 0 || x >= TEX_WIDTH || y < 0 || y >= TEX_HEIGHT)` — 条件評価。条件を評価して分岐する。
- srcs/engine/texture/texture_utils.c:21 `		return (0);` — 戻り値として 0 を返す。
- srcs/engine/texture/texture_utils.c:22 `	pixel = texture->addr + (y * texture->line_length` — 文の評価。式/制御構文を処理する。
- srcs/engine/texture/texture_utils.c:23 `			+ x * (texture->bits_per_pixel / 8));` — 文の評価。式または宣言を処理する。
- srcs/engine/texture/texture_utils.c:24 `	return (*(unsigned int *)pixel);` — 戻り値として *(unsigned int *)pixel を返す。
- srcs/engine/texture/texture_utils.c:25 `}`

## handle_keypress（srcs/engine/key_handler/key_handler.c）

- srcs/engine/key_handler/key_handler.c:37 `int	handle_keypress(int keycode, t_game *game)` — 関数定義開始。関数 handle_keypress の実装が始まる。
- srcs/engine/key_handler/key_handler.c:38 `{`
- srcs/engine/key_handler/key_handler.c:39 `	if (keycode == KEY_ESC)` — 条件評価。条件を評価して分岐する。
- srcs/engine/key_handler/key_handler.c:40 `		close_window(game);` — 関数呼び出し。close_window を呼び出し、ウィンドウを閉じる。
- srcs/engine/key_handler/key_handler.c:41 `	else if (keycode >= 0 && keycode < KEY_STATE_SIZE)` — 条件評価。前条件が偽のときに追加条件を評価。
- srcs/engine/key_handler/key_handler.c:42 `		game->keys[keycode] = 1;` — 代入。game->keys[keycode] に 1 を設定する。
- srcs/engine/key_handler/key_handler.c:43 `	return (0);` — 戻り値として 0 を返す。
- srcs/engine/key_handler/key_handler.c:44 `}`

## close_window（srcs/engine/key_handler/key_handler.c, 開始行:20）

- srcs/engine/key_handler/key_handler.c:20 `int	close_window(t_game *game)` — 関数定義開始。関数 close_window の実装が始まる。
- srcs/engine/key_handler/key_handler.c:21 `{`
- srcs/engine/key_handler/key_handler.c:22 `	mlx_loop_end(game->mlx);` — 関数呼び出し。mlx_loop_end を呼び出し、イベントループを終了する。
- srcs/engine/key_handler/key_handler.c:23 `	return (0);` — 戻り値として 0 を返す。
- srcs/engine/key_handler/key_handler.c:24 `}`

## handle_keyrelease（srcs/engine/key_handler/key_handler.c）

- srcs/engine/key_handler/key_handler.c:46 `int	handle_keyrelease(int keycode, t_game *game)` — 関数定義開始。関数 handle_keyrelease の実装が始まる。
- srcs/engine/key_handler/key_handler.c:47 `{`
- srcs/engine/key_handler/key_handler.c:48 `	if (keycode >= 0 && keycode < KEY_STATE_SIZE)` — 条件評価。条件を評価して分岐する。
- srcs/engine/key_handler/key_handler.c:49 `		game->keys[keycode] = 0;` — 代入。game->keys[keycode] に 0 を設定する。
- srcs/engine/key_handler/key_handler.c:50 `	return (0);` — 戻り値として 0 を返す。
- srcs/engine/key_handler/key_handler.c:51 `}`

## cleanup_textures（srcs/engine/texture/texture_cleanup.c）

- srcs/engine/texture/texture_cleanup.c:16 `void	cleanup_textures(t_game *game)` — 関数定義開始。関数 cleanup_textures の実装が始まる。
- srcs/engine/texture/texture_cleanup.c:17 `{`
- srcs/engine/texture/texture_cleanup.c:18 `	if (game->textures.north.img)` — 条件評価。条件を評価して分岐する。
- srcs/engine/texture/texture_cleanup.c:19 `		mlx_destroy_image(game->mlx, game->textures.north.img);` — 関数呼び出し。mlx_destroy_image を呼び出し、MLX の画像を破棄する。
- srcs/engine/texture/texture_cleanup.c:20 `	if (game->textures.south.img)` — 条件評価。条件を評価して分岐する。
- srcs/engine/texture/texture_cleanup.c:21 `		mlx_destroy_image(game->mlx, game->textures.south.img);` — 関数呼び出し。mlx_destroy_image を呼び出し、MLX の画像を破棄する。
- srcs/engine/texture/texture_cleanup.c:22 `	if (game->textures.east.img)` — 条件評価。条件を評価して分岐する。
- srcs/engine/texture/texture_cleanup.c:23 `		mlx_destroy_image(game->mlx, game->textures.east.img);` — 関数呼び出し。mlx_destroy_image を呼び出し、MLX の画像を破棄する。
- srcs/engine/texture/texture_cleanup.c:24 `	if (game->textures.west.img)` — 条件評価。条件を評価して分岐する。
- srcs/engine/texture/texture_cleanup.c:25 `		mlx_destroy_image(game->mlx, game->textures.west.img);` — 関数呼び出し。mlx_destroy_image を呼び出し、MLX の画像を破棄する。
- srcs/engine/texture/texture_cleanup.c:26 `}`

## 未呼び出しの関数（正常起動では実行されない）

## setup_event_hooks（srcs/engine/game_loop.c, 開始行:38）

- srcs/engine/game_loop.c:38 `static void	setup_event_hooks(t_game *game)` — 関数定義開始。関数 setup_event_hooks の実装が始まる。
- srcs/engine/game_loop.c:39 `{`
- srcs/engine/game_loop.c:40 `	mlx_hook(game->win, ON_KEYDOWN, 0, handle_keypress, game);` — 関数呼び出し。mlx_hook を呼び出し、イベントフックを設定する。
- srcs/engine/game_loop.c:41 `	mlx_hook(game->win, ON_KEYUP, 0, handle_keyrelease, game);` — 関数呼び出し。mlx_hook を呼び出し、イベントフックを設定する。
- srcs/engine/game_loop.c:42 `	mlx_hook(game->win, ON_DESTROY, 0, close_window, game);` — 関数呼び出し。mlx_hook を呼び出し、イベントフックを設定する。
- srcs/engine/game_loop.c:43 `	mlx_loop_hook(game->mlx, render_frame, game);` — 関数呼び出し。mlx_loop_hook を呼び出し、ループフックを設定する。
- srcs/engine/game_loop.c:44 `}`

## close_window（srcs/engine/key_handler/key_handler.c, 開始行:28）

- srcs/engine/key_handler/key_handler.c:28 `int	close_window(t_game *game)` — 関数定義開始。関数 close_window の実装が始まる。
- srcs/engine/key_handler/key_handler.c:29 `{`
- srcs/engine/key_handler/key_handler.c:30 `	cleanup_game(game);` — 関数呼び出し。cleanup_game を呼び出し、ゲームをクリーンアップする。
- srcs/engine/key_handler/key_handler.c:31 `	exit(0);` — 関数呼び出し。exit を呼び出し、プロセスを終了する。
- srcs/engine/key_handler/key_handler.c:32 `	return (0);` — 戻り値として 0 を返す。
- srcs/engine/key_handler/key_handler.c:33 `}`

## cleanup_resources（srcs/error/error_cleanup.c）

- srcs/error/error_cleanup.c:17 `void	cleanup_resources(t_cleanup_data *cleanup_data)` — 関数定義開始。関数 cleanup_resources の実装が始まる。
- srcs/error/error_cleanup.c:18 `{`
- srcs/error/error_cleanup.c:19 `	if (!cleanup_data)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_cleanup.c:20 `		return ;` — 戻り値を返さずに関数から戻る。
- srcs/error/error_cleanup.c:21 `	if (cleanup_data->config)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_cleanup.c:22 `		free_config_data(cleanup_data->config);` — 関数呼び出し。free_config_data を呼び出し、設定データを解放する。
- srcs/error/error_cleanup.c:23 `	if (cleanup_data->map)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_cleanup.c:24 `		free_map((void **)cleanup_data->map);` — 関数呼び出し。free_map を呼び出し、マップを解放する。
- srcs/error/error_cleanup.c:25 `	free(cleanup_data);` — 関数呼び出し。free を呼び出し、メモリを解放する。
- srcs/error/error_cleanup.c:26 `}`

## print_error_header（srcs/error/error_exit.c）

- srcs/error/error_exit.c:21 `static void	print_error_header(void)` — 関数定義開始。関数 print_error_header の実装が始まる。
- srcs/error/error_exit.c:22 `{`
- srcs/error/error_exit.c:23 `	write(2, "Error\n", 6);` — 関数呼び出し。write を呼び出し、出力する。
- srcs/error/error_exit.c:24 `}`

## print_error_msg（srcs/error/error_exit.c）

- srcs/error/error_exit.c:26 `static void	print_error_msg(const char *msg, const char *context)` — 関数定義開始。関数 print_error_msg の実装が始まる。
- srcs/error/error_exit.c:27 `{`
- srcs/error/error_exit.c:28 `	write(2, msg, ft_strlen(msg));` — 関数呼び出し。write を呼び出し、出力する。
- srcs/error/error_exit.c:29 `	if (context)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_exit.c:30 `	{`
- srcs/error/error_exit.c:31 `		write(2, ": ", 2);` — 関数呼び出し。write を呼び出し、出力する。
- srcs/error/error_exit.c:32 `		write(2, context, ft_strlen(context));` — 関数呼び出し。write を呼び出し、出力する。
- srcs/error/error_exit.c:33 `	}`
- srcs/error/error_exit.c:34 `	write(2, "\n", 1);` — 関数呼び出し。write を呼び出し、出力する。
- srcs/error/error_exit.c:35 `}`

## error_exit（srcs/error/error_exit.c）

- srcs/error/error_exit.c:37 `void	error_exit(t_error_code code, const char *ctx, void *cleanup)` — 関数定義開始。関数 error_exit の実装が始まる。
- srcs/error/error_exit.c:38 `{`
- srcs/error/error_exit.c:39 `	const char	*msg;` — 変数宣言。ローカル変数を用意する。
- srcs/error/error_exit.c:40 ``
- srcs/error/error_exit.c:41 `	print_error_header();` — 関数呼び出し。print_error_header を呼び出し、エラーヘッダーを出力する。
- srcs/error/error_exit.c:42 `	msg = get_error_message(code);` — 代入。msg に get_error_message(code) を設定する。
- srcs/error/error_exit.c:43 `	print_error_msg(msg, ctx);` — 関数呼び出し。print_error_msg を呼び出し、エラーメッセージを出力する。
- srcs/error/error_exit.c:44 `	if (cleanup)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_exit.c:45 `		cleanup_resources((t_cleanup_data *)cleanup);` — 関数呼び出し。cleanup_resources を呼び出し、リソースを解放する。
- srcs/error/error_exit.c:46 `	exit(1);` — 関数呼び出し。exit を呼び出し、プロセスを終了する。
- srcs/error/error_exit.c:47 `}`

## error_exit_simple（srcs/error/error_exit.c）

- srcs/error/error_exit.c:49 `void	error_exit_simple(t_error_code error_code)` — 関数定義開始。関数 error_exit_simple の実装が始まる。
- srcs/error/error_exit.c:50 `{`
- srcs/error/error_exit.c:51 `	error_exit(error_code, NULL, NULL);` — 関数呼び出し。error_exit を呼び出し、エラーで終了する。
- srcs/error/error_exit.c:52 `}`

## get_parse_error（srcs/error/error_messages.c）

- srcs/error/error_messages.c:16 `static const char	*get_parse_error(t_error_code code)` — 関数定義開始。関数 get_parse_error の実装が始まる。
- srcs/error/error_messages.c:17 `{`
- srcs/error/error_messages.c:18 `	if (code == ERR_UNKNOWN_IDENTIFIER)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:19 `		return ("Unknown identifier in config section");` — 戻り値として "Unknown identifier in config section" を返す。
- srcs/error/error_messages.c:20 `	if (code == ERR_DUPLICATE_IDENTIFIER)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:21 `		return ("Duplicate identifier found");` — 戻り値として "Duplicate identifier found" を返す。
- srcs/error/error_messages.c:22 `	if (code == ERR_SYNTAX_TEXTURE)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:23 `		return ("Invalid texture path syntax");` — 戻り値として "Invalid texture path syntax" を返す。
- srcs/error/error_messages.c:24 `	if (code == ERR_SYNTAX_RGB)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:25 `		return ("Invalid RGB color format or range");` — 戻り値として "Invalid RGB color format or range" を返す。
- srcs/error/error_messages.c:26 `	if (code == ERR_MISSING_IDENTIFIER)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:27 `		return ("Missing required identifier");` — 戻り値として "Missing required identifier" を返す。
- srcs/error/error_messages.c:28 `	return (NULL);` — 戻り値として NULL を返す。
- srcs/error/error_messages.c:29 `}`

## get_map_error（srcs/error/error_messages.c）

- srcs/error/error_messages.c:31 `static const char	*get_map_error(t_error_code code)` — 関数定義開始。関数 get_map_error の実装が始まる。
- srcs/error/error_messages.c:32 `{`
- srcs/error/error_messages.c:33 `	if (code == ERR_CONFIG_AFTER_MAP)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:34 `		return ("Config line appeared after map section");` — 戻り値として "Config line appeared after map section" を返す。
- srcs/error/error_messages.c:35 `	if (code == ERR_MINIMUM_MAP_SIZE)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:36 `		return ("Map is too small (minimum 3x3 required)");` — 戻り値として "Map is too small (minimum 3x3 required)" を返す。
- srcs/error/error_messages.c:37 `	if (code == ERR_MAXIMUM_MAP_SIZE)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:38 `		return ("Map exceeds maximum allowed size");` — 戻り値として "Map exceeds maximum allowed size" を返す。
- srcs/error/error_messages.c:39 `	if (code == ERR_WALL_ENCLOSURE)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:40 `		return ("Map is not enclosed by walls");` — 戻り値として "Map is not enclosed by walls" を返す。
- srcs/error/error_messages.c:41 `	if (code == ERR_PLAYER_COUNT_ZERO)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:42 `		return ("No player start position found");` — 戻り値として "No player start position found" を返す。
- srcs/error/error_messages.c:43 `	if (code == ERR_PLAYER_COUNT_MULTIPLE)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:44 `		return ("Multiple player start positions found");` — 戻り値として "Multiple player start positions found" を返す。
- srcs/error/error_messages.c:45 `	if (code == ERR_ROW_LENGTH_INCONSISTENT)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:46 `		return ("Inconsistent row lengths in map");` — 戻り値として "Inconsistent row lengths in map" を返す。
- srcs/error/error_messages.c:47 `	if (code == ERR_INVALID_CHARACTER)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:48 `		return ("Invalid character in map");` — 戻り値として "Invalid character in map" を返す。
- srcs/error/error_messages.c:49 `	if (code == ERR_SPACE_VOID_CONTACT)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:50 `		return ("Space character touches void area");` — 戻り値として "Space character touches void area" を返す。
- srcs/error/error_messages.c:51 `	return (NULL);` — 戻り値として NULL を返す。
- srcs/error/error_messages.c:52 `}`

## get_system_error（srcs/error/error_messages.c）

- srcs/error/error_messages.c:54 `static const char	*get_system_error(t_error_code code)` — 関数定義開始。関数 get_system_error の実装が始まる。
- srcs/error/error_messages.c:55 `{`
- srcs/error/error_messages.c:56 `	if (code == ERR_FILE_NOT_FOUND)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:57 `		return ("File not found");` — 戻り値として "File not found" を返す。
- srcs/error/error_messages.c:58 `	if (code == ERR_FILE_READ_PERMISSION)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:59 `		return ("Permission denied reading file");` — 戻り値として "Permission denied reading file" を返す。
- srcs/error/error_messages.c:60 `	if (code == ERR_INVALID_FILE_EXTENSION)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:61 `		return ("Invalid file extension");` — 戻り値として "Invalid file extension" を返す。
- srcs/error/error_messages.c:62 `	if (code == ERR_INVALID_PATH)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:63 `		return ("Invalid file path");` — 戻り値として "Invalid file path" を返す。
- srcs/error/error_messages.c:64 `	if (code == ERR_MALLOC_FAILURE)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:65 `		return ("Memory allocation failed");` — 戻り値として "Memory allocation failed" を返す。
- srcs/error/error_messages.c:66 `	if (code == ERR_BUFFER_OVERFLOW)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:67 `		return ("Buffer overflow detected");` — 戻り値として "Buffer overflow detected" を返す。
- srcs/error/error_messages.c:68 `	return (NULL);` — 戻り値として NULL を返す。
- srcs/error/error_messages.c:69 `}`

## get_engine_error（srcs/error/error_messages.c）

- srcs/error/error_messages.c:71 `static const char	*get_engine_error(t_error_code code)` — 関数定義開始。関数 get_engine_error の実装が始まる。
- srcs/error/error_messages.c:72 `{`
- srcs/error/error_messages.c:73 `	if (code == ERR_MLX_INIT_FAILURE)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:74 `		return ("Failed to initialize MLX");` — 戻り値として "Failed to initialize MLX" を返す。
- srcs/error/error_messages.c:75 `	if (code == ERR_WINDOW_CREATION_FAILURE)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:76 `		return ("Failed to create window");` — 戻り値として "Failed to create window" を返す。
- srcs/error/error_messages.c:77 `	if (code == ERR_IMAGE_CREATION_FAILURE)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:78 `		return ("Failed to create image");` — 戻り値として "Failed to create image" を返す。
- srcs/error/error_messages.c:79 `	if (code == ERR_TEXTURE_LOAD_FAILURE)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:80 `		return ("Failed to load texture");` — 戻り値として "Failed to load texture" を返す。
- srcs/error/error_messages.c:81 `	if (code == ERR_DDA_OUT_OF_BOUNDS)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:82 `		return ("DDA algorithm accessed out of bounds");` — 戻り値として "DDA algorithm accessed out of bounds" を返す。
- srcs/error/error_messages.c:83 `	if (code == ERR_DRAW_COORD_OUT_OF_RANGE)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:84 `		return ("Drawing coordinate out of range");` — 戻り値として "Drawing coordinate out of range" を返す。
- srcs/error/error_messages.c:85 `	return (NULL);` — 戻り値として NULL を返す。
- srcs/error/error_messages.c:86 `}`

## get_error_message（srcs/error/error_messages.c）

- srcs/error/error_messages.c:88 `const char	*get_error_message(t_error_code code)` — 関数定義開始。関数 get_error_message の実装が始まる。
- srcs/error/error_messages.c:89 `{`
- srcs/error/error_messages.c:90 `	const char	*msg;` — 変数宣言。ローカル変数を用意する。
- srcs/error/error_messages.c:91 ``
- srcs/error/error_messages.c:92 `	if (code == ERR_INVALID_ARGC)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:93 `		return ("Usage: ./cub3D <map.cub>");` — 戻り値として "Usage: ./cub3D <map.cub>" を返す。
- srcs/error/error_messages.c:94 `	if (code == ERR_INVALID_ARGV)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:95 `		return ("Invalid argument");` — 戻り値として "Invalid argument" を返す。
- srcs/error/error_messages.c:96 `	msg = get_parse_error(code);` — 代入。msg に get_parse_error(code) を設定する。
- srcs/error/error_messages.c:97 `	if (msg)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:98 `		return (msg);` — 戻り値として msg を返す。
- srcs/error/error_messages.c:99 `	msg = get_map_error(code);` — 代入。msg に get_map_error(code) を設定する。
- srcs/error/error_messages.c:100 `	if (msg)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:101 `		return (msg);` — 戻り値として msg を返す。
- srcs/error/error_messages.c:102 `	msg = get_system_error(code);` — 代入。msg に get_system_error(code) を設定する。
- srcs/error/error_messages.c:103 `	if (msg)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:104 `		return (msg);` — 戻り値として msg を返す。
- srcs/error/error_messages.c:105 `	msg = get_engine_error(code);` — 代入。msg に get_engine_error(code) を設定する。
- srcs/error/error_messages.c:106 `	if (msg)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_messages.c:107 `		return (msg);` — 戻り値として msg を返す。
- srcs/error/error_messages.c:108 `	return ("An error occurred");` — 戻り値として "An error occurred" を返す。
- srcs/error/error_messages.c:109 `}`

## set_error_status（srcs/error/error_status.c）

- srcs/error/error_status.c:17 `void	set_error_status(t_error_code error_code)` — 関数定義開始。関数 set_error_status の実装が始まる。
- srcs/error/error_status.c:18 `{`
- srcs/error/error_status.c:19 `	g_error_status = error_code;` — 代入。g_error_status に error_code を設定する。
- srcs/error/error_status.c:20 `}`

## get_error_status（srcs/error/error_status.c）

- srcs/error/error_status.c:22 `t_error_code	get_error_status(void)` — 関数定義開始。関数 get_error_status の実装が始まる。
- srcs/error/error_status.c:23 `{`
- srcs/error/error_status.c:24 `	return (g_error_status);` — 戻り値として g_error_status を返す。
- srcs/error/error_status.c:25 `}`

## clear_error_status（srcs/error/error_status.c）

- srcs/error/error_status.c:27 `void	clear_error_status(void)` — 関数定義開始。関数 clear_error_status の実装が始まる。
- srcs/error/error_status.c:28 `{`
- srcs/error/error_status.c:29 `	g_error_status = 0;` — 代入。g_error_status に 0 を設定する。
- srcs/error/error_status.c:30 `}`

## get_warning_message（srcs/error/error_warning.c）

- srcs/error/error_warning.c:17 `static const char	*get_warning_message(t_warning_code code)` — 関数定義開始。関数 get_warning_message の実装が始まる。
- srcs/error/error_warning.c:18 `{`
- srcs/error/error_warning.c:19 `	if (code == WARN_UNREACHABLE_AREA)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_warning.c:20 `		return ("Unreachable area detected");` — 戻り値として "Unreachable area detected" を返す。
- srcs/error/error_warning.c:21 `	if (code == WARN_PERFORMANCE_ISSUE)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_warning.c:22 `		return ("Performance issue detected");` — 戻り値として "Performance issue detected" を返す。
- srcs/error/error_warning.c:23 `	return ("Warning");` — 戻り値として "Warning" を返す。
- srcs/error/error_warning.c:24 `}`

## error_warning（srcs/error/error_warning.c）

- srcs/error/error_warning.c:26 `void	error_warning(t_warning_code warning_code, const char *context)` — 関数定義開始。関数 error_warning の実装が始まる。
- srcs/error/error_warning.c:27 `{`
- srcs/error/error_warning.c:28 `	const char	*msg;` — 変数宣言。ローカル変数を用意する。
- srcs/error/error_warning.c:29 ``
- srcs/error/error_warning.c:30 `	write(2, "Warning: ", 9);` — 関数呼び出し。write を呼び出し、出力する。
- srcs/error/error_warning.c:31 `	msg = get_warning_message(warning_code);` — 代入。msg に get_warning_message(warning_code) を設定する。
- srcs/error/error_warning.c:32 `	write(2, msg, ft_strlen(msg));` — 関数呼び出し。write を呼び出し、出力する。
- srcs/error/error_warning.c:33 `	if (context)` — 条件評価。条件を評価して分岐する。
- srcs/error/error_warning.c:34 `	{`
- srcs/error/error_warning.c:35 `		write(2, ": ", 2);` — 関数呼び出し。write を呼び出し、出力する。
- srcs/error/error_warning.c:36 `		write(2, context, ft_strlen(context));` — 関数呼び出し。write を呼び出し、出力する。
- srcs/error/error_warning.c:37 `	}`
- srcs/error/error_warning.c:38 `	write(2, "\n", 1);` — 関数呼び出し。write を呼び出し、出力する。
- srcs/error/error_warning.c:39 `}`

## free_partial_map（srcs/parse/map/load_map.c）

- srcs/parse/map/load_map.c:17 `static void	free_partial_map(char **map, size_t count)` — 関数定義開始。関数 free_partial_map の実装が始まる。
- srcs/parse/map/load_map.c:18 `{`
- srcs/parse/map/load_map.c:19 `	size_t	i;` — 変数宣言。ローカル変数を用意する。
- srcs/parse/map/load_map.c:20 ``
- srcs/parse/map/load_map.c:21 `	i = 0;` — 代入。i に 0 を設定する。
- srcs/parse/map/load_map.c:22 `	while (i < count)` — ループ評価。条件が真の間ループする。
- srcs/parse/map/load_map.c:23 `	{`
- srcs/parse/map/load_map.c:24 `		free(map[i]);` — 関数呼び出し。free を呼び出し、メモリを解放する。
- srcs/parse/map/load_map.c:25 `		i++;` — 文の評価。式または宣言を処理する。
- srcs/parse/map/load_map.c:26 `	}`
- srcs/parse/map/load_map.c:27 `	free(map);` — 関数呼び出し。free を呼び出し、メモリを解放する。
- srcs/parse/map/load_map.c:28 `}`

