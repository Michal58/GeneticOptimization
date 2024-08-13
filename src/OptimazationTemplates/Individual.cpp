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

void Individual::memoizeFitness(double newFitness)
{
	memoizedFitness = newFitness;
	wasEvaluated = true;
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

int Individual::getSizeOfGenotype()
{
	return genotype->size();
}

void Individual::fillAllGensRandomly()
{
	fillAllGensRandomly(getDefaultRandomizer());
}

void Individual::fillAllGensRandomly(Randomizer& randomGenerator)
{
	registerChangesInGenotype();

	genotype->resize(evaluator.getCountOfDimensions());

	for (int iDomain = 0; iDomain < genotype->size(); iDomain++)
	{
		int diceRoll = randomGenerator.randInRange(evaluator.getCountOfDomainValues(iDomain));
		int genToFill = evaluator.getDomain(iDomain)->next(diceRoll);
		mutateGen(iDomain, genToFill);
	}
}

int Individual::getGenAt(int index)
{
	return genotype->at(index);
}

double Individual::evaluateFitness()
{
	if (!wasEvaluated)
		memoizeFitness(evaluator.evaluateFitness(*genotype));

	return memoizedFitness;
}

bool Individual::isFitnessEvaluated()
{
	return wasEvaluated;
}

void Individual::forcelyMemoizeFitness(double newFitness)
{
	memoizeFitness(newFitness);
}

std::vector<int>* Individual::copyGenotype()
{
	return new std::vector<int>(*genotype);
}

OptimazationCase& Individual::getOptimazationCase()
{
	return evaluator;
}

int Individual::getCountOfValuesAt(int index)
{
	return evaluator.getCountOfDomainValues(index);
}

std::unique_ptr<DomainIterator> Individual::getDomain(int indexOfDimension)
{
	return evaluator.getDomain(indexOfDimension);
}
