#include "Action.h"
#include "SelectionPolicy.h"
#include "Settlement.h"
#include <vector>
#include <string>
#include <stdexcept>



//BaseAction:

BaseAction::BaseAction(): _status(ActionStatus::PENDING), _errorMsg("") {
}

ActionStatus BaseAction::getStatus() const {
    return _status;
}

void BaseAction::complete() {
    _status = ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg) {
    _status = ActionStatus::ERROR;
    this->_errorMsg = errorMsg;
}

const std::string& BaseAction::getErrorMsg() const {
    return _errorMsg;
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//AddFacility 
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
    BaseAction(),_facilityName(facilityName), _facilityCategory(facilityCategory), _price(price), _lifeQualityScore(lifeQualityScore), _economyScore(economyScore), _environmentScore(environmentScore) {};

void AddFacility::act(Simulation &simulation) {

    simulation.addAction(this); // Add the action to the simulation
    if(simulation.isFacilityExists(_facilityName)){
        this->error("Facility already exists");
    }else{
    // Create a new Facility object
    FacilityType *facility = new FacilityType(_facilityName, _facilityCategory, _price, _lifeQualityScore, _economyScore, _environmentScore);
    
    // Add the facility to the simulation
    simulation.addFacility(*facility);
    this->BaseAction::complete();
    }
    
    //AddFacility *AddFacility::clone() const {

}

AddFacility *AddFacility::clone() const {
    return new AddFacility(*this);
}

// Function to return a string representation of the action
const string AddFacility::toString() const {
    // suntax:<action_1_name> <action_1_args> <action_1_status>

    return "Add Facility: " + _facilityName + " " + std::to_string(static_cast<int>(_facilityCategory)) + " " + std::to_string(_price) + " " + std::to_string(_lifeQualityScore) + " " + std::to_string(_economyScore) + " " + std::to_string(_environmentScore);
}




//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




// AddPlan

// Define a vector of valid selection policies
std::vector<std::string> selectionPolicies = {"nve", "bal", "eco", "env"};

// Constructor for AddPlan class
AddPlan::AddPlan(const std::string &settlementName, const std::string &selectionPolicy)
    :BaseAction(),  _settlementName(settlementName), _selectionPolicy(selectionPolicy) {
    // Check if the provided selection policy is valid
    if (!isApolicy(selectionPolicy)) {
        error("Invalid selection policy");
    }
    
}

// Function to check if the provided policy is valid
bool AddPlan::isApolicy(const std::string &policy) {
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
        this->BaseAction::error("Settlement does not exist");
    }else{
        // Add the plan to the simulation
        simulation.addPlan(simulation.getSettlement(_settlementName), policy);
        this->BaseAction::complete();
    }

    
}

// Function to clone the AddPlan action
AddPlan *AddPlan::clone() const {
    return new AddPlan(*this);
}
// Function to return a string representation of the action
const std::string AddPlan::toString() const {
    return "Add Plan: " + _settlementName + " " + _selectionPolicy;
}



//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//AddSettlement
AddSettlement:: AddSettlement(const string &settlementName,SettlementType settlementType):
BaseAction(), 
_settlementName(settlementName),
_settlementType(settlementType){}


