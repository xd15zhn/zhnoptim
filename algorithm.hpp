#ifndef __ZHNOPTIM_H
#define __ZHNOPTIM_H
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <iomanip>

#define INFINITE                      1e12
#define EPSILON                       1e-12
#define ABS(x)                        ((x)>=0?(x):-(x))
#ifndef PRINT_NAME_VALUE
#define PRINT_NAME_VALUE(x)           std::cout<<#x<<": "<<x<<std::endl;
#endif
#define ASSERT_ERROR_ALG(e, s)        if(!(e)){std::cout<<"Zhn algorithm Error: "<<s<<std::endl;abort();}
#define ASSERT_WARNING_ALG(e, s)      if(!(e)){std::cout<<"Zhn algorithm Warning: "<<s<<std::endl;}
#define NAMESPACE_ZHNOPTIM_L          namespace zhnoptim {
#define NAMESPACE_ZHNOPTIM_R          }
NAMESPACE_ZHNOPTIM_L


class Algorithm{
public:
    enum TermCriteria{  // Termination criteria
        EPS,  // Iteration terminates when the cost is less than a certain value.
        COUNT,  // Iteration terminates after a certain number of times.
        BOTHAND,  // Iteration terminates when both conditions EPS and COUNT are satisfied.
        BOTHOR  // Iteration terminates when condition EPS or COUNT is satisfied.
    };
    Algorithm(const std::vector<double>& solution, int solvelen=0);
    virtual ~Algorithm() {};
    void Set_CostFunction(double(*f)(const std::vector<double>& solution)) { _costFunc=f; };
    void Set_TerminationConditions(double mincost, int maxiterate, TermCriteria type=EPS);
    double Get_Cost() const { return _MinCost; };
    std::vector<double> Get_BestSolution() const { return _BestSolution; };
    void Solution_Print() const;
    virtual void run() = 0;
protected:
    int _solvelen;  // Length of solution vector
    int _IterateCnt, _TermIterate;  // Current and total number of iterations
    double(*_costFunc)(const std::vector<double>& solution);
    TermCriteria TermType;
    double _TermCost, _MinCost;  // Current and minimum cost value
    std::vector<double> _BestSolution;
};


/***********************
Differential Evolution(DE/best/2)
**********************/
class Differential_Evolution: public Algorithm{
public:
    Differential_Evolution(const std::vector<double>& solution, int solvelen=1, int popsize=15);
    virtual ~Differential_Evolution() {};
    virtual void run();
    void Set_Param(double F, double CR) { _F=F;_CR=CR; };
private:
    std::vector<std::vector<double>> population;
    std::vector<double> mutant, offspring;
    int _popsize;  // number of the population
    double _F, _CR;  // 缩放因子,交叉因子
    double fit1, fit2;  // 适应度值
    int in1, in2;  // 2个差分向量的个体编号
    std::default_random_engine gen;  // 生成初始化种子
    std::normal_distribution<double> NormDis;  // 正态分布
    std::uniform_real_distribution<double> UniFloatDis;  // [0,1]均匀分布
    std::uniform_int_distribution<unsigned> UniIntDis;  // 整数均匀分布
};


/***********************
Pattern Search
**********************/
class Pattern_Search: public Algorithm{
public:
    Pattern_Search(const std::vector<double>& solution, int solvelen=0, double deltaStart=0.25);
    virtual ~Pattern_Search() {};
    virtual void run();
    void Set_Param(double deltaStart) { _delta = deltaStart; };
private:
    double _delta;
};

NAMESPACE_ZHNOPTIM_R
#endif  // ZHNOPTIM
