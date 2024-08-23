#include "P3RunArrangementManager.h"

ManagerOfRunArrangement* P3RunArrangementManager::createInstance(OptimazationCase& givenCaseToSolve)
{
	return new P3RunArrangementManager(givenCaseToSolve);
}

P3RunArrangementManager::P3RunArrangementManager(OptimazationCase& givenCaseToSolve):
	ManagerOfRunArrangement(givenCaseToSolve) {}

StopCriterium* P3RunArrangementManager::createStopCriterium()
{
	return new IterationCtirterium(ARRANGED_P3_ITERATIONS_COUNT);
}

GeneticOptimizer* P3RunArrangementManager::createGeneticOptimizer()
{
	return new ParameterLessPopulationPyramid(givenCaseToSolve);
}
