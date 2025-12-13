/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:00:00 by rnakatan          #+#    #+#             */
/*   Updated: 2025/12/13 00:00:00 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

class TestStats {
private:
	int total;
	int passed;
	int failed;

public:
	TestStats();
	void recordTest(bool success);
	void printSummary() const;
	int getFailed() const;
};

#endif // TEST_UTILS_HPP
