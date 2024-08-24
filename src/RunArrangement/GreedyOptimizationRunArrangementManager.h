#pragma once
#include "ManagerOfRunArrangement.h"
#include "../ClassicalGeneticAlgorithm/GeneticAlgorithm.h"
#include "../CommonComponents/HillClimbers/GreedyHillClimber.h"

#define GREEDY_OPTIMIZATION_ITERATIONS_COUNT 2
#define SAME_SOLUTION_OPTIMIZATION_COUNT 2

class GreedyOptimizationRunArrangementManager: public ManagerOfRunArrangement
{
	Individual* initialIndividual;

public:

	static ManagerOfRunArrangement* createInstance(OptimizationCase& givenCaseToSolve);
	GreedyOptimizationRunArrangementManager(OptimizationCase& givenCaseToSolve);
	~GreedyOptimizationRunArrangementManager();

	StopCriterion* createStopCriterion() override;
	GeneticOptimizer* createGeneticOptimizer() override;
};

