﻿#include "Iterative.h"
#include "Maths.h"
#include <QDebug>
#include <math.h>
#include <algorithm>

extern size_t number_of_iterations;
extern Maths::T_matrix iterations;
std::vector<double> Iterative::getResult(const std::vector<std::string>& _funcs, const std::vector<double>& _init_guess)
{
	auto W = Maths::Linear::reverseMatrix(Maths::Calculus::jacobian(_funcs, _init_guess));
    std::vector<double> delta_iteration(_init_guess.size(),0);
    std::vector<double> x_vector(_init_guess);
    number_of_iterations = 0;
    double prev_delta, curr_delta;
	do 
	{
        delta_iteration = Maths::Linear::multiplyMatrixByVector(W, Maths::calcFuncVector(_funcs, x_vector));
		for (size_t i = 0 ; i < x_vector.size(); ++i)
		{
            x_vector[i] -= delta_iteration[i];
            if(isinf(x_vector[i])|| isnan(x_vector[i]))
               { throw (std::exception("System is not solvable with this initial guess")); }
		}
        ++number_of_iterations;
        curr_delta = abs(*std::max_element(delta_iteration.begin(), delta_iteration.end(), [](auto a, auto b) {return abs(a) < abs(b); }));
        if(number_of_iterations>10)
        {
            if(curr_delta >= prev_delta)
                throw (std::exception("System is not solvable with this initial guess"));
        }
        prev_delta = curr_delta;
        iterations.push_back(x_vector);
    } while (curr_delta >= pressision);
    delta_iteration = Maths::Linear::multiplyMatrixByVector(W, Maths::calcFuncVector(_funcs, x_vector));
    curr_delta = abs(*std::max_element(delta_iteration.begin(), delta_iteration.end(), [](auto a, auto b) {return abs(a) < abs(b); }));
    if(curr_delta <= pressision)
    {
         return x_vector;
    }
    throw (std::exception("System is not solvable with this initial guess"));
}

std::vector<double> GaussZeidel::getResult(const std::vector<std::string> &_funcs, const std::vector<double> &_init_guess)
{
    auto W = Maths::Linear::reverseMatrix(Maths::Calculus::jacobian(_funcs, _init_guess));
    std::vector<double> delta_iteration(_init_guess.size(),0.0);
    std::vector<double> x_vector(_init_guess);
    number_of_iterations = 0;
    double prev_delta, curr_delta;
    do
    {
         for (size_t i = 0 ; i < x_vector.size(); ++i)
         {
            delta_iteration = Maths::Linear::multiplyMatrixByVector(W, Maths::calcFuncVector(_funcs, x_vector));
            x_vector[i] -= delta_iteration[i]; 
            if(isinf(x_vector[i])|| isnan(x_vector[i]))
                { throw (std::exception("System is not solvable with this initial guess")); }
         }
        ++number_of_iterations;
        curr_delta = abs(*std::max_element(delta_iteration.begin(), delta_iteration.end(), [](auto a, auto b) {return abs(a) < abs(b); }));
        if(number_of_iterations>10)
        {
            if(curr_delta >= prev_delta)
                throw (std::exception("System is not solvable with this initial guess"));
        }
        prev_delta = curr_delta;
        iterations.push_back(x_vector);
    } while(curr_delta >= pressision);
     delta_iteration = Maths::Linear::multiplyMatrixByVector(W, Maths::calcFuncVector(_funcs, x_vector));
     curr_delta = abs(*std::max_element(delta_iteration.begin(), delta_iteration.end(), [](auto a, auto b) {return abs(a) < abs(b); }));
     if(curr_delta <= pressision)
     {
          return x_vector;
     }
     throw (std::exception("System is not solvable with this initial guess"));
}
