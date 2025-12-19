# テスト

## 概要

cub3Dプロジェクトのテストは、C++で実装されています。これにより、モダンなテストフレームワークの機能を活用し、より表現力豊かで保守しやすいテストコードを作成できます。

## テストの構造

### ディレクトリ構成

```
tests/
├── parse/
│   ├── config/          # 設定パーサーのテスト
│   └── map/             # マップパーサーのテスト
│       ├── test_parse_map.cpp    # メインテストランナー
│       ├── test_map_file.cpp     # テストヘルパー関数
│       ├── test_map_file.h       # ヘッダーファイル
│       ├── valid_simple.cub      # 有効なマップ（シンプル）
│       ├── valid_medium.cub      # 有効なマップ（中規模）
│       ├── valid_with_spaces.cub # 有効なマップ（スペース含む）
│       ├── invalid_no_player.cub     # 無効：プレイヤーなし
│       ├── invalid_two_players.cub   # 無効：プレイヤー複数
│       ├── invalid_no_wall.cub       # 無効：壁が閉じていない
│       ├── invalid_too_small.cub     # 無効：サイズ不足
│       └── invalid_bad_char.cub      # 無効：不正な文字
```

## テストの実行

### マップパーサーテスト

```bash
make test_parse_map
```

このコマンドは以下を実行します：
1. C++テストファイル（`.cpp`）とCソースファイル（`.c`）をコンパイル
2. テスト実行可能ファイルを生成
3. 自動的にテストを実行

### 出力例

```
===== Parse Map Module Tests =====

=== Testing tests/parse/map/valid_simple.cub ===
✓ Test passed (valid map)
Map content:
[0]         1111111111111111111111111
[1]         1000000000110000000000001
...

=== Testing tests/parse/map/invalid_no_player.cub ===
Error: Map must have exactly one player start position (found 0)
✓ Test passed (invalid map detected)

===== All Tests Completed =====
```

## テストの技術仕様

### 言語とコンパイラ

- **言語**: C++11
- **コンパイラ**: `c++` (g++/clang++)
- **コンパイルフラグ**: `-Wall -Wextra -Werror -std=c++11`

### C/C++インターフェース

テストコードはC++で実装されていますが、テスト対象のコード（パーサー）はCで実装されています。この相互運用は以下の方法で実現されています：

#### extern "C" の使用

```cpp
// test_map_file.cpp
extern "C" {
    #include "parse.h"
    const char **read_map(const char *filename);
    void free_map(void **map);
}

// 関数の実装
extern "C" void test_map_file(const char *filename, int expected_result)
{
    // テスト実装
}
```

#### ヘッダーファイルのガード

```cpp
// test_map_file.h
#ifndef TEST_MAP_FILE_H
# define TEST_MAP_FILE_H

#ifdef __cplusplus
extern "C" {
#endif

void test_map_file(const char *filename, int expected_result);

#ifdef __cplusplus
}
#endif

#endif
```

### Makefileの設定

```makefile
# C++コンパイラとフラグ
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11

# C++ソースファイルとCソースファイルを分離
TEST_MAP_CXX_SRCS = tests/parse/map/test_parse_map.cpp \
                    tests/parse/map/test_map_file.cpp
TEST_MAP_C_SRCS = srcs/parse/map/parse_map.c \
                  srcs/utils/ft_strlen.c \
                  # ...

# それぞれのコンパイルルール
tests/parse/map/%.o: tests/parse/map/%.cpp
    $(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

srcs/%.o: srcs/%.c
    $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
```

## テストケースの追加

### 新しいテストマップの追加

1. `tests/parse/map/`に`.cub`ファイルを作成
2. マップデータのみを含める（設定行は不要）
3. `test_parse_map.cpp`のmain関数に新しいテストケースを追加

```cpp
// tests/parse/map/test_parse_map.cpp
int main(void)
{
    std::cout << "===== Parse Map Module Tests =====" << std::endl;
    
    // 新しいテストを追加
    test_map_file("tests/parse/map/my_new_test.cub", 0);  // 有効なマップ
    test_map_file("tests/parse/map/my_invalid_test.cub", -1);  // 無効なマップ
    
    std::cout << "\n===== All Tests Completed =====" << std::endl;
    return 0;
}
```

## ベストプラクティス

### テストファイルの命名規則

- 有効なマップ: `valid_*.cub`
- 無効なマップ: `invalid_*.cub`
- テストコード: `test_*.cpp`

### テストマップの要件

- 設定行（NO, SO, WE, EA, F, C）を含めない
- マップデータのみを記述
- 1行1レコード、改行で区切る

### コーディングスタイル

```cpp
// C++の機能を活用
void test_function()
{
    // std::coutを使用（printf の代わり）
    std::cout << "Test message" << std::endl;
    
    // nullptr を使用（NULL の代わり）
    char *ptr = nullptr;
    
    // range-based forを活用
    for (size_t i = 0; map[i]; i++)
    {
        std::cout << map[i] << std::endl;
    }
}
```

## トラブルシューティング

### リンクエラー: undefined reference to `test_map_file`

**原因**: `extern "C"`の指定が不足している

**解決方法**:
1. ヘッダーファイルに`extern "C"`ガードを追加
2. 実装ファイルで`extern "C"`を関数定義に追加

### コンパイルエラー: ISO C++ forbids

**原因**: CコードとC++コードの混在

**解決方法**:
- Cヘッダーを`extern "C"`ブロック内でインクルード
- C++標準ヘッダー（`<cstdio>`, `<cstdlib>`等）を使用

## 参照

- [開発環境セットアップ](../setup.md)
- [デバッグガイド](../debugging.md)
- [コーディング規約](../coding-standards.md)
