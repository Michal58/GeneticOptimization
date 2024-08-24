#pragma once

#include "OptimizationCase.h"
#include "Individual.h"

#define LOG_ALLOWED 1
#define LOG_FORBIDDEN 0
#define LOG_PERMISSION LOG_ALLOWED

class StopCriterium
{
public:

	virtual bool isLimitReached() = 0;
	virtual void updateStance() = 0;
};


class GeneticOptimizer
{

protected:

	OptimizationCase& caseInstance;

public:

	GeneticOptimizer(OptimizationCase& caseInstance);
	virtual ~GeneticOptimizer();

	virtual void reset() = 0;
	virtual bool isReadyToSearch() = 0;
	virtual void runIteration() = 0;
	virtual void searchForTheBestSolution(StopCriterium& stopController);
	virtual Individual* peekTheBestIndividual() = 0;
	virtual Individual* copyTheBestIndividual() = 0;
};


