#pragma once
#include "OptimizationTemplates/OptimizationCase.h"
#include "OptimizationTemplates/GeneticOptimizer.h"
#include "RunArrangement/RunArrangement.h"
#include "RunArrangement/ClassicalRunArrangementManager.h"
#include "RunArrangement/GreedyOptimazationRunArrangementManager.h"
#include "RunArrangement/P3RunArrangementManager.h"

typedef ManagerOfRunArrangement* (*arrangementMangerCreator) (OptimizationCase&);

const arrangementMangerCreator ARRANGEMENT_CONSTRUCTORS[] = 
{
	& ClassicalRunArrangementManager::createInstance,
	& GreedyOptimazationRunArrangementManager::createInstance,
	& P3RunArrangementManager::createInstance
};

struct OptimizationResult 
{
	double fitnessValue;
	std::vector<int>* solutionVector;		// struct only stores result, so the task of vector deletion is caller responsibility
};

class OptimazationRun 
{
public:

	const static int CLASSICAL_ARRANGEMENT_MANAGER_CODE = 0;

private:

	OptimizationCase& givenCaseToSolve;
	RunArrangement* possiblyCreatedRunArrangement;
	RunArrangement& arrangedRunSet;
	ManagerOfRunArrangement* possiblyPassedManagerOfRunArrangement;

	RunArrangement* createRunArrangement(GeneticOptimizer& givenOptimizerAsSolver, StopCriterium& givenCriteriumOfStop);

public:

	OptimazationRun(OptimizationCase& givenCaseToSolve, GeneticOptimizer& givenOptimizerAsSolver, StopCriterium& givenCriteriumOfStop);
	OptimazationRun(OptimizationCase& givenCaseToSolve, RunArrangement& arrangedRunSet);
	OptimazationRun(OptimizationCase& givenCaseToSolve, ManagerOfRunArrangement* arrangementManager);
	OptimazationRun(OptimizationCase& givenCaseToSolve, int indexOfArrangementManagerCreator);
	~OptimazationRun();
	OptimizationResult findOptimizedSolution();
};