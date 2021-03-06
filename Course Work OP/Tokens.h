#pragma once

#include <vector>
#include <functional>

namespace Tokens
{
	namespace Operators
	{
		struct S_Operator // Operator structure
		{
			S_Operator(char _F_operator, size_t _presedence, bool _associativity, double(*_function)(double, double)) :
				F_operator(_F_operator), presedence(_presedence), associativity(_associativity), function(_function) {}
			enum associativity_tag // left or right associativity
			{
				E_left = 0,
				E_right = 1
			};
			char F_operator; // representing char
			size_t presedence; // operator presedence compared to others
			bool associativity = E_left; // left or right
			double(*function)(double, double); // a function that implements operator's behavior (pointer to it)

		};

		/*storage for defined operators*/
		const std::vector<S_Operator> operators_container // adding new operators can be done here and just here
		{
			{ '+', 1, S_Operator::E_left, [](auto operant1, auto operant2) {return operant1 + operant2; } },
			{ '-', 1, S_Operator::E_left, [](auto operant1, auto operant2) {return operant1 - operant2; } },
			{ '*', 2, S_Operator::E_left, [](auto operant1, auto operant2) {return operant1 * operant2; } },
			{ '/', 2, S_Operator::E_left, [](auto operant1, auto operant2) {return operant1 / operant2; } },
			{ '^', 3, S_Operator::E_right,[](auto operant1, auto operant2) {return pow(operant1 , operant2); } }
		};

		bool isOperator(char _in); // prototype of a function to check is the _in char is a defined operator
		const S_Operator& getOperator(char _in); // prototype of a function to get the operator struct based on the input char
	}

	namespace Functions
	{
		struct S_UnaryFunction // function structure
		{
			std::string name; // representing name
			double(*function)(double); // a function that implements it's behavior (pointer to it)
		};

		/*storage for defined functions*/
		const std::vector<S_UnaryFunction> functions_container // define new functions here
		{
			{"unary_minus",[](auto argument) { return -argument; }},
			{"sqrt", [](auto argument) { return sqrt(argument); }},
			{"cbrt", [](auto argument) { return sqrt(argument); } },
			{"exp", [](auto argument) { return exp(argument); }},
			{"sin", [](auto argument) { return sin(argument); }},
			{"cos", [](auto argument) { return cos(argument); }},
			{"ln", [](auto argument) { return log(argument); }},
			{"log10",[](auto argument) {return log10(argument); }},
			{"abs", [](auto argument) {return abs(argument); }}

		};

		bool isFunction(const std::string& _in); // prototype of a function to check is the _in string is a defined function token
		const S_UnaryFunction& getFunction(const std::string& _in); // prototype of a function to get the function struct based on the input string
	}
}
