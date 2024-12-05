#include "Action.h"
#include "SelectionPolicy.h"
#include <vector>
#include <string>
#include <stdexcept>

// Define a vector of valid selection policies
std::vector<std::string> selectionPolicies = {"nve", "bal", "eco", "env"};

// Constructor for AddPlan class
AddPlan::AddPlan(const std::string &settlementName, const std::string &selectionPolicy)
    : _settlementName(settlementName), _selectionPolicy(selectionPolicy) {
    // Check if the provided selection policy is valid
    if (!isApolicy(selectionPolicy)) {
        this->error("Invalid selection policy");
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

    simulation.addAction(this); // Add the action to the simulation

    // Create a new SelectionPolicy object (this line seems to have a typo and should be corrected)
    SelectionPolicy *policy = nullptr;
    if (_selectionPolicy == "nve") {
        policy = new NaiveSelection();
    } else if (_selectionPolicy == "bal") {
        policy = new BalancedSelection(0, 0, 0);       
    } else if (_selectionPolicy == "eco") {
        policy = new EconomySelection();
    } else if (_selectionPolicy == "env") {
        policy = new SustainabilitySelection();
    }
    
   
    if(simulation.isSettlementExists(_settlementName)){
        this->error("Settlement does not exist");
    }else{
        // Add the plan to the simulation
        simulation.addPlan(simulation.getSettlement(_settlementName), policy);
        this->complete();
    }

    
}

// Function to clone the AddPlan action
AddPlan *AddPlan::clone() const {
    return new AddPlan(*this);

// Function to return a string representation of the action
const std::string AddPlan::toString() const {
    return "Add Plan: " + _settlementName + " " + _selectionPolicy;
}

