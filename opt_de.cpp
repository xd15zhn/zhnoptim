#include "algorithm.hpp"
NAMESPACE_ZHNOPTIM_L

/***********************
Differential Evolution algorithm initialize
*@ solution: Initial solution vector
*@ solvelen: Length of solution vector
*@ popsize: number of the population
**********************/
Differential_Evolution::Differential_Evolution(const std::vector<double> &solution, int solvelen, int popsize)
    : Algorithm(solution, solvelen)
{
    gen = std::default_random_engine((unsigned int)time(0));
    NormDis = std::normal_distribution<double>(0, 1);
    UniFloatDis = std::uniform_real_distribution<double>(0, 1);
    UniIntDis = std::uniform_int_distribution<unsigned>(0, _solvelen - 1);
    _popsize = popsize;
    _F = _CR = 0.5;
    mutant = offspring = _BestSolution;
    population.push_back(_BestSolution);
    for (int i = 1; i < popsize; ++i){
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
    std::cout << "Differential Evalution begins." << std::endl;
    _MinCost = _costFunc(population[0]);
    _BestSolution = population[0];
    for (short i = 1; i < _solvelen; i++) {
        fit1 = _costFunc(population[i]);
        if (fit1 < _MinCost) {
            _MinCost = fit1;
            _BestSolution = population[i];
        }
    }
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
            fit1 = _costFunc(population[i]);
            fit2 = _costFunc(offspring);
            if (fit2 < fit1) {
                for (short j = 0; j < _solvelen; j++)
                    population[i][j] = offspring[j];
                if (fit2 < _MinCost) {
                    _MinCost = fit2;
                    _BestSolution = population[i];
                    Solution_Print();
                }
            }
        }
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
