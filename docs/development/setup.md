# 開発環境セットアップ

## 必要要件

### OS

- Linux (Ubuntu 20.04以降推奨)
- macOS (MinilibX OpenGL版使用時)

### ツール

| ツール名 | バージョン | 用途 |
|----------|-----------|------|
| gcc/clang | 9.0+ | Cコンパイラ |
| g++/clang++ | 9.0+ | C++コンパイラ（テスト用） |
| make | 4.0+ | ビルドツール |
| git | 2.0+ | バージョン管理 |

## インストール手順

<!-- インストール手順を記述してください -->

### 1. リポジトリのクローン

```bash
git clone <repository-url>
cd cub3D
```

### 2. 依存関係のインストール

```bash
# 依存関係のインストールコマンド
```

### 3. ビルド

```bash
make
```

## 動作確認

<!-- 動作確認の手順を記述してください -->

```bash
./cub3D <map_file>
```

## テストの実行

### マップパーサーテスト

```bash
make test_parse_map
```

テストはC++で実装されています。詳細は[テストガイド](testing.md)を参照してください。

## トラブルシューティング

### MinilibXのコンパイルエラー

**Linux**: X11開発ライブラリのインストールが必要
```bash
sudo apt-get install libx11-dev libxext-dev
```

### テストのコンパイルエラー

C++コンパイラが必要です：
```bash
# Ubuntu/Debian
sudo apt-get install g++

# macOS (Xcode Command Line Tools)
xcode-select --install
```

### 問題1

**症状:**

**解決方法:**

## 参照

<!-- 参照ドキュメントへのリンクを記述してください -->

- [コーディング規約](./coding-standards.md)
- [デバッグ](./debugging.md)
