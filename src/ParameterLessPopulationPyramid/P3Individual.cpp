#include "P3Individual.h"

// Combining hashed was sourced from Boost library
// https://www.boost.org/LICENSE_1_0.txt

unsigned int P3Individual::combineHashes(unsigned int accumulatedHash, unsigned int partialHash)
{
	return accumulatedHash
		^(partialHash
		+ HASH_ADDITION_ELEMENT
		+ (accumulatedHash << HASH_LEFT_SHIFT_DEGREE)
		+ (accumulatedHash >> HASH_RIGHT_SHIFT_DEGREE));
}

unsigned int P3Individual::calculateHash()
{
	std::hash<int> hashingFunction;
	unsigned int accumulatedHash = hashingFunction(genotype->at(0));
	for (int i = 1; i < genotype->size(); i++)
	{
		unsigned int partialHash = hashingFunction(genotype->at(i));
		accumulatedHash = combineHashes(accumulatedHash, partialHash);
	}

	return accumulatedHash;
}

void P3Individual::memoizeHash(int calculatedHash)
{
	memoizedHash = calculatedHash;
	wasHashEvaluated = true;
}

void P3Individual::registerChangesInGenotype()
{
	Individual::registerChangesInGenotype();
	wasHashEvaluated = false;
}

P3Individual::P3Individual(OptimazationCase& evaluator):
	Individual(evaluator),
	wasHashEvaluated(false) {}

P3Individual::P3Individual(const P3Individual& other):
	Individual(other),
	memoizedHash(other.memoizedHash),
	wasHashEvaluated(other.wasHashEvaluated) {}

bool P3Individual::operator==(const P3Individual& other) const
{
	return *genotype==*other.genotype;
}

unsigned int P3Individual::getHash()
{
	updateHash();
	return memoizedHash;
}

void P3Individual::updateHash()
{
	if (!wasHashEvaluated)
		memoizeHash(calculateHash());
}

void P3Individual::greedilyOptimize()
{
	greedilyOptimize(GreedyHillClimber(*this, true, GreedyHillClimber::CONFIRMATION));
}

void P3Individual::greedilyOptimize(GreedyHillClimber& hillClimberToUse)
{
	hillClimberToUse.setIndividualToOptimize(*this, false);
	hillClimberToUse.optimizeIndividual();
}

ResultOfCrossover* P3Individual::crossover(Individual& donorOfGens, ParametersOfCrossover& crossoverParameters)
{
	return nullptr;
}

Individual* P3Individual::clone()
{
	return new P3Individual(*this);
}

Randomizer& P3Individual::getDefaultRandomizer()
{
	return *Mt19937Randomizer::getSingletonInstance();
}
