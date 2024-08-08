#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "../OptimazationTemplates/OptimazationCase.h"
#include "../OptimazationTemplates/Individual.h"
#include "Mt19937Randomizer.h"

class ClassicalIndividual;

class PairOfIndividuals:public ResultOfCrossover
{
public:

	PairOfIndividuals(ClassicalIndividual* inividual1, ClassicalIndividual* individual2);
	PairOfIndividuals(const PairOfIndividuals& other);

	//here's deliberately no destructor

	ClassicalIndividual* individual1;		//pointer on the heap
	ClassicalIndividual* individual2;		//pointer on the heap

	ClassicalIndividual* getFitterIndividual();
};

class CutIndex : public ParametersOfCrossover 
{

public:

	CutIndex(int exclusiveCutIndex);
	int exclusiveCutIndex;
};

class ClassicalIndividual:public Individual
{
public:

	ClassicalIndividual(OptimazationCase& evaluator);
	ClassicalIndividual(const ClassicalIndividual& other);

	void tryToMutateAllGensRandomly(double chanceForGenMutation);

	ClassicalIndividual** generateMutatntsOverGen(int genIndex, int& sizeOfArrayLengthContainer);


	void randomlyMutateGen(int genIndex);
	void fillAllGensRandomly();
	int getSizeOfGenotype();

	int getDomainSize(int index);

	void copyGenotypeToContainer(std::vector<int>& container);

	PairOfIndividuals crossover(ClassicalIndividual* const partner, int exclusiveCutIndex);
	ResultOfCrossover* crossover(Individual& donorOfGens, ParametersOfCrossover& crossoverParameters) override;
	Individual* clone() override;
};

