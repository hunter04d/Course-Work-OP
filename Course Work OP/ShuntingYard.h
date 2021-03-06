﻿#pragma once
#include <string>
#include <vector>

namespace ShuntingYard
{
	void preAnalize(std::string& _in);//  prototype of a function  that converts an expression from mathematical to one that can be procced by shunting yard

	std::string shuntingYard(const std::string& _in, size_t _function_number);//  prototype of a function function to convert a function from infix to postfix notation

	double calculateFunc(const std::string& _RPN, const std::vector<double>& _arg_vals);//  prototype of a function that takes a function in RPN and a point and get's function value at that point

	int getVariableToken(const std::string& _in, size_t _pos, size_t _function_number);//  prototype of a function that checks if there is a spaning variable token at this position and if there is output it's length

	int getNumberToken(const std::string& _in, size_t _pos = 0);//  prototype of a function that checks if there is a spaning number token at this position and if there is outputs it's length

	int getFuncToken(const std::string& _in, size_t _pos = 0);//  prototype of a function that checks if there is a spaning function token at this position and if there is outputs it's length

	bool operatorCompare(char _in_char, const std::string& _tops_of_stack);//  prototype of a function that compares presedence of the current operator and the operator (or a left brace or a function) on top of the stack
}
