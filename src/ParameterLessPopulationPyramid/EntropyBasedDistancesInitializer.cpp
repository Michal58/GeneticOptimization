#include "EntropyBasedDistancesInitializer.h"

void EntropyBasedInitializer::createSingletonClusters(DistancesLookup& distancesToInitialize)
{
    ClustersSet& setToPrepare = InitializerOfDistancesLookup::accessSingleClusters(distancesToInitialize);

    GeneIndexCluster::resetDistinctNumbersGeneration();
    for (int iIndexInGenotype = 0; iIndexInGenotype < caseToSolve.getCountOfDimensions(); iIndexInGenotype++)
        setToPrepare.insert(new GeneIndexCluster(iIndexInGenotype, GeneIndexCluster::generateDistinctNumber()));
}

void EntropyBasedInitializer::fillDistancesWithFirstIndexOfSequenceAlwaysSmallerThanSecond(int firstIndexOfLeafInSequence, std::vector<Cluster*>& sequenceOfClusters, DistancesLookup& distancesToInitialize)
{
    ClusterPairsToDistances& distancesMapping = InitializerOfDistancesLookup::accessDistancesMap(distancesToInitialize);
    for (int jSecondClusterInPair = firstIndexOfLeafInSequence + 1; jSecondClusterInPair < sequenceOfClusters.size(); jSecondClusterInPair++)
    {
        ClustersPair pairToDetermineDistance(*sequenceOfClusters[firstIndexOfLeafInSequence], *sequenceOfClusters[jSecondClusterInPair]);
        double distanceOfPair = calculateDistanceBetweenTwoClusterLeaves(pairToDetermineDistance);
        distancesMapping.insert({ pairToDetermineDistance,distanceOfPair });
    }
}

void EntropyBasedInitializer::initializeMapOfDistances(DistancesLookup& distancesToInitialize)
{
    ClustersSet& setOfAllClusters = InitializerOfDistancesLookup::accessSingleClusters(distancesToInitialize);

    std::vector<Cluster*> sequenceOfClusters;
    sequenceOfClusters.reserve(setOfAllClusters.size());
    for (Cluster* singleCluster : setOfAllClusters)
        sequenceOfClusters.push_back(singleCluster);

    for (int iFirstClusetInPair = 0; iFirstClusetInPair < sequenceOfClusters.size(); iFirstClusetInPair++)
        fillDistancesWithFirstIndexOfSequenceAlwaysSmallerThanSecond(iFirstClusetInPair, sequenceOfClusters, distancesToInitialize);
    
}

double EntropyBasedInitializer::getProbabilityFromSetOfGenesFrequency(int setOfGenesFrequency)
{
    int countOfGenotypes = frequenciesOfGenesLookup.getCountOfConsideredGenotypes();
    return static_cast<double>(setOfGenesFrequency) / static_cast<double>(countOfGenotypes);
}

std::vector<GenesPairInGenotype> EntropyBasedInitializer::getCartesianProductOfGenes(GeneIndexCluster& firstLeafAsGeneRepresentation, GeneIndexCluster& secondLeafAsGeneRepresentation)
{

    int firstLeafAssociatedDimension = firstLeafAsGeneRepresentation.getAssociatedIndex();
    int secondLeafAssociatedDimension = secondLeafAsGeneRepresentation.getAssociatedIndex();

    std::vector<GenesPairInGenotype> cartesianProduct;
    cartesianProduct.reserve(caseToSolve.getCountOfDomainValues(firstLeafAssociatedDimension)
        * caseToSolve.getCountOfDomainValues(secondLeafAssociatedDimension));

    std::unique_ptr<DomainIterator> firstDomain = caseToSolve.getDomain(firstLeafAssociatedDimension);

    while (firstDomain->hasNext())
    {
        int firstDomainCurrentValue = firstDomain->next();
        std::unique_ptr<DomainIterator> secondDomain = caseToSolve.getDomain(secondLeafAssociatedDimension);

        while (secondDomain->hasNext())
        {
            int secondDomainCurrentValue = secondDomain->next();
            GenesPairInGenotype pairOfGenes = GenesPairInGenotype(firstLeafAssociatedDimension, firstDomainCurrentValue, secondLeafAssociatedDimension, secondDomainCurrentValue);
            cartesianProduct.push_back(pairOfGenes);
        }
    }

    return cartesianProduct;
}

