#include "RunArrangement.h"

RunArrangement::RunArrangement(GeneticOptimizer& proposedSolver, StopCriterium& proposedCriteriumOfStop):
	proposedSolver(proposedSolver),
	proposedCriteriumOfStop(proposedCriteriumOfStop) {}
