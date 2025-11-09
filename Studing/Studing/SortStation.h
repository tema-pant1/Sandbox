#pragma once
#include <iostream>
#include "DynArray.h"
#include "Stack.h"

bool is_operator(std::string input);

int arity(std::string oprtr);

void from_stck_to_out(stack<std::string>& stack, DynamicArray<std::string>& result);

void process_token(std::string& token, stack<std::string>& operators, DynamicArray<std::string>& result);

void sort_to_RPN(DynamicArray<std::string>& result, std::string input);

void calculator();