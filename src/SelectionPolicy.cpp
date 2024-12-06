#include "SelectionPolicy.h"
#include <vector>
#include <string>
#include <climits>
#include <bits/algorithmfwd.h>

//################################################################################
//sub class SustainabilitySelection
// Constructor
SustainabilitySelection::SustainabilitySelection() : lastSelectedIndex(-1) {}

// Method to select a facility
const FacilityType& SustainabilitySelection::selectFacility(const std::vector<FacilityType>& facilitiesOptions) {
    for(int i = lastSelectedIndex+1; i - lastSelectedIndex < facilitiesOptions.size(); i++) {
        if(facilitiesOptions[i%facilitiesOptions.size()].getCategory() == FacilityCategory::ENVIRONMENT) {
            lastSelectedIndex = i%facilitiesOptions.size();
            return facilitiesOptions[i];
        }
    }

    lastSelectedIndex++;
    return facilitiesOptions[lastSelectedIndex];
}

// Method to convert to string
const std::string SustainabilitySelection::toString() const {
    return "Sustainability Selection Policy";
}

// Method to clone the object
SustainabilitySelection* SustainabilitySelection::clone() const {
    return new SustainabilitySelection(*this);
}

//end SustainabilitySelection
//################################################################################



//################################################################################
//sub class NavieSelection
NaiveSelection::NaiveSelection() : lastSelectedIndex(-1) {}

// Assuming the return type is a reference to FacilityType
const FacilityType& NaiveSelection::selectFacility(const std::vector<FacilityType> &facilitiesOptions) {
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    return facilitiesOptions[lastSelectedIndex];
}

const std::string NaiveSelection::toString() const {
    return "Naive Selection Policy Last Index + " + std::to_string(lastSelectedIndex);
}

NaiveSelection *NaiveSelection::clone() const {
    return new NaiveSelection(*this);
}

//end NaiveSelection
//################################################################################



//################################################################################
//sub class EconomySelection

// Constructor
EconomySelection::EconomySelection() : lastSelectedIndex(-1) {}

// Method to select a facility
const FacilityType& EconomySelection::selectFacility(const std::vector<FacilityType>& facilitiesOptions) {
    for(int i = lastSelectedIndex+1; i - lastSelectedIndex < facilitiesOptions.size(); i++) {
        if(facilitiesOptions[i%facilitiesOptions.size()].getCategory() == FacilityCategory::ECONOMY) {
            lastSelectedIndex = i%facilitiesOptions.size();
            return facilitiesOptions[i];
        }
    }

    lastSelectedIndex++;
    return facilitiesOptions[lastSelectedIndex];
}

// Method to convert to string
const std::string EconomySelection::toString() const {
    return "Economy Selection Policy";
}

// Method to clone the object
EconomySelection* EconomySelection::clone() const {
    return new EconomySelection(*this);
}

//end EconomySelection
//################################################################################


//################################################################################
//sub class BalancedSelection
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore) :
 LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}


const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
    int min = INT_MAX;
    int index = 0;
    for (int i = 0; i < facilitiesOptions.size(); i++) {
        int distance = calculateDistance(facilitiesOptions[i].getLifeQualityScore() + LifeQualityScore, facilitiesOptions[i].getEconomyScore() + EconomyScore, facilitiesOptions[i].getEnvironmentScore() + EnvironmentScore);
        if (distance < min) {
            min = distance;
            index = i;
        }
    }
    return facilitiesOptions[index];
}

int BalancedSelection::calculateDistance(int x, int y, int z) {
    std::vector<int> nums = {x, y, z};
    int max = *std::max_element(nums.begin(), nums.end());
    int min = *std::min_element(nums.begin(), nums.end());
    return max - min;
}

const string BalancedSelection::toString() const {
    return "Balanced Selection Policy with scores: " + std::to_string(LifeQualityScore) + ", " + std::to_string(EconomyScore) + ", " + std::to_string(EnvironmentScore);
}

BalancedSelection* BalancedSelection::clone() const {
    return new BalancedSelection(*this);
}


//################################################################################