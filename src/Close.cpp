#include "Action.h"

Close::Close(){};

void Close::act(Simulation &simulation) {
    simulation.addAction(this); // Add the action to the simulation
    
    for(int i = 0; i < simulation.getPlanCounter(); i++){
        simulation.getPlan(i).printStatus();
    }

    this->complete();
    simulation.close();
    
    
}

const string Close::toString() const {
    return "Close";
}   