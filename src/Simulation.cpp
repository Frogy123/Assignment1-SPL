#include "Simulation.h"
#include "Action.h"

void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy) {
   Plan* p = new Plan(planCounter, settlement, selectionPolicy, facilitiesOptions);
   plans.push_back(*p);
}