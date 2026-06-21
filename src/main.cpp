/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: main.cpp
 */

#include <iostream>

#include "arguments.hpp"
#include "copy_processor.hpp"
#include "file_device.hpp"
#include <fcntl.h>

using namespace diskcopy;

void print_usage()
{
    std::cout << "Usage: diskcopy if=<input_file> of=<output_file> [bs=<block_size>]\n";
    std::cout << "  if: Required. Path to the input file.\n";
    std::cout << "  of: Required. Path to the output file.\n";
    std::cout << "  bs: Optional. Block size in bytes (must be a positive multiple of " << ARGUMENTS_DEFAULT_BLOCK_SIZE << "). Default is " << ARGUMENTS_DEFAULT_BLOCK_SIZE << ".\n";
}

/**
 * Program entry point.
 *
 * Returns 0 to indicate successful execution.
 */
int main(
    int argc,
    const char* argv[])
{
    arguments args;
    if (!args.try_parse(argc, argv))
    {
        print_usage();
        return 1; // Non-zero return value indicates failure.
    }

    error err;
    copy_processor processor(args.block_size());
    file_device input;
    file_device output;

    if (!input.open(args.input_file().c_str(), O_RDONLY, 0, err))
    {
        std::cerr << "Error: Failed to open input file '" << args.input_file() << "'. Code: " << err.code() << ", Message: " << err.message() << "\n";
        return 1;
    }

    if (!output.open(args.output_file().c_str(), O_WRONLY | O_CREAT, 0644, err))
    {
        std::cerr << "Error: Failed to open output file '" << args.output_file() << "'. Code: " << err.code() << ", Message: " << err.message() << "\n";
        return 1;
    }

    if (!processor.copy(input, output))
    {
        std::cerr << "Error: Failed to copy data.\n";
        return 1;
    }

	return 0;
}
