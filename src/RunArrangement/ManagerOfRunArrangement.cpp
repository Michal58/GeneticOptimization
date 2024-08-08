#include "ManagerOfRunArrangement.h"

void ManagerOfRunArrangement::createRunArrangement()
{
	arrangedStopCriterium = createStopCriterium();
	arrangedOptimizer = createGeneticOptimizer();
	createdRunArrangement = new RunArrangement(*arrangedOptimizer, *arrangedStopCriterium);
}

void ManagerOfRunArrangement::createRunArrangement(StopCriterium* arrangedStopCriterium, GeneticOptimizer* arrangedOptimizer)
{
	this->arrangedStopCriterium = arrangedStopCriterium;
	this->arrangedOptimizer = arrangedOptimizer;
}

ManagerOfRunArrangement::ManagerOfRunArrangement(OptimazationCase& givenCaseToSolve) :
	givenCaseToSolve(givenCaseToSolve)
{
	this->createdRunArrangement = nullptr;
	this->arrangedStopCriterium = nullptr;
	this->arrangedOptimizer = nullptr;
}

ManagerOfRunArrangement::~ManagerOfRunArrangement()
{
	delete createdRunArrangement;
	delete arrangedStopCriterium;
	delete arrangedOptimizer;
}

RunArrangement& ManagerOfRunArrangement::shareRunArrangement()
{
	if (createdRunArrangement == nullptr)
		createRunArrangement();
	return *createdRunArrangement;
}