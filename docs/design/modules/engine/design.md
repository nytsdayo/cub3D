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
- **key_handler/**: キーボード入力処理（実装済み）
- **renderer/**: レンダリング処理
- **raycasting/**: レイキャスティングアルゴリズム（実装済み）
- **player/**: プレイヤー移動・回転・衝突検出（実装済み）
- **texture/**: テクスチャ読み込み・サンプリング・破棄（実装済み）

## 内部設計

### ゲームループの流れ

```
run_game_loop()
  ↓
setup_event_hooks()
  ├─ mlx_hook(ON_KEYDOWN) → handle_keypress()    # キー押下を記録
  ├─ mlx_hook(ON_KEYUP) → handle_keyrelease()    # キー解放を記録
  ├─ mlx_hook(ON_DESTROY) → close_window()
  └─ mlx_loop_hook() → render_frame()
       ├─ process_held_keys()                     # 押されているキーを処理
       └─ レイキャスティング + 描画
  ↓
mlx_loop() [ブロッキング]
  ↓
cleanup_game()
```

**キー入力処理の仕組み：**
- `handle_keypress()` と `handle_keyrelease()` が `game->keys[256]` 配列を更新
- `render_frame()` 内で毎フレーム `process_held_keys()` を呼び出し
- 押されているキーに対応する移動・回転関数を実行
- フレームレートに同期した安定した動作を実現

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
- ✅ 入力処理（key_handler/）
- ✅ レイキャスティング（raycasting/）
- ✅ プレイヤー操作（player/）
- ✅ 連続キー押下処理
- ✅ 衝突判定改善（バウンディングボックス、X/Y軸分離）
- ✅ テクスチャマッピング（texture/ - 2025-12-19実装完了）
- ✅ スマート壁スライディング（player/ - 2025-12-20実装完了）
- ✅ 配列インデックスバグ修正（raycasting/ - 2025-12-20修正完了）
- ⏳ パーサー統合（パートナー担当、進行中）

## 参照

- [README](./README.md)
- [init設計](./init/design.md)
- [input設計](./key_handler/design.md)
- [renderer設計](./renderer/design.md)
- [player設計](./player/design.md)
- [raycasting設計](./raycasting/design.md)
- [texture設計](./texture/design.md)
- [ADR-0002: main.cのリファクタリング](../../../decisions/0002-main-refactoring-separation-of-concerns.md)
- [ADR-0003: プレイヤー移動・回転の実装方針](../../../decisions/0003-player-movement-implementation.md)
- [ADR-0004: テクスチャマッピングの実装方針](../../../decisions/0004-texture-mapping-implementation.md)
- [ADR-0005: world_map配列インデックスの修正](../../../decisions/0005-fix-world-map-array-indexing.md)
- [ADR-0006: スマート壁スライディングの実装](../../../decisions/0006-smart-wall-sliding-implementation.md)
