/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/13 03:21:46 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stdlib.h>

/**
 * @brief 設定ファイルからテクスチャパスとRGB値を読み込む
 * @param filepath .cubファイルのパス
 * @param config 設定データを格納する構造体
 * @return 成功: 0 / 失敗: エラーコード
 */
int load_config(const char *filepath, t_config_data *config) {
  (void)filepath;
  (void)config;
  return (0);
}
