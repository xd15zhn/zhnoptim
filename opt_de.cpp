#include <random>
#include <ctime>
#include "zhnoptim.hpp"
NAMESPACE_ZHNOPTIM_L

Differential_Evolution::~Differential_Evolution() {}
void Differential_Evolution::Set_Param(double F, double CR) { _F=F;_CR=CR; }

/***********************
Differential Evolution algorithm initialize
*@ solution: Initial solution vector
*@ solvelen: Length of solution vector
*@ popsize: number of the population
**********************/
Differential_Evolution::Differential_Evolution(const std::vector<double> &solution, int popsizeeach)
    : Algorithm(solution)
{
    _solvelen = solution.size();
    gen = std::default_random_engine((unsigned int)time(0));
    NormDis = std::normal_distribution<double>(0, 1);
    UniFloatDis = std::uniform_real_distribution<double>(0, 1);
    UniIntDis = std::uniform_int_distribution<unsigned>(0, _solvelen - 1);
    _popsize = popsizeeach * _solvelen;
    _F = _CR = 0.5;
    mutant = offspring = _BestSolution;
    population.push_back(_BestSolution);
    for (int i = 1; i < _popsize; ++i){
        population.push_back(_BestSolution);
        for (int j=0; j<_solvelen; ++j) {
            fit1 = NormDis(gen);
            population[i][j] = fit1;
        }
    }
}

void Differential_Evolution::run()
{
    bool finished = false;
    _MinCost = _costFunc->Function(population[0]);
    _BestSolution = population[0];
    for (short i = 1; i < _solvelen; i++) {
        fit1 = _costFunc->Function(population[i]);
        if (fit1 < _MinCost) {
            _MinCost = fit1;
            _BestSolution = population[i];
        }
    }
    Solution_Print(_printformat);
    do {
        for (short i = 0; i < _popsize; i++) {
            /*变异:使每个个体变异产生变异个体*/
            in1 = UniIntDis(gen);
            in2 = UniIntDis(gen);
            for (short j = 0; j < _solvelen; j++) {
                _F = UniFloatDis(gen);
                mutant[j] = population[i][j] + _F*(population[in1][j] - population[in2][j]);
            }
            /*交叉:变异个体与原个体交叉产生后代个体*/
            for (short j = 0; j < _solvelen; j++) {
                if (UniFloatDis(gen) > _CR)
                    offspring[j] = population[i][j];
                else
                    offspring[j] = mutant[j];
            }
            /*选择:后代个体与原个体竞争并保留优胜个体*/
            fit1 = _costFunc->Function(population[i]);
            fit2 = _costFunc->Function(offspring);
            if (fit2 < fit1) {
                for (short j = 0; j < _solvelen; j++)
                    population[i][j] = offspring[j];
                if (fit2 < _MinCost) {
                    _MinCost = fit2;
                    _BestSolution = population[i];
                    Solution_Print(_printformat==PRINT_UPDATE ? 2:0);
                }
            }
        }
        Solution_Print(_printformat==PRINT_ITERATE ? 1:0);
        _IterateCnt++;
        switch (TermType){
        case EPS: finished = _MinCost <= _TermCost; break;
        case COUNT: finished = _IterateCnt >= _TermIterate; break;
        case BOTHAND: finished = (_MinCost <= _TermCost) && (_IterateCnt >= _TermIterate); break;
        case BOTHOR: finished = (_MinCost <= _TermCost) || (_IterateCnt >= _TermIterate); break;
        default: finished = false; break;
        }
    } while (!finished);
}

NAMESPACE_ZHNOPTIM_R
