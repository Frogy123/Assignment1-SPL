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
        void start(); //david
        void addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy); //eitan
        void addAction(BaseAction *action); //david
        bool addSettlement(Settlement *settlement); //eitan
        bool addFacility(FacilityType facility); //david
        bool isSettlementExists(const string &settlementName); //eitan
        bool isFacilityExists(const string &facilityName); //eitan
        bool isPlanExists(const int planID); //david
        int getPlanCounter() const; //eitan
        Settlement &getSettlement(const string &settlementName); //david
        Plan &getPlan(const int planID) noexcept(false);//eitan
        void step();//david
        void close();//eitan
        void open();//david
        void printActionsLog(); // david - using the to string method of each action

        

    private:
        bool isRunning;
        int planCounter; //For assigning unique plan IDs
        vector<BaseAction*> actionsLog;
        vector<Plan> plans;
        vector<Settlement*> settlements;
        vector<FacilityType> facilitiesOptions; //by config file

};