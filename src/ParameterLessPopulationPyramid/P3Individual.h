#pragma once
#include "../OptimazationTemplates/Individual.h"
#include "../CommonComponents/HillClimbers/GreedyHillClimber.h"
#include "../CommonComponents//Randomizers/Mt19937Randomizer.h"
#include "../CommonComponents/Hashing/Hashable.h"
#include "../CommonComponents/Functionalities/Functionalities.h"

class P3Individual: public Individual, public Hashable
{

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
	unsigned int getHash() override;
	void updateHash();
	bool equals(const Hashable& other) const override;
	void greedilyOptimize();
	void greedilyOptimize(GreedyHillClimber& hillClimberToUse);
	ResultOfCrossover* crossover(Individual& donorOfGens, ParametersOfCrossover& crossoverParameters) override;
	Individual* clone() override;
	Randomizer& getDefaultRandomizer() override;
};
