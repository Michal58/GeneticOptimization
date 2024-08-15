#pragma once
#include <iostream>
#include <unordered_map>
#include "P3Individual.h"
#include "../CommonComponents/Functionalities/Functionalities.h"
#include "../CommonComponents/Hashing/PointerBaseHasher.h"

struct GenInGenotype
{
	int indexInGenotype;
	int genValue;

	GenInGenotype(int indexInGenotype, int genValue);
	bool operator==(const GenInGenotype& other) const;
};

struct GenesPairInGenotype: public Hashable
{
	static const int COUNT_OF_BASE_ELEMENTS = 4;

	GenInGenotype firstGenWithItsIndex;
	GenInGenotype secondGenWithItsIndex;

	GenesPairInGenotype(GenInGenotype firstGenWithItsIndex, GenInGenotype secondGenWithItsIndex);
	GenesPairInGenotype(int firstIndexInGenotype, int firstGenValue, int secondIndexInGenotype, int secondGenValue);

	unsigned int calculateHash() override;
	bool equals(const Hashable& other) const override;
};

class GenesFrequenciesLookup
{
	using LookupStructure = std::unordered_map<GenesPairInGenotype*, int, PointerBaseHasher<GenesPairInGenotype>, PointerBaseHasher<GenesPairInGenotype>>;

	static const int INITIAL_FREQUENCY = 0;

	LookupStructure* genesFrequenciesMapping;
	bool isThereGenesPairRegistered(GenesPairInGenotype unionOfGens);
	void initializeFrequencyWithNewPair(GenesPairInGenotype* pairToMap);
	void updateFrequencyWithPair(GenesPairInGenotype pairToUpdateFrequency);
	void updateFrequenciesKeepingFirstIndexOfMappingPairNotBiggerThanSecond(GenesPairInGenotype mappingPair, P3Individual& recentlyAddedIndividual);

	void deleteMappingPairs();

public:

	GenesFrequenciesLookup();
	~GenesFrequenciesLookup();

	int getFrequencyOfSingleGenInGenotypes(GenInGenotype genAndItsIndex);
	int getFrequencyOfGenesPairInGenotypes(GenesPairInGenotype unionOfGens);

	void updateWithIndividual(P3Individual& recentlyAddedIndividual);
};

using PairwiseGeneValueFrequencies = GenesFrequenciesLookup;

