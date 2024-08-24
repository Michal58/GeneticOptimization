#pragma once
#include "../CommonComponents/Clusterization/Cluster.h"
#define INVALID_MERGE_CLUSTER_ERROR "Provided cluster to merge isn't valid"
#define THERE_IS_NO_ASSOCIATED_INDEX "There is no associated index - cluster isn't a leaf"

class GeneIndexCluster: public Cluster
{
	const static int INITIAL_DISTINCT_NUMBER = 0;
	static int nextDistinctNumber;

	std::vector<int> representedIndices;

	GeneIndexCluster(int associatedDistinctNumber);

public:
	static void resetDistinctNumbersGeneration();
	static int generateDistinctNumber();

	GeneIndexCluster(int representedIndex, int providedDistinctNumber);
	GeneIndexCluster(const GeneIndexCluster& other);
	Cluster* getCopy() const override;
	int cardinality() override;
	Cluster* getMergedCluster(const Cluster& toMerge, int distinctNumberForMerged) const override;
	int proposeDistinctNumber() const override;
	int getAssociatedIndex();

	std::vector<int>& shareIndices();
};

