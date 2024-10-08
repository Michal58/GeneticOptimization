#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include "Cluster.h"
#include "../Hashing/ObjectBaseHasher.h"

#define DISTANCE_DOESNT_EXIST_ERROR_MESSAGE "Distance doesn't exist"

class InitializerOfDistancesLookup;

class ClustersPair: public Hashable
{
	Cluster* firstCluster;
	Cluster* secondCluster;

public:

	ClustersPair();
	ClustersPair(Cluster& firstCluster, Cluster& secondCluster);

	Cluster& first();
	Cluster& second();
	unsigned int calculateHash() const override;
	bool equals(const Hashable& other) const override;
};

using ClustersSet = std::unordered_set<Cluster*, PointerBaseHasher<Cluster>, PointerBaseHashablesComparator<Cluster>>;
using ClusterPairsToDistances = std::unordered_map<ClustersPair, double, ObjectBaseHasher<ClustersPair>, ObjectBaseHashablesComparator<ClustersPair>>;

class DistancesLookup
{
	friend class InitializerOfDistancesLookup;

	ClustersSet allSingleClusters;			// we aren't responsible for clusters deallocation in this case
	ClusterPairsToDistances distancesMap;	

	bool isThereClusterPair(ClustersPair pairToCheck);
	Cluster* mergeClusters(const Cluster& firstToMerge, const Cluster& secondToMerge);
	double calculateCkDistanceToCiCjUnion(Cluster& Ck, Cluster& Ci, Cluster& Cj);
	void mapDistanceToMergedCluster(Cluster* distanceCalculationParticipant,Cluster* mergedCluster, Cluster& firstMergeMember, Cluster& secondMergeMember);
	void removePairsWithClusterFromDistances(Cluster& toRemove);
	void updateDistancesToMergedCluster(Cluster* mergedCluster, Cluster& firstMergeMember, Cluster& secondMergeMember);

public:

	DistancesLookup(InitializerOfDistancesLookup& initializer);
	double getDistance(Cluster& first, Cluster& second);
	double getDistance(ClustersPair pair);
	Cluster* replaceClustersByMergedClusterAndReturnIt(Cluster& firstToMerge, Cluster& secondToMerge);
	ClustersSet& shareAllSingleClusters();
	void putIntoContainerPairsAssociatedWithCluster(std::vector<ClustersPair>& container, Cluster* clusterToAssociate);
	std::vector<ClustersPair> getKeysOfMap();
	int allClustersCardinality();
};


class InitializerOfDistancesLookup
{
protected:

	ClustersSet& accessSingleClusters(DistancesLookup& lookupToAccess);
	ClusterPairsToDistances& accessDistancesMap(DistancesLookup& lookupToAccess);

public:
	virtual void initializeDistancesLookup(DistancesLookup& distancesToInitialize) = 0;
};