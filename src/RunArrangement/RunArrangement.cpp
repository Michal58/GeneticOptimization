#include "RunArrangement.h"

RunArrangement::RunArrangement(GeneticOptimizer& proposedSolver, StopCriterion& proposedCriterionOfStop):
	proposedSolver(proposedSolver),
	proposedCriterionOfStop(proposedCriterionOfStop) {}
