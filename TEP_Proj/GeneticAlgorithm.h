#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include <random>
#include "Individual.h"
#include "Optimizer.h"
using namespace std;

class CGeneticAlgorithm : public NGroupingChallenge::COptimizer {
public:
    CGeneticAlgorithm(int iPopSize, double dMutProb, double dCrossProb,
                      NGroupingChallenge::CGroupingEvaluator &cEvaluator);
    ~CGeneticAlgorithm() override;

    void vInitialize() override;
    void vRun() override;

private:
    int i_pop_size;
    double d_mut_prob;
    double d_cross_prob;
    NGroupingChallenge::CGroupingEvaluator& c_evaluator;
    vector<CIndividual> v_pop;
    mt19937 c_random_engine;

    CIndividual& c_next_pop();
    CIndividual& c_select_parent();
};

constexpr int i_DEFAULT_POP_SIZE = 100; //constexpr - znane juz w czasie kompilacji
constexpr double d_DEFAULT_MUT_PROB = 0.15;
constexpr double d_DEFAULT_CROSS_PROB = 0.65;
constexpr int i_END_COND_MAX_GEN_SIZE = 50;
constexpr int i_MAX_POTENTIAL_PARENT_COUNT = 100;
constexpr int i_MIN_POTENTIAL_PARENT_COUNT = 2;

#endif //GENETICALGORITHM_H
