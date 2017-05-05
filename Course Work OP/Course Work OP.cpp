// Course Work OP.cpp : Defines the entry point for the console application.
//
#include "ShuntingYard.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <algorithm>
#include "Maths.h"
#include "Iterative.h"

int main()
{
	std::vector<std::string> func = { shuntingYard("2x1^2-x1x2-5x1+1",2),shuntingYard("sqrt(x1)+x2",2) };
	std::vector<double> a{ 0.7,-2 };
	std::cout << "Res: " << Iterative::getResult(func, a).at(0);
	system("pause");
}
