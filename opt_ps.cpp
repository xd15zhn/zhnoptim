#include "zhnoptim.hpp"
NAMESPACE_ZHNOPTIM_L

Pattern_Search::~Pattern_Search() {}
void Pattern_Search::Set_Param(double deltaStart) { _delta = deltaStart; }

Pattern_Search::Pattern_Search(const std::vector<double>& solution, double deltaStart)
    : Algorithm(solution)
{
    _solvelen = solution.size();
    _delta = deltaStart;
}

void Pattern_Search::run()
{
    _MinCost = _costFunc->Function(_BestSolution);
    double tempCost, oldCost = _MinCost;
    do {
        for (short i = 0; i < _solvelen; i++) {
            _BestSolution[i] += _delta;
            tempCost = _costFunc->Function(_BestSolution);
            if (tempCost >= _MinCost)
                _BestSolution[i] -= 2 * _delta;
            else {
                _MinCost = tempCost;
                continue;
            }
            tempCost = _costFunc->Function(_BestSolution);
            if (tempCost >= _MinCost)
                _BestSolution[i] += _delta;
            else
                _MinCost = tempCost;
        }
        if (_MinCost >= oldCost) _delta /= 2;
        else oldCost = _MinCost;
    } while (_delta>ZHNOPTIM_EPSILON);
}

NAMESPACE_ZHNOPTIM_R
