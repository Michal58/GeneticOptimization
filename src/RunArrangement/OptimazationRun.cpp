#include "../OptimazationRun.h"

OptimazationRun::OptimazationRun(OptimazationCase& givenCaseToSolve, GeneticOptimizer& givenOptimizerAsSolver, StopCriterium& givenCriteriumOfStop):
    givenCaseToSolve(givenCaseToSolve),
    arrangedRunSet(*createRunArrangement(givenOptimizerAsSolver, givenCriteriumOfStop))
{
    possiblyPassedManagerOfRunArrangement = nullptr;
}

OptimazationRun::OptimazationRun(OptimazationCase& givenCaseToSolve, RunArrangement& arrangedRunSet):
    givenCaseToSolve(givenCaseToSolve),
    arrangedRunSet(arrangedRunSet)
{
    possiblyCreatedRunArrangement = nullptr;
    possiblyPassedManagerOfRunArrangement = nullptr;
}

OptimazationRun::OptimazationRun(OptimazationCase& givenCaseToSolve, ManagerOfRunArrangement* arrangementManager): 
    givenCaseToSolve(givenCaseToSolve),
    arrangedRunSet(arrangementManager->shareRunArrangement())
{
    possiblyCreatedRunArrangement = nullptr;
    possiblyPassedManagerOfRunArrangement = arrangementManager;
}

OptimazationRun::OptimazationRun(OptimazationCase& givenCaseToSolve, int indexOfArrangementConstructor) :
    OptimazationRun(givenCaseToSolve, ARRANGEMENT_CONSTRUCTORS[indexOfArrangementConstructor](givenCaseToSolve)) {}

OptimazationRun::~OptimazationRun()
{
    delete possiblyPassedManagerOfRunArrangement;
    delete possiblyCreatedRunArrangement;
}

OptimazationResult OptimazationRun::findOptimizedSolution()
{
    GeneticOptimizer& proposedSolver = arrangedRunSet.proposedSolver;
    StopCriterium& proposedCriteriumOfStop = arrangedRunSet.proposedCriteriumOfStop;

    proposedSolver.reset();
    proposedSolver.searchForTheBestSolution(proposedCriteriumOfStop);

    Individual* solution = proposedSolver.peekTheBestIndividual();
    return OptimazationResult{ solution->evaluateFitness(),solution->copyGenotype() };
}

RunArrangement* OptimazationRun::createRunArrangement(GeneticOptimizer& givenOptimizerAsSolver, StopCriterium& givenCriteriumOfStop)
{
    this->possiblyCreatedRunArrangement = new RunArrangement(givenOptimizerAsSolver, givenCriteriumOfStop);
    return this->possiblyCreatedRunArrangement;
}
