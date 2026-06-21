/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: file_device_test.cpp
 */

#include "test_class.hpp"
#include "file_device.hpp"
#include <filesystem>
#include <vector>
#include <fcntl.h>
#include <iostream>

using namespace diskcopy;

/**
 * Test class for file_device behavior.
 */
class file_device_test : public test_class
{
public:
    static file_device_test instance;

    file_device_test();
    ~file_device_test() override;

    bool test_open_new_file();
    bool test_open_invalid_path();
    bool test_open_and_read();
};

file_device_test file_device_test::instance;

file_device_test::file_device_test()
    : test_class("file_device_test")
{
    add("test_open_new_file", (test_method)&file_device_test::test_open_new_file);
    add("test_open_invalid_path", (test_method)&file_device_test::test_open_invalid_path);
    add("test_open_and_read", (test_method)&file_device_test::test_open_and_read);
}

file_device_test::~file_device_test()
{
}

bool file_device_test::test_open_new_file()
{
    file_device device;
    error err;
    std::filesystem::path test_file_path = context()->get_test_data_path() / std::filesystem::path("new_test_file.txt");
    bool result = device.open(test_file_path.string().c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644, err);
    if (!result)
    {
        std::cerr << "Failed to open file: " << err.code() << " - " << err.message() << std::endl;
    }

    return result;
}

bool file_device_test::test_open_invalid_path()
{
    file_device device;
    error err;
    bool result = device.open("invalid_path", O_RDONLY, 0, err);
    if (result)
    {
        std::cerr << "Unexpectedly succeeded in opening invalid path." << std::endl;
    }
    else
    {
        std::cerr << "Failed to open invalid path as expected: " << err.code() << " - " << err.message() << std::endl;
    }

    return !result;
}

bool file_device_test::test_open_and_read()
{
    file_device device;
    error err;
    std::filesystem::path test_file_path = std::filesystem::path("/dev/zero");
    bool open_result = device.open(test_file_path.string().c_str(), O_RDONLY, 0, err);
    if (!open_result)
    {
        std::cerr << "Failed to open file: " << err.code() << " - " << err.message() << std::endl;
        return false;
    }

    std::vector<uint8_t> buffer(1024);
    size_t bytes_read = 0;
    bool read_result = device.read(buffer, bytes_read, err);
    if (!read_result)
    {
        std::cerr << "Failed to read from file: " << err.code() << " - " << err.message() << std::endl;
        return false;
    }

    // For this test, we just want to verify that we were able to read some data.
    return bytes_read > 0;
}