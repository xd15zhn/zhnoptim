#ifndef __ZHNOPTIM_H
#define __ZHNOPTIM_H
#include <vector>

#define ZHNOPTIM_INFINITE             1e12
#define ZHNOPTIM_EPSILON              1e-12
#define ZHNOPTIM_ABS(x)               ((x)>=0?(x):-(x))
#ifndef PRINT_NAME_VALUE
#define PRINT_NAME_VALUE(x)           std::cout<<#x<<": "<<x<<std::endl;
#endif
#define ASSERT_ERROR_ALG(e, s)        if(!(e)){std::cout<<"Zhn algorithm Error: "<<s<<std::endl;abort();}
#define ASSERT_WARNING_ALG(e, s)      if(!(e)){std::cout<<"Zhn algorithm Warning: "<<s<<std::endl;}
#define NAMESPACE_ZHNOPTIM_L          namespace zhnoptim {
#define NAMESPACE_ZHNOPTIM_R          }
NAMESPACE_ZHNOPTIM_L

enum TermCriteria {  // Termination criteria
    EPS,  // Iteration terminates when the cost is less than a certain value.
    COUNT,  // Iteration terminates after a certain number of times.
    BOTHAND,  // Iteration terminates when both conditions EPS and COUNT are satisfied.
    BOTHOR,  // Iteration terminates when condition EPS or COUNT is satisfied.
};
enum PRINT_FORMAT {  // When the best solution is printed.
    NO_PRINT,  // Donnot print.
    PRINT_ITERATE,  // Print after every iterate step.
    PRINT_UPDATE,  // Print when a new best solution is found.
};

/**********************
Used to provide another method to replace the pointer to a function.
**********************/
class UserFunc
{
public:
    virtual double Function(const std::vector<double>& u) {return u[0];};
};

class Algorithm
{
public:
    Algorithm(const std::vector<double>& solution);
    virtual ~Algorithm();
    void Set_CostFunction(UserFunc *f);

    // 
    void Set_TerminationConditions(double mincost, int maxiterate, TermCriteria type=COUNT);
    // 设置输出格式
    void Set_PrintFormat(PRINT_FORMAT format);
    double Get_Cost() const;
    std::vector<double> Get_BestSolution() const;
    void Solution_Print(int mode) const;
    virtual void run() = 0;
protected:
    int _IterateCnt, _TermIterate;  // Current and total number of iterations
    UserFunc *_costFunc;
    TermCriteria TermType;
    PRINT_FORMAT _printformat = PRINT_UPDATE;
    double _TermCost, _MinCost;  // Current and minimum cost value
    std::vector<double> _BestSolution;
};


/***********************
Differential Evolution(DE/best/2)
**********************/
class Differential_Evolution: public Algorithm
{
public:
    Differential_Evolution(const std::vector<double>& solution, int popsizeeach=15);
    virtual ~Differential_Evolution();
    virtual void run();
    void Set_Param(double F, double CR);
private:
    int _solvelen;
    std::vector<std::vector<double>> _population;
    int _popsize;  // number of the population
    double _F, _CR;  // 缩放因子,交叉因子
};


/***********************
Pattern Search
**********************/
class Pattern_Search: public Algorithm{
public:
    Pattern_Search(const std::vector<double>& solution, double deltaStart=0.25);
    virtual ~Pattern_Search();
    virtual void run();
    void Set_Param(double deltaStart);
private:
    int _solvelen;
    double _delta;
};

NAMESPACE_ZHNOPTIM_R
#endif  // ZHNOPTIM
