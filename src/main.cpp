/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: main.cpp
 */

 #include <iostream>

 #include "arguments.hpp"

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

	return 0;
}
