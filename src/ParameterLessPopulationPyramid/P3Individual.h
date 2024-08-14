#pragma once
#include "../OptimazationTemplates/Individual.h"
#include "../CommonComponents/HillClimbers/GreedyHillClimber.h"
#include "../CommonComponents//Randomizers/Mt19937Randomizer.h"

class HashGetterOfP3Individual;
class EqualityCheckerOfP3Individual;

class P3Individual: public Individual
{
	friend class EqualityCheckerOfP3Individual;

	static const unsigned int HASH_ADDITION_ELEMENT = 0x9e3779b9;
	static const unsigned int HASH_LEFT_SHIFT_DEGREE = 6;
	static const unsigned int HASH_RIGHT_SHIFT_DEGREE = 2;

	unsigned int memoizedHash;
	bool wasHashEvaluated;

	unsigned int combineHashes(unsigned int accumulatedHash, unsigned int partialHash);
	unsigned int calculateHash();
	void memoizeHash(int calculatedHash);

protected:

	void registerChangesInGenotype() override;

public:

	P3Individual(OptimazationCase& evaluator);
	P3Individual(const P3Individual& other);
	bool operator==(const P3Individual& other) const;
	unsigned int getHash();
	void updateHash();
	void greedilyOptimize();
	void greedilyOptimize(GreedyHillClimber& hillClimberToUse);
	ResultOfCrossover* crossover(Individual& donorOfGens, ParametersOfCrossover& crossoverParameters) override;
	Individual* clone() override;
	Randomizer& getDefaultRandomizer() override;
};


class HashGetterOfP3Individual
{
public:
	unsigned int  operator()(P3Individual* const & individualInstance) const 
	{
		return individualInstance->getHash();
	}
};

class EqualityCheckerOfP3Individual
{
public:
	bool operator () (P3Individual const* firstIndividual, P3Individual const* secondIndividual) const 
	{
		return *firstIndividual == *secondIndividual;
	}
};