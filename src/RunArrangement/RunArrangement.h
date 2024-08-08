#pragma once
#include "../OptimazationTemplates/OptimazationCase.h"
#include "../OptimazationTemplates/GeneticOptimizer.h"

struct RunArrangement {

	GeneticOptimizer& proposedSolver;
	StopCriterium& proposedCriteriumOfStop;

	RunArrangement(GeneticOptimizer& proposedSolver, StopCriterium& proposedCriteriumOfStop);
};
