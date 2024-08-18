#include "GeneIndexCluster.h"

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
    representedIndicies.push_back(representedIndex);
}

GeneIndexCluster::GeneIndexCluster(const GeneIndexCluster& other):
    Cluster(other),
    representedIndicies(other.representedIndicies) {}

Cluster* GeneIndexCluster::getCopy() const
{
    return new GeneIndexCluster(*this);
}

int GeneIndexCluster::cardinality()
{
    return representedIndicies.size();
}

Cluster* GeneIndexCluster::getMergedCluster(const Cluster& toMerge, int distinctNumberForMerged) const
{
    if (!isInstanceOf<GeneIndexCluster>(toMerge))
        throw std::runtime_error(INVALID_MERGE_CLUSTER_ERROR);

    GeneIndexCluster* mergedCluster = new GeneIndexCluster(distinctNumberForMerged);
    mergedCluster->representedIndicies = this->representedIndicies;

    std::vector<int>& indiciesToMergeIn= mergedCluster->representedIndicies;
    const std::vector<int>& indiciesToBeMerged = ((GeneIndexCluster&)toMerge).representedIndicies;

    indiciesToMergeIn.insert(indiciesToMergeIn.end(), indiciesToBeMerged.begin(), indiciesToBeMerged.end());
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
    return representedIndicies[0];
}

std::vector<int>& GeneIndexCluster::shareIndicies()
{
    return representedIndicies;
}
