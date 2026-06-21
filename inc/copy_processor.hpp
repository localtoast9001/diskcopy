/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: copy_processor.hpp
 */

#pragma once
#ifndef COPY_PROCESSOR_HPP
#define COPY_PROCESSOR_HPP

#include <cstdint>
#include "device.hpp"

namespace diskcopy
{

/**
 * Class: copy_processor
 * Description: Handles the copying of data from an input source to an output destination.
 */
class copy_processor
{
public:
    copy_processor(uint64_t block_size);
    ~copy_processor() = default;

    bool copy(device& input, device& output);

private:
    uint64_t _block_size;
};

}

#endif // COPY_PROCESSOR_HPP
