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
Algorithm::Algorithm(const std::vector<double>& solution) {
    _costFunc = nullptr;
    for (int i=0; i<(int)solution.size(); ++i)
        _BestSolution.push_back(solution[i]);
    _IterateCnt = 0; _TermIterate = 1e4;
    _MinCost = ZHNOPTIM_INFINITE; _TermCost = 1;
    TermType = COUNT;
    std::cout.precision(8);
}
Algorithm::~Algorithm() {}
void Algorithm::Set_TerminationConditions(double mincost, int maxiterate, TermCriteria type) {
    _TermCost = mincost; _TermIterate = maxiterate; TermType = type;
}
void Algorithm::Set_PrintFormat(PRINT_FORMAT format) { _printformat = format; }
void Algorithm::Solution_Print(int mode) const {
    if (mode == 0) return;
    std::cout << _MinCost;
    if (mode == 1) { std::cout << std::endl; return; }
    std::cout << "  ";
    for (int i=0; i<_BestSolution.size(); ++i)
        std::cout << _BestSolution[i] << ", ";
    std::cout << std::endl;
}

NAMESPACE_ZHNOPTIM_R
