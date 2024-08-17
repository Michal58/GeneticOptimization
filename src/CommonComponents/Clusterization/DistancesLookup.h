#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Cluster.h"
#include "../Hashing/ObjectBaseHasher.h"

#define DISTANCE_DOESNT_EXIST_ERROR_MESSAGE "Distance doesn't exist"

struct ClustersPair: public Hashable
{
	Cluster& firstCluster;
	Cluster& secondCluser;

	ClustersPair(Cluster& firstCluster, Cluster& secondCluster);

	unsigned int calculateHash() override;
	bool equals(const Hashable& other) const override;
};

class InitializerOfDistancesLookup
{
public:
	virtual void initializeDistancesLookup(DistancesLookup& distancesToInitialize) = 0;
};

using ClustersSet = std::unordered_set<Cluster*, PointerBaseHasher<Cluster>, PointerBaseHashablesComparator<Cluster>>;

class DistancesLookup
{
	friend class InitializerOfDistancesLookup;

	using ClusterPairsToDistances = std::unordered_map<ClustersPair, double, ObjectBaseHasher<ClustersPair>, ObjectBaseHashablesComparator<ClustersPair>>;

	ClustersSet allSingleClusters;			// we aren't responsible for clusters deallocation in this case
	ClusterPairsToDistances distancesMap;	

	bool isThereClusterPair(ClustersPair pairToCheck);
	Cluster* mergeClusters(const Cluster& firstToMerge, const Cluster& secondToMerge);
	double calculateCkDistanceToCiCjUnion(Cluster& Ck, Cluster& Ci, Cluster& Cj);
	void mapDistanceToMergedCluster(Cluster* distanceCalculationParticipant,Cluster* mergedCluster, Cluster& firstMergeMember, Cluster& secondMergeMember);
	void removeClusterFromDistances(Cluster& toRemove);
	void updateDistancesToMergedCluster(Cluster* mergedCluster, Cluster& firstMergeMember, Cluster& secondMergeMember);

public:

	DistancesLookup(InitializerOfDistancesLookup& initializer);
	double getDistance(Cluster& first, Cluster& second);
	double getDistance(ClustersPair pair);
	Cluster* replaceClustersByMergedClusterAndReturnIt(Cluster& firstToMerge, Cluster& secondToMerge);
	ClustersSet& shareAllSingleClusters();
	void putIntoContainerPairsAssociatedWithCluster(std::vector<ClustersPair> container, Cluster* clusterToAssociate);
	std::vector<ClustersPair> getKeysOfMap();
	int allClustersCardinality();
};

