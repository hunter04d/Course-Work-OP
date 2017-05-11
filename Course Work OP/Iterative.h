#pragma once
#include <vector>
#include <Maths.h>

double static const pressision = 0.0001; // pressision to which to calculate

/**
 * @brief The S_Result struct contains the results
 */
struct S_Result
{
	std::vector<double> x_vector;
	Maths::T_matrix iterations;
	size_t number_of_iterations;
	double time;
};

// Iterative method
namespace Iterative
{
	S_Result getResult(const std::vector<std::string>& _funcs, const std::vector<double>& _init_guess);// prototype of a function to get the result using Iterative method
}

// Gauss Seidel method
namespace GaussSeidel
{
	S_Result getResult(const std::vector<std::string>& _funcs, const std::vector<double>& _init_guess);// prototype of a function to get the result using Gauss Seidel method
}
