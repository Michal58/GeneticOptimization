#include "GenesFrequenciesLookup.h"

GeneInGenotype::GeneInGenotype(int indexInGenotype, int genValue):
	indexInGenotype(indexInGenotype),
	genValue(genValue) {}

bool GeneInGenotype::operator==(const GeneInGenotype& other) const
{
	return this->genValue == other.genValue
		&& this->indexInGenotype == other.indexInGenotype;
}

GenesPairInGenotype::GenesPairInGenotype() :
	firstGenWithItsIndex(GeneInGenotype::INVALID_INDEX, GeneInGenotype::ANY_VALUE),
	secondGenWithItsIndex(GeneInGenotype::INVALID_INDEX, GeneInGenotype::ANY_VALUE) {}

GenesPairInGenotype::GenesPairInGenotype(GeneInGenotype firstGenWithItsIndex, GeneInGenotype secondGenWithItsIndex):
	Hashable(false),
	firstGenWithItsIndex(firstGenWithItsIndex),
	secondGenWithItsIndex(secondGenWithItsIndex) {}

GenesPairInGenotype::GenesPairInGenotype(int firstIndexInGenotype, int firstGenValue, int secondIndexInGenotype, int secondGenValue):
	GenesPairInGenotype
	(
		GeneInGenotype(firstIndexInGenotype,firstGenValue)
		,GeneInGenotype(secondIndexInGenotype, secondGenValue)
	) {}

bool GenesPairInGenotype::equals(const Hashable& other) const
{
	if (!isInstanceOf<GenesPairInGenotype>(&other))
		return false;

	GenesPairInGenotype& otherGenesPair = (GenesPairInGenotype&)other;
	return this->firstGenWithItsIndex == otherGenesPair.firstGenWithItsIndex
		&& this->secondGenWithItsIndex == otherGenesPair.secondGenWithItsIndex;
}

unsigned int GenesPairInGenotype::calculateHash() const
{
	std::vector<int> valuesToHash = 
	{
		firstGenWithItsIndex.genValue,
		secondGenWithItsIndex.genValue,
		firstGenWithItsIndex.indexInGenotype,
		secondGenWithItsIndex.indexInGenotype
	};

	unsigned int hashValue = Hashable::calculateHashOfVectorOfElementaryTypes(valuesToHash);

	return hashValue;
}

bool GenesFrequenciesLookup::isThereGenesPairRegistered(GenesPairInGenotype unionOfGens)
{
	return genesFrequenciesMapping->find(&unionOfGens) != genesFrequenciesMapping->end();
}

void GenesFrequenciesLookup::initializeFrequencyWithNewPair(GenesPairInGenotype* pairToMap)
{
	genesFrequenciesMapping->insert({ pairToMap, INITIAL_FREQUENCY });
}

void GenesFrequenciesLookup::updateFrequencyWithPair(GenesPairInGenotype pairToUpdateFrequency)
{
	(*genesFrequenciesMapping)[&pairToUpdateFrequency]++;
}

void GenesFrequenciesLookup::updateFrequenciesKeepingFirstIndexOfMappingPairNotBiggerThanSecond(GenesPairInGenotype mappingPair, P3Individual& recentlyAddedIndividual)
{
	int startingIndex = mappingPair.firstGenWithItsIndex.indexInGenotype;
	for (int iGenForPairCreationIndex = startingIndex; iGenForPairCreationIndex < recentlyAddedIndividual.getSizeOfGenotype(); iGenForPairCreationIndex++)
	{
		mappingPair.secondGenWithItsIndex.indexInGenotype = iGenForPairCreationIndex;
		mappingPair.secondGenWithItsIndex.genValue = recentlyAddedIndividual.getGenAt(iGenForPairCreationIndex);

		if (!isThereGenesPairRegistered(mappingPair))
			initializeFrequencyWithNewPair(new GenesPairInGenotype(mappingPair));

		updateFrequencyWithPair(mappingPair);
	}
}

void GenesFrequenciesLookup::deleteMappingPairs()
{
	using MappingPair = std::pair<GenesPairInGenotype* const, int>;
	for (MappingPair& currentPair : (*genesFrequenciesMapping))
		delete currentPair.first;
}

GenesFrequenciesLookup::GenesFrequenciesLookup():
	countOfConsideredGenotypes(0)
{
	genesFrequenciesMapping = new LookupStructure;
}

GenesFrequenciesLookup::~GenesFrequenciesLookup()
{
	deleteMappingPairs();
	delete genesFrequenciesMapping;
}

int GenesFrequenciesLookup::getCountOfConsideredGenotypes()
{
	return countOfConsideredGenotypes;
}

int GenesFrequenciesLookup::getFrequencyOfSingleGenInGenotypes(GeneInGenotype genAndItsIndex)
{
	GenesPairInGenotype unionOfSameElements(genAndItsIndex, genAndItsIndex);
	return getFrequencyOfGenesPairInGenotypes(unionOfSameElements);
}

int GenesFrequenciesLookup::getFrequencyOfGenesPairInGenotypes(GenesPairInGenotype unionOfGens)
{
	if (isThereGenesPairRegistered(unionOfGens))
		return genesFrequenciesMapping->at(&unionOfGens);
	else
		return INITIAL_FREQUENCY;
}

void GenesFrequenciesLookup::updateWithIndividual(P3Individual& recentlyAddedIndividual)
{
	for (int iMainGenIndex = 0; iMainGenIndex < recentlyAddedIndividual.getSizeOfGenotype(); iMainGenIndex++)
	{
		int valueOfMainGen = recentlyAddedIndividual.getGenAt(iMainGenIndex);
		GenesPairInGenotype initialPair(iMainGenIndex, valueOfMainGen, iMainGenIndex, valueOfMainGen);
		updateFrequenciesKeepingFirstIndexOfMappingPairNotBiggerThanSecond(initialPair, recentlyAddedIndividual);
	}

	countOfConsideredGenotypes++;
}

