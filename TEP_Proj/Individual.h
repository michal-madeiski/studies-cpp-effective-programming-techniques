#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <vector>
#include "GeneticProject/GaussianGroupingEvaluatorFactory.h"
#include "GeneticProject/GroupingEvaluator.h"
using namespace std;

class CIndividual {
public:
  CIndividual();
  CIndividual(const CIndividual& cIndividual);
  CIndividual(const vector<int>& vGenotype);
  ~CIndividual();

  pair<CIndividual, CIndividual> cross(const CIndividual& cOther);
  void mutate(double dMutProb, int iLowerBound, int iUpperBound);
  void calculateFitness(const NGroupingChallenge::CGroupingEvaluator &cEvaluator);

  string s_to_string() const;

  int iGetGenotypeSize() const;
  vector<int> vGetGenotype() const;
  double dGetFitness() const;
  bool bIsCorrectFitness() const;

private:
  int i_genotype_size;
  vector<int> v_genotype;
  double d_fitness;
  bool b_correct_fitness;
  mt19937 c_random_engine;
};

constexpr int i_DEFAULT_GENOTYPE_SIZE = 0; //constexpr - znane juz w czasie kompilacji
constexpr double d_DEFAULT_FITNESS = 0.0;
constexpr bool b_DEFAULT_CORRECT_FITNESS = true;

#endif //INDIVIDUAL_H
