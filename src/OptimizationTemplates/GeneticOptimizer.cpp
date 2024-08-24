#include "GeneticOptimizer.h"

GeneticOptimizer::GeneticOptimizer(OptimizationCase& caseInstance):
	caseInstance(caseInstance) {}

GeneticOptimizer::~GeneticOptimizer() {}

void GeneticOptimizer::searchForTheBestSolution(StopCriterium& stopController)
{
	if (!isReadyToSearch())
		return;

	while (!stopController.isLimitReached())
	{
		runIteration();
		stopController.updateStance();

		#if LOG_PERMISSION == LOG_ALLOWED
				std::cout << peekTheBestIndividual()->evaluateFitness() << std::endl;
		#endif
	}
}
