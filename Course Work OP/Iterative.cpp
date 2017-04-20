#include "Iterative.h"
#include "Maths.h"
#include <algorithm>
#include <iostream>

std::vector<double> Iterative::getResult(const std::vector<std::string>& _funcs, const std::vector<double>& _init_guess)
{
	auto W = Maths::Linear::reverseMatrix(Maths::Calculus::jacobian(_funcs, _init_guess));
	std::vector<double> delta_iteration(_init_guess.size(),0);
	std::vector<double> x_vector(_init_guess);
	auto b = 0;
	do 
	{
		for (size_t i = 0 ; i < x_vector.size(); ++i)
		{
			x_vector[i] -= delta_iteration[i];
			std::cout << x_vector[i] << ' ';
		}
		std::cout << '\n';
		delta_iteration = Maths::Linear::multiplyMatrixByVector(W, Maths::calcFuncVector(_funcs, x_vector));
		++b;
	} while (b < 10);
	return x_vector;
}

bool Iterative::mergeConditionBy_vNorm(const std::vector<std::string>& _funcs, const std::vector<double>& _init_guess)
{
	auto jacob_matrix = Maths::Calculus::jacobian(_funcs, _init_guess);
	auto W = Maths::Linear::reverseMatrix(jacob_matrix);
	std::vector<double> a1;
	std::vector<double> ini2(_init_guess);
	for (int i = 0; i < jacob_matrix.size(); ++i)
	{
		ini2[i] = _init_guess[i] - 0.1;
	//	a1.push_back(Maths::Calculus::derivative(_funcs[i], _init_guess, 0));
	}
	for (int i = 0; i < jacob_matrix.size(); ++i)
	{
		//ini2[i] = _init_guess[i] - 0.1;
		a1.push_back(Maths::Calculus::derivative(_funcs[i], ini2, 0));
	}
	std::vector<double> l1;
	std::cout << "d vector: ";
	for (int i = 0; i < jacob_matrix.size(); ++i)
	{
		double sum = 0;
		for (int j = 0 ; j < jacob_matrix.size(); ++j)
		{
			sum += W[i][j] * a1[j];
		}
		std::cout << sum << ' ';
		l1.push_back(sum);
	}
	std::cout << '\n';


	return true;

}
