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
 * @brief Maths::Calculus::jacobian - function to get the Jacobi matrix of functions _funcs at point _point
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

/**
 * @brief Maths::Linear::reverseMatrixGauss - function to invert the input Matrix using Gauss method
 * @param _matrix - input matrix
 * @return matrix inverse to the input
 */
T_matrix Maths::Linear::reverseMatrixGauss(const T_matrix& _matrix)
{
	int size = _matrix.size();
	auto exetended_matrix = _matrix;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (j == i)
			{
				exetended_matrix[i].push_back(1);
			}
			else { exetended_matrix[i].push_back(0); }
		}
	}
	// forward iterations
	for (int i = 0; i < size; ++i)
	{
		// search max abs(element) in a row number ind
		double max_element = 0;
		int index_of_max = -1;
		for (int j = i; j < size; ++j)
		{
			if (max_element < abs(exetended_matrix[j][i]))
			{
				max_element = abs(exetended_matrix[j][i]);
				index_of_max = j;
			}
		}
		if (max_element == 0)
		{
			throw (std::exception("Bad intial guess. Please change it"));
		}
		// pivot to the largest element to avoid division by zero
		std::swap(exetended_matrix[i], exetended_matrix[index_of_max]);
		for (int j = i + 1; j < size; ++j)
		{
			double coef = exetended_matrix[j][i] / exetended_matrix[i][i];
			for (int k = 0; k < size * 2; ++k)
			{
				exetended_matrix[j][k] -= exetended_matrix[i][k] * coef;
			}
		}
	}
	// reverse iterations
	for (int i = size - 1; i > 0; --i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			double coef = exetended_matrix[j][i] / exetended_matrix[i][i];
			for (int k = 0; k < size * 2; ++k)
			{
				exetended_matrix[j][k] -= exetended_matrix[i][k] * coef;
			}
		}
	}
	// identity transformation
	for (int i = 0; i < size; ++i)
	{
		double diag_elem = exetended_matrix[i][i];
		for (int j = 0; j < size * 2; ++j)
		{
			exetended_matrix[i][j] /= diag_elem;
		}
	}
	T_matrix out;
	for (auto vector : exetended_matrix)
	{
		out.emplace_back(vector.cbegin() + size, vector.cend());
	}
	return out;
}

/**
 * @brief Maths::Linear::multiplyMatrixByVector - function to multiply a matrix by a vector
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
