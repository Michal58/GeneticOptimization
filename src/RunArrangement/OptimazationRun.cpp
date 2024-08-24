#include "../OptimizationRun.h"

OptimizationRun::OptimizationRun(OptimizationCase& givenCaseToSolve, GeneticOptimizer& givenOptimizerAsSolver, StopCriterion& givenCriterionOfStop):
    givenCaseToSolve(givenCaseToSolve),
    arrangedRunSet(*createRunArrangement(givenOptimizerAsSolver, givenCriterionOfStop))
{
    possiblyPassedManagerOfRunArrangement = nullptr;
}

OptimizationRun::OptimizationRun(OptimizationCase& givenCaseToSolve, RunArrangement& arrangedRunSet):
    givenCaseToSolve(givenCaseToSolve),
    arrangedRunSet(arrangedRunSet)
{
    possiblyCreatedRunArrangement = nullptr;
    possiblyPassedManagerOfRunArrangement = nullptr;
}

OptimizationRun::OptimizationRun(OptimizationCase& givenCaseToSolve, ManagerOfRunArrangement* arrangementManager): 
    givenCaseToSolve(givenCaseToSolve),
    arrangedRunSet(arrangementManager->shareRunArrangement())
{
    possiblyCreatedRunArrangement = nullptr;
    possiblyPassedManagerOfRunArrangement = arrangementManager;
}

OptimizationRun::OptimizationRun(OptimizationCase& givenCaseToSolve, int indexOfArrangementConstructor) :
    OptimizationRun(givenCaseToSolve, ARRANGEMENT_CONSTRUCTORS[indexOfArrangementConstructor](givenCaseToSolve)) {}

OptimizationRun::~OptimizationRun()
{
    delete possiblyPassedManagerOfRunArrangement;
    delete possiblyCreatedRunArrangement;
}

OptimizationResult OptimizationRun::findOptimizedSolution()
{
    GeneticOptimizer& proposedSolver = arrangedRunSet.proposedSolver;
    StopCriterion& proposedCriterionOfStop = arrangedRunSet.proposedCriterionOfStop;

    proposedSolver.reset();
    proposedSolver.searchForTheBestSolution(proposedCriterionOfStop);

    Individual* solution = proposedSolver.peekTheBestIndividual();
    return OptimizationResult{ solution->evaluateFitness(),solution->copyGenotype() };
}

RunArrangement* OptimizationRun::createRunArrangement(GeneticOptimizer& givenOptimizerAsSolver, StopCriterion& givenCriterionOfStop)
{
    this->possiblyCreatedRunArrangement = new RunArrangement(givenOptimizerAsSolver, givenCriterionOfStop);
    return this->possiblyCreatedRunArrangement;
}
