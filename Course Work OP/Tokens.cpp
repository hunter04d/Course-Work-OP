
#include "Tokens.h"


/**
 * @brief isOperator - function to check is the _in char is a defined operator
 * @param _in - input char
 * @return  true if it is indeed an operator, else false
 */
bool Tokens::Operators::isOperator(char _in)
{
	for (size_t i = 0; i < operators_container.size(); ++i)
	{
		if (_in == operators_container.at(i).F_operator)
			return true;
	}
	return false;
}

/**
 * @brief getOperator - function to get the operator struct based on the input char
 * @param _in - input char
 * @return a reference to a corresponding operator in the operator container
 */
const Tokens::Operators::S_Operator& Tokens::Operators::getOperator(char _in)
{
	for (size_t i = 0; i < operators_container.size(); ++i)
	{
		if (_in == operators_container.at(i).F_operator)
			return operators_container.at(i);
	}
	exit(EXIT_FAILURE);
}

/**
 * @brief isFunction - function to check is the _in string is a defined function token
 * @param _in - input string to check
 * @return true if it is indeed an function, else false
 */
bool Tokens::Functions::isFunction(const std::string& _in)
{
	for (size_t i = 0; i <functions_container.size(); ++i)
	{
		if (_in == functions_container.at(i).name)
			return true;
	}
	return false;
}

/**
 * @brief getFunction - function to get the function struct based on the input string
 * @param _in - input string
 * @return a reference to a corresponding function in the function storage
 */
const Tokens::Functions::S_UnaryFunction& Tokens::Functions::getFunction(const std::string& _in)
{
	for (size_t i = 0; i < functions_container.size(); ++i)
	{
		if (_in == functions_container.at(i).name)
			return functions_container.at(i);
	}
	exit(EXIT_FAILURE);
}
