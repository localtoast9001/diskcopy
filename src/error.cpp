/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: error.cpp
 */
#include <cstring>
#include "error.hpp"
using namespace diskcopy;

error::error(int code, const std::string& message)
    : _code(code), _message(message)
{
}

/**
 * Sets the error code, using a message corresponding to the code.
 */
void error::set(int code)
{
    _code = code;
    _message = std::strerror(code);
}

/**
 * Sets the error code and message from the global errno variable.
 */
void error::set_from_errno()
{
    set(errno);
}
