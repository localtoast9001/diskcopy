/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: file_handle.cpp
 */

#include "file_handle.hpp"
#include <unistd.h>
#include <cerrno>
#include <fcntl.h>

namespace diskcopy
{

file_handle::file_handle()
    : _fd(file_handle::invalid_handle)
{
}

file_handle::file_handle(int handle)
    : _fd(handle)
{
}

file_handle::file_handle(file_handle&& other)
    : _fd(other._fd)
{
    other._fd = file_handle::invalid_handle;
}

file_handle::~file_handle()
{
    close();
}


/**
 * Closes the file handle if it is valid. After calling this method, the file handle will be invalid.
 */
void file_handle::close()
{
    if (_fd != file_handle::invalid_handle)
    {
        ::close(_fd);
        _fd = file_handle::invalid_handle;
    }
}

/**
 * Opens a file and stores the file descriptor in this object. If the file is successfully opened, this object will take ownership of the file descriptor and will close it when the object goes out of scope.
 */
bool file_handle::open(
    const char* path,
    int flags,
    int mode,
    int& err_code)
{
    int fd = ::open(path, flags, mode);
    if (fd == file_handle::invalid_handle)
    {
        err_code = errno;
        return false;
    }
    
    close();
    _fd = fd;
    return true;
}

}
