/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: arguments.cpp
 */

#include <cstring>
#include "arguments.hpp"
using namespace diskcopy;

arguments::arguments()
: _block_size(ARGUMENTS_DEFAULT_BLOCK_SIZE)
{
}

/**
 * Attempts to parse raw command-line arguments.
 *
 * @param argc Number of command-line arguments.
 * @param argv Raw argument vector from main.
 * @return True if parsing succeeds; otherwise false.
 */
bool arguments::try_parse(
	int argc,
	const char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        const char* arg = argv[i];
        const char* opt_val = nullptr;
        if (is_option(arg, "if", &opt_val))
        {
            _input_file = opt_val;
        }
        else if (is_option(arg, "of", &opt_val))
        {
            _output_file = opt_val;
        }
        else if (is_option(arg, "bs", &opt_val))
        {
            _block_size = std::strtoull(opt_val, nullptr, 10);
            if (_block_size == 0 || _block_size % ARGUMENTS_DEFAULT_BLOCK_SIZE != 0)
            {
                // Invalid block size.
                return false;
            }
        }
        else
        {
            // Unrecognized argument.
            return false;
        }
    }

    if (_input_file.empty() || _output_file.empty())
    {
        // Required arguments not provided.
        return false;
    }

    return true;
}

bool arguments::is_option(
    const char* arg,
    const char* option_name,
    const char** value_out)
{
    size_t opt_len = strlen(option_name);
    if (strncmp(arg, option_name, opt_len) == 0 && arg[opt_len] == '=')
    {
        *value_out = arg + opt_len + 1;
        return true;
    }

    return false;
}
