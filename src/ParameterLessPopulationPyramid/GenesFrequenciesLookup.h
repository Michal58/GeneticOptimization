#pragma once
#include <iostream>
#include <unordered_map>
#include "P3Individual.h"
#include "../CommonComponents/Functionalities/Functionalities.h"
#include "../CommonComponents/Hashing/PointerBaseHasher.h"

struct GeneInGenotype
{
	static const int INVALID_INDEX = -1;
	static const int ANY_VALUE = -1;

	int indexInGenotype;
	int genValue;

	GeneInGenotype(int indexInGenotype, int genValue);
	bool operator==(const GeneInGenotype& other) const;
};

struct GenesPairInGenotype: public Hashable
{
	static const int COUNT_OF_BASE_ELEMENTS = 4;

	GeneInGenotype firstGenWithItsIndex;
	GeneInGenotype secondGenWithItsIndex;

	GenesPairInGenotype();
	GenesPairInGenotype(GeneInGenotype firstGenWithItsIndex, GeneInGenotype secondGenWithItsIndex);
	GenesPairInGenotype(int firstIndexInGenotype, int firstGenValue, int secondIndexInGenotype, int secondGenValue);

	unsigned int calculateHash() const override;
	bool equals(const Hashable& other) const override;
};

class GenesFrequenciesLookup
{
	using LookupStructure = std::unordered_map<GenesPairInGenotype*, int, PointerBaseHasher<GenesPairInGenotype>, PointerBaseHasher<GenesPairInGenotype>>;

	static const int INITIAL_FREQUENCY = 0;

	LookupStructure* genesFrequenciesMapping;
	int countOfConsideredGenotypes;

	bool isThereGenesPairRegistered(GenesPairInGenotype unionOfGens);
	void initializeFrequencyWithNewPair(GenesPairInGenotype* pairToMap);
	void updateFrequencyWithPair(GenesPairInGenotype pairToUpdateFrequency);
	void updateFrequenciesKeepingFirstIndexOfMappingPairNotBiggerThanSecond(GenesPairInGenotype mappingPair, P3Individual& recentlyAddedIndividual);

	void deleteMappingPairs();

public:

	GenesFrequenciesLookup();
	~GenesFrequenciesLookup();

	int getCountOfConsideredGenotypes();

	int getFrequencyOfSingleGenInGenotypes(GeneInGenotype genAndItsIndex);
	int getFrequencyOfGenesPairInGenotypes(GenesPairInGenotype unionOfGens);

	void updateWithIndividual(P3Individual& recentlyAddedIndividual);
};

using PairwiseGeneValueFrequencies = GenesFrequenciesLookup;

