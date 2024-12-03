#include <Action.h>    
        
        PrintPlanStatus::PrintPlanStatus(int planId):_planId(planId){}
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


        const string PrintPlanStatus::toString() const {}


        