#pragma once
#include "OptimizationTemplates/OptimizationCase.h"
#include "OptimizationTemplates/GeneticOptimizer.h"
#include "RunArrangement/RunArrangement.h"
#include "RunArrangement/ClassicalRunArrangementManager.h"
#include "RunArrangement/GreedyOptimizationRunArrangementManager.h"
#include "RunArrangement/P3RunArrangementManager.h"

typedef ManagerOfRunArrangement* (*arrangementMangerCreator) (OptimizationCase&);

const arrangementMangerCreator ARRANGEMENT_CONSTRUCTORS[] = 
{
	& ClassicalRunArrangementManager::createInstance,
	& GreedyOptimizationRunArrangementManager::createInstance,
	& P3RunArrangementManager::createInstance
};

struct OptimizationResult 
{
	double fitnessValue;
	std::vector<int>* solutionVector;		// struct only stores result, so the task of vector deletion is caller responsibility
};

class OptimizationRun 
{
public:

	const static int CLASSICAL_ARRANGEMENT_MANAGER_CODE = 0;

private:

	OptimizationCase& givenCaseToSolve;
	RunArrangement* possiblyCreatedRunArrangement;
	RunArrangement& arrangedRunSet;
	ManagerOfRunArrangement* possiblyPassedManagerOfRunArrangement;

	RunArrangement* createRunArrangement(GeneticOptimizer& givenOptimizerAsSolver, StopCriterion& givenCriterionOfStop);

public:

	OptimizationRun(OptimizationCase& givenCaseToSolve, GeneticOptimizer& givenOptimizerAsSolver, StopCriterion& givenCriterionOfStop);
	OptimizationRun(OptimizationCase& givenCaseToSolve, RunArrangement& arrangedRunSet);
	OptimizationRun(OptimizationCase& givenCaseToSolve, ManagerOfRunArrangement* arrangementManager);
	OptimizationRun(OptimizationCase& givenCaseToSolve, int indexOfArrangementManagerCreator);
	~OptimizationRun();
	OptimizationResult findOptimizedSolution();
};