/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: main.cpp
*   Author: Sameera Warsi
*   Desc: This program will simulate the behavior of Digital One-Celled Organisms (DOCOs) within a simulated world.
*   Date: October 16th, 2018
*
*   I attest that this program is entirely my own work
*******************************************************************/
#include <iostream>

#include "Simulation.h"

int main()
{
	//Instantiate a simulation object
	Simulation sim;
	//Load the simulation data
	sim.loadData();
	//Run the simulation
	sim.run();

	return 1;

}