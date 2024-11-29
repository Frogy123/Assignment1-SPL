#include "Action.h"
#include "SelectionPolicy.h"
#include <vector>
#include <string>
#include <stdexcept>

// Define a vector of valid selection policies
std::vector<std::string> selectionPolicies = {"nve", "bal", "eco", "env"};

// Constructor for AddPlan class
AddPlan::AddPlan(const std::string &settlementName, const std::string &selectionPolicy)
    : settlementName(settlementName), selectionPolicy(selectionPolicy) {
    // Check if the provided selection policy is valid
    if (!isApolicy(selectionPolicy)) {
        throw std::invalid_argument("Invalid selection policy");
    }

    
}

// Function to check if the provided policy is valid
bool isApolicy(const std::string &policy) {
    // Iterate through the list of valid policies
    for (int i = 0; i < selectionPolicies.size(); i++) {
        // If the policy matches one in the list, return true
        if (selectionPolicies[i] == policy) {
            return true;
        }
    }
    // If no match is found, return false
    return false;
}

// Function to perform the action of adding a plan to the simulation
void AddPlan::act(Simulation &simulation) {
    // Create a new SelectionPolicy object (this line seems to have a typo and should be corrected)
    SelectionPolicy *policy = nullptr;
    if (selectionPolicy == "nve") {
        policy = new NaiveSelection();
    } else if (selectionPolicy == "bal") {
        policy = new BalancedSelection(0, 0, 0);       
    } else if (selectionPolicy == "eco") {
        policy = new EconomySelection();
    } else if (selectionPolicy == "env") {
        policy = new SustainabilitySelection();
    }
    // Add the plan to the simulation
    if(simulation.isSettlementExists(settlementName)){
        erorr("Settlement does not exist");
    }
    simulation.addPlan(simulation.getSettlement(settlementName), policy);
    simulation.addAction(this);
}
