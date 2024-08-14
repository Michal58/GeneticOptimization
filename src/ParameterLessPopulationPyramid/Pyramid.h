#pragma once
#include "PopulationLevel.h"

class Pyramid
{
	std::vector<PopulationLevel*> pyramidLevels;

	void deleteLevelsFromPyramid();

public:

	Pyramid();
	~Pyramid();

	std::vector<PopulationLevel*>::iterator begin();
	std::vector<PopulationLevel*>::iterator end();

	bool hasLevelAt(int depth);
	PopulationLevel& getLevel(int depth);
	PopulationLevel& getOrCreateNextLevelAt(int depth);
};

