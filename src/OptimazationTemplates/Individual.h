#pragma once

#include "OptimazationCase.h"
#include "Randomizer.h"
#include <iostream>
#include <vector>

class ParametersOfCrossover {
};

class ResultOfCrossover {
};

const ParametersOfCrossover INITIAL_CROSSOVER_PARAMETERS;

class Individual
{
protected:

	friend class OptimazationCase;

	OptimazationCase& evaluator;

	bool wasEvaluated;
	double memoizedFitness;

	std::vector<int>* genotype;

	void registerChangesInGenotype();
	virtual void setGenAt(int index, int newGen);
	virtual void setEvaluatedFitness(double newEvaluation);
	virtual double getEvaluatedFitness();

public:

	Individual(OptimazationCase& evaluator);
	Individual(const Individual& other);
	virtual ~Individual();

	virtual ResultOfCrossover* crossover(Individual& donorOfGens, ParametersOfCrossover& crossoverParameters) = 0;

	virtual double evaluateFitness();

	virtual Individual* clone() = 0;
	virtual void moveContentTo(Individual& other);

	virtual int peekGen(int index);
	virtual void mutateGen(int index, int newGen);

	virtual int getValuesRangeAt(int index);
	virtual void fillAllGensRandomly(Randomizer& randomGenerator);

	bool isFitnessEvaluated();

	std::vector<int>* copyGenotype();
};
