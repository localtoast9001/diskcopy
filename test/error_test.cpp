/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: error_test.cpp
 */

#include "test_class.hpp"
#include "error.hpp"
#include <cstring>
#include <iostream>

using namespace diskcopy;

/**
 * Test class for error behavior.
 */
class error_test : public test_class
{
public:
    static error_test instance;

    /**
	 * Initializes the error test class.
	 */
	error_test();

	/**
	 * Cleans up the error test class.
	 */
	~error_test() override;

    bool test_constructor();
    bool test_set();
    bool test_set_from_errno();
};

error_test error_test::instance;

error_test::error_test()
    : test_class("error_test")
{
    add("test_constructor", (test_method)&error_test::test_constructor);
    add("test_set", (test_method)&error_test::test_set);
    add("test_set_from_errno", (test_method)&error_test::test_set_from_errno);
}

error_test::~error_test()
{
}

bool error_test::test_constructor()
{
    error err(1, "message");
    return err.code() == 1 && err.message() == "message";
}

bool error_test::test_set()
{
    error err(0, "");
    err.set(1);
    std::cerr << "Error code: " << err.code() << ", message: " << err.message() << std::endl;
    return err.code() == 1 && err.message() == std::strerror(1);
}

bool error_test::test_set_from_errno()
{
    error err(0, "");
    errno = 2;
    err.set_from_errno();
    std::cerr << "Error code: " << err.code() << ", message: " << err.message() << std::endl;
    return err.code() == 2 && err.message() == std::strerror(2);
}