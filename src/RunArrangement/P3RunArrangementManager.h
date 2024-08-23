#pragma once
#include "ManagerOfRunArrangement.h"
#include "../ClassicalGeneticAlgorithm/GeneticAlgorithm.h"
#include "../ParameterLessPopulationPyramid/ParameterLessPopulationPyramid.h"

#define ARRANGED_P3_ITERATIONS_COUNT 2000

class P3RunArrangementManager: public ManagerOfRunArrangement
{
public:

	static ManagerOfRunArrangement* createInstance(OptimazationCase& givenCaseToSolve);

	P3RunArrangementManager(OptimazationCase& givenCaseToSolve);
	StopCriterium* createStopCriterium() override;
	GeneticOptimizer* createGeneticOptimizer() override;
};

