#include "Action.h"

AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
    _facilityName(facilityName), _facilityCategory(facilityCategory), _price(price), _lifeQualityScore(lifeQualityScore), _economyScore(economyScore), _environmentScore(environmentScore) {};

void AddFacility::act(Simulation &simulation) {

    simulation.addAction(this); // Add the action to the simulation
    if(simulation.isFacilityExists(_facilityName)){
        this->error("Facility already exists");
    }else{
    // Create a new Facility object
    FacilityType *facility = new FacilityType(_facilityName, _facilityCategory, _price, _lifeQualityScore, _economyScore, _environmentScore);
    
    // Add the facility to the simulation
    simulation.addFacility(*facility);
    this->complete();
    }
    

}

// Function to return a string representation of the action
const string AddFacility::toString() const {
    return "Add Facility: " + _facilityName + " " + std::to_string(static_cast<int>(_facilityCategory)) + " " + std::to_string(_price) + " " + std::to_string(_lifeQualityScore) + " " + std::to_string(_economyScore) + " " + std::to_string(_environmentScore);
}