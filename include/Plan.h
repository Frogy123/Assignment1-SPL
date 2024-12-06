#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::vector;

enum class PlanStatus {
    AVALIABLE,
    BUSY,
};

class Plan {
    public:
        Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);
        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;
        void setSelectionPolicy(SelectionPolicy *selectionPolicy);
        void step();
        void printStatus();
        const vector<Facility*> &getFacilities() const;
        void addFacility(Facility* facility);
        const string toString() const;
        const string getPolicy() const;
        int getID();
        

        // rule of 5:

        //copy constructor :
        Plan(const Plan &other);

        //destructor:
        ~Plan();


        //copy assignment operator: not clear how to implement and is not used
        Plan& operator=(const Plan &other) = delete;
        //move assignment opperator:not clear how to implement and is not used
        Plan& operator=(const Plan &&other) = delete;

        //move constructor:
        Plan(Plan&& other);




    private:
        int _plan_id;
        const Settlement &_settlement;
        SelectionPolicy *_selectionPolicy; //What happens if we change this to a reference?
        PlanStatus _status;
        vector<Facility*> _facilities;
        vector<Facility*> _underConstruction;
        const vector<FacilityType> &_facilityOptions;
        int _life_quality_score, _economy_score, _environment_score;
        const int _construction_limit; 
        int _free_construction_slots; 
};