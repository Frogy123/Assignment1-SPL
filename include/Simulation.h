#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
using std::string;
using std::vector;

class BaseAction;
class SelectionPolicy;

class Simulation {
    public:
        Simulation(const string &configFilePath); //eitan
        
        //adders:
        void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy); //eitan
        void addAction(BaseAction *action); //david
        bool addSettlement(Settlement *settlement); //eitan
        bool addFacility(FacilityType facility); //david

    	//booelan quaries:
        bool isSettlementExists(const string &settlementName); //eitan
        bool isPlanExists(int planID); // david V
        bool isFacilityExists(const string &facilityName); //eitan

        //getters:
        int getPlanCounter() const; //eitan
        Settlement &getSettlement(const string &settlementName); //david
        Plan &getPlan(const int planID);//eitan


        //commands:
        void start(); //david
        void step();//david
        void close();//eitan
        void open();//david 
        void printActionsLog(); // david - using the to string method of each action
        void clear(); //eitan


        //rule of 5:
        Simulation(const Simulation &other);
        ~Simulation();
        Simulation(Simulation &&other);
        Simulation& operator=(Simulation &&other);
        Simulation& operator=(Simulation &other);
        

    private:
        bool _isRunning;
        int _planCounter; //For assigning unique plan IDs
        vector<BaseAction*> _actionsLog;
        vector<Plan> _plans;
        vector<Settlement*> _settlements;
        vector<FacilityType> _facilitiesOptions; //by config file
        string _actionsLogString; // saves each action as a string, syntax: <action_name> <action_args> <action_status>
};