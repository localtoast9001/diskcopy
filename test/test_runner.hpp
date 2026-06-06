/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: test_runner.hpp
 */

#pragma once

#ifndef __TEST_RUNNER_HPP__
#define __TEST_RUNNER_HPP__

#include <initializer_list>
#include <map>
#include <string>

#include "test_class.hpp"

/**
 * Manages the execution of test cases.
 */
class test_runner
{
public:
    /**
     * Initializes the test runner.
     */
    test_runner();

    /**
     * Initializes the test runner with an explicit test list.
     *
     * @param tests Test class instances to include.
     */
    test_runner(
        std::initializer_list<test_class*> tests);

    /**
     * Cleans up test runner resources.
     */
    ~test_runner();

    /**
     * Runs selected tests.
     *
     * @return Process-style status code.
     */
    int run() const;

    /**
     * Gets the test classes included in this runner.
     *
     * @return Map of test class names to instance pointers.
     */
    const std::map<std::string, test_class*>& tests() const
    {
        return test_classes;
    }

protected:
    /**
     * Called by run() to determine if a test class should be executed.
     *
     * @param test The test class instance.
     * @return True if the test should be run, false otherwise.
     */
    virtual bool should_run(test_class& test) const;

private:
    struct summary
    {
        int pass_count;
        int fail_count;
    };

    /**
     * Runs the tests in a test class.
     */
    summary run_test(test_class& test) const;

    /**
     * Runs a test method and reports the result.
     *
     * @param test The test class instance.
     * @param method The test method pointer.
     * @param full_test_name The full test name including the class name.
     * @return True if the test passed, false otherwise.
     */
    bool run_test_method(
        test_class& test,
        test_class::test_method method,
        const std::string& full_test_name) const;

    // copy of the test class instances map for iteration during run.
    std::map<std::string, test_class*> test_classes;
};

#endif // __TEST_RUNNER_HPP__