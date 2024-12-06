#include "Facility.h"

//FacilityType:
FacilityType::FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score):
 name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score) //first intalization
     {}

const string &FacilityType::getName() const{
    return name;
}

int FacilityType::getCost() const{
    return price;
}

int FacilityType::getLifeQualityScore() const{
    return lifeQuality_score;
}

int FacilityType::getEnvironmentScore() const{
    return environment_score;
}

int FacilityType::getEconomyScore() const{
    return economy_score;
}

FacilityCategory FacilityType::getCategory() const{
    return category;
}



//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//Facility:
//constructor 1
Facility:: Facility(const string &name, const string &settlementName, const FacilityCategory category,const int price, const int lifeQuality_score, const int economy_score,
const int environment_score): 
FacilityType::FacilityType(name,category,price,lifeQuality_score,economy_score,environment_score),
settlementName(settlementName),
status(FacilityStatus::UNDER_CONSTRUCTIONS),
timeLeft(price)
{}


//constructor 2
Facility:: Facility(const FacilityType &type, const string &settlementName):  
FacilityType::FacilityType(type),
settlementName(settlementName),
status(FacilityStatus::UNDER_CONSTRUCTIONS),
timeLeft(price)
{}



//getters:
const string& Facility::getSettlementName() const{
    return settlementName;
}


const int Facility::getTimeLeft() const{
    return timeLeft;
}

const FacilityStatus& Facility::getStatus() const{
    return status;
}

//setters:

void Facility::setStatus(FacilityStatus status){
    status = status;
}

//step
FacilityStatus Facility::step(){
    timeLeft--;
    if(timeLeft == 0){
        status = FacilityStatus::OPERATIONAL;
    }
    return status;
}


//to string:
const string Facility::toString() const{
    
    return "settlement name: " + settlementName +"\nstatus: " +  FacilityStatusToString(status) + "\ntime left: " +std::to_string(timeLeft);
}


const string Facility::FacilityStatusToString(FacilityStatus status) const{
    string status_str;
    switch(status){
        case FacilityStatus::UNDER_CONSTRUCTIONS:
            status_str = "UNDER_CONSTRUCTIONS";
            break;
        case FacilityStatus::OPERATIONAL:
            status_str = "CITY";
            break;
    }
    return status_str;
}





