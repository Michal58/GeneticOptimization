#pragma once
#include "../OptimizationTemplates/Individual.h"
#include "../CommonComponents/HillClimbers/GreedyHillClimber.h"
#include "../CommonComponents//Randomizers/Mt19937Randomizer.h"
#include "../CommonComponents/Hashing/Hashable.h"
#include "../CommonComponents/Functionalities/Functionalities.h"
#include "GeneIndexCluster.h"

struct ClusterBaseCrossoverParameters: public ParametersOfCrossover
{
	GeneIndexCluster& crossoverCluster;
	ClusterBaseCrossoverParameters(GeneIndexCluster& crossoverCluster);
};

struct PreviousGenes: public ResultOfCrossover
{
	bool didGenesChange;
	std::vector<int>* previousGenes;
	PreviousGenes(std::vector<int>*  previousGenes, bool didGenesChange);
};

class P3Individual: public Individual, public Hashable
{
protected:

	void registerChangesInGenotype() override;

public:

	P3Individual(OptimizationCase& evaluator);
	P3Individual(const P3Individual& other);
	bool operator==(const P3Individual& other) const;
	unsigned int calculateHash() const override;
	bool equals(const Hashable& other) const override;
	void greedilyOptimize();
	void greedilyOptimize(GreedyHillClimber& hillClimberToUse);
	ResultOfCrossover* crossover(Individual& donorOfGens, ParametersOfCrossover& crossoverParameters) override;
	Individual* clone() override;
	Randomizer& getDefaultRandomizer() override;
	void revertChanges(GeneIndexCluster& clusterOfChange, std::vector<int>* previousGenes, double previousFitness, unsigned int prevoiusHash);
};
