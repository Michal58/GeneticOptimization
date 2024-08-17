#pragma once
#include "../DistancesLookup.h"

class SelectorOfClustersMerging
{
protected:

	DistancesLookup* associatedLookup;		// not for deletion

public:

	SelectorOfClustersMerging();
	SelectorOfClustersMerging(DistancesLookup& associatedLookup);
	virtual void setAssociatedLookup(DistancesLookup& associatedLookup);
	virtual void selectClustersForMerging(Cluster*& fitsSelectedClusterContainer, Cluster*& secondSelectedClusterContainer) = 0;
	virtual void updateWithNewCluster(Cluster* newCluster) = 0;
};

