#include "ShuntingYard.h"
#include <sstream>
#include "mainwindow.h"
#include "Operators.h"
#include <cctype>
#include <string>
#include <algorithm>
#include "Stack.h"

void preAnalize(std::string& _in) // insert * when makes sence
{
    _in.erase(std::remove_if(_in.begin(), _in.end(), std::isspace), _in.end());
    for(size_t i = 0u; i < _in.size();++i)
    {
        char& curr_char = _in[i];
        if (curr_char == '(' && i != 0)
        {
            if (isdigit(_in[i - 1]))
            {
                int reverse_i = 1;
                while (isdigit(_in[i - reverse_i]) || _in[i - reverse_i] == '.')
                {
                    if (i - reverse_i == 0)
                    {
                        _in.insert(_in.begin() + i, '*');
                        break;
                    }
                    ++reverse_i;
                }
                if (_in[i-reverse_i] == 'x'|| !isalpha(_in[i - reverse_i]))
                {
                    _in.insert(_in.begin() + i, '*');
                }
            }
        }
        if (isalpha(curr_char) && i != 0)
        {
            if (isdigit(_in[i - 1]))
            {
                _in.insert(_in.begin() + i, '*');
            }
        }
    }
}

std::string shuntingYard(const std::string& _in, size_t _function_number) //to RPN
{
	size_t pos(0);
	Stack<std::string> stack;
	bool last_was_func = false;
    bool last_was_operator = false;
	std::string out;
   // std::vector<bool> has_variable(_function_number, false);
	while (pos < _in.size())
	{
		char curr_char = _in[pos];
		//Variable
        auto var_pair = getVariableToken(_in, pos, _function_number);
		if (var_pair != -1)
		{
			if (_in[pos]== '-')
			{
				out += _in.substr(pos+1, var_pair-1) + ' ';
               // has_variable.at(std::stoi(_in.substr(pos+2,var_pair-2))-1) = true;
				out += "unary_minus ";
			}
            else
            {
                out += _in.substr(pos, var_pair) + ' ';
               // has_variable.at(std::stoi(_in.substr(pos+1,var_pair-1))-1) = true;
            }
			pos += var_pair;
			last_was_func = false;
            last_was_operator = false;
			continue;
		}
		// Number
		int num_len = getNumberToken(_in, pos);
		if (num_len != -1)
		{
			out += (_in.substr(pos, num_len) + ' ');
			pos += num_len;
			last_was_func = false;
            last_was_operator = false;
			continue;
		}
		// Braces
		if (curr_char == '(')
		{
			stack.push("(");
			++pos;
			last_was_func = false;
            last_was_operator = false;
			continue;
		}
		if (curr_char == ')')
		{
			if (last_was_func)
			{
				throw std::exception("Empty function argument list");
			}
			bool found_left_parenthesis = false;
			while (!(stack.empty() || (found_left_parenthesis = stack.top() == "(")))
			{
				out += stack.pop() + ' ';
			}
			if (found_left_parenthesis == false) // if the stack is emptied and the left parenthesis was not found
			{
				throw std::exception("Mismatched Parenthesis");
			}
			stack.pop();
			if (!stack.empty() && isFunction(stack.top()))
			{
				out += stack.pop() + ' ';
			}
			++pos;
			last_was_func = false;
            last_was_operator = false;
			continue;
		}
		// Operators
		if (isOperator(curr_char))
        {
            if(last_was_operator)
            {
                std::string exception_happened( "No second operant after operator \"");
                exception_happened.push_back(curr_char);
                exception_happened +="\" at position " + std::to_string(pos+1);
                throw(std::exception(exception_happened.c_str()));
            }
			while (!stack.empty() && operatorCompare(curr_char, stack.top()))
			{
				out += stack.pop() + ' ';
			}
			stack.push(std::string(1, curr_char));
			++pos;
			last_was_func = false;
            last_was_operator = true;
			continue;
		}
		// Functions
		int func_len = getFuncToken(_in, pos);
		if (func_len != -1)
		{
			last_was_func = true;
            last_was_operator = false;
			stack.push(_in.substr(pos, func_len));
			stack.push("(");
			pos += func_len + 1;
			continue;
		}
		std::string exception_happened = "Unknown token at position " + std::to_string(pos + 1);
		throw std::exception(exception_happened.c_str());
	}
	while (!stack.empty())
	{
		if (stack.top() == "(")
			throw std::exception("Error: Mismatched parenthesis");
		out += stack.pop() + ' ';
	}
/*
    for(size_t i = 0; i < _function_number; ++i)
    {
        if(has_variable.at(i) == false)
        {
            throw std::exception("Not all variables are present");
        }
    }
*/
    if(last_was_operator)
    {
        throw(std::exception("operator without a second operant at the end of the function"));
    }
	return out;
}


