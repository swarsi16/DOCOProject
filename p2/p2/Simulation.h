//===========================================================
// Simulation.h
// Author: Sameera Warsi
//===========================================================
#ifndef SIMULATION_H
#define SIMULATION_H

#include "DOCOWorld.h"
#include "DOCOFactory.h"

class Simulation 
{
 private: 
    DOCOWorld *world; 
    DOCOFactory *docofactory;

 public:
    Simulation();

    bool loadData();
    bool run();

};

#endif
