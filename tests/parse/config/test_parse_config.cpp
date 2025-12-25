/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_config.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/20 00:46:24 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.hpp"
#include <iostream>
#include <string>

extern "C" {
	#include "parse.h"
	#include "utils.h"
}

class ConfigTester {
private:
	TestStats& stats;

	void reportTest(const std::string& testName, int result, bool expectedSuccess) {
		bool passed = expectedSuccess ? (result == 0) : (result != 0);
		stats.recordTest(passed);

		if (passed) {
			std::cout << "✓ PASS: " << testName << std::endl;
		} else {
			std::cout << "✗ FAIL: " << testName 
					  << " (expected " << (expectedSuccess ? "success" : "failure")
					  << ", got " << (result == 0 ? "success" : "failure")
					  << ")" << std::endl;
		}
	}

public:
	ConfigTester(TestStats& s) : stats(s) {}

	void testValidateConfigFile(const std::string& filepath, 
								 const std::string& testName,
								 bool expectedSuccess) {
		char** inputData = (char**)read_map(filepath.c_str());
		if (!inputData) {
			std::cout << "✗ ERROR: Failed to read file: " << filepath << std::endl;
			stats.recordTest(false);
			return;
		}

		size_t lineIndex = 0;
		int result = validate_config(inputData, &lineIndex);
		reportTest(testName, result, expectedSuccess);
		free_map((void**)inputData);
	}
};

int main() {
	std::cout << "=== Config Parser Test Suite ===" << std::endl << std::endl;
	
	TestStats stats;
	ConfigTester tester(stats);

	// 有効なConfigのテスト
	std::cout << "--- Valid Configs ---" << std::endl;
	tester.testValidateConfigFile("test_data/config/valid_config.cub",
								  "Valid: Standard config", true);
	tester.testValidateConfigFile("test_data/config/config_with_blanks.cub",
								  "Valid: Config with blank lines", true);

	// 無効なConfigのテスト
	std::cout << "\n--- Invalid Configs ---" << std::endl;
	tester.testValidateConfigFile("test_data/config/invalid_duplicate.cub",
								  "Invalid: Duplicate identifier", false);
	tester.testValidateConfigFile("test_data/config/invalid_rgb.cub",
								  "Invalid: RGB value out of range", false);
	tester.testValidateConfigFile("test_data/config/missing_identifier.cub",
								  "Invalid: Missing identifier (EA)", false);

	stats.printSummary();
	return stats.getFailed() == 0 ? 0 : 1;
}
