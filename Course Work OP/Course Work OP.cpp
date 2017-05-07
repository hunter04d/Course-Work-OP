// Course Work OP.cpp : Defines the entry point for the console application.
//
#include "ShuntingYard.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <algorithm>
#include <chrono>
#include "Maths.h"
#include "Iterative.h"

const auto testsize = 10;
using namespace std::chrono;
void Init(std::vector<std::string> &_funcs, std::vector<double>& _init_guess,int _size)
{
	for(int i = 0; i<_size;++i)
	{
		_init_guess.push_back(0.2);
	}
	for (int j = 0; j < _size; ++j)
	{
		std::string initer;
		int intit_pow = _size - j;
		for (int i = 0; i < _size; ++i)
		{
			if(i==j)
			{
				initer += std::to_string(0.1*_size);
			}
			//initer += std::to_string(_size);
			initer +="x" + std::to_string(i + 1) + '^' + std::to_string(intit_pow) + '+';
			--intit_pow;
			if (intit_pow == 0)
			{
				intit_pow = _size;
			}	
		}
		initer.pop_back();
		//initer.push_back('-');
		//initer.push_back('1');
		_funcs.push_back(initer);
	}
}

const int test_size = 10;
time_point<high_resolution_clock>  begun = high_resolution_clock::now();
int main()
{


	std::ofstream file("resultGaussZeidel1000.txt", std::ios_base::app);
	file << '\n';
	std::vector<std::string> functions;
	std::vector<double> init_guess;
	std::vector<double> res;
	for(int i = 2; i <= 17;++i)
	{
		Init(functions, init_guess, i);
		for (auto& x : functions)
		{
			preAnalize(x);
			x = shuntingYard(x,i);
		}
		res = GaussZeidel::getResult(functions, init_guess);
		auto ended = high_resolution_clock::now();
		std::string s = std::to_string(duration_cast<duration<double, std::milli>>(ended - begun).count());
		std::replace(s.begin(), s.end(), '.', ',');
		file <<i << '\t' << s <<'\n';
		functions.clear();
		init_guess.clear();
	}
}
