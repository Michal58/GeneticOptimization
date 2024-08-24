#pragma once
#include "RunArrangement.h"

class ManagerOfRunArrangement {
protected:

	OptimizationCase& givenCaseToSolve;
	RunArrangement* createdRunArrangement;

	StopCriterion* arrangedStopCriterion;
	GeneticOptimizer* arrangedOptimizer;

	void createRunArrangement();
	void createRunArrangement(StopCriterion* arrangedStopCriterion, GeneticOptimizer* arrangedOptimizer);

	virtual StopCriterion* createStopCriterion() = 0;
	virtual GeneticOptimizer* createGeneticOptimizer() = 0;

public:

	ManagerOfRunArrangement(OptimizationCase& givenCaseToSolve);
	virtual ~ManagerOfRunArrangement();
	RunArrangement& shareRunArrangement();
};


