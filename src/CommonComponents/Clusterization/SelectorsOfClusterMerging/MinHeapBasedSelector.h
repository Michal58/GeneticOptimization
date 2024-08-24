#pragma once
#include "SelectorOfClustersMerging.h"
#include <queue>

class MinHeapBasedSelector;

class HeapNodeOfClusterPair
{
	ClustersPair associatedPair;
	MinHeapBasedSelector* associatedSelector;

public:

	HeapNodeOfClusterPair(ClustersPair associatedPair, MinHeapBasedSelector& associatedSelector);
	ClustersPair getPair() const;
	double getPairDistance();
	bool operator==(const HeapNodeOfClusterPair& other) const;
};

class ComparatorOfClustersPair
{
public:
	bool operator()(HeapNodeOfClusterPair firstNode, HeapNodeOfClusterPair secondNode);
};

class MinHeapBasedSelector: public SelectorOfClustersMerging
{
	std::priority_queue<HeapNodeOfClusterPair, std::vector<HeapNodeOfClusterPair>, ComparatorOfClustersPair> minHeapOfPairs;
	ClustersSet removedClusters;

	bool isClusterRemoved(Cluster& toCheckIfIsRemoved);
	bool isAnyOfTheClustersRemoved(ClustersPair pair);
	void markClustersAsRemoved(ClustersPair pair);

public:

	DistancesLookup& getAssociatedLookup();
	void setAssociatedLookup(DistancesLookup& associatedLookup) override;
	void selectClustersForMerging(Cluster*& firstSelectedClusterContainer, Cluster*& secondSelectedClusterContainer) override;
	void updateWithMergedCluster(Cluster* mergedCluster) override;
};

