#include "Action.h"

ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy): _planId(planId), _newPolicy(newPolicy) {};
void ChangePlanPolicy::act(Simulation &Simulation){
    
    Simulation.addAction(this);
    
    if(!Simulation.isPlanExists(_planId)){
        this->error("Plan does not exist");
        return;
    }
    
    Plan &plan = Simulation.getPlan(_planId); //need to throw erorr if plan does not exist

    if(_newPolicy == plan.getPolicy()){
        this->error("The new policy is the same as the current policy");
        return;
    }


    SelectionPolicy *policy = nullptr;
    if (_newPolicy == "nve") {
        policy = new NaiveSelection();
    } else if (_newPolicy == "bal") {
        policy = new BalancedSelection(plan.getlifeQualityScore(), plan.getEconomyScore(), plan.getEnvironmentScore());       
    } else if (_newPolicy == "eco") {
        policy = new EconomySelection();
    } else if (_newPolicy == "env") {
        policy = new SustainabilitySelection();
    }

    plan.setSelectionPolicy(policy);
    this->complete();
    
}

const string ChangePlanPolicy::toString() const {
    return "ChangePolicy" + std::to_string(_planId) + " " + _newPolicy;
}

