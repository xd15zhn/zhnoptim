#include <iostream>
#include <fstream>
#include "zhnoptim.hpp"
NAMESPACE_ZHNOPTIM_L

void Algorithm::Set_CostFunction(UserFunc *f) { _costFunc=f; }
double Algorithm::Get_Cost() const { return _MinCost; }
std::vector<double> Algorithm::Get_BestSolution() const { return _BestSolution; }

/***********************
Algorithm initialize
*@ solution: Initial solution vector
*@ solvelen: Length of solution vector
**********************/
Algorithm::Algorithm(const std::vector<double>& solution)
{
    _costFunc = nullptr;
    _fp = nullptr;
    for (int i=0; i<(int)solution.size(); ++i)
        _BestSolution.push_back(solution[i]);
    _IterateCnt = 0; _TermIterate = 1e4;
    _MinCost = ZHNOPTIM_INFINITE; _TermCost = 1;
    TermType = COUNT;
    if (_printfile) {
        _fp = new std::fstream;
        _fp->open("data.csv", std::ios::out);
        ASSERT_ERROR_ALG(_fp->is_open(), "Failed to open data file!");
        _fp->precision(8);
    }
    else
        std::cout.precision(8);
}
Algorithm::~Algorithm()
{
    if (!_fp) return;
    if (!_fp->is_open()) return;
    _fp->close();
    delete _fp; _fp = nullptr;
}

void Algorithm::Set_TerminationConditions(double mincost, int maxiterate, TermCriteria type)
{
    _TermCost = mincost; _TermIterate = maxiterate; TermType = type;
}

#define MACRO_SOLUTION_PRINT(x) \
    if (mode == 0) return; \
    x << _MinCost; \
    if (mode == 1) { x << std::endl; return; } \
    x << "  "; \
    for (int i=0; i<_BestSolution.size(); ++i) \
        x << _BestSolution[i] << ", "; \
    x << std::endl;

void Algorithm::Solution_Print(int mode) const
{
    if (_printfile) {
        MACRO_SOLUTION_PRINT(*_fp);
    }
    else {
        MACRO_SOLUTION_PRINT(std::cout);
    }
}

NAMESPACE_ZHNOPTIM_R
