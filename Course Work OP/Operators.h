#pragma once

#include <vector>
#include <functional>


struct T_Operator
{	
	enum associativity_tag
	{
		E_left = 0,
		E_right = 1
	};
	char F_operator;
	size_t presedence;
	bool associativity = E_left;//left or right
	double(*function)(double, double);

};

const std::vector<T_Operator> operators //adding new operators can be done here and just here
{
	{ '+', 1, T_Operator::E_left, [](auto operant1, auto operant2) {return operant1 + operant2; } },
	{ '-', 1, T_Operator::E_left, [](auto operant1, auto operant2) {return operant1 - operant2; } },
	{ '*', 2, T_Operator::E_left, [](auto operant1, auto operant2) {return operant1 * operant2; } },
	{ '/', 2, T_Operator::E_left, [](auto operant1, auto operant2) {return operant1 / operant2; } },
	{ '^', 3, T_Operator::E_right,[](auto operant1, auto operant2) {return pow(operant1 , operant2); } }

};

bool isOperator(char _in);
const T_Operator& getOperator(char _in);

struct T_UnaryFunction
{
	std::string name;
	std::function<double(double)> functions;
};

const std::vector<T_UnaryFunction> functions //define new functions here
{
	{"unary_minus",[](auto argument) { return -argument; }},
	{"sqrt", [](auto argument) { return sqrt(argument); }},
	{"cbrt", [](auto argument) { return sqrt(argument); } },
	{"exp", [](auto argument) { return exp(argument); }},
	{"sin", [](auto argument) { return sin(argument); }},
	{"cos", [](auto argument) { return cos(argument); }},
	{"log", [](auto argument) { return log(argument); }},
	{"log10",[](auto argument) {return log10(argument); }}

};

bool isFunction(const std::string& _in);
const T_UnaryFunction& getFunction(const std::string& _in);
