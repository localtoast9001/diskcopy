/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: file_device.cpp
 */

#include "file_device.hpp"
#include <unistd.h>

using namespace diskcopy;

/**
 * Opens a file and stores the file descriptor in this object. If the file is successfully opened, this object will take ownership of the file descriptor and will close it when the object goes out of scope.
 * @param path Path to the file to open.
 * @param flags Flags to use when opening the file.
 * @param mode Mode to use when opening the file.
 * @param err Error object to store error information if the open fails.
 * @return True if the open was successful, false otherwise.
 */
bool file_device::open(
    const char* path,
    int flags,
    int mode,
    error& err)
{
    int err_code = 0;
    bool result = _handle.open(path, flags, mode, err_code);
    if (!result)
    {
        err.set(err_code);
    }

    return result;
}

/**
 * Reads data from the device.
 * @param buffer Buffer to read data into.
 * @param bytes_read Number of bytes actually read.
 * @param err Error object to store error information if the read fails.
 * @return True if the read was successful, false otherwise.
 */
bool file_device::read(
    const std::span<uint8_t>& buffer,
    size_t& bytes_read,
    error& err)
{
    ssize_t b_read = ::read(_handle.get(), buffer.data(), buffer.size());
    bytes_read = static_cast<size_t>(b_read);
    if (b_read < 0)
    {
        err.set_from_errno();
        return false;
    }

    return true;
}

/**
 * Writes data to the device.
 * @param buffer Buffer containing data to write.
 * @param bytes_written Number of bytes actually written.
 * @param err Error object to store error information if the write fails.
 * @return True if the write was successful, false otherwise.
 */
bool file_device::write(
    const std::span<const uint8_t>& buffer,
    size_t& bytes_written,
    error& err)
{
    ssize_t b_written = ::write(_handle.get(), buffer.data(), buffer.size());
    bytes_written = static_cast<size_t>(b_written);
    if (b_written < 0)
    {
        err.set_from_errno();
        return false;
    }

    return true;
}