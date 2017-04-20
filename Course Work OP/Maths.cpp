#include "Maths.h"

using Maths::T_matrix;
double Maths::Calculus::derivative(const std::string&_func, std::vector<double> _arg_vals, size_t _by_arg)
{
	auto variable = _arg_vals[_by_arg];
	_arg_vals[_by_arg] = variable + delta_x;
	double func_at_plus_dx = calculateFunc(_func, _arg_vals);
	_arg_vals[_by_arg] = variable - delta_x;
	double func_at_minus_dx = calculateFunc(_func, _arg_vals);
	return (func_at_plus_dx - func_at_minus_dx) / (2 * delta_x);
}

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
		throw std::exception("bad Matrix");
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

double Maths::Linear::hNorm(const T_matrix& _matrix, size_t _row)
{
	double sum = 0;
	for (const auto& x : _matrix[_row])
	{
		sum += abs(x);
	}
	return sum;
}

double Maths::Linear::vNorm(const T_matrix & _matrix, size_t _col)
{
	double sum = 0;
	for(size_t i = 0; i < _matrix.size(); ++i)
	{

		sum += abs(_matrix[i][_col]);
	}
	return sum;
}

std::vector<double> Maths::calcFuncVector(const std::vector<std::string>& _func, std::vector<double> arg_vals)
{
	std::vector<double> out;
	for(const auto& func:_func)
	{
		out.push_back(calculateFunc(func, arg_vals));
	}
	return out;
}
