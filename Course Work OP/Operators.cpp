
#include "Operators.h"



bool isOperator(char _in)
{
	for (size_t i = 0; i < operators.size(); ++i)
	{
		if (_in == operators.at(i).F_operator)
			return true;
	}
	return false;
}

const T_Operator& getOperator(char _in)
{
	for (size_t i = 0; i < operators.size(); ++i)
	{
		if (_in == operators.at(i).F_operator)
			return operators.at(i);
	}
	exit(EXIT_FAILURE);
}

bool isFunction(const std::string& _in)
{
	for (size_t i = 0; i < functions.size(); ++i)
	{
		if (_in == functions.at(i).name)
			return true;
	}
	return false;
}

const T_UnaryFunction& getFunction(const std::string& _in)
{
	for (size_t i = 0; i < functions.size(); ++i)
	{
		if (_in == functions.at(i).name)
			return functions.at(i);
	}
	exit(EXIT_FAILURE);
}
