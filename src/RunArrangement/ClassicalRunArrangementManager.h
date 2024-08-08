#pragma once
#include "ManagerOfRunArrangement.h"
#include "../ClassicalGeneticAlgorithm/GeneticAlgorithm.h"

#define ARRANGED_CLASSICAL_ITERATIONS_COUNT 2000
#define ARRANGED_CLASSICAL_POPULATION_SIZE 600
#define ARRANGED_CLASSICAL_CROSSOVER_CHANCE 1
#define ARRANGED_CLASSICAL_GEN_MUTATION_CHANCE 0.0001


class ClassicalRunArrangementManager: public ManagerOfRunArrangement
{
public:

	static ManagerOfRunArrangement* createInstance(OptimazationCase& givenCaseToSolve);
	ClassicalRunArrangementManager(OptimazationCase& givenCaseToSolve);

	StopCriterium* createStopCriterium() override;
	GeneticOptimizer* createGeneticOptimizer() override;
};

