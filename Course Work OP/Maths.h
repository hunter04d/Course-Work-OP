#pragma once
#include <string>
#include <vector>
#include "ShuntingYard.h"

namespace Maths
{
	using T_matrix = std::vector<std::vector<double>>;
	inline int powNegative1(int _pow)
	{
		return _pow % 2 ? -1 : 1;
	}
	std::vector<double> calcFuncVector(const std::vector<std::string>&_func, std::vector<double> arg_vals);
	namespace Calculus 
	{
		const double delta_x(sqrt(1e-15)); // dx for the derivatives
		double derivative(const std::string&_func, std::vector<double> arg_vals, size_t _by_arg);
		T_matrix jacobian(const std::vector<std::string> _funcs, std::vector<double> _point);
	}
	namespace Linear
	{
		double determinant(const T_matrix& _matrix);
		double algebraicExtention(const T_matrix& _matrix, size_t _row, size_t _col);
		T_matrix reverseMatrix(const T_matrix& _matrix);
		std::vector<double> multiplyMatrixByVector(const T_matrix& _matrix, const std::vector<double> _vector);
		double hNorm(const T_matrix& _matrix, size_t _row);
		double vNorm(const T_matrix& _matrix, size_t _col);
	}
}
