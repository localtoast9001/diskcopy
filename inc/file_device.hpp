/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: file_device.hpp
 */

#pragma once
#ifndef __FILE_DEVICE_HPP__
#define __FILE_DEVICE_HPP__

#include "device.hpp"
#include "file_handle.hpp"

namespace diskcopy
{

/**
 * Device interface for file-based devices.
 */
class file_device : public device
{
public:
    file_device() = default;
    virtual ~file_device() = default;

    /**
     * Opens a file and stores the file descriptor in this object. If the file is successfully opened, this object will take ownership of the file descriptor and will close it when the object goes out of scope.
     * @param path Path to the file to open.
     * @param flags Flags to use when opening the file.
     * @param mode Mode to use when opening the file.
     * @param err Error object to store error information if the open fails.
     * @return True if the open was successful, false otherwise.
     */
    bool open(
        const char* path,
        int flags,
        int mode,
        error& err);

    /**
     * Reads data from the device.
     * @param buffer Buffer to read data into.
     * @param bytes_read Number of bytes actually read.
     * @param err Error object to store error information if the read fails.
     * @return True if the read was successful, false otherwise.
     */
    virtual bool read(
        const std::span<uint8_t>& buffer,
        size_t& bytes_read,
        error& err);

    /**
     * Writes data to the device.
     * @param buffer Buffer containing data to write.
     * @param bytes_written Number of bytes actually written.
     * @param err Error object to store error information if the write fails.
     * @return True if the write was successful, false otherwise.
     */
    virtual bool write(
        const std::span<const uint8_t>& buffer,
        size_t& bytes_written,
        error& err);
private:
    file_handle _handle; 
};

}

#endif // __FILE_DEVICE_HPP__
