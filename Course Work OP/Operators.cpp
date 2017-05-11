
#include "Operators.h"


/**
 * @brief isOperator - function to check is the _in char is a defined operator
 * @param _in - input char
 * @return  true if it is indeed an operator, else false
 */
bool isOperator(char _in)
{
	for (size_t i = 0; i < operators.size(); ++i)
	{
		if (_in == operators.at(i).F_operator)
			return true;
	}
	return false;
}

/**
 * @brief getOperator - function to get the operator struct based on the input char
 * @param _in - input char
 * @return a reference to a corresponding operator in the operator container
 */
const T_Operator& getOperator(char _in)
{
	for (size_t i = 0; i < operators.size(); ++i)
	{
		if (_in == operators.at(i).F_operator)
			return operators.at(i);
	}
	exit(EXIT_FAILURE);
}

/**
 * @brief isFunction - function to check is the _in string is a defined function token
 * @param _in - input string to check
 * @return true if it is indeed an function, else false
 */
bool isFunction(const std::string& _in)
{
	for (size_t i = 0; i < functions.size(); ++i)
	{
		if (_in == functions.at(i).name)
			return true;
	}
	return false;
}

/**
 * @brief getFunction - function to get the function struct based on the input string
 * @param _in - input string
 * @return a reference to a corresponding function in the function storage
 */
const T_UnaryFunction& getFunction(const std::string& _in)
{
	for (size_t i = 0; i < functions.size(); ++i)
	{
		if (_in == functions.at(i).name)
			return functions.at(i);
	}
	exit(EXIT_FAILURE);
}
