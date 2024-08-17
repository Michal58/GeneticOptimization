#pragma once
#include "SelectorOfClustersMerging.h"

class ReciprocalNearestNeighborsSelector: public SelectorOfClustersMerging
{
	static const int LAST_BUT_ONE_OFFSET = 2;

	ClustersSet* singleClusters;
	std::vector<Cluster*> seriesOfClustersWithDescendingDistances;

	Cluster* findClusterInSingleClustersWhichMakesTheClosestDistanceWithLastElementOfSeries();

public:

	ReciprocalNearestNeighborsSelector();
	~ReciprocalNearestNeighborsSelector();
	void setAssociatedLookup(DistancesLookup& associatedLookup) override;
	void selectClustersForMerging(Cluster*& fitsSelectedClusterContainer, Cluster*& secondSelectedClusterContainer) override;
	void updateWithNewCluster(Cluster* newCluster) override;
};

