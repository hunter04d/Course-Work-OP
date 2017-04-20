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
	Maths::T_matrix a(25, std::vector<double>(25, 5));
	std::cout << Maths::Linear::determinant(a) << '\n';
	system("pause");
}