void EntropyBasedInitializer::updateEntropySum(double& currentSum, int frequencyOfElement)
{
    double probabilityOfOccurance = getProbabilityFromSetOfGenesFrequency(frequencyOfElement);
    double nextUpdate = probabilityOfOccurance == static_cast<double>(0) ?
        0 : probabilityOfOccurance * std::log(probabilityOfOccurance);
    currentSum += nextUpdate;
}

double EntropyBasedInitializer::calculateEntropy(GeneIndexCluster& leaf)
{
    int associatedDimensionOfLeaf = leaf.getAssociatedIndex();
    std::unique_ptr<DomainIterator> domain = caseToSolve.getDomain(associatedDimensionOfLeaf);

    double currentSum = 0;

    while (domain->hasNext())
    {
        int currentValue = domain->next();
        int geneFrequency = frequenciesOfGenesLookup.getFrequencyOfSingleGenInGenotypes(GeneInGenotype(associatedDimensionOfLeaf, currentValue));
        updateEntropySum(currentSum, geneFrequency);
    }

    return -currentSum;
}

double EntropyBasedInitializer::calculateEntropy(ClustersPair pairOfLeaves)
{
    GeneIndexCluster& firstLeaf = (GeneIndexCluster&)pairOfLeaves.first();
    GeneIndexCluster& secondLeaf = (GeneIndexCluster&)pairOfLeaves.second();

    int firstLeafAssociatedDimension = firstLeaf.getAssociatedIndex();
    int secondLeafAssociatedDimension = secondLeaf.getAssociatedIndex();

    std::unique_ptr<DomainIterator> firstDomain = caseToSolve.getDomain(firstLeafAssociatedDimension);

    double currentSum = 0;

    std::vector<GenesPairInGenotype> productOfTwoDimensions = getCartesianProductOfGenes(firstLeaf, secondLeaf);
    for (GenesPairInGenotype pairOfGenes : productOfTwoDimensions)
    {
        int pairOfGenesFrequency = frequenciesOfGenesLookup.getFrequencyOfGenesPairInGenotypes(pairOfGenes);
        updateEntropySum(currentSum, pairOfGenesFrequency);
    }

    return -currentSum;
}

double EntropyBasedInitializer::calculateDistanceBetweenTwoClusterLeaves(ClustersPair clusterLeaves)
{
    GeneIndexCluster& Ci = (GeneIndexCluster&)clusterLeaves.first();
    GeneIndexCluster& Cj = (GeneIndexCluster&)clusterLeaves.second();

    ClustersPair CiCj(Ci, Cj);

    double HCi = calculateEntropy(Ci);
    double HCj = calculateEntropy(Cj);
    double HCiCj = calculateEntropy(CiCj);

    if (HCiCj == 0)
        return 0;
    else
        return ENTROPY_MINUEND - (HCi + HCj) / HCiCj;
}

EntropyBasedInitializer::EntropyBasedInitializer(OptimizationCase& caseToSolve, GenesFrequenciesLookup& frequenciesOfGenesLookup):
    caseToSolve(caseToSolve),
    frequenciesOfGenesLookup(frequenciesOfGenesLookup) {}

void EntropyBasedInitializer::setFrequenciesOfGenesLookup(GenesFrequenciesLookup& frequenciesOfGenesLookup)
{
    this->frequenciesOfGenesLookup = frequenciesOfGenesLookup;
}

void EntropyBasedInitializer::initializeDistancesLookup(DistancesLookup& distancesToInitialize)
{
    createSingletonClusters(distancesToInitialize);
    initializeMapOfDistances(distancesToInitialize);
}
