#include <Action.h>


PrintActionsLog::PrintActionsLog(){}
void PrintActionsLog::act(Simulation &simulation) {
        simulation.printActionsLog();
        complete();
}
PrintActionsLog* PrintActionsLog::clone() const {}
const string PrintActionsLog::toString() const {}
