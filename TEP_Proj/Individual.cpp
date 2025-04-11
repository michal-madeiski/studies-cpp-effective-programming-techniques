#include <iostream>
#include "Individual.h"
using namespace std;

CIndividual::CIndividual() : c_random_engine(random_device{}())
{
    i_genotype_size = i_DEFAULT_GENOTYPE_SIZE;
    v_genotype = vector<int>(i_genotype_size);
    d_fitness = d_DEFAULT_FITNESS;
    b_correct_fitness = b_DEFAULT_CORRECT_FITNESS;
}

CIndividual::CIndividual(const vector<int>& vGenotype) : c_random_engine(random_device{}())
{
    i_genotype_size = vGenotype.size();
    this->v_genotype = vGenotype;
    d_fitness = numeric_limits<double>::max();
    b_correct_fitness = false;
}

CIndividual::CIndividual(const CIndividual &cIndividual) : c_random_engine(random_device{}())
{
    i_genotype_size = cIndividual.v_genotype.size();
    v_genotype = cIndividual.v_genotype;
    d_fitness = cIndividual.d_fitness;
    b_correct_fitness = cIndividual.b_correct_fitness;
}

CIndividual::~CIndividual()
{

}

pair<CIndividual, CIndividual> CIndividual::cross(const CIndividual &c_other)
{
    uniform_int_distribution<int> c_rand_split_index (1, i_genotype_size - 1);

    int i_split_index = c_rand_split_index(c_random_engine); //od tego !włącznie! jest cz2

    vector<int> v_child1;
    vector<int> v_child2;

    for (int i = 0; i < i_split_index; ++i)
    {
        v_child1.push_back(v_genotype.at(i));
        v_child2.push_back(c_other.vGetGenotype().at(i));
    }

    for (int i = i_split_index; i < i_genotype_size; ++i)
    {
        v_child1.push_back(c_other.vGetGenotype().at(i));
        v_child2.push_back(v_genotype.at(i));
    }

    CIndividual c_indv1(v_child1);
    CIndividual c_indv2(v_child2);
    return make_pair(c_indv1, c_indv2);
}

void CIndividual::mutate(double d_mut_prob, int i_lower_bound, int i_upper_bound)
{
    uniform_real_distribution<double> c_rand_mut_prob(0.0, 1.0);
    uniform_int_distribution<int> newNumInGenotype(i_lower_bound, i_upper_bound);

    for (int i = 0; i < i_genotype_size; i++)
    {
        if (c_rand_mut_prob(c_random_engine) < d_mut_prob)
        {
            v_genotype[i] = newNumInGenotype(c_random_engine);
            b_correct_fitness = false;
        }
    }
}

void CIndividual::calculateFitness(const NGroupingChallenge::CGroupingEvaluator &c_evaluator)
{
    b_correct_fitness = true;
    d_fitness = c_evaluator.dEvaluate(v_genotype);
}

string CIndividual::s_to_string() const
{
    string s_individual_string;
    for (int i = 0; i < i_genotype_size; ++i)
    {
        s_individual_string += to_string(v_genotype[i]);
    }
    return s_individual_string;
}

int CIndividual::iGetGenotypeSize() const
{
    return v_genotype.size();
}

vector<int> CIndividual::vGetGenotype() const
{
    return v_genotype;
}

double CIndividual::dGetFitness() const
{
    return d_fitness;
}

bool CIndividual::bIsCorrectFitness() const
{
    return b_correct_fitness;
}













