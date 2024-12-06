#include "Simulation.h"
#include "Auxiliary.h"
#include "Action.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Auxiliary.h"



//constructor
Simulation::Simulation(const string &configFilePath): _isRunning(false), _planCounter(0), _actionsLogString("") {
    //parse the config file
    std::ifstream file("path/to/your/file.txt"); // Open the file
    std::string line;
    while (std::getline(file, line)) {
        // Process the line
        vector<string> args = Auxiliary::parseArguments(line);
        if(args[0] != "#"){
            if(args[1] == "settlement"){
                addSettlement(new Settlement(args[2], SettlementType(stoi(args[3]))));
            }else if(args[0] == "facility"){
                addFacility(FacilityType(args[1], FacilityCategory(stoi(args[2])),stoi(args[3]),stoi(args[4]),stoi(args[5]),stoi(args[6])));
            }else if(args[0] == "plan"){
                addPlan(getSettlement(args[1]), new NaiveSelection());
            }
        }
    }

    file.close(); // Close the file

    //TODO
}

//adders: 

void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy) {
   _planCounter++;
   Plan* p = new Plan(_planCounter, settlement, selectionPolicy, _facilitiesOptions);
   _plans.push_back(*p);
}

bool Simulation::addSettlement(Settlement *settlement){
    _settlements.push_back(settlement);
    return true;
}

void Simulation:: addAction(BaseAction *action){
    _actionsLog.push_back(action);
}

bool Simulation:: addFacility(FacilityType facility){
    _facilitiesOptions.push_back(facility);
}



// boolean queries 



bool Simulation::isSettlementExists(const string &settlementName){
      for (Settlement* s : _settlements){
         if (s->getName() == settlementName){
               return true;
         }
      }
      return false;
}

bool Simulation::isPlanExists(int planID){
    for(Plan plan: _plans){
        if(plan.getID() == planID)
            return true;
    }
    return false;
}

bool Simulation::isFacilityExists(const string &facilityName){
      for (FacilityType f : _facilitiesOptions){
         if (f.getName() == facilityName){
               return true;
         }
      }
      return false;
}







//getters:


int Simulation::getPlanCounter() const{
      return _planCounter;
} 

Plan& Simulation::getPlan(const int planID){
   return _plans[planID];
}

Settlement& Simulation::getSettlement(const string &settlementName){
    // I assume that settlementName infact exists in _settlements
    for(Settlement* set: _settlements){
        if(set->getName() == settlementName)
            return *set;
    }   
}


// actions:

void Simulation::start(){
    open();
    std::cout << "The simulation has started“" << std::endl;
    string line;
    vector<string> args;
    BaseAction* currentAction = nullptr;
    while (_isRunning)
    {
        std::cin >> line;
        args = Auxiliary::parseArguments(line);

        if(args[0] == "step"){
            int nSteps = stoi(args[1]);
            currentAction = new  SimulateStep(nSteps);

        }
        else if (args[0] == "plan"){
            string settelmentName = args[1], selectionPolicy = args[2];
            currentAction = new AddPlan(settelmentName,selectionPolicy);

        }
        else if (args[0] == "settlement"){
            string settlementName, strSettlementType;
            SettlementType settlmentType = SettlementType(stoi(strSettlementType));  // 0 = village , 1 = city , 2 = metropolis 
            currentAction = new AddSettlement(settlementName,settlmentType);

        }
        else if (args[0] == "facility"){
            // syntax: facility <facility_name> <category> <price> <lifeq_impact> <eco_impact> <env_impact>
            string facility_name;
            FacilityCategory category;
            int price,lifeq_impact,eco_impact,env_impact;
            facility_name = args[1]; 
            category = FacilityCategory(stoi(args[2]));
            price = stoi(args[3]);
            lifeq_impact = stoi(args[4]);
            eco_impact = stoi(args[5]);
            env_impact = stoi(args[6]);
            
            currentAction = new AddFacility(facility_name,category,price,lifeq_impact,eco_impact,env_impact);

        }
        else if (args[0] == "planStatus"){
            //Syntax: planStatus <plan_id>
            int plan_id = stoi(args[1]);
            currentAction = new PrintPlanStatus(plan_id);

        }
        else if (args[0] == "changePolicy"){
            //Syntax: changePolicy <plan_id> <selection_policy>
            int plan_id = stoi(args[1]);
            string selection_policy = args[2];
            currentAction = new ChangePlanPolicy(plan_id,selection_policy);
        }
        else if (args[0] == "log"){
            //Input Syntax: log
            currentAction = new PrintActionsLog();
        }
        else if (args[0] == "close"){
            //Syntax: close
            currentAction = new Close();

        }
        else if (args[0] == "backup"){
            //Syntax: backup
            currentAction = new BackupSimulation();

        }
        else if (args[0] == "restore"){
            //Syntax: restore
            currentAction = new RestoreSimulation();
        }
        currentAction->act(*this);
        _actionsLogString += line + " "+ ActionStatusToString(currentAction->getStatus()) + "\n";// we can assume the input is matching the syntax thus there are no extra chars in the end of the line, 
                                                                                                //without this assumption we would simply add a syntax check funtion
    }
    
    
} 


