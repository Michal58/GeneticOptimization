#pragma once
#include "RunArrangement.h"

class ManagerOfRunArrangement {
protected:

	OptimazationCase& givenCaseToSolve;
	RunArrangement* createdRunArrangement;

	StopCriterium* arrangedStopCriterium;
	GeneticOptimizer* arrangedOptimizer;

	void createRunArrangement();
	void createRunArrangement(StopCriterium* arrangedStopCriterium, GeneticOptimizer* arrangedOptimizer);

	virtual StopCriterium* createStopCriterium() = 0;
	virtual GeneticOptimizer* createGeneticOptimizer() = 0;

public:

	ManagerOfRunArrangement(OptimazationCase& givenCaseToSolve);
	virtual ~ManagerOfRunArrangement();
	RunArrangement& shareRunArrangement();
};


