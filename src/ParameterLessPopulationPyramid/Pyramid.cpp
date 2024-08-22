#include "Pyramid.h"

void Pyramid::deleteLevelsFromPyramid()
{
    clearVectorOfPointers(pyramidLevels);
}

Pyramid::Pyramid(OptimazationCase& caseToOptimize):
    caseToOptimize(caseToOptimize) {}

Pyramid::~Pyramid()
{
    deleteLevelsFromPyramid();
}

std::vector<PopulationLevel*>::iterator Pyramid::begin()
{
    return pyramidLevels.begin();
}

std::vector<PopulationLevel*>::iterator Pyramid::end()
{
    return pyramidLevels.end();
}

bool Pyramid::hasLevelAt(int depth)
{
    return -1 < depth && depth < pyramidLevels.size();
}

void Pyramid::addIndividualAndOptionallyCreateLevelAtDepth(P3Individual* individualToAdd, int depth)
{
    getOrCreateNextLevelAt(depth).addIndividual(individualToAdd);
}

PopulationLevel& Pyramid::getLevel(int depth)
{
    return *(pyramidLevels[depth]);
}

PopulationLevel& Pyramid::getOrCreateNextLevelAt(int depth)
{
    if (depth == pyramidLevels.size())
        pyramidLevels.push_back(new PopulationLevel(caseToOptimize));
    return getLevel(depth);
}
