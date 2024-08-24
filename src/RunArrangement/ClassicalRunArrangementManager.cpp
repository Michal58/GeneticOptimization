#include "ClassicalRunArrangementManager.h"

ClassicalRunArrangementManager::ClassicalRunArrangementManager(OptimizationCase& givenCaseToSolve):
	ManagerOfRunArrangement(givenCaseToSolve) {}

StopCriterium* ClassicalRunArrangementManager::createStopCriterium()
{
	return new IterationCtirterium(ARRANGED_CLASSICAL_ITERATIONS_COUNT);
}

GeneticOptimizer* ClassicalRunArrangementManager::createGeneticOptimizer()
{
	return new GeneticAlgorithm(
		ARRANGED_CLASSICAL_POPULATION_SIZE,
		ARRANGED_CLASSICAL_CROSSOVER_CHANCE,
		ARRANGED_CLASSICAL_GEN_MUTATION_CHANCE,
		givenCaseToSolve
	);
}

ManagerOfRunArrangement* ClassicalRunArrangementManager::createInstance(OptimizationCase& givenCaseToSolve)
{
	return new ClassicalRunArrangementManager(givenCaseToSolve);
}
