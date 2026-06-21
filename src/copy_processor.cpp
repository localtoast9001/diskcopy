/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: copy_processor.cpp
 */

#include "copy_processor.hpp"
#include <iostream>

using namespace diskcopy;

copy_processor::copy_processor(uint64_t block_size)
    : _block_size(block_size)
{
}

bool copy_processor::copy(device& input, device& output)
{
    uint8_t* buffer = new uint8_t[_block_size];
    if (!buffer)
    {
        return false;
    }

    std::span<uint8_t> buffer_span(buffer, _block_size);
    error err;

    bool success = true;
    while (true)
    {
        size_t bytes_read = 0;
        if (!input.read(buffer_span, bytes_read, err))
        {
            success = false;
            break;
        }
        else if (bytes_read == 0)
        {
            // End of input
            break;
        }

        size_t bytes_written = 0;
        if (!output.write(buffer_span.first(bytes_read), bytes_written, err))
        {
            success = false;
            break;
        }
        else if (bytes_written != bytes_read)
        {
            // Not all bytes were written, treat as an error
            success = false;
            break;
        }

        std::cout << '.'; // Print a dot for each block copied to indicate progress.
    }

    delete[] buffer;
    return success;
}