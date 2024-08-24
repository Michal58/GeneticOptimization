#pragma once
#include <unordered_set>
#include "../CommonComponents/Hashing/PointerBaseHasher.h"
#include "../OptimizationTemplates/GeneticOptimizer.h"
#include "P3Individual.h"
#include "Pyramid.h"

using IndividualsHashSet = std::unordered_set<P3Individual*, PointerBaseHasher<P3Individual>, PointerBaseHashablesComparator<P3Individual>>;

class ParameterLessPopulationPyramid: public GeneticOptimizer
{
	GreedyHillClimber* commonGreedyOptimizer;
	Individual* theBestIndividual;
	Pyramid* populationPyramid;
	IndividualsHashSet* allDistinctIndividualsSet;		// stotred elements not to delete

	bool isInitialized;

	void decideOnAddingIndividualToPyramid(P3Individual& potentiallyDistinctIndividual, int potentialPyramidLevelToUpdate);
	void tryToImproveSolutionWithCluster(GeneIndexCluster& clusterOfChange, P3Individual& solution, PopulationLevel& population);

public:

	ParameterLessPopulationPyramid(OptimizationCase& caseInstance);
	~ParameterLessPopulationPyramid();

	bool isIndividualDistinct(P3Individual& possibleDistinctIndividual);
	void mixSolutionWithPopulation(P3Individual& solution, PopulationLevel& population);

	void reset() override;
	bool isReadyToSearch() override;
	void runIteration() override;
	Individual* peekTheBestIndividual() override;
	Individual* copyTheBestIndividual() override;
};

using P3 = ParameterLessPopulationPyramid;