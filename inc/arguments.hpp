/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: arguments.hpp
 */

#pragma once

#ifndef __ARGUMENTS_HPP__
#define __ARGUMENTS_HPP__

#include <string>
#include <cstdint>

#define ARGUMENTS_DEFAULT_BLOCK_SIZE 512

namespace diskcopy
{

/**
 * Represents parsed command-line arguments.
 */
class arguments
{
public:
    arguments();
    ~arguments() = default;

	/**
	 * Attempts to parse raw command-line arguments.
	 *
	 * @param argc Number of command-line arguments.
	 * @param argv Raw argument vector from main.
	 * @return True if parsing succeeds; otherwise false.
	 */
	bool try_parse(
		int argc,
		const char* argv[]);

    const std::string& input_file() const
    {
        return _input_file;
    }

    const std::string& output_file() const
    {
        return _output_file;
    }

    uint64_t block_size() const
    {
        return _block_size;
    }

private:
    static bool is_option(
        const char* arg,
        const char* option_name,
        const char** value_out);

    std::string _input_file;
    std::string _output_file;
    uint64_t _block_size;
};

}

#endif // __ARGUMENTS_HPP__
