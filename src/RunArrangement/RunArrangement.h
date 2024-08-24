#pragma once
#include "../OptimizationTemplates/OptimizationCase.h"
#include "../OptimizationTemplates/GeneticOptimizer.h"

struct RunArrangement {

	GeneticOptimizer& proposedSolver;
	StopCriterium& proposedCriteriumOfStop;

	RunArrangement(GeneticOptimizer& proposedSolver, StopCriterium& proposedCriteriumOfStop);
};
