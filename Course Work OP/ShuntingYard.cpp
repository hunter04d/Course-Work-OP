#include "ShuntingYard.h"
#include <sstream>
#include "Operators.h"
#include <cctype>
#include <string>
#include "Stack.h"


void preAnalize(std::string& _in) // insert * and change x, y, z to x1, x2, x3
{
	for(size_t i = 0u; i < _in.size();++i)
	{
		char& curr_char = _in[i];
		if (curr_char == '(' && i != 0)
		{
			if (isdigit(_in[i - 1]))
			{
				_in.insert(_in.begin() + i, '*');
			}
			
		}
		if (curr_char == 'x' && i != 0)
		{
			if (isdigit(_in[i - 1]))
			{
				_in.insert(_in.begin() + i, '*');
			}
		}/*if (isalpha(curr_char))
		{
			curr_char = tolower(curr_char);
		}*/

		/*if (curr_char == 'x' || isdigit(_in[i+1]) == false)
		{
			
		}*/
	}
}

std::string shuntingYard(const std::string& _in) //to RPN
{
	size_t pos(0);
	Stack<std::string> stack;
	bool last_was_func = false;
	std::string out;
	while (pos < _in.size())
	{
		char curr_char = _in[pos];
		//Variable
		auto var_pair = getVariableToken(_in, pos);
		if (var_pair != -1)
		{
			if (_in[pos]== '-')
			{
				out += _in.substr(pos+1, var_pair-1) + ' ';
				out += "unary_minus ";
			}
			else { out += _in.substr(pos, var_pair) + ' '; }
			pos += var_pair;
			last_was_func = false;
			continue;
		}
		// Number
		int num_len = getNumberToken(_in, pos);
		if (num_len != -1)
		{
			out += (_in.substr(pos, num_len) + ' ');
			pos += num_len;
			last_was_func = false;
			continue;
		}
		// Braces
		if (curr_char == '(')
		{
			stack.push("(");
			++pos;
			last_was_func = false;
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
			continue;
		}
		// Operators
		if (isOperator(curr_char))
		{
			while (!stack.empty() && operatorCompare(curr_char, stack.top()))
			{
				out += stack.pop() + ' ';
			}
			stack.push(std::string(1, curr_char));
			++pos;
			last_was_func = false;
			continue;
		}
		// Functions
		int func_len = getFuncToken(_in, pos);
		if (func_len != -1)
		{
			last_was_func = true;
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

int getVariableToken(const std::string& _in, size_t _pos)
{
	if (_in[_pos] == 'x' || (_pos == 0 && _in[_pos] == '-') || (_in[_pos] == '-' && (_in[_pos - 1] == '(' || isOperator(_in[_pos - 1]))))
	{
		bool has_minus = false;
		int count = 1;
		if (_in[_pos+1]=='x')
		{
			has_minus = true;
			++count;
		}
		for (int i = _pos + count; i < _in.size(); ++i)
		{
			if (isdigit(_in[i]))
			{
				++count;
			}
			else break;
		}
		if (count == 1+int(has_minus) || std::stoi(_in.substr(_pos+1+has_minus,count-1-has_minus)) > 2 /*NUM_OF_FUNCTIONS*/ )
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
		for (int i = _pos + 1; i < _in.size(); ++i)
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
		return count;
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
		for (int i = _pos + 1; i < _in.size(); ++i)
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
				throw std::exception("Function at the end of the string");
			}
		}
		if (isFunction(_in.substr(_pos, count)))
			return count;
		std::string exception_happened = "Unknown function token at position " + std::to_string(_pos + 1) + ' ' + _in.substr(_pos, count);
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
