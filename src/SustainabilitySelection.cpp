#include "SelectionPolicy.h"
#include <vector>
#include <string>

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
