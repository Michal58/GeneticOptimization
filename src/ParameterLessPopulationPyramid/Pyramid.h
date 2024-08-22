#pragma once
#include "PopulationLevel.h"

class Pyramid
{
	std::vector<PopulationLevel*> pyramidLevels;
	OptimazationCase& caseToOptimize;

	void deleteLevelsFromPyramid();

public:

	Pyramid(OptimazationCase& caseToOptimize);
	~Pyramid();

	std::vector<PopulationLevel*>::iterator begin();
	std::vector<PopulationLevel*>::iterator end();

	bool hasLevelAt(int depth);

	PopulationLevel& getLevel(int depth);
	PopulationLevel& getOrCreateNextLevelAt(int depth);
	void addIndividualAndOptionallyCreateLevelAtDepth(P3Individual* individualToAdd, int depth);
};

