#include "Maths.h"
#include<sstream>

using Maths::T_matrix;

/**
 * @brief Maths::allVariablesArePresent - function to check if all variable tokens are present in _funcs
 * @param _funcs - functions to check in postfix notation
 * @return true if all variables are present (the same number as the numbe of functions), else false
 */
bool Maths::allVariablesArePresent(std::vector<std::string> _funcs)
{
    std::string token;
    std::istringstream stream;
    std::vector<bool> has_var(_funcs.size(),false);
    for(const auto& x: _funcs)
    {
        stream.str(x);
        while (stream >> token)
        {
            if (token[0] == 'x')
            {
                has_var.at(std::stoi(token.substr(1))-1) = true;
            }
        }
        stream.clear();
    }
    for(const auto &x: has_var)
    {
        if(x == false)
        {
            return false;
        }
    }
    return true;
}
/**
 * @brief Maths::Calculus::derivative - function to get the derivative of the function at point _arg_vals by variable _by_arg+1
 * @param _func - function in postfix notation
 * @param _arg_vals - point where to calculate the derivative
 * @param _by_arg - agrument by which to get the derivative
 * @return value of the derivative
 */
double Maths::Calculus::derivative(const std::string&_func, std::vector<double> _arg_vals, size_t _by_arg)
{
	auto variable = _arg_vals[_by_arg];
	_arg_vals[_by_arg] = variable + delta_x;
	double func_at_plus_dx = calculateFunc(_func, _arg_vals);
	_arg_vals[_by_arg] = variable - delta_x;
	double func_at_minus_dx = calculateFunc(_func, _arg_vals);
	return (func_at_plus_dx - func_at_minus_dx) / (2 * delta_x);
}

/**
 * @brief Maths::Calculus::jacobian - get Jacobi matrix of functions _funcs at point _point
 * @param _funcs - functions
 * @param _point - point in which jacobian is calculated
 * @return Jacobi matrix
 */
T_matrix Maths::Calculus::jacobian(const std::vector<std::string> _funcs, std::vector<double> _point)
{
	T_matrix out(_funcs.size(), std::vector<double>(_funcs.size()));
	for(size_t i = 0 ; i < out.size(); ++i)
	{
		for (size_t j = 0; j < out.size(); ++j)
		{
			out[i][j] = derivative(_funcs[i], _point, j);
		}
	}
	return out;
}

double Maths::Linear::determinant(const T_matrix& _matrix)
{
	if (_matrix.size() == 1)
	{
		return _matrix.at(0).at(0);
	}
	if (_matrix.size() == 2)
	{
		return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
	}
	double sum = 0;
	auto sub_matrix = _matrix;
	sub_matrix.erase(sub_matrix.cbegin());

	for (size_t i = 0 ; i < _matrix.size();++i)
	{
		auto sub_matrix_copy = sub_matrix;
		for(auto& vector : sub_matrix_copy)
		{
			vector.erase(vector.cbegin() + i);
		}
		sum += _matrix[0][i] * Maths::powNegative1(2 + i) * determinant(sub_matrix_copy);
	}
	return sum;
}

double Maths::Linear::algebraicExtention(const T_matrix& _matrix, size_t _row, size_t _col)
{
	auto sub_matrix = _matrix;
	sub_matrix.erase(sub_matrix.cbegin() + _row);
	for (auto& row: sub_matrix)
	{
		row.erase(row.cbegin() + _col);
	}
	return powNegative1(2 + _row + _col)* determinant(sub_matrix);
}

T_matrix Maths::Linear::reverseMatrix(const T_matrix& _matrix)
{
	double det = determinant(_matrix);
	if (det == 0)
	{
        throw std::exception("Bad Initial Guess. Please Change it");
	}
	T_matrix out(_matrix.size(), std::vector<double>(_matrix.size()));
	for (size_t i = 0; i < _matrix.size(); ++i)
	{
		for(size_t j = 0 ; j < _matrix.size();++j)
		{
			out[j][i] = (1/det)*algebraicExtention(_matrix, i, j);
		}
	}
	return out;
}
/**
 * @brief Maths::Linear::multiplyMatrixByVector - function multiply a matrix by a vector
 * @param _matrix - matrix
 * @param _vector - vector which is matrix is multiplied by
 * @return vector, product of _matrix and _vector
 */
std::vector<double> Maths::Linear::multiplyMatrixByVector(const T_matrix& _matrix, const std::vector<double> _vector)
{
	size_t r = _vector.size();
	std::vector<double> out(r);
	for (size_t i = 0; i < r; ++i)
	{
		double sum = 0;
		for(size_t j = 0; j < r; ++j)
		{
			sum += _matrix[i][j] * _vector[j];
		}
		out[i] = sum;
	}
	return out;
}
/**
 * @brief Maths::calcFuncVector - function that calculates value of functions _func at point arg_vals
 * @param _func - functions in postfix notation
 * @param arg_vals - Point to calculate in
 * @return values of functions at point arg_vals
 */
std::vector<double> Maths::calcFuncVector(const std::vector<std::string>& _func, std::vector<double> arg_vals)
{
	std::vector<double> out;
	for(const auto& func:_func)
	{
		out.push_back(calculateFunc(func, arg_vals));
	}
	return out;
}
