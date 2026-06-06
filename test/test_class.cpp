/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * File: test_class.cpp
 */

#include "test_class.hpp"

test_class::init_node* test_class::init_head = nullptr;

/**
 * Initializes a map with all test class instances.
 * @param instances Map to populate with test class names and pointers.
 */
void test_class::init_instances(std::map<std::string, test_class*>& instances)
{
    init_node* current = init_head;
    while (current != nullptr)
    {
        instances[current->instance->name()] = current->instance;
        current = current->next;
    }
}

/**
 * Initializes a test class instance.
 *
 * @param name Name of the test class.
 */
test_class::test_class(
	const std::string& name)
	: _name(name)
{
    init_node* node = new init_node{init_head, this};
    init_head = node;
}

/**
 * Adds a test method by name.
 *
 * @param name Name of the test method.
 * @param method Function pointer for the test method.
 */
void test_class::add(
	const std::string& name,
	test_method method)
{
    _methods[name] = method;
}
