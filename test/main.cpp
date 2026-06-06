/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: main.cpp
 */

#include "test_runner.hpp"
#include <iostream>

/**
 * Program entry point for the test runner.
 *
 * @return Process-style status code.
 */
int main()
{
    test_runner runner;
   
    return runner.run();
}