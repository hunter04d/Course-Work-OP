#include "Iterative.h"
#include "Maths.h"
#include <QDebug>
#include <math.h>
#include <algorithm>
#include <chrono>

/**
 * @brief Iterative::getResult - function to solve the system using the fixed point iteration method
 * @param _funcs - system of functions, each function comes in postfix notation
 * @param _init_guess - point, intial guess for the system
 * @return S_Result struct, containing the result, each iteration, number of iterations, time
 */
Iterative::S_Result Iterative::FixedPointIteration::getResult(const std::vector<std::string>& _funcs, const std::vector<double>& _init_guess)
{
	Iterative::S_Result result {_init_guess,Maths::T_matrix(),0,0};
	std::vector<double> delta_iteration(_init_guess.size(),0);
	double prev_delta, curr_delta;
	auto begun_time = std::chrono::high_resolution_clock::now();
	auto W = Maths::Linear::reverseMatrixGauss(Maths::Calculus::jacobiMatrix(_funcs, _init_guess));
	do 
	{
		delta_iteration = Maths::Linear::multiplyMatrixByVector(W, Maths::calcFuncVector(_funcs, result.x_vector)); // change of variables on each iterations
		for (size_t i = 0 ; i < result.x_vector.size(); ++i)
		{
			result.x_vector[i] -= delta_iteration[i];
			if(isinf(result.x_vector[i])|| isnan(result.x_vector[i]))
               { throw (std::exception("System is not solvable with this initial guess")); }
		}
		++result.number_of_iterations;
        curr_delta = abs(*std::max_element(delta_iteration.begin(), delta_iteration.end(), [](auto a, auto b) {return abs(a) < abs(b); }));
		if(result.number_of_iterations>10)
        {
            if(curr_delta >= prev_delta)
                throw (std::exception("System is not solvable with this initial guess"));
        }
        prev_delta = curr_delta;
		result.iterations.push_back(result.x_vector);
	} while (curr_delta >= pressision);
	delta_iteration = Maths::Linear::multiplyMatrixByVector(W, Maths::calcFuncVector(_funcs, result.x_vector));
    curr_delta = abs(*std::max_element(delta_iteration.begin(), delta_iteration.end(), [](auto a, auto b) {return abs(a) < abs(b); }));
	if(curr_delta <= pressision)
    {
		 auto ended_time = std::chrono::high_resolution_clock::now();
		 result.time = round(std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(ended_time - begun_time).count()*1000.0)/1000.0;
		 return result;
    }
    throw (std::exception("System is not solvable with this initial guess"));
}

/**
 * @brief GaussSeidel::getResult - function to solve the system using the Iterative method
 * @param _funcs - system of functions, each function comes in postfix notation
 * @param _init_guess - point, intial guess for the system
 * @return S_Result struct, containing the result, each iteration, number of iterations, time
 */
Iterative::S_Result Iterative::GaussSeidel::getResult(const std::vector<std::string> &_funcs, const std::vector<double> &_init_guess)
{
	Iterative::S_Result result {_init_guess,Maths::T_matrix(),0,0};
	std::vector<double> delta_iteration(_init_guess.size(),0);
	double prev_delta, curr_delta;
	auto begun_time = std::chrono::high_resolution_clock::now();
	auto W = Maths::Linear::reverseMatrixGauss(Maths::Calculus::jacobiMatrix(_funcs, _init_guess));
	do
	{
		for (size_t i = 0 ; i < result.x_vector.size(); ++i)
		{
			double curr_variable_delta = Maths::Linear::multiplyVectorsScalar(W[i], Maths::calcFuncVector(_funcs, result.x_vector)); //change of the current variable
			result.x_vector[i] -= curr_variable_delta;
			if(isinf(result.x_vector[i])|| isnan(result.x_vector[i]))
			   { throw (std::exception("System is not solvable with this initial guess")); }
			delta_iteration[i] = curr_variable_delta;
		}
		++result.number_of_iterations;
		curr_delta = abs(*std::max_element(delta_iteration.begin(), delta_iteration.end(), [](auto a, auto b) {return abs(a) < abs(b); }));
		if(result.number_of_iterations>10)
		{
			if(curr_delta >= prev_delta)
				throw (std::exception("System is not solvable with this initial guess"));
		}
		prev_delta = curr_delta;
		result.iterations.push_back(result.x_vector);
	} while (curr_delta >= Iterative::pressision);
	delta_iteration = Maths::Linear::multiplyMatrixByVector(W, Maths::calcFuncVector(_funcs, result.x_vector));
	curr_delta = abs(*std::max_element(delta_iteration.begin(), delta_iteration.end(), [](auto a, auto b) {return abs(a) < abs(b); }));
	if(curr_delta <= Iterative::pressision)
	{
		 auto ended_time = std::chrono::high_resolution_clock::now();
		 result.time = round(std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(ended_time - begun_time).count()*1000.0)/1000.0;
		 return result;
	}
	throw (std::exception("System is not solvable with this initial guess"));
}
