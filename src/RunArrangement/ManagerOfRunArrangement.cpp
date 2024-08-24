#include "ManagerOfRunArrangement.h"

void ManagerOfRunArrangement::createRunArrangement()
{
	arrangedStopCriterion = createStopCriterion();
	arrangedOptimizer = createGeneticOptimizer();
	createdRunArrangement = new RunArrangement(*arrangedOptimizer, *arrangedStopCriterion);
}

void ManagerOfRunArrangement::createRunArrangement(StopCriterion* arrangedStopCriterion, GeneticOptimizer* arrangedOptimizer)
{
	this->arrangedStopCriterion = arrangedStopCriterion;
	this->arrangedOptimizer = arrangedOptimizer;
}

ManagerOfRunArrangement::ManagerOfRunArrangement(OptimizationCase& givenCaseToSolve) :
	givenCaseToSolve(givenCaseToSolve)
{
	this->createdRunArrangement = nullptr;
	this->arrangedStopCriterion = nullptr;
	this->arrangedOptimizer = nullptr;
}

ManagerOfRunArrangement::~ManagerOfRunArrangement()
{
	delete createdRunArrangement;
	delete arrangedStopCriterion;
	delete arrangedOptimizer;
}

RunArrangement& ManagerOfRunArrangement::shareRunArrangement()
{
	if (createdRunArrangement == nullptr)
		createRunArrangement();
	return *createdRunArrangement;
}