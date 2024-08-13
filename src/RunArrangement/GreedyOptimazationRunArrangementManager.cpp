#include "GreedyOptimazationRunArrangementManager.h"

ManagerOfRunArrangement* GreedyOptimazationRunArrangementManager::createInstance(OptimazationCase& givenCaseToSolve)
{
	return new GreedyOptimazationRunArrangementManager(givenCaseToSolve);
}

GreedyOptimazationRunArrangementManager::GreedyOptimazationRunArrangementManager(OptimazationCase& givenCaseToSolve):
	ManagerOfRunArrangement(givenCaseToSolve)
{
	initialIndividual = new ClassicalIndividual(givenCaseToSolve);
	initialIndividual->fillAllGensRandomly();
}

GreedyOptimazationRunArrangementManager::~GreedyOptimazationRunArrangementManager()
{
	delete initialIndividual;
}

StopCriterium* GreedyOptimazationRunArrangementManager::createStopCriterium()
{
	return new IterationCtirterium(GREEDY_OPTIMAZATION_ITERATIONS_COUNT);
}

GeneticOptimizer* GreedyOptimazationRunArrangementManager::createGeneticOptimizer()
{
	return new GreedyHillClimber(*initialIndividual, true, SAME_SOLUTION_OPTIMAZATION_COUNT);
}
