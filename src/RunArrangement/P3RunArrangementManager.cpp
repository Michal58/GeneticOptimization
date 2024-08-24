#include "P3RunArrangementManager.h"

ManagerOfRunArrangement* P3RunArrangementManager::createInstance(OptimizationCase& givenCaseToSolve)
{
	return new P3RunArrangementManager(givenCaseToSolve);
}

P3RunArrangementManager::P3RunArrangementManager(OptimizationCase& givenCaseToSolve):
	ManagerOfRunArrangement(givenCaseToSolve) {}

StopCriterion* P3RunArrangementManager::createStopCriterion()
{
	return new IterationCriterion(ARRANGED_P3_ITERATIONS_COUNT);
}

GeneticOptimizer* P3RunArrangementManager::createGeneticOptimizer()
{
	return new ParameterLessPopulationPyramid(givenCaseToSolve);
}
