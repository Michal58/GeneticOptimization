#include "ClusterizationPerformer.h"

ClusterizationPerformer::ClusterizationPerformer(SelectorOfClustersMerging& clustersToMergeSelector):
    clustersToMergeSelector(clustersToMergeSelector) {}

std::vector<Cluster*>* ClusterizationPerformer::perfromClusterization(DistancesLookup& distances, bool notAddClustersWithZeroDistances)
{
    std::vector<Cluster*>* allClusters = new std::vector<Cluster*>;
    
    clustersToMergeSelector.setAssociatedLookup(distances);
    
    while (distances.allClustersCardinality() > 1)
    {
        Cluster* firstClusterToMerge;
        Cluster* secondClusterToMerge;
        clustersToMergeSelector.selectClustersForMerging(firstClusterToMerge, secondClusterToMerge);
        double selectedClustersDistance = distances.getDistance(*firstClusterToMerge, *secondClusterToMerge);
        Cluster* firstAndSecondUnion = distances.replaceClustersByMergedClusterAndReturnIt(*firstClusterToMerge, *secondClusterToMerge);
        clustersToMergeSelector.updateWithNewCluster(firstAndSecondUnion);
        if (!notAddClustersWithZeroDistances || !selectedClustersDistance == 0)
        {
            allClusters->push_back(firstClusterToMerge);
            allClusters->push_back(secondClusterToMerge);
        }
    }

    allClusters->push_back(*distances.shareAllSingleClusters().begin());
    return allClusters;
}
