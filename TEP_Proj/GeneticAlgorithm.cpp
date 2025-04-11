#include <iostream>
#include <random>
#include "GeneticAlgorithm.h"
using namespace std;

CGeneticAlgorithm::CGeneticAlgorithm(int iPopSize, double dMutProb, double dCrossProb,
    NGroupingChallenge::CGroupingEvaluator &cEvaluator) : i_pop_size(iPopSize), d_mut_prob(dMutProb),
                                                          d_cross_prob(dCrossProb), c_evaluator(cEvaluator),
                                                          c_random_engine(random_device{}())
{

}

CGeneticAlgorithm::~CGeneticAlgorithm()
{
    cout << "~CGeneticAlgorithm" << endl;
}

void CGeneticAlgorithm::vRun()
{
    vInitialize();

    vector<int> v_curr_best_ans;
    double d_curr_best_fitness = numeric_limits<double>::max();

    for (int i = 0; i < i_END_COND_MAX_GEN_SIZE; ++i)
    {
        CIndividual c_curr_individual = c_next_pop();
        double d_prev_best_fitness = d_curr_best_fitness;

        if (c_curr_individual.dGetFitness() < d_curr_best_fitness)
        {
            d_curr_best_fitness = c_curr_individual.dGetFitness();
            v_curr_best_ans = c_curr_individual.vGetGenotype();
        }

        cout << "gen: " << i + 1 << " | curr best fitness: " << c_curr_individual.dGetFitness() <<
                " | ovrl best fitness: " << d_curr_best_fitness;
        if (c_curr_individual.dGetFitness() < d_prev_best_fitness) {
            cout << " NEW BEST";
        }
        cout << endl;

    }
    cout << endl;

    cout << "best answer: ";
    for (int i = 0; i < v_curr_best_ans.size(); ++i)
    {
        cout << v_curr_best_ans[i] << " ";
        if ((i+1) % 50 == 0)
        {
            cout << endl;
            cout << "             ";
        }
    }
    cout << endl;

    cout << "fitness of best answer: " << d_curr_best_fitness << endl;
}

void CGeneticAlgorithm::vInitialize()
{
    vector<CIndividual> v_pop_temp;

    uniform_int_distribution<int> rand(c_evaluator.iGetLowerBound(), c_evaluator.iGetUpperBound());

    for (int i = 0; i < i_pop_size; ++i)
    {
        vector<int> temp;
        for (int j = 0; j < c_evaluator.iGetNumberOfPoints(); ++j)
        {
            temp.push_back(rand(c_random_engine));
        }
        v_pop_temp.push_back(temp);
    }

    for (int i = 0; i < i_pop_size; ++i)
    {
        v_pop_temp.at(i).calculateFitness(c_evaluator);
    }

    v_pop = v_pop_temp;
}

CIndividual& CGeneticAlgorithm::c_next_pop()
{
    vector<CIndividual> v_new_pop;

    uniform_real_distribution<double> c_rand(0.0, 1.0); //do crossChance

    double d_best_fitness = numeric_limits<double>::max();
    int i_best_ans_idx = -1;

    for (int i = 0; i < i_pop_size/2; ++i)
    {
        CIndividual* pc_parent1 = &c_select_parent();
        CIndividual* pc_parent2 = &c_select_parent();
        if (pc_parent1 == pc_parent2)
        {
            v_new_pop.push_back(*pc_parent1);
            v_new_pop.push_back(*pc_parent2);
        } else
          {
            double d_cross_chance = c_rand(c_random_engine);
            if (d_cross_chance < d_cross_prob)
            {
                pair<CIndividual, CIndividual> children = pc_parent1->cross(*pc_parent2);
                v_new_pop.push_back(children.first);
                v_new_pop.push_back(children.second);
            } else
              {
                v_new_pop.push_back(*pc_parent1);
                v_new_pop.push_back(*pc_parent2);
              }
          }
    }

    for (int i = 0; i < i_pop_size; ++i)
    {
        double d_mut_chance = c_rand(c_random_engine);

        if (d_mut_chance < d_mut_prob)
        {
            v_new_pop.at(i).mutate(d_mut_prob, c_evaluator.iGetLowerBound(), c_evaluator.iGetUpperBound());
        }

        if (!v_new_pop.at(i).bIsCorrectFitness())
        {
            v_new_pop.at(i).calculateFitness(c_evaluator);
        }

        if (v_new_pop.at(i).dGetFitness() < d_best_fitness)
        {
            d_best_fitness = v_new_pop.at(i).dGetFitness();
            i_best_ans_idx = i;
        }
    }

    v_pop.clear();
    v_pop = v_new_pop;
    return v_pop.at(i_best_ans_idx);
}

CIndividual& CGeneticAlgorithm::c_select_parent()
{
    uniform_int_distribution<int> c_rand(0, i_pop_size-1); //do wybrania potencjalnych rodzicow

    vector<CIndividual*> v_potential_parents;
    double d_best_fitness = numeric_limits<double>::max();
    int i_best_ans_idx = -1;

    //wybieranie z wiecej niz 2 - wieksza szansa na cos lepszego, ale maks 100 zeby nie bylo za dlugo
    int i_potential_parent_count = i_pop_size/10;
    if (i_potential_parent_count > i_MAX_POTENTIAL_PARENT_COUNT)
    {
        i_potential_parent_count = i_MAX_POTENTIAL_PARENT_COUNT;
    }
    if (i_potential_parent_count < i_MIN_POTENTIAL_PARENT_COUNT)
    {
        i_potential_parent_count = i_MIN_POTENTIAL_PARENT_COUNT;
    }

    for (int i = 0; i < i_potential_parent_count; ++i)
    {
        int idx = c_rand(c_random_engine);
        v_potential_parents.push_back(&v_pop.at(idx));
    }

    for (int i = 0; i < i_potential_parent_count; ++i)
    {
        if (v_potential_parents.at(i)->dGetFitness() < d_best_fitness)
        {
            d_best_fitness = v_potential_parents.at(i)->dGetFitness();
            i_best_ans_idx = i;
        }
    }
    return *v_potential_parents.at(i_best_ans_idx);
}