void AddSettlement::act(Simulation &simulation) {
    if(simulation.isSettlementExists(_settlementName))
        this->BaseAction::error("Settlement already exists");
    else {
        Settlement* toAdd = new Settlement(_settlementName,_settlementType);
        simulation.addSettlement(toAdd);
        this->BaseAction::complete();
    }
}
AddSettlement* AddSettlement::clone() const{
    AddSettlement* clone = new AddSettlement(_settlementName,_settlementType);
    return clone;
}
const string AddSettlement::toString() const{
    return "AddSettlment" + _settlementName + SettlementTypeTostring(_settlementType);
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//BackupSimulation 
extern Simulation* backup;


BackupSimulation::BackupSimulation(): BaseAction(){}

void BackupSimulation::act(Simulation &simulation) {
    simulation.addAction(this);

    backup = new Simulation(simulation);
    complete();
}

BackupSimulation* BackupSimulation::clone() const {
    return new BackupSimulation();
}


const string BackupSimulation::toString() const {
    return "Backup";
}

        
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//restoreSimulation 
extern Simulation* backup;


RestoreSimulation::RestoreSimulation(): BaseAction(){}

void RestoreSimulation::act(Simulation &simulation) {
    simulation.addAction(this);
    if(backup == nullptr){
        error("No backup available");

    }
    simulation = *backup;
    complete();
}

RestoreSimulation* RestoreSimulation::clone() const {
    return new RestoreSimulation();
}


const string RestoreSimulation::toString() const {
    return "Restore";
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//ChangePlanPolicy
ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy): 
BaseAction(),
 _planId(planId), 
 _newPolicy(newPolicy) 
 {};

void ChangePlanPolicy::act(Simulation &Simulation){
    
    Simulation.addAction(this);
    
    if(!Simulation.isPlanExists(_planId)){
        this->BaseAction::error("Plan does not exist");
        return;
    }
    
    Plan &plan = Simulation.getPlan(_planId); //need to throw erorr if plan does not exist

    if(_newPolicy == plan.getPolicy()){
        this->error("The new policy is the same as the current policy");
        return;
    }


    SelectionPolicy *policy = nullptr;
    if (_newPolicy == "nve") {
        policy = new NaiveSelection();
    } else if (_newPolicy == "bal") {
        policy = new BalancedSelection(plan.getlifeQualityScore(), plan.getEconomyScore(), plan.getEnvironmentScore());       
    } else if (_newPolicy == "eco") {
        policy = new EconomySelection();
    } else if (_newPolicy == "env") {
        policy = new SustainabilitySelection();
    }

    plan.setSelectionPolicy(policy);
    this->complete();
    
}

ChangePlanPolicy* ChangePlanPolicy::clone() const {
    return new ChangePlanPolicy(_planId,_newPolicy);
}

const string ChangePlanPolicy::toString() const {
    return "ChangePolicy" + std::to_string(_planId) + " " + _newPolicy;
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Close

Close::Close(): BaseAction() {};

void Close::act(Simulation &simulation) {
    simulation.addAction(this); // Add the action to the simulation
    
    for(int i = 0; i < simulation.getPlanCounter(); i++){
        simulation.getPlan(i).printStatus();
    }   

    this->complete();
    simulation.close(); 
    
}

Close* Close::clone() const {
    return new Close();
}

const string Close::toString() const {
    return "Close";
}   


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//PrintActionsLog 

PrintActionsLog::PrintActionsLog(): BaseAction(){}
void PrintActionsLog::act(Simulation &simulation) {
        simulation.printActionsLog();
        complete();
}
PrintActionsLog* PrintActionsLog::clone() const {
    return new PrintActionsLog();
}
const string PrintActionsLog::toString() const {
    return "PrintActionsLog";
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//PrintPlanStatus 
PrintPlanStatus::PrintPlanStatus(int planId):
BaseAction(),
_planId(planId){}


void PrintPlanStatus::act(Simulation &simulation){
    simulation.addAction(this);

    Plan p = simulation.getPlan(_planId);
    if(simulation.isPlanExists(_planId)){
        p.printStatus();
        complete();
    } 
    else  error("Plan doesn’t exist");
}



PrintPlanStatus* PrintPlanStatus::clone() const {
    return new PrintPlanStatus(_planId);
}



const string PrintPlanStatus::toString() const {
    return "PlanStatus" + std::to_string(_planId);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        
//SimulateStep

SimulateStep::SimulateStep(const int numOfSteps): 
BaseAction(),
_numOfSteps(numOfSteps){}

void SimulateStep::act(Simulation &simulation) {
    simulation.addAction(this);

    for(int i = 0; i< _numOfSteps; i++){
        simulation.step();
    }
    complete();
}


const string SimulateStep::toString() const {
    return std::to_string(_numOfSteps);
}


SimulateStep* SimulateStep::clone() const{
    return new SimulateStep(_numOfSteps);
}
