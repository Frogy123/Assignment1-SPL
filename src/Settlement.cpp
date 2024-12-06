#include "../include/Settlement.h"

// constuctors:
Settlement:: Settlement(const string &name, SettlementType type) : name(name), type(type) {}


// getters:
const string& Settlement::getName() const{
    return name;
}

SettlementType Settlement::getType() const{
    return type;  
}

// to string:
const string Settlement::toString() const{
    string type_str = SettlementTypeTostring(type);
    return "name: " + name + "type: " + type_str ;
}

string SettlementTypeTostring(SettlementType type){
    string type_str;
    switch(type) {
        case SettlementType::VILLAGE:
            type_str = "VILLAGE";
            break;
        case SettlementType::CITY:
            type_str = "CITY";
            break;
        case SettlementType::METROPOLIS:
            type_str = "METROPOLIS";
            break;
    }
    return type_str;
}
