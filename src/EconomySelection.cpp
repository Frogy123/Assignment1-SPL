#include "SelectionPolicy.h"
#include "Facility.h"
#include <vector>
#include <string>

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
