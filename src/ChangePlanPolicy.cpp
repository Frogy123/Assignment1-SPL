#include "Action.h"

ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy): planId(planId), newPolicy(newPolicy) {};
void ChangePlanPolicy::act(Simulation &Simulation){
    
    Simulation.addAction(this);
    
    if(!Simulation.isPlanExists(planId)){
        this->error("Plan does not exist");
        return;
    }
    
    Plan &plan = Simulation.getPlan(planId); //need to throw erorr if plan does not exist

    if(newPolicy == plan.getPolicy()){
        this->error("The new policy is the same as the current policy");
        return;
    }


    SelectionPolicy *policy = nullptr;
    if (newPolicy == "nve") {
        policy = new NaiveSelection();
    } else if (newPolicy == "bal") {
        policy = new BalancedSelection(plan.getlifeQualityScore(), plan.getEconomyScore(), plan.getEnvironmentScore());       
    } else if (newPolicy == "eco") {
        policy = new EconomySelection();
    } else if (newPolicy == "env") {
        policy = new SustainabilitySelection();
    }

    plan.setSelectionPolicy(policy);
    this->complete();
    
}

const string ChangePlanPolicy::toString() const {
    return "Change Plan Policy: " + std::to_string(planId) + " " + newPolicy;
}

