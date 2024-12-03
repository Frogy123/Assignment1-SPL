#include <Action.h>
extern Simulation* backup;


BackupSimulation::BackupSimulation(){}

void BackupSimulation::act(Simulation &simulation) {
    simulation.addAction(this);

    backup = new Simulation(simulation);
    complete;
}

BackupSimulation* BackupSimulation::clone() const {
    return new BackupSimulation();
}


const string BackupSimulation::toString() const {}

        