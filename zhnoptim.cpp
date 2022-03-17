#include <iostream>
#include "zhnoptim.hpp"
NAMESPACE_ZHNOPTIM_L

Algorithm::~Algorithm() {}
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
    for (int i=0; i<(int)solution.size(); ++i)
        _BestSolution.push_back(solution[i]);
    _IterateCnt = 0; _TermIterate = 1e4;
    _MinCost = ZHNOPTIM_INFINITE; _TermCost = 1;
    TermType = COUNT;
    std::cout.precision(8);
}

void Algorithm::Set_TerminationConditions(double mincost, int maxiterate, TermCriteria type)
{
    _TermCost = mincost; _TermIterate = maxiterate; TermType = type;
}

void Algorithm::Solution_Print() const
{
    std::cout<<_MinCost<<": ";
    for (int i=0; i<_BestSolution.size(); ++i)
        std::cout<<_BestSolution[i]<<", ";
    std::cout<<std::endl;
}

NAMESPACE_ZHNOPTIM_R
