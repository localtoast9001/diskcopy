/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: file_handle_test.cpp
 */

#include "test_class.hpp"
#include "file_handle.hpp"
#include <cstdlib>
#include <fcntl.h>
#include <filesystem>

using namespace diskcopy;

class file_handle_test : public test_class
{
public:
    static file_handle_test instance;

    file_handle_test();
    ~file_handle_test() override;

    bool test_destructor_closes_handle();
    bool test_open_new_file();
    bool test_open_closes_existing_file();
    bool test_move_semantics();
    bool test_open_invalid_path();
};

file_handle_test file_handle_test::instance;

file_handle_test::file_handle_test()
    : test_class("file_handle_test")
{
    add("test_open_new_file", (test_method)&file_handle_test::test_open_new_file);
    add("test_open_invalid_path", (test_method)&file_handle_test::test_open_invalid_path);
    add("test_move_semantics", (test_method)&file_handle_test::test_move_semantics);
    add("test_destructor_closes_handle", (test_method)&file_handle_test::test_destructor_closes_handle);
    add("test_open_closes_existing_file", (test_method)&file_handle_test::test_open_closes_existing_file);
}

file_handle_test::~file_handle_test()
{
}

bool file_handle_test::test_move_semantics()
{
    diskcopy::file_handle handle1;
    int err_code = 0;
    std::filesystem::path test_file_path = context()->get_test_data_path() / std::filesystem::path("test_file.txt");
    bool result = handle1.open(test_file_path.string().c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644, err_code);
    if (!result)
    {
        return false;
    }

    diskcopy::file_handle handle2(std::move(handle1));
    return handle1.get() == -1 && handle2.get() != -1;
}

bool file_handle_test::test_open_new_file()
{
    diskcopy::file_handle handle;
    int err_code = 0;
    std::filesystem::path test_file_path = context()->get_test_data_path() / std::filesystem::path("new_test_file.txt");
    bool result = handle.open(test_file_path.string().c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644, err_code);
    return result && err_code == 0 && handle.get() != -1;
}

bool file_handle_test::test_open_invalid_path()
{
    diskcopy::file_handle handle;
    int err_code = 0;
    bool result = handle.open("invalid_path", O_RDONLY, 0, err_code);
    return !result && err_code != 0;
}

bool file_handle_test::test_destructor_closes_handle()
{
    int fd = -1;
    {
        diskcopy::file_handle handle;
        int err_code = 0;
        std::filesystem::path test_file_path = context()->get_test_data_path() / std::filesystem::path("temp_file.txt");
        bool result = handle.open(test_file_path.string().c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644, err_code);
        if (!result)
        {
            return false;
        }
        fd = handle.get();
    }

    // After the handle goes out of scope, the file descriptor should be closed.
    return fd != -1 && fcntl(fd, F_GETFD) == -1; // F_GETFD returns -1 if the fd is invalid (closed).
}

bool file_handle_test::test_open_closes_existing_file()
{
    diskcopy::file_handle handle;
    int err_code1 = 0;
    std::filesystem::path test_file_path1 = context()->get_test_data_path() / std::filesystem::path("new_file.txt");
    bool result1 = handle.open(test_file_path1.string().c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644, err_code1);
    if (!result1)
    {
        return false;
    }

    int fd1 = handle.get();

    int err_code2 = 0;
    std::filesystem::path test_file_path2 = context()->get_test_data_path() / std::filesystem::path("new_file2.txt");
    bool result2 = handle.open(test_file_path2.string().c_str(), O_RDWR | O_CREAT | O_TRUNC, 0644, err_code2);
    if (!result2)
    {
        return false;
    }

    int fd2 = handle.get();

    // The fd managed by the handle should be closed when a new file is opened, so fd1 should be invalid now.
    return fd1 != -1 && fd2 != -1 && fcntl(fd1, F_GETFD) == -1; // fd1 should be closed.
}