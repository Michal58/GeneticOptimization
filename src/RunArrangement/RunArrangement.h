#pragma once
#include "../OptimizationTemplates/OptimizationCase.h"
#include "../OptimizationTemplates/GeneticOptimizer.h"

struct RunArrangement {

	GeneticOptimizer& proposedSolver;
	StopCriterion& proposedCriterionOfStop;

	RunArrangement(GeneticOptimizer& proposedSolver, StopCriterion& proposedCriterionOfStop);
};
