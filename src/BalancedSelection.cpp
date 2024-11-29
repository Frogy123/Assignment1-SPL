#include "SelectionPolicy.h"
#include <climits>
#include <bits/algorithmfwd.h>

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

const string BalancedSelection::toString() const {
    return "Balanced Selection Policy with scores: " + std::to_string(LifeQualityScore) + ", " + std::to_string(EconomyScore) + ", " + std::to_string(EnvironmentScore);
}

BalancedSelection* BalancedSelection::clone() const {
    return new BalancedSelection(*this);
}


int calculateDistance(int x, int y, int z) {
    std::vector<int> nums = {x, y, z};
    int max = *std::max_element(nums.begin(), nums.end());
    int min = *std::min_element(nums.begin(), nums.end());
    return max - min;
}

