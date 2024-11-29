#include "SelectionPolicy.h"
#include <vector>

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

