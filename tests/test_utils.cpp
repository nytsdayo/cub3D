/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/13 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.hpp"
#include <iostream>

TestStats::TestStats() : total(0), passed(0), failed(0) {}

void TestStats::recordTest(bool success) {
	total++;
	if (success)
		passed++;
	else
		failed++;
}

void TestStats::printSummary() const {
	std::cout << "\n=== Test Summary ===" << std::endl;
	std::cout << "Total:  " << total << std::endl;
	std::cout << "Passed: " << passed << std::endl;
	std::cout << "Failed: " << failed << std::endl;
	if (failed == 0)
		std::cout << "\n✓ All tests passed!" << std::endl;
	else
		std::cout << "\n✗ Some tests failed." << std::endl;
}

int TestStats::getFailed() const {
	return failed;
}
