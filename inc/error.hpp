/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: error.hpp
 */

#pragma once
#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#include <string>

namespace diskcopy
{

/**
 * Represents an error that can be printed for the user.
 */
class error
{
public:
    error() : _code(0), _message() {}
    error(int code, const std::string& message);

    inline int code() const
    {
        return _code;
    }

    inline const std::string& message() const
    {
        return _message;
    }

    /**
     * Sets the error code, using a message corresponding to the code.
     */
    void set(int code);

    /**
     * Sets the error code and message from the global errno variable.
     */
    void set_from_errno();

private:
    int _code;
    std::string _message;
};

}

#endif // __ERROR_HPP__