double calculateFunc(const std::string& _RPN, const std::vector<double>& _arg_vals)
{
	std::istringstream stream(_RPN);
	Stack<double> numbers;
	std::string token;
	double number_token;
	while (stream >> token)
	{
		if (token[0] == 'x')
		{
            numbers.push(_arg_vals[std::stoi(token.substr(1))-1]);
		}
		else if (std::istringstream(token) >> number_token)
		{
			numbers.push(number_token);
		}
		else
		{
			if (isOperator(token[0]))
			{

				double operant2(numbers.pop()), operant1(numbers.pop());
				const T_Operator& v_operator = getOperator(token[0]);
				numbers.push(v_operator.function(operant1, operant2));
			}
			else // isFunction(token)
			{
				double argument(numbers.pop());
				const T_UnaryFunction& v_function = getFunction(token);
				numbers.push(v_function.functions(argument));
			}
		}
	}
	return numbers.top();
}

int getVariableToken(const std::string& _in, size_t _pos,size_t _function_number)
{
    if (_in[_pos] == 'x' || (_pos == 0 && _in[_pos] == '-') || (_in[_pos] == '-' && (_in[_pos - 1] == '(' || isOperator(_in[_pos - 1]))))
    {
        bool has_minus = false;
        int count = 1;
        if (_pos < _in.size() - 1)
        {
            if (_in[_pos] == '-' && _in[_pos + 1] == 'x')
            {
                has_minus = true;
                ++count;
            }
        }
        else { throw std::exception("trailing minus at the end of the function"); }
        for (size_t i = _pos + count; i < _in.size(); ++i)
        {
            if (isdigit(_in[i]))
            {
                ++count;
            }
            else break;
        }
        if (count == 1 + int(has_minus))
        {
            throw std::exception("x must have a number after it");
        }
        if (std::stoi(_in.substr(_pos + 1 + has_minus, count - 1 - has_minus)) > _function_number /*NUM_OF_FUNCTIONS*/)
        {
            throw std::exception("A variable has higher index than total number of functions");
        }
        return count;
    }
    return -1;
}

int getNumberToken(const std::string& _in, size_t _pos /*= 0*/)
{
	// number is defined as any number of digits, one dot is possible and unary minus assuming it is in the beginning of the str or has '(' before it 
	if (isdigit(_in[_pos]) || (_pos == 0 && _in[_pos] == '-') || (_in[_pos] == '-' && (_in[_pos - 1] == '(' || isOperator(_in[_pos - 1]))))
	{
		size_t count = 1;
		bool dottag = false;
        for (size_t i = _pos + 1; i < _in.size(); ++i)
		{
			if (isdigit(_in[i]))
			{
				++count;
			}
			else if (_in[i] == '.' && dottag == false)
			{
				if (dottag == false)
				{
					dottag = true; ++count;
				}
				//more then one dot in a num
				else 
				{
					std::string exception_happened = "Unrecognized dot at position " + std::to_string(_pos + count + 1);
					throw std::exception(exception_happened.c_str());
				}
			}
			else { break; }
		}
        return int(count);
	}
	return -1;
}

int getFuncToken(const std::string& _in, size_t _pos /*= 0*/)
{
	//function is defined as letters and numbers until '(' starting with !!!a letter!!!  
	//example: log10, ln, sin, cos, ect...
	if (isalpha(_in[_pos]))
	{
		size_t count = 1;
        for (size_t i = _pos + 1; i < _in.size(); ++i)
		{
			if (isalnum(_in[i]))
			{
				++count;
			}
			if (_in[i] == '(')
			{
				break;
			}
			if (i ==_in.size()-1)
			{
                throw std::exception("Unknown string Entered");
			}
		}
		if (isFunction(_in.substr(_pos, count)))
            return int(count);
        std::string exception_happened = "Unknown token at position " + std::to_string(_pos + 1) + ' ' + _in.substr(_pos, count);
		throw std::exception(exception_happened.c_str());
	}
	return -1;
}


// compare operator precedence 
bool operatorCompare(char _in_char, const std::string& _tops_of_stack)
{
	const T_Operator& curr_operator = getOperator(_in_char);
	size_t top_of_stack_presedence;
	if (_tops_of_stack == "(")
	{
		top_of_stack_presedence = 0;
	}
	else
	{
		top_of_stack_presedence = getOperator(_tops_of_stack.at(0)).presedence;
	}
	if ((curr_operator.associativity == T_Operator::E_left &&
		curr_operator.presedence <= top_of_stack_presedence) ||
		(curr_operator.associativity == T_Operator::E_right &&
			curr_operator.presedence < top_of_stack_presedence))
	{
		return true;
	}
	return false;
}
