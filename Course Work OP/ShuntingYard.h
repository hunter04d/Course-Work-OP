#pragma once
#include <string>
#include <vector>

void preAnalize(std::string& _in);

std::string shuntingYard(const std::string& _in, size_t _function_number);

double calculateFunc(const std::string& _RPN, const std::vector<double>& _arg_vals);

int getVariableToken(const std::string& _in, size_t _pos, size_t _function_number);

int getNumberToken(const std::string& _in, size_t _pos = 0);

int getFuncToken(const std::string& _in, size_t _pos = 0);

bool operatorCompare(char _in_char,const std::string& _tops_of_stack);
