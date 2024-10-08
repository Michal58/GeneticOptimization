#include "ClassicalIndividual.h"

PairOfIndividuals::PairOfIndividuals(ClassicalIndividual* individual1, ClassicalIndividual* individual2)
{
	this->individual1 = individual1;
	this->individual2 = individual2;
}

PairOfIndividuals::PairOfIndividuals(const PairOfIndividuals& other)
{
	individual1 = other.individual1;
	individual2 = other.individual2;
}

ClassicalIndividual* PairOfIndividuals::getFitterIndividual()
{
	if (individual1->evaluateFitness() >= individual2->evaluateFitness())
		return individual1;
	else
		return individual2;
}

ClassicalIndividual::ClassicalIndividual(OptimizationCase& evaluator) :Individual(evaluator) {}

ClassicalIndividual::ClassicalIndividual(const ClassicalIndividual& other): Individual(other) {}

void ClassicalIndividual::tryToMutateAllGensRandomly(double chanceForGenMutation)
{
	for (int i = 0; i < genotype->size(); i++)
	{
		double diceRoll = Mt19937Randomizer::getSingletonInstance()->chanceRand();

		if (diceRoll <= chanceForGenMutation)
			randomlyMutateGen(i);
	}
}

ClassicalIndividual** ClassicalIndividual::generateMutantsOverGen(int genIndex, int& containerOfSizeOfArrayLength)
{
	int valuesRange = evaluator.getCountOfDomainValues(genIndex);
	ClassicalIndividual** mutantsArray = new ClassicalIndividual * [valuesRange - 1];
	for (int i = 0; i < (*genotype)[genIndex]; i++)
	{
		mutantsArray[i] = new ClassicalIndividual(*this);
		mutantsArray[i]->genotype->at(genIndex) = i;
	}
	for (int i = (*genotype)[genIndex] + 1; i < valuesRange; i++)
	{
		mutantsArray[i - 1] = new ClassicalIndividual(*this);
		mutantsArray[i - 1]->genotype->at(genIndex) = i;
	}

	containerOfSizeOfArrayLength = valuesRange - 1;

	return mutantsArray;
}

PairOfIndividuals ClassicalIndividual::crossover(ClassicalIndividual* const partner, int exclusiveCutIndex)
{
	ClassicalIndividual* firstChild = new ClassicalIndividual(this->evaluator);
	ClassicalIndividual* secondChild = new ClassicalIndividual(this->evaluator);


	for (int i = 0; i < exclusiveCutIndex; i++)
	{
		firstChild->genotype->at(i) = partner->genotype->at(i);
		secondChild->genotype->at(i) = genotype->at(i);
	}

	for (int i = exclusiveCutIndex; i < genotype->size(); i++)
	{
		firstChild->genotype->at(i) = genotype->at(i);
		secondChild->genotype->at(i) = partner->genotype->at(i);
	}

	return PairOfIndividuals(firstChild, secondChild);
}

void ClassicalIndividual::randomlyMutateGen(int genIndex)
{
	int diceRoll= Mt19937Randomizer::getSingletonInstance()->randInRange(evaluator.getCountOfDomainValues(genIndex));
	mutateGene(genIndex, diceRoll);
}

ResultOfCrossover* ClassicalIndividual::crossover(Individual& donorOfGens, ParametersOfCrossover& crossoverParameters)
{
	int exclusiveCutIndex = ((CutIndex*)(&crossoverParameters))->exclusiveCutIndex;
	PairOfIndividuals crossoverResult = crossover((ClassicalIndividual*)(&donorOfGens), exclusiveCutIndex);
	ResultOfCrossover* pairOfIndividualsAsFinalResult = new PairOfIndividuals(crossoverResult);
	return pairOfIndividualsAsFinalResult;
}

Individual* ClassicalIndividual::clone()
{
	return new ClassicalIndividual(*this);
}

Randomizer& ClassicalIndividual::getDefaultRandomizer()
{
	return *Mt19937Randomizer::getSingletonInstance();
}

CutIndex::CutIndex(int exclusiveCutIndex)
{
	this->exclusiveCutIndex = exclusiveCutIndex;
}
