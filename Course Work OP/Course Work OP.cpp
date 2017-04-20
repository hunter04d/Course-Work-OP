// Course Work OP.cpp : Defines the entry point for the console application.
//
#include "ShuntingYard.h"
#include <string>
#include <iostream>
#include <algorithm>
#include "Maths.h"
#include "Iterative.h"

int main()
{
	std::string a = shuntingYard("x1^2+x2^2-1");
	std::string b = shuntingYard("x1^3-x2");
	std::cout << a << '\n';
	std::cout << b << '\n';
	std::vector<std::string> func = {a ,b };
	std::vector<double> points = { 2,2 };
	if (Iterative::mergeConditionBy_vNorm(func,points))
	{
		auto result = Iterative::getResult(func, points);
		for (auto x : result)
		{
			std::cout << x << ' ';
		}
		std::cout << '\n';
	}
	else
	{
		std::cout << "does not merge\n";
	}

	system("pause");
}
