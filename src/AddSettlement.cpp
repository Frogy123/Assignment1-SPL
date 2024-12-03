#include <Action.h>
AddSettlement:: AddSettlement(const string &settlementName,SettlementType settlementType):_settlementName(settlementName),_settlementType(settlementType){}


void AddSettlement::act(Simulation &simulation) {
    if(simulation.isSettlementExists(_settlementName))
        error("Settlement already exists");
    else {
        Settlement* toAdd = new Settlement(_settlementName,_settlementType);
        simulation.addSettlement(toAdd);
        complete();
    }
}
AddSettlement* AddSettlement::clone() const{
    AddSettlement* clone = new AddSettlement(_settlementName,_settlementType);
    return clone;
}
const string AddSettlement::toString() const{
    return BaseAction::toString() + _settlementName + settlementTypeToString(_settlementType);
}