#pragma once
#include <vector>

double static pressision = 0.0001;

namespace Iterative
{
	std::vector<double> getResult(const std::vector<std::string>& _funcs, const std::vector<double>& _init_guess);
}
namespace GaussZeidel
{
    std::vector<double> getResult(const std::vector<std::string>& _funcs, const std::vector<double>& _init_guess);
}
