#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Cluster.h"
#include "../Hashing/ObjectBaseHasher.h"

#define DISTANCE_DOESNT_EXIST_ERROR_MESSAGE "Distance doesn't exist"

struct ClustersPair: public Hashable
{
	const Cluster& firstCluster;
	const Cluster& secondCluser;

	ClustersPair(const Cluster& firstCluster, const Cluster& secondCluster);

	unsigned int calculateHash() override;
	bool equals(const Hashable& other) const override;
};

class InitializerOfDistancesLookup
{
public:
	virtual void initializeDistancesLookup(DistancesLookup& distancesToInitialize) = 0;
};

class DistancesLookup
{
	friend class InitializerOfDistancesLookup;
	using ClusterPairsToDistances = std::unordered_map<ClustersPair, double, ObjectBaseHasher<ClustersPair>, ObjectBaseHashablesComparator<ClustersPair>>;

	ClusterPairsToDistances distancesMap;

	bool isThereClusterPair(ClustersPair pairToCheck);

public:

	DistancesLookup(InitializerOfDistancesLookup& initializator);
	double getDistance(const Cluster& first, const Cluster& second);
	void addCluster(const Cluster& unionOfFirstAndSecond, const Cluster& first, const Cluster& second);
};

