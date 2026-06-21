/**
 * @file test_context.hpp
 * @brief Declaration of the test_context class.
 */
#pragma once
#ifndef __TEST_CONTEXT_HPP__
#define __TEST_CONTEXT_HPP__

#include <string>

/**
 * @brief The test_context class provides environment metadata and other context info and services for running tests.
 */
class test_context
{
public:
    test_context();
    ~test_context() = default;

    inline const std::string& get_test_run_id() const { return _test_run_id; }
    inline const std::string& get_test_data_path() const { return _test_data_path; }

    void init();

private:
    std::string _test_run_id;
    std::string _test_data_path;

    test_context(const test_context&) = delete;
    test_context& operator=(const test_context&) = delete;
};

#endif // __TEST_CONTEXT_HPP__