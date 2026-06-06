/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: arguments_test.cpp
 */

#include "test_class.hpp"
#include "arguments.hpp"

#define COUNT_OF(x) (sizeof(x) / sizeof((x)[0]))

/**
 * Test class for arguments behavior.
 */
class arguments_test : public test_class
{
public:
    static arguments_test instance;

    /**
	 * Initializes the arguments test class.
	 */
	arguments_test();

	/**
	 * Cleans up the arguments test class.
	 */
	~arguments_test() override;

    bool test_try_parse();
    bool test_try_parse_missing_required();
    bool test_try_parse_default_block_size();
    bool test_try_parse_unrecognized_argument();
    bool test_try_parse_invalid_format();
    bool test_try_parse_invalid_block_size();
};

arguments_test arguments_test::instance;

/**
 * Initializes the arguments test class.
 */
arguments_test::arguments_test()
	: test_class("arguments_test")
{
    add("test_try_parse", (test_method)&arguments_test::test_try_parse);
    add("test_try_parse_missing_required", (test_method)&arguments_test::test_try_parse_missing_required);
    add("test_try_parse_default_block_size", (test_method)&arguments_test::test_try_parse_default_block_size);
    add("test_try_parse_unrecognized_argument", (test_method)&arguments_test::test_try_parse_unrecognized_argument);
    add("test_try_parse_invalid_format", (test_method)&arguments_test::test_try_parse_invalid_format);
    add("test_try_parse_invalid_block_size", (test_method)&arguments_test::test_try_parse_invalid_block_size);
}

/**
 * Cleans up the arguments test class.
 */
arguments_test::~arguments_test()
{
}

bool arguments_test::test_try_parse()
{
    const char* argv[] = {
        "program_name",
        "if=input.txt",
        "of=output.txt",
        "bs=1024"
    };
    arguments args;
    bool result = args.try_parse(COUNT_OF(argv), argv);
    return result &&
           args.input_file() == "input.txt" &&
           args.output_file() == "output.txt" &&
           args.block_size() == 1024;
}

bool arguments_test::test_try_parse_missing_required()
{
    const char* argv[] = {
        "program_name",
        "if=input.txt"
    };
    arguments args;
    return !args.try_parse(COUNT_OF(argv), argv);
}

bool arguments_test::test_try_parse_default_block_size()
{
    const char* argv[] = {
        "program_name",
        "if=input.txt",
        "of=output.txt"
    };
    arguments args;
    bool result = args.try_parse(COUNT_OF(argv), argv);
    return result &&
           args.input_file() == "input.txt" &&
           args.output_file() == "output.txt" &&
           args.block_size() == ARGUMENTS_DEFAULT_BLOCK_SIZE;
}

bool arguments_test::test_try_parse_unrecognized_argument()
{
    const char* argv[] = {
        "program_name",
        "if=input.txt",
        "of=output.txt",
        "unknown=arg"
    };
    arguments args;
    return !args.try_parse(COUNT_OF(argv), argv);
}

bool arguments_test::test_try_parse_invalid_format()
{
    const char* argv[] = {
        "program_name",
        "ifinput.txt", // Missing '='
        "of=output.txt"
    };
    arguments args;
    return !args.try_parse(COUNT_OF(argv), argv);
}

bool arguments_test::test_try_parse_invalid_block_size()
{
    const char* argv[] = {
        "program_name",
        "if=input.txt",
        "of=output.txt",
        "bs=not_a_number"
    };
    arguments args;
    return !args.try_parse(COUNT_OF(argv), argv);
}