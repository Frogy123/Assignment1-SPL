#include "Simulation.h"
#include "Action.h"

void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy) {
    AddPlan action = AddPlan(settlement.getName(), selectionPolicy);
}