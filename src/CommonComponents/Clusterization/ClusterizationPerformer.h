#pragma once
#include "Cluster.h"
#include "DistancesLookup.h"
#include "SelectorsOfClusterMerging/SelectorOfClustersMerging.h"

class ClusterizationPerformer
{
	SelectorOfClustersMerging& clustersToMergeSelector;

public:

	ClusterizationPerformer(SelectorOfClustersMerging& clustersToMergeSelector);
	std::vector<Cluster*>* performClusterization(DistancesLookup& distances, bool removeClustersWithZeroDistances);
};

