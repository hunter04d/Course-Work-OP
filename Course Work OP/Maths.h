#pragma once
#include <string>
#include <vector>
#include "ShuntingYard.h"

/**
 * Functions related to maths
 */
namespace Maths
{
	using T_matrix = std::vector<std::vector<double>>; // matrix type alias

	inline int powNegative1(int _pow) // fast inline power of -1
	{
		return _pow % 2 ? -1 : 1;
	}

    bool allVariablesArePresent(std::vector<std::string> _funcs);

	std::vector<double> calcFuncVector(const std::vector<std::string>&_func, std::vector<double> arg_vals);
	//Calculus problems
	namespace Calculus 
	{
		const double delta_x(sqrt(1e-15)); // dx for the derivatives (sqrt of the smalest number that double can represent)

		double derivative(const std::string&_func, std::vector<double> arg_vals, size_t _by_arg);

		T_matrix jacobian(const std::vector<std::string> _funcs, std::vector<double> _point);
	}
	// linear algebra problems
	namespace Linear
	{
		T_matrix reverseMatrixGauss(const T_matrix& _matrix);

		std::vector<double> multiplyMatrixByVector(const T_matrix& _matrix, const std::vector<double> _vector);
	}
}
