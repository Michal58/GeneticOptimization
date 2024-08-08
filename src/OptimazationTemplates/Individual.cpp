#include "Individual.h"

void Individual::registerChangesInGenotype()
{
	memoizedFitness = evaluator.getValueOutOfAllDomains();
	wasEvaluated = false;
}

void Individual::setGenAt(int index, int newGen)
{
	(*genotype)[index] = newGen;
}

void Individual::setEvaluatedFitness(double newEvaluation)
{
	this->memoizedFitness = newEvaluation;
}

double Individual::getEvaluatedFitness()
{
	return memoizedFitness;
}

Individual::Individual(OptimazationCase& evaluator):
	evaluator(evaluator)
{
	genotype = new std::vector<int>(evaluator.getCountOfDimensions());
	wasEvaluated = false;
	memoizedFitness = evaluator.getValueOutOfAllDomains();
}

Individual::Individual(const Individual& other):
	evaluator(other.evaluator),
	wasEvaluated(other.wasEvaluated),
	memoizedFitness(other.memoizedFitness)
{
	this->genotype = new std::vector<int>(*other.genotype);
}

Individual::~Individual()
{
	delete genotype;
}

void Individual::moveContentTo(Individual& other)
{
	other.evaluator = evaluator;
	other.wasEvaluated = wasEvaluated;
	other.memoizedFitness = memoizedFitness;
	other.genotype = genotype;
}

int Individual::peekGen(int index)
{
	return (*genotype)[index];
}

void Individual::mutateGen(int index, int newGen)
{
	registerChangesInGenotype();
	setGenAt(index, newGen);
}

void Individual::fillAllGensRandomly(Randomizer& randomGenerator)
{
	registerChangesInGenotype();

	for (int iDomain = 0; iDomain < genotype->size(); iDomain++)
	{
		int diceRoll = randomGenerator.randInRange(evaluator.getCountOfDomainValues(iDomain));
		(*genotype)[iDomain] = evaluator.getDomain(iDomain)->next(diceRoll);
	}
}

double Individual::evaluateFitness()
{
	if (wasEvaluated)
		return memoizedFitness;
	else
	{
		memoizedFitness = evaluator.evaluateFitness(*genotype);
		wasEvaluated = true;
	}
}

bool Individual::isFitnessEvaluated()
{
	return wasEvaluated;
}

std::vector<int>* Individual::copyGenotype()
{
	return new std::vector<int>(*genotype);
}

int Individual::getValuesRangeAt(int index)
{
	return evaluator.getCountOfDomainValues(index);
}
