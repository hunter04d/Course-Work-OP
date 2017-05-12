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

	inline int powNegative1(int _pow) // fast inline power of -1 function
	{
		return _pow % 2 ? -1 : 1;
	}

	bool allVariablesArePresent(const std::vector<std::string>& _funcs); // prototype of a function to check if all variable tokens are present in _funcs

	std::vector<double> calcFuncVector(const std::vector<std::string>&_func,const std::vector<double>& arg_vals); // prototype of a function that calculates value of functions _func at point arg_vals
	// Calculus problems
	namespace Calculus 
	{
		const double delta_x(sqrt(1e-15)); // dx for the derivatives (sqrt of the smalest number that double can represent)

		double derivative(const std::string&_func, std::vector<double> arg_vals, size_t _by_arg); // prototype of a function to get the derivative of the function at point _arg_vals by variable _by_arg+1

		T_matrix jacobian(const std::vector<std::string>& _funcs, const std::vector<double>& _point); // prototype of a function to get the Jacobi matrix of functions _funcs at point _point
	}
	// linear algebra problems
	namespace Linear
	{
		T_matrix reverseMatrixGauss(const T_matrix& _matrix); // prototype of a function that inverts the input matrix using Gauss method

		double multiplyVectorsScalar(const std::vector<double>& _vector1, const std::vector<double>& _vector2); // prototype of a function that multiplies two vectors scalarlly

		std::vector<double> multiplyMatrixByVector(const T_matrix& _matrix, const std::vector<double>& _vector); // prototype of a function to multiply a matrix by a vector
	}
}
