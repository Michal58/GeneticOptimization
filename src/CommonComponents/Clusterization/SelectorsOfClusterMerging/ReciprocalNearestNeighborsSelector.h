#pragma once
#include "SelectorOfClustersMerging.h"

class ReciprocalNearestNeighborsSelector: public SelectorOfClustersMerging
{
	static const int LAST_BUT_ONE_OFFSET = 2;

	ClustersSet* singleClustersOutOfSeries;
	std::vector<Cluster*> seriesOfClustersWithDescendingDistances;

	Cluster* getLastButOneSeriesElement();
	Cluster* findClusterInSingleClustersWhichMakesTheClosestDistanceWithLastElementOfSeries();
	void moveToSeriesClusterFromSingleClusters(Cluster* toExpandSeries);
	bool findIfAddingClusterFromSingleClusterKeepsDescendingOrderOfSeries(Cluster* theBestClusterFoundInSingleClusters);

public:

	ReciprocalNearestNeighborsSelector();
	~ReciprocalNearestNeighborsSelector();
	void setAssociatedLookup(DistancesLookup& associatedLookup) override;
	void selectClustersForMerging(Cluster*& fitsSelectedClusterContainer, Cluster*& secondSelectedClusterContainer) override;
	void updateWithMergedCluster(Cluster* mergedCluster) override;
};

