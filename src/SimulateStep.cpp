#include "Action.h"

SimulateStep::SimulateStep(const int numOfSteps): _numOfSteps(numOfSteps){}

void SimulateStep::act(Simulation &simulation) {
    simulation.addAction(this);

    for(int i = 0; i< _numOfSteps; i++){
        simulation.step();
    }
    complete();
}


const string SimulateStep::toString() const {
    return BaseAction::toString() +  std::to_string(_numOfSteps);
}


SimulateStep* SimulateStep::clone() const{
    return new SimulateStep(_numOfSteps);
}