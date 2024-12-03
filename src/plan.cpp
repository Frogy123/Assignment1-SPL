#include "../include/Plan.h"
#include <iostream>
#include <vector>

//constructor:

Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions): 
_plan_id(planId),
_settlement(settlement),
_selectionPolicy(selectionPolicy),
_facilityOptions(facilityOptions),
_construction_limit(((int)settlement.getType()) + 1), // VILLAGE = 0 , CITY = 1, METROPOLIS = 2 : buildLimit(VILLAGE) = 1 , buildLimit(CITY) = 2, buildLimit(METROPOLIS) = 3
_free_construction_slots(_construction_limit), 
_status(PlanStatus::AVALIABLE)
{} //the scores are intialized to zero by deafault, and _facilities,  _underConstruction are intialized to null_ptr 

//rule of 3:

Plan::Plan(const Plan &other):
_plan_id(other._plan_id),
_settlement(other._settlement),
_selectionPolicy(other._selectionPolicy->clone()),
_facilityOptions(other._facilityOptions),
_construction_limit(other._construction_limit),
_free_construction_slots(other._free_construction_slots),
_status(other._status)
{
    for(Facility* fac:other._facilities){
        _facilities.push_back(new Facility(*fac));
    }
    for(Facility* fac:other._underConstruction){
        _underConstruction.push_back(new Facility(*fac));
    }
}



Plan:: ~Plan(){
    delete _selectionPolicy;
    for(Facility* fac:_underConstruction){
        delete fac;
    }
    for(Facility* fac:_facilities){
        delete fac;
    }
}


//getters:

const int Plan::getlifeQualityScore() const{
    return _life_quality_score; 
}


const int Plan::getEconomyScore() const{
    return _economy_score;
}


const int Plan::getEnvironmentScore() const{
    return _environment_score;
}


// setters:
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){

    delete selectionPolicy; // each instance of Plan has unique instance of SelectionPlan
    selectionPolicy = selectionPolicy;
}


// other methods:
void Plan::step(){ //TODO: Update the scores 
    if(_status == PlanStatus::AVALIABLE){
        while(_free_construction_slots > 0)
        {
            const FacilityType& chosen_facility_type(_selectionPolicy->selectFacility(_facilityOptions));
            Facility* fac(new Facility(chosen_facility_type,_settlement.getName())); // remember to destroy fac later 
            _underConstruction.push_back(fac);
            _free_construction_slots --;
        }
    } 
    else
    {
        for(Facility* fac:_facilities)
        {
            if(fac->step() == FacilityStatus::OPERATIONAL){ // notice we reduced the time remaining the moment we call the step func
                // remove fac from _underConstruction:
                //underConstruction.erase(std::remove(underConstruction.begin(), underConstruction.end(), fac), underConstruction.end());
                // remove - moves fac to the end of the vector, and then we erase the last value in the vector 
                _free_construction_slots ++;
                _facilities.push_back(fac);
            }
        }

        if(_free_construction_slots == 0)
            _status = PlanStatus::BUSY;
        else _status = PlanStatus::AVALIABLE;

    }

}






void Plan::printStatus(){
    string status_str;
    if(_status == PlanStatus::AVALIABLE)
        status_str = "AVALIABLE";
    else status_str = "BUSY";


    std::cout 
    << "\nPlanID: " << _plan_id
    << "\nSettlementName " << _settlement.getName()
    << "\nPlanStatus: " << status_str
    //<< "\nSelectionPolicy: " << selectionPolicy->getPolicyType()
    << "\nLifeQualityScore: " << _life_quality_score
    << "\nEconomyScore: " << _economy_score
    << "\nEnvrionmentScore: "  << _environment_score
    << std::endl;

    for(Facility* fac:_underConstruction){
        std::cout 
        << "\nFacilityName: " << fac->getName()
        << "\nFacilityStatus: " <<  "UNDER_CONSTRUCTIONS"
        << std::endl;
    }


    for(Facility* fac:_facilities){
        std::cout 
        << "\nFacilityName: " << fac->getName()
        << "\nFacilityStatus: " <<  "OPERATIONAL"
        << std::endl;
    }
}

