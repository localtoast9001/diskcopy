/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: test_class.hpp
 */

#pragma once

#ifndef __TEST_CLASS_HPP__
#define __TEST_CLASS_HPP__

#include <string>
#include <map>

#include "test_context.hpp"

/**
 * Base class for test classes.
 */
class test_class
{
public:
    typedef bool (test_class::*test_method)();
    virtual ~test_class() = default;

    /**
     * Gets the name of this test class.
     * @return Name of the test class.
     */
    inline const std::string& name() const 
    {
        return _name; 
    }

    /**
     * Gets the test methods registered for this class.
     *
     * @return Map of test method names to function pointers.
     */
    inline const std::map<std::string, test_method>& c_methods() const
    {
        return _methods;
    }

    /**
     * Initializes a map with all test class instances.
     * @param instances Map to populate with test class names and pointers.
     */
    static void init_instances(std::map<std::string, test_class*>& instances);

    /**
     * Gets the test context for this class.
     * @return Pointer to the test context.
     */
    inline test_context* context() const
    {
        return _context;
    }

    void start_run(test_context* context);

protected:
    test_class(const std::string& name);

    void add(const std::string& name, test_method method);

private:
    std::string _name;
    std::map<std::string, test_method> _methods;
    test_context* _context;

    struct init_node
    {
        init_node* next;
        test_class* instance;
    };

    static init_node* init_head;
};

#endif // __TEST_CLASS_HPP__
