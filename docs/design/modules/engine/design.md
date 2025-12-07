# engine モジュール設計

## 目的

ゲームエンジンの制御とレンダリングを担当するモジュール。
ウィンドウシステム（MinilibX）の初期化、ゲームループの管理、フレームレンダリング、プレイヤー操作などを統合的に管理する。

## 責務

- **ゲームの初期化**: MinilibXの初期化、ウィンドウ生成
- **ゲームループの管理**: イベントフック設定、メインループ起動、クリーンアップ
- **レンダリング**: フレームごとの描画処理（レイキャスティング含む）
- **プレイヤー制御**: 移動、回転、衝突検出（実装済み）

## インターフェース

### 公開関数

| 関数名 | 説明 | 引数 | 戻り値 |
|--------|------|------|--------|
| `init_game` | ゲーム構造体を初期化し、MLXを初期化する | `t_game *game` | `void` |
| `run_game_loop` | イベントフックを設定し、ゲームループを起動する | `t_game *game` | `void` |
| `render_frame` | 1フレームをレンダリングする（MLXループフック） | `t_game *game` | `int` |

### プレイヤー操作関数（player/）

| 関数名 | 説明 | 引数 | 戻り値 |
|--------|------|------|--------|
| `move_forward` | プレイヤーを前方に移動 | `t_game *game` | `void` |
| `move_backward` | プレイヤーを後方に移動 | `t_game *game` | `void` |
| `move_left` | プレイヤーを左に移動 | `t_game *game` | `void` |
| `move_right` | プレイヤーを右に移動 | `t_game *game` | `void` |
| `rotate_left` | プレイヤーを左に回転 | `t_game *game` | `void` |
| `rotate_right` | プレイヤーを右に回転 | `t_game *game` | `void` |

### サブモジュール構成

- **init/**: 初期化関連（MLX、ゲーム構造体、プレイヤー）
- **game_loop.c**: ゲームループとイベント管理
- **renderer/**: レンダリング処理
- **raycasting/**: レイキャスティングアルゴリズム（実装済み）
- **player/**: プレイヤー移動・回転・衝突検出（実装済み）

## 内部設計

### ゲームループの流れ

```
run_game_loop()
  ↓
setup_event_hooks()
  ├─ mlx_key_hook() → handle_keypress()
  ├─ mlx_hook(ON_DESTROY) → close_window()
  └─ mlx_loop_hook() → render_frame()
  ↓
mlx_loop() [ブロッキング]
  ↓
cleanup_game()
```

### 設計方針

- **単一責任原則**: 各関数は1つの責務のみを持つ
  - `init_game`: 初期化のみ
  - `run_game_loop`: ループ管理のみ
  - `render_frame`: レンダリングのみ

- **依存性逆転**: `main.c`はエンジンの詳細を知らない
  - イベントフックの種類・設定方法は`engine`モジュール内で完結
  - `main.c`は`run_game_loop()`を呼ぶだけ

- **拡張性**: 将来の機能追加に対応
  - テクスチャマッピング、ミニマップ、スプライトなどは
    各サブモジュールに追加可能

## エラーハンドリング

- **初期化失敗**: `init_mlx()`でMLX初期化やウィンドウ生成に失敗した場合、
  エラーメッセージを標準エラー出力に書き込み、`exit(EXIT_FAILURE)`で終了

- **実行時エラー**: ゲームループ中のエラーは、適切なクリーンアップを行った上で
  `close_window()`を通じてループを終了

- **クロスプラットフォーム対応**:
  - macOS/Linuxで異なるMLX実装に対応
  - `#ifdef __linux__`で条件分岐（例: `mlx_destroy_display()`）

## 実装状況

- ✅ ゲーム初期化（init/）
- ✅ ゲームループ（game_loop.c）
- ✅ レイキャスティング（raycasting/）
- ✅ プレイヤー操作（player/）
- ⏳ テクスチャマッピング（未実装）
- ⏳ パーサー統合（進行中）

## 参照

- [README](./README.md)
- [init設計](./init/design.md)
- [renderer設計](./renderer/design.md)
- [player設計](./player/design.md)
- [raycasting設計](./raycasting/design.md)
- [ADR-0002: main.cのリファクタリング](../../../decisions/0002-main-refactoring-separation-of-concerns.md)
