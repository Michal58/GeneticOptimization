#pragma once
#include "GenesFrequenciesLookup.h"
#include "../CommonComponents/Clusterization/DistancesLookup.h"
#include "GeneIndexCluster.h"

class EntropyBasedInitializer: public InitializerOfDistancesLookup
{
	const static int ENTROPY_MINUEND = 2;

	OptimazationCase& caseToSolve;
	GenesFrequenciesLookup& frequenciesOfGenesLookup;

	void createSingletonClusters(DistancesLookup& distancesToInitialize);
	void fillDistancesWithFirstIndexOfSequenceAlwaysSmallerThanSecond(int firstIndexOfLeafInSequence, std::vector<Cluster*>& sequenceOfClusters, DistancesLookup& distancesToInitialize);
	void initializeMapOfDistances(DistancesLookup& distancesToInitialize);
	double getProbabilityFromSetOfGenesFrequency(int setOfGenesFrequency);
	std::vector<GenesPairInGenotype> getCartesianProductOfGenes(GeneIndexCluster& firstLeafAsGeneRepresentation, GeneIndexCluster& secondLeafAsGeneRepresentation);
	void updateEntropySum(double& currentSum, int frequencyOfElement);
	double calculateEntropy(GeneIndexCluster& leaf);
	double calculateEntropy(ClustersPair pairOfLeaves);
	double calculateDistanceBetweenTwoClusterLeaves(ClustersPair basePairForCalculation);

public:

	EntropyBasedInitializer(OptimazationCase& caseToSolve, GenesFrequenciesLookup& frequenciesOfGenesLookup);
	void setFrequenciesOfGenesLookup(GenesFrequenciesLookup& frequenciesOfGenesLookup);
	void initializeDistancesLookup(DistancesLookup& distancesToInitialize) override;
};
