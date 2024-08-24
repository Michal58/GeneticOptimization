#pragma once
#include "ManagerOfRunArrangement.h"
#include "../ClassicalGeneticAlgorithm/GeneticAlgorithm.h"
#include "../ParameterLessPopulationPyramid/ParameterLessPopulationPyramid.h"

#define ARRANGED_P3_ITERATIONS_COUNT 2000

class P3RunArrangementManager: public ManagerOfRunArrangement
{
public:

	static ManagerOfRunArrangement* createInstance(OptimizationCase& givenCaseToSolve);

	P3RunArrangementManager(OptimizationCase& givenCaseToSolve);
	StopCriterium* createStopCriterium() override;
	GeneticOptimizer* createGeneticOptimizer() override;
};