void Simulation::step(){
    for(Plan plan:_plans){
        plan.step();
    }
}

void Simulation::open(){
    _isRunning = true;
}

void Simulation::close(){
    _isRunning = false;   

}

void Simulation::clear(){
      for (Settlement* s : _settlements){
         s = nullptr;
      }
      for (BaseAction* a : _actionsLog){
         a = nullptr;
      }
}

void Simulation::printActionsLog(){
    std::cout << _actionsLogString << std::endl;
}








// rule of 5:



//copy constructor:
Simulation::Simulation(const Simulation& other):
_isRunning(other._isRunning), _planCounter(other._planCounter),_plans(other._plans), _facilitiesOptions(other._facilitiesOptions)
{
    BaseAction* actCopy;
    for(BaseAction* act: other._actionsLog){
        actCopy = act->clone();
        _actionsLog.push_back(actCopy);
    }
    Settlement* setCopy;
    for(Settlement* set: other._settlements){
        setCopy = new Settlement(*set);
        _settlements.push_back(setCopy);
    }
}

//destructor:
Simulation::~Simulation(){
    for(BaseAction* act: _actionsLog){
            delete act;
    }
    for(Settlement* set:_settlements){
        delete set;
    }
}

// Move Assignment Operator:   
Simulation& Simulation::operator=(Simulation&& other){
    if(&other != this){
        _isRunning = other._isRunning;
        _planCounter = other._planCounter;

        //assign plans
        _plans.clear();

        for(Plan plan: other._plans){
            _plans.push_back(plan);
         }

         //assign facilitiesOptions 
        _facilitiesOptions.clear();
        for(FacilityType fac: other._facilitiesOptions){
            _facilitiesOptions.push_back(fac);
        }


        //delete my stuff
        for(BaseAction* act: _actionsLog){
            delete act;
        }
        for(Settlement* set:_settlements){
            delete set;
         }
         

         
        //steal other's stuff
        _actionsLog = other._actionsLog;
        _settlements = other._settlements;

        //make other forget about the stuff I stole:
        other._actionsLog.clear();
        other._settlements.clear();

    }

    return *this;
}



// move constructor:
Simulation::Simulation(Simulation &&other):
_isRunning(other._isRunning),
_planCounter(other._planCounter),
_actionsLog(other._actionsLog),
_plans(other._plans),
_settlements(other._settlements),
_facilitiesOptions(other._facilitiesOptions)
{
    other.clear();
}


Simulation& Simulation::operator=(Simulation &other){
    if(&other != this){
        _isRunning = other._isRunning;
        _planCounter = other._planCounter;

        //assign plans
        _plans.clear();

        for(Plan plan: other._plans){
            _plans.push_back(plan);
         }

         //assign facilitiesOptions 
        _facilitiesOptions.clear();

        for(FacilityType fac: other._facilitiesOptions){
            _facilitiesOptions.push_back(fac);
        }

        //delete my stuff
        for(BaseAction* act: _actionsLog){
            delete act;
        }
        for(Settlement* set:_settlements){
            delete set;
         }
        for(BaseAction* act: _actionsLog){
            act = act->clone();
        }

        for(Settlement* set:_settlements){
            set = new Settlement(*set);
        }
    }
    return *this;
}


