#include "GeneIndexCluster.h"

int GeneIndexCluster::nextDistinctNumber = GeneIndexCluster::INITIAL_DISTINCT_NUMBER;

GeneIndexCluster::GeneIndexCluster(int associatedDistinctNumber):
    Cluster(associatedDistinctNumber) {}

void GeneIndexCluster::resetDistinctNumbersGeneration()
{
    GeneIndexCluster::nextDistinctNumber = GeneIndexCluster::INITIAL_DISTINCT_NUMBER;
}

int GeneIndexCluster::generateDistinctNumber()
{
    int numberToReturn = nextDistinctNumber;
    nextDistinctNumber++;
    return numberToReturn;
}

GeneIndexCluster::GeneIndexCluster(int representedIndex, int providedDistinctNumber):
    Cluster(providedDistinctNumber)
{
    representedIndices.push_back(representedIndex);
}

GeneIndexCluster::GeneIndexCluster(const GeneIndexCluster& other):
    Cluster(other),
    representedIndices(other.representedIndices) {}

Cluster* GeneIndexCluster::getCopy() const
{
    return new GeneIndexCluster(*this);
}

int GeneIndexCluster::cardinality()
{
    return representedIndices.size();
}

Cluster* GeneIndexCluster::getMergedCluster(const Cluster& toMerge, int distinctNumberForMerged) const
{
    if (!isInstanceOf<GeneIndexCluster>(&toMerge))
        throw std::runtime_error(INVALID_MERGE_CLUSTER_ERROR);

    GeneIndexCluster* mergedCluster = new GeneIndexCluster(distinctNumberForMerged);
    mergedCluster->representedIndices = this->representedIndices;

    std::vector<int>& indicesToMergeIn= mergedCluster->representedIndices;
    const std::vector<int>& indicesToBeMerged = ((GeneIndexCluster&)toMerge).representedIndices;

    indicesToMergeIn.insert(indicesToMergeIn.end(), indicesToBeMerged.begin(), indicesToBeMerged.end());
    return mergedCluster;
}

int GeneIndexCluster::proposeDistinctNumber() const
{
    return generateDistinctNumber();
}

int GeneIndexCluster::getAssociatedIndex()
{
    if (!isSingletonCluster())
        throw std::runtime_error(THERE_IS_NO_ASSOCIATED_INDEX);
    return representedIndices[0];
}

std::vector<int>& GeneIndexCluster::shareIndices()
{
    return representedIndices;
}
