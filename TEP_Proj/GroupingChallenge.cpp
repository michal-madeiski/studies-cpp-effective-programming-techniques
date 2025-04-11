#include "GeneticProject/GaussianGroupingEvaluatorFactory.h"
#include "GeneticProject/GroupingEvaluator.h"
#include "GeneticAlgorithm.h"
using namespace NGroupingChallenge;

int main()
{
	CGaussianGroupingEvaluatorFactory c_evaluator_factory(5, 100);

	c_evaluator_factory
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0);

	CGroupingEvaluator* pc_evaluator = c_evaluator_factory.pcCreateEvaluator(0);

	CGeneticAlgorithm c_genetic_algorithm(2000, 0.15, 0.65, *pc_evaluator);
	c_genetic_algorithm.vRun();
	cout << endl;

	delete pc_evaluator;

	return 0;
}