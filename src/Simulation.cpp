#include "Simulation.h"

Simulation:isSettlementExists(const string &settlementName) {
    for (int i = 0; i < settlements.size(); i++) {
        if (settlements[i]->getName() == settlementName) {
            return true;
        }
    }
    return false;
} 