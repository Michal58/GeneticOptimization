#pragma once
#include "ManagerOfRunArrangement.h"
#include "../ClassicalGeneticAlgorithm/GeneticAlgorithm.h"
#include "../CommonComponents/HillClimbers/GreedyHillClimber.h"

#define GREEDY_OPTIMAZATION_ITERATIONS_COUNT 2
#define SAME_SOLUTION_OPTIMAZATION_COUNT 2

class GreedyOptimazationRunArrangementManager: public ManagerOfRunArrangement
{
	Individual* initialIndividual;

public:

	static ManagerOfRunArrangement* createInstance(OptimizationCase& givenCaseToSolve);
	GreedyOptimazationRunArrangementManager(OptimizationCase& givenCaseToSolve);
	~GreedyOptimazationRunArrangementManager();

	StopCriterium* createStopCriterium() override;
	GeneticOptimizer* createGeneticOptimizer() override;
};

