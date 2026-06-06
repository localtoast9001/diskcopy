/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: test_runner.cpp
 */

#include "test_runner.hpp"
#include <iostream>

namespace
{
constexpr const char* k_pass_label = "\x1b[32m[PASS]\x1b[0m";
constexpr const char* k_fail_label = "\x1b[31m[FAIL]\x1b[0m";
}

/**
 * Initializes the test runner.
 */
test_runner::test_runner()
	: test_classes()
{
    test_class::init_instances(test_classes);
}

/**
 * Initializes the test runner with an explicit test list.
 *
 * @param tests Test class instances to include.
 */
test_runner::test_runner(
	std::initializer_list<test_class*> tests)
{
	for (test_class* test : tests)
	{
		if (test != nullptr)
		{
			test_classes[test->name()] = test;
		}
	}
}

/**
 * Cleans up test runner resources.
 */
test_runner::~test_runner()
{
}

/**
 * Called by run() to determine if a test class should be executed.
 *
 * @param test The test class instance.
 * @return True if the test should be run, false otherwise.
 */
bool test_runner::should_run(
	test_class& test) const
{
	(void)test;
	return true;
}

/**
 * Runs selected tests.
 *
 * @return Process-style status code.
 */
int test_runner::run() const
{
    summary total_summary = {0, 0};
    for (const auto& pair : test_classes)
    {
        test_class* test = pair.second;
        if (test != nullptr && should_run(*test))
        {
            summary result = run_test(*test);
            total_summary.pass_count += result.pass_count;
            total_summary.fail_count += result.fail_count;

            std::cout << test->name() << ": "
                      << result.pass_count << " passed, "
                      << result.fail_count << " failed.\n";
        }
    }

    std::cout << "Total: " << total_summary.pass_count << " passed, "
              << total_summary.fail_count << " failed.\n";
	return total_summary.fail_count == 0 ? 0 : 1;
}

test_runner::summary test_runner::run_test(
    test_class& test) const
{
    int fail_count = 0;
    int pass_count = 0;
    for (const auto& pair : test.c_methods())
    {
        const std::string& method_name = pair.first;
        test_class::test_method method = pair.second;
        auto full_test_name = test.name() + "::" + method_name;
        if (!method)
        {
            std::cerr << "Test method " << full_test_name << " has null function pointer.\n";
            fail_count++;
            continue;
        }

        bool passed = run_test_method(
            test,
            method,
            full_test_name);
        if (passed)
        {
            pass_count++;
            std::cout << k_pass_label << " " << full_test_name << std::endl;
        }
        else
        {
            fail_count++;
            std::cout << k_fail_label << " " << full_test_name << std::endl;
        }

    }

    summary result;
    result.pass_count = pass_count;
    result.fail_count = fail_count;
    return result;
}

bool test_runner::run_test_method(
    test_class& test,
    test_class::test_method method,
    const std::string& full_test_name) const
{
    bool pass = false;
    try
    {
        pass = (test.*method)();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception in test " << full_test_name << ": ";
        std::cerr << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "Unknown exception in test " << full_test_name << '\n';
    }

    return pass;
}
