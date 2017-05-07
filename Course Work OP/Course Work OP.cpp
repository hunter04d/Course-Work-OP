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
		_init_guess.push_back(0);
	}
	std::string initer;
	for (int i = 0; i < _size; ++i)
	{
		initer += "x" + std::to_string(i+1) + '+';
	}
	initer.pop_back();
	size_t pos = 0;
	for (int i = 0; i < _size; ++i)
	{
		std::string init_copy = initer;
		init_copy.insert(pos, std::to_string(_size));
		pos = initer.find('+', pos) + 1;
		if(pos == std::string::npos)
		{
			pos = 0;
		}
		_funcs.push_back(init_copy);
	}
}

const int test_size = 10;
time_point<high_resolution_clock>  begun = high_resolution_clock::now();
int main()
{


	std::ofstream file("result.txt");
	std::vector<std::string> functions;
	std::vector<double> init_guess;
	std::vector<double> res;
	for (int i = 2; i <= 100; ++i)
	{
		Init(functions, init_guess, i);
		for (auto& x : functions)
		{
			preAnalize(x);
			x = shuntingYard(x,i);
		}
		res = Iterative::getResult(functions, init_guess);
		auto ended = high_resolution_clock::now();
		std::string s = std::to_string(duration_cast<duration<double, std::milli>>(ended - begun).count());
		std::replace(s.begin(), s.end(), '.', ',');
		file  <<i << '\t' << s <<'\n';
		std::cout << i << '\n';
		functions.clear();
		init_guess.clear();
	}
	system("pause");
}
