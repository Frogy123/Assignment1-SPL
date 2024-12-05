#include "Simulation.h"
#include "Action.h"

void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy) {
   planCounter++;
   Plan* p = new Plan(planCounter, settlement, selectionPolicy, facilitiesOptions);
   plans.push_back(*p);
}

bool Simulation::addSettlement(Settlement *settlement){
    settlements.push_back(settlement);
    return true;
}

bool Simulation::isSettlementExists(const string &settlementName){
      for (Settlement* s : settlements){
         if (s->getName() == settlementName){
               return true;
         }
      }
      return false;
}
bool Simulation::isFacilityExists(const string &facilityName){
      for (FacilityType f : facilitiesOptions){
         if (f.getName() == facilityName){
               return true;
         }
      }
      return false;
}
int Simulation::getPlanCounter() const{
      return planCounter;
} //eitan

Plan& Simulation::getPlan(const int planID){
   return plans[planID];
}
void Simulation::close(){
    isRunning = false;   

}

void Simulation::clear(){
      for (Settlement* s : settlements){
         s = nullptr;
      }
      for (BaseAction* a : actionsLog){
         a = nullptr;
      }
}

Simulation::Simulation(Simulation &&other):
isRunning(other.isRunning),
planCounter(other.planCounter),
actionsLog(other.actionsLog),
plans(other.plans),
settlements(other.settlements),
facilitiesOptions(other.facilitiesOptions)
{
    other.clear();
}

Simulation& Simulation::operator=(Simulation &&other){
    if(this != &other){
        other.clear();
    }
    return *this;
}
