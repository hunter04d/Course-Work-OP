#pragma once
#include <vector>
#include <Maths.h>

double static const pressision = 1e-4; // pressision to which to calculate

/**
 * @brief The S_Result struct contains the results
 */
struct S_Result
{
	std::vector<double> x_vector; // the actual result
	Maths::T_matrix iterations; // all the iterations
	size_t number_of_iterations; // number of iterations
	double time; // time takken
};

// Fixed point iteration method
namespace FixedPointIteration
{
	S_Result getResult(const std::vector<std::string>& _funcs, const std::vector<double>& _init_guess);// prototype of a function to get the result using fixed point iteration method
}

// Gauss Seidel method
namespace GaussSeidel
{
	S_Result getResult(const std::vector<std::string>& _funcs, const std::vector<double>& _init_guess);// prototype of a function to get the result using Gauss Seidel method
}
