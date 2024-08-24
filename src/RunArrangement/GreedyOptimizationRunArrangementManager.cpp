#include "GreedyOptimizationRunArrangementManager.h"

ManagerOfRunArrangement* GreedyOptimizationRunArrangementManager::createInstance(OptimizationCase& givenCaseToSolve)
{
	return new GreedyOptimizationRunArrangementManager(givenCaseToSolve);
}

GreedyOptimizationRunArrangementManager::GreedyOptimizationRunArrangementManager(OptimizationCase& givenCaseToSolve):
	ManagerOfRunArrangement(givenCaseToSolve)
{
	initialIndividual = new ClassicalIndividual(givenCaseToSolve);
	initialIndividual->fillAllGensRandomly();
}

GreedyOptimizationRunArrangementManager::~GreedyOptimizationRunArrangementManager()
{
	delete initialIndividual;
}

StopCriterion* GreedyOptimizationRunArrangementManager::createStopCriterion()
{
	return new IterationCriterion(GREEDY_OPTIMIZATION_ITERATIONS_COUNT);
}

GeneticOptimizer* GreedyOptimizationRunArrangementManager::createGeneticOptimizer()
{
	return new GreedyHillClimber(*initialIndividual, true, SAME_SOLUTION_OPTIMIZATION_COUNT);
}
