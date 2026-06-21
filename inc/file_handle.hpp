/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: file_handle.hpp
 */
#pragma once
#ifndef __FILE_HANDLE_HPP__
#define __FILE_HANDLE_HPP__

namespace diskcopy
{

/**
 * Wrapper for a file handle that ensures the handle is properly closed when the object goes out of scope.
 */
class file_handle
{
public:
    file_handle();
    file_handle(int fd);
    file_handle(file_handle&& other);
    ~file_handle();

    inline bool is_valid() const
    {
        return _fd != invalid_handle;
    }

    inline int get() const 
    {
        return _fd;
    }

    /**
     * Closes the file handle if it is valid. After calling this method, the file handle will be invalid.
     */
    void close();

    /**
     * Opens a file and stores the file descriptor in this object. If the file is successfully opened, this object will take ownership of the file descriptor and will close it when the object goes out of scope.
     */
    bool open(
        const char* path,
        int flags,
        int mode,
        int& err_code);

private:
    constexpr static int invalid_handle = -1;
    int _fd;

    file_handle(const file_handle&) = delete;
    file_handle& operator=(const file_handle&) = delete;
};
}

#endif // __FILE_HANDLE_HPP__
