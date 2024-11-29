#include "../include/Plan.h"
#include <iostream>
#include <vector>

//constructor:

Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions): 
plan_id(planId),
settlement(settlement),
selectionPolicy(selectionPolicy),
facilityOptions(facilityOptions),
construction_limit(((int)settlement.getType()) + 1), // VILLAGE = 0 , CITY = 1, METROPOLIS = 2 : buildLimit(VILLAGE) = 1 , buildLimit(CITY) = 2, buildLimit(METROPOLIS) = 3
free_construction_slots(construction_limit), 
status(PlanStatus::AVALIABLE)
{} //the scores are intialized to zero by deafault, and _facilities,  _underConstruction are intialized to null_ptr 



//getters:

const int Plan::getlifeQualityScore() const{
    return life_quality_score; 
}


const int Plan::getEconomyScore() const{
    return economy_score;
}


const int Plan::getEnvironmentScore() const{
    return environment_score;
}


// setters:
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){

    delete selectionPolicy; // each instance of Plan has unique instance of SelectionPlan
    selectionPolicy = selectionPolicy;
}


// other methods:
void Plan::step(){ //TODO: Update the scores 
    if(status == PlanStatus::AVALIABLE){
        while(free_construction_slots > 0)
        {
            const FacilityType& chosen_facility_type(selectionPolicy->selectFacility(facilityOptions));
            Facility* fac(new Facility(chosen_facility_type,settlement.getName())); // remember to destroy fac later 
            underConstruction.push_back(fac);
            free_construction_slots --;
        }
    } 
    else
    {
        for(Facility* fac:facilities)
        {
            if(fac->step() == FacilityStatus::OPERATIONAL){ // notice we reduced the time remaining the moment we call the step func
                // remove fac from _underConstruction:
                //underConstruction.erase(std::remove(underConstruction.begin(), underConstruction.end(), fac), underConstruction.end());
                // remove - moves fac to the end of the vector, and then we erase the last value in the vector 
                free_construction_slots ++;
                facilities.push_back(fac);
            }
        }

        if(free_construction_slots == 0)
            status = PlanStatus::BUSY;
        else status = PlanStatus::AVALIABLE;

    }

}




void Plan::printStatus(){
    string status_str;
    if(status == PlanStatus::AVALIABLE)
        status_str = "AVALIABLE";
    else status_str = "BUSY";


    std::cout 
    << "\nPlanID: " << plan_id
    << "\nSettlementName " << settlement.getName()
    << "\nPlanStatus: " << status_str
    //<< "\nSelectionPolicy: " << selectionPolicy->getPolicyType()
    << "\nLifeQualityScore: " << life_quality_score
    << "\nEconomyScore: " << economy_score
    << "\nEnvrionmentScore: "  << environment_score
    << std::endl;

    for(Facility* fac:underConstruction){
        std::cout 
        << "\nFacilityName: " << fac->getName()
        << "\nFacilityStatus: " <<  "UNDER_CONSTRUCTIONS"
        << std::endl;
    }


    for(Facility* fac:facilities){
        std::cout 
        << "\nFacilityName: " << fac->getName()
        << "\nFacilityStatus: " <<  "OPERATIONAL"
        << std::endl;
    }
}

