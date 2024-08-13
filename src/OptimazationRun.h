#pragma once
#include "OptimazationTemplates/OptimazationCase.h"
#include "OptimazationTemplates/GeneticOptimizer.h"
#include "RunArrangement/RunArrangement.h"
#include "RunArrangement/ClassicalRunArrangementManager.h"
#include "RunArrangement/GreedyOptimazationRunArrangementManager.h"

typedef ManagerOfRunArrangement* (*arrangementMangerCreator) (OptimazationCase&);

const arrangementMangerCreator ARRANGEMENT_CONSTRUCTORS[] = {
	& ClassicalRunArrangementManager::createInstance,
	& GreedyOptimazationRunArrangementManager::createInstance
};

struct OptimazationResult {
	double fitnessValue;
	std::vector<int>* solutionVector;		// struct only stores result, so the task of vector deletion is caller responsibility
};

class OptimazationRun {
public:

	const static int CLASSICAL_ARRANGEMENT_MANAGER_CODE = 0;

private:

	OptimazationCase& givenCaseToSolve;
	RunArrangement* possiblyCreatedRunArrangement;
	RunArrangement& arrangedRunSet;
	ManagerOfRunArrangement* possiblyPassedManagerOfRunArrangement;

	RunArrangement* createRunArrangement(GeneticOptimizer& givenOptimizerAsSolver, StopCriterium& givenCriteriumOfStop);

public:

	OptimazationRun(OptimazationCase& givenCaseToSolve, GeneticOptimizer& givenOptimizerAsSolver, StopCriterium& givenCriteriumOfStop);
	OptimazationRun(OptimazationCase& givenCaseToSolve, RunArrangement& arrangedRunSet);
	OptimazationRun(OptimazationCase& givenCaseToSolve, ManagerOfRunArrangement* arrangementManager);
	OptimazationRun(OptimazationCase& givenCaseToSolve, int indexOfArrangementManagerCreator);
	~OptimazationRun();
	OptimazationResult findOptimizedSolution();
};