#include "Action.h"

AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
    facilityName(facilityName), facilityCategory(facilityCategory), price(price), lifeQualityScore(lifeQualityScore), economyScore(economyScore), environmentScore(environmentScore) {};

void AddFacility::act(Simulation &simulation) {

    simulation.addAction(this); // Add the action to the simulation
    if(simulation.isFacilityExists(facilityName)){
        this->error("Facility already exists");
    }else{
    // Create a new Facility object
    FacilityType *facility = new FacilityType(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
    
    // Add the facility to the simulation
    simulation.addFacility(*facility);
    this->complete();
    }
    

}

// Function to return a string representation of the action
const string AddFacility::toString() const {
    return "Add Facility: " + facilityName + " " + std::to_string(static_cast<int>(facilityCategory)) + " " + std::to_string(price) + " " + std::to_string(lifeQualityScore) + " " + std::to_string(economyScore) + " " + std::to_string(environmentScore);
}