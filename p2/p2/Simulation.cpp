/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: Simulation.cpp
*   Author: Sameera Warsi
*   Desc: This program will simulate the behavior of Digital One-Celled Organisms (DOCOs) within a simulated world.
*   Date: October 16th, 2018
*
*   I attest that this program is entirely my own work
*******************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <sys/types.h>     // needed for the _ftime() function
#include <sys/timeb.h>     // contains definition of _timeb struct
#include <time.h>          // needed for other time functions and structures

#include "Simulation.h"
#include "DataParser.h"
#include "DOCO.h"
#include "gridItem.h"

using namespace std;

Simulation::Simulation() 
{
	world = 0;
	docofactory = DOCOFactory::getInstance();
}

bool Simulation::loadData()
{
	char filename[500];

	std::cout << "Input date file name: ";
	std::cin >> filename;

	DataParser * parser = DataParser::getInstance(filename);

	if (parser->getDOCOWorldWidth() < 0)
		return 0;

	//Setting the seed for the random function
	srand(1);

	int width, height;
	width = parser->getDOCOWorldWidth();
	height = parser->getDOCOWorldHeight();

	//Creating a DOCOWorld of width and height cells
	world = new DOCOWorld(width, height);

	//Ask the parser for the number of DOCOs
	int nDOCOs = parser->getDOCOCount();

	float rand_val;
	int i, xpos, ypos;
	char movement[20];
	DOCO *d, *prevDOCO;
	gridItem *g;
	string move;

	for(i = 0; i < nDOCOs; i++) { 
		//Ask the parser for the movement and position of each DOCO
		parser->getDOCOData(movement, &xpos, &ypos);
		move = movement;

		//Create a DOCO at this location in the DOCOWorld
		d = docofactory->createDOCO(move);
		d->setPosition(xpos, ypos);

		////Obtain a random value between 0-1
		//rand_val = (float) rand()/((float) RAND_MAX);
		////Based on the random value, set a direction of movement
		//// between 0-7. 
		//// 0: North; 1: Northeast; 2: East; 3: Southeast
		//// 4: South; 5: Southwest; 6: West; 7: Northwest
		//d->setDirection((int)(7*rand_val));

		//Ask the world for the gridItem at position xpos, ypos
		g = world->getgridItem(xpos,ypos);

		//Set the DOCO on this gridItem
		g->setDOCO(d);

		//Setting the head to be the first DOCO
		if(world->getHead() == 0) 
		{
			world->setHead(d);
			prevDOCO = d;
			continue;
		}
		//Update the singly linked list to set the next pointer
		// for the previous DOCO to be this DOCO
		prevDOCO->setNext(d);

		prevDOCO = d;
	}

	//Randomly distribute food pellets into world grid
	for(i = 0; i < parser->getFoodCount(); i++) 
	{
		//Get a random value between 0-1
		rand_val = (float) rand()/((float) RAND_MAX);
		//Compute the x position between 0
		// to width - 1
		xpos = (int) (rand_val*(width-1));
		rand_val = (float) rand()/((float) RAND_MAX);
		//Compute the y position between 0
		// to height - 1
		ypos = (int) (rand_val*(height-1));

		//Ask the world for gridItem at this position
		g = world->getgridItem(xpos, ypos);
		//Add pellet to this cell
		g->addPellet();

		//If a DOCO exists in cell, eat
		if(g->getDOCO()) {
			g->getDOCO()->Eat(g);
		}
	}

	for(i = 0; i < parser->getObstacleCount(); i++) { 
		//Ask the parser for the movement and position of each DOCO
		parser->getObstacleData( &xpos, &ypos);

		//Ask the world for the gridItem at position xpos, ypos
		g = world->getgridItem(xpos,ypos);

		//Set the DOCO on this gridItem
		g->setObstacle();
	}

	return 1;
}

#if !defined(WIN32)
#define _timeb timeb
#define _ftime ftime
#endif

bool Simulation::run()
{
	struct _timeb   tStruct;
	double          thisTime;
	double          outputTime;
	bool            done = false;  // while loop flag

	int i,j,width,height;
	int numberNewPellets;
	int xpos,ypos;
	float rand_val;

	gridItem *g;

	//Get the width and height from DOCOWorld
	world->getWidthAndHeight(width, height);

	int cnt = 0; //Set counter to count the number of live DOCOs 
	_ftime(&tStruct);	// Get start time
	thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0); // Convert to double
	outputTime = thisTime + 1.0; // Set next 1 second interval time

	while(true)     // Start an eternal loop
	{
		_ftime(&tStruct);    // Get the current time
		thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000.0); // Convert to double
		// Check for 1 second interval to print status to screen
		if(thisTime >= outputTime)
		{
			//Get a random value between 0-1
			rand_val = (float) rand()/((float) RAND_MAX);
			// Now make it between 1-10
			numberNewPellets = (int) (rand_val*9.f) + 1;

			for(i=0; i < numberNewPellets; i++)
			{
				xpos = (int) (rand_val*(width-1));
				rand_val = (float) rand()/((float) RAND_MAX);
				//Compute the y position between 0
				// to height - 1
				ypos = (int) (rand_val*(height-1));

				//Ask the world for gridItem at this position
				g = world->getgridItem(xpos, ypos);
				if(g->isEmpty() && g->getNumberOfPellets() < 3) 
				{
					//Add pellet to this cell
					g->addPellet();
				}
			}

			//Clear the console window
#if !defined(WIN32)
			system("clear");
#else
			system("CLS");
#endif

			cout << "Program 1: Demonstration DOCO Simulation\n  ";
			for(i = 0; i < width; i++) 
				cout << i/10;
			cout << endl << "  ";
			for(i = 0; i < width; i++) 
				cout << i%10;
			cout << endl;

			//Get a pointer to the first DOCO
			DOCO *d = world->getHead();

			cnt = 0; //Initialize the number of live DOCOs to be 0
			while(d) {
				//If this DOCO is dead, get the next DOCO
				if(d->getDead()) {
					d = d->getNext();
					continue;
				}
				//Increment the number of live DOCOs
				cnt++;
				//Move DOCO
				d->Move(world);
				d = d->getNext();
			}
			//cout << "NDOCOS " << cnt << endl;
			// If no live DOCOS, then quit
			if(cnt == 0) {
				cout << "No DOCO's left in the world" << endl;
				return 1; 
			}

			int dir;
			for (j=0; j < height; j++) {
				cout << setw(2) << j;
				for(i=0; i < width; i++) {
					g = world->getgridItem(i, j);

					if(g->getDOCO()) 
					{
						dir = g->getDOCO()->getDirection();
						if(dir == 0 || dir == 4)
							cout << "|";
						else if(dir == 2 || dir == 6)
							cout << "=";
						else
							cout << "X";
					}
					else if (g->getNumberOfPellets()) 
						cout << ".";
					else if (g->getObstacle())
						cout << "\xB2";
					else
						cout << "-";
				}
				cout << endl;
			}

			// Call functions to perform actions at 1 second intervals
			outputTime += 1.0; // Set time for next 1 second interval
		}
		// Do other stuff here
	}

	return true;
}

