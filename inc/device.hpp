/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: device.hpp
 */

#pragma once
#ifndef __DEVICE_HPP__
#define __DEVICE_HPP__

#include <span>
#include <cstdint>
#include "error.hpp"

namespace diskcopy
{

/**
 *  Abstract base class representing a device.
 */
class device
{
public:
    virtual ~device() = default;

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
        error& err) = 0;

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
        error& err) = 0;

protected:
    device() = default;
};

}

#endif // __DEVICE_HPP__