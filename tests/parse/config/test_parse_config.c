/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_config.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/13 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

// テスト結果の統計
typedef struct s_test_stats
{
	int	total;
	int	passed;
	int	failed;
}	t_test_stats;

// テスト統計をグローバルに保持
static t_test_stats	g_stats = {0, 0, 0};

/**
 * @brief テストケースの実行とレポート
 * @param test_name テスト名
 * @param result テスト結果 (0: 成功, !0: 失敗)
 * @param expected_success 期待される結果 (1: 成功を期待, 0: 失敗を期待)
 */
void	report_test(const char *test_name, int result, int expected_success)
{
	int	passed;

	g_stats.total++;
	if (expected_success)
		passed = (result == 0);
	else
		passed = (result != 0);
	if (passed)
	{
		printf("✓ PASS: %s\n", test_name);
		g_stats.passed++;
	}
	else
	{
		printf("✗ FAIL: %s (expected %s, got %s)\n", test_name,
			expected_success ? "success" : "failure",
			result == 0 ? "success" : "failure");
		g_stats.failed++;
	}
}

/**
 * @brief Config検証のテスト
 * @param filepath テストファイルのパス
 * @param test_name テスト名
 * @param expected_success 期待される結果
 */
void	test_validate_config_file(const char *filepath, const char *test_name,
		int expected_success)
{
	char		**input_data;
	size_t		line_index;
	int			result;

	input_data = (char **)read_map(filepath);
	if (!input_data)
	{
		printf("✗ ERROR: Failed to read file: %s\n", filepath);
		g_stats.total++;
		g_stats.failed++;
		return ;
	}
	line_index = 0;
	result = validate_config(input_data, &line_index);
	report_test(test_name, result, expected_success);
	free_map((void **)input_data);
}

/**
 * @brief テスト統計の表示
 */
void	print_test_summary(void)
{
	printf("\n=== Test Summary ===\n");
	printf("Total:  %d\n", g_stats.total);
	printf("Passed: %d\n", g_stats.passed);
	printf("Failed: %d\n", g_stats.failed);
	if (g_stats.failed == 0)
		printf("\n✓ All tests passed!\n");
	else
		printf("\n✗ Some tests failed.\n");
}

/**
 * @brief メイン関数
 */
int	main(void)
{
	printf("=== Config Parser Test Suite ===\n\n");
	// 有効なConfigのテスト
	printf("--- Valid Configs ---\n");
	test_validate_config_file("test_data/config/valid_config.cub",
		"Valid: Standard config", 1);
	test_validate_config_file("test_data/config/config_with_blanks.cub",
		"Valid: Config with blank lines", 1);
	// 無効なConfigのテスト
	printf("\n--- Invalid Configs ---\n");
	test_validate_config_file("test_data/config/invalid_duplicate.cub",
		"Invalid: Duplicate identifier", 0);
	test_validate_config_file("test_data/config/invalid_rgb.cub",
		"Invalid: RGB value out of range", 0);
	test_validate_config_file("test_data/config/missing_identifier.cub",
		"Invalid: Missing identifier (EA)", 0);
	print_test_summary();
	return (g_stats.failed == 0 ? 0 : 1);
}
