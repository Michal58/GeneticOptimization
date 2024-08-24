#pragma once
#include "RunArrangement.h"

class ManagerOfRunArrangement {
protected:

	OptimizationCase& givenCaseToSolve;
	RunArrangement* createdRunArrangement;

	StopCriterium* arrangedStopCriterium;
	GeneticOptimizer* arrangedOptimizer;

	void createRunArrangement();
	void createRunArrangement(StopCriterium* arrangedStopCriterium, GeneticOptimizer* arrangedOptimizer);

	virtual StopCriterium* createStopCriterium() = 0;
	virtual GeneticOptimizer* createGeneticOptimizer() = 0;

public:

	ManagerOfRunArrangement(OptimizationCase& givenCaseToSolve);
	virtual ~ManagerOfRunArrangement();
	RunArrangement& shareRunArrangement();
};


