#pragma once
#include "../OptimazationTemplates/Individual.h"
#include "../CommonComponents/Functionalities/Functionalities.h"
#include "../CommonComponents/Clusterization/ClusterizationPerformer.h"
#include "../CommonComponents/Clusterization/SelectorsOfClusterMerging/MinHeapBasedSelector.h"
#include "P3Individual.h"
#include "GenesFrequenciesLookup.h"
#include "EntropyBasedDistancesInitializer.h"
#define ERROR_IN_CLUSTERIZATION_PROCESS_ASSUMPTION "There's no cluster representing union of all singletion clusters"

class ClusterSizeComparator
{
public:
	bool operator()(Cluster* first, Cluster* second) const;
};

class PopulationLevel
{
	const static int DEFAULT_POPULATION_SIZE = 1;

	OptimazationCase& caseToOptimize;

	std::vector<P3Individual*> population;
	GenesFrequenciesLookup populationGenesFrequenciesLookup;

	std::vector<Cluster*>* estimatedGenesClusters;

	void updateClusterizationAndFrequencies(P3Individual* newIndividual);
	void orderClustersWithSizeAscending();
	void removeClusterWithCardinalityOfGenotype();
	void conductClusterization(ClusterizationPerformer& clusterizationExecutor, DistancesLookup& clustersDistancesLookup);

public:

	PopulationLevel(OptimazationCase& caseToOptimize);
	~PopulationLevel();
	void addIndividual(P3Individual* newIndividual);
	std::vector<Cluster*>& shareClusters();
	std::vector<int> getShuffledIndiciesOfIndividualsInPopulation();
	P3Individual* getSomeIndividual();
	P3Individual& getIndividualFromIndex(int index);
};

