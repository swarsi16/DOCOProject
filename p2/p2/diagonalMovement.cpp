//===========================================================
// diagonalMovement.cpp
// Author: Sameera Warsi
//===========================================================

#include <iostream>
#include <stdlib.h>

#include "diagonalMovement.h"
#include "DOCO.h"
#include "DOCOFactory.h"
#include "gridItem.h"

diagonalMovement::diagonalMovement()
{
    float rand_val = (float) rand()/((float) RAND_MAX);
    int i = (int) (rand_val * 40.f);

    if(i <= 9) 
        setDirection(1);
    else if (i >= 10 && i <= 19)
        setDirection(3);
    else if (i >= 20 && i <= 29)
        setDirection(5);	
    else
        setDirection(7);
}

diagonalMovement::~diagonalMovement()
{
}

void diagonalMovement::Move(DOCOWorld *w,DOCO *d) 
{
    int width, height, xpos, ypos;
    int i, locx[8], locy[8];
    gridItem *g, *top, *bottom, *right, *left, *opposite;
    //Save the current location of this DOCO in the 
    //DOCOWorld
    d->getPosition(xpos,ypos);

    w->getWidthAndHeight(width, height); 

    for(i = 0; i < 8; i++) {
        //Initialize arrays to current locations
        locx[i] = xpos;
        locy[i] = ypos;
    }
    // Based on the current location modify
    // the position based on the 8 different possible
    // directions that the DOCO could move

    // ----------------
    // | NE |  N | NE|
    // ----------------
    // |  W |  * | E |
    // ----------------
    // | SW |  S | SE|
    // ----------------

    // 0: North; 1: Northeast; 2: East; 3: Southeast
    // 4: South; 5: Southwest; 6: West; 7: Northwest

    // North cell
    locy[NORTH] -= 1;
    // Northeast cell
    locx[NORTHEAST] += 1;
    locy[NORTHEAST] -= 1;
    // East cell
    locx[EAST] +=1;
    //Southeast cell
    locx[SOUTHEAST] += 1;
    locy[SOUTHEAST] += 1;
    // South cell 
    locy[SOUTH] += 1;
    //Southwest cell
    locx[SOUTHWEST] -= 1;
    locy[SOUTHWEST] += 1;
    //West cell
    locx[WEST] -= 1;
    //Northwest cell
    locx[NORTHWEST] -= 1;
    locy[NORTHWEST] -= 1;

    w->getWidthAndHeight(width, height); 

    int energyLevel = d->getEnergyLevel();

    // First check if neighbor cells have any food
    for (i = 0; i < 8; i++)
	{
            //For each of the directions, check
            //to make sure DOCO is not on edge of world
            if(locx[i] < 0 || locy[i] < 0 ||
               locx[i] == width || locy[i] == height) 
                continue;

            //Ask the world for gridItem at the
            //neighboring cell
            g = w->getgridItem(locx[i], locy[i]); 
            //If the neighboring cell contains food pellets
            //then the DOCO will consume them
            if(g->getNumberOfPellets()) {
                //Take 10 units of energy away 
                //due to movement
                energyLevel -= 25;
                d->setEnergyLevel(energyLevel);

                //Tell the DOCO to eat all the food pellets
                //in the neighboring cell
                d->Eat(g);
                //Set the DOCO for the neigboring cell
                //to be this DOCO
                g->setDOCO(d);
                //If the energy level for a DOCO reaches 750 
                //or more, then the DOCO will split in half
                // as well as its energy level
                if(d->getEnergyLevel() >= 750) {
                    DOCO *n = d->getNext();
                    d->setEnergyLevel(375);

                    DOCO * newdoco;
                    std::string move;

                    //Determine whether the DOCO is going in the
                    //horizontal, vertical, or diagonal direction

                    move = "DIAGONAL";

                    newdoco = DOCOFactory::getInstance()->createDOCO(move);
                    newdoco->setPosition(locx[i],locy[i]);
                    newdoco->setEnergyLevel(375);
                    newdoco->setLive();

                    if (direction == NORTHEAST)
                        newdoco->setDirection(SOUTHWEST);
                    else if (direction == SOUTHEAST)
                        newdoco->setDirection(NORTHWEST);
                    else if (direction == SOUTHWEST)
                        newdoco->setDirection(NORTHEAST);
                    else if (direction == NORTHWEST)
                        newdoco->setDirection(SOUTHEAST);

                    g->setDOCOClone(newdoco);

                    d->setNext(newdoco);
                    newdoco->setNext(n);

                }
                //Ask the world for the gridItem
                //for the original location of this DOCO
                //before movement
                g = w->getgridItem(xpos, ypos);
                //Set the DOCO pointer for that gridItem to be 0
                g->setDOCO(0);
                //Update position of this DOCO
                d->setPosition(locx[i],locy[i]);

                return;
            }
	}

    // Now try to move the DOCO in its current direction
    if(locx[direction] >= 0 && locy[direction] >=0 
       && locx[direction] != width && locy[direction] != height) 
	{
            //Ask the world for the gridItem in the neighboring
            //cell in the direction of movement
            g = w->getgridItem(locx[direction], locy[direction]);
            //Check if the neighboring cell does not contain a DOCO
            // or obstacle
            if(g->isEmpty()) {
                //Decrement energy level by 10 due to
                //movement
                energyLevel -= 25;
                d->setEnergyLevel(energyLevel);

                //If the energy level reaches 0
                if(energyLevel <= 0) {
                    //mark the DOCO as dead
                    d->setDead();
                    //Ask the world for the gridItem
                    //at this DOCO's position
                    g = w->getgridItem(xpos, ypos);
                    //Remove the DOCO from the world
                    g->setDOCO(0);

                    return;
                }

                //Set the DOCO for the neigboring cell
                //to be this DOCO
                g->setDOCO(d);
                //Ask the world for the gridItem 
                //at this DOCOs position
                g = w->getgridItem(xpos, ypos);
                //Remove the DOCO from previous location
                g->setDOCO(0);

                //Update the position of the DOCO
                d->setPosition(locx[direction],locy[direction]);

                return;
            }
	}

    //If the DOCO did not find food and could
    //not move in its current direction
    //then the following needs to be done:
    //
    //initialize all directions to 0
    top = 0;
    bottom = 0;
    right = 0;
    left = 0;
    opposite = 0;
	
    //if able to move in the north direction
    //DOCO moves to the top
    if(locy[NORTH] >= 0)
	{
            g = w->getgridItem(xpos, locy[NORTH]);
            if(g->isEmpty())
                top = g;
	}
    //if able to move in the south direction
    //DOCO moves to the bottom
    if(locy[SOUTH] != height)
	{
            g = w->getgridItem(xpos, locy[SOUTH]);
            if(g->isEmpty())
                bottom = g;
	}
    //if able to move in the west direction
    //DOCO moves to the left
    if(locx[WEST] >= 0)
	{
            g = w->getgridItem(locx[WEST], ypos);
            if(g->isEmpty())
                left = g;
	}
    //if able to move in the east direction
    //DOCO moves to the east
    if(locx[EAST] != width)
	{
            g = w->getgridItem(locx[EAST], ypos);
            if(g->isEmpty())
                right = g;
	}
    //whatever the initial direction is
    //change to its opposite direction
    if(direction == NORTHEAST && (locx[SOUTHWEST] >= 0 && locy[SOUTHWEST] < height))
	{
            g = w->getgridItem(locx[SOUTHWEST],locy[SOUTHWEST]);
            if(g->isEmpty())
                opposite = g;
	}
    if(direction == SOUTHEAST && (locx[NORTHWEST] >= 0 && locy[NORTHWEST] >= 0))
	{
            g = w->getgridItem(locx[NORTHWEST],locy[NORTHWEST]);
            if(g->isEmpty())
                opposite = g;
	}	
    if(direction == SOUTHWEST && (locx[NORTHEAST] < width && locy[NORTHEAST] >= 0))
	{
            g = w->getgridItem(locx[NORTHEAST],locy[NORTHEAST]);
            if(g->isEmpty())
                opposite = g;
	}
    if(direction == NORTHWEST && (locx[SOUTHEAST] < width && locy[SOUTHWEST] < height))
	{
            g = w->getgridItem(locx[SOUTHEAST],locy[SOUTHEAST]);
            if(g->isEmpty())
                opposite = g;
	}

    // See if were on the edge in either the EAST or WEST
    // direction
    if(locx[direction] < 0 || locx[direction] == width ||
       locy[direction] < 0 || locy[direction] == height)
	{
            // If we have both a top and bottom then choose randomly
            // between the two. Otherwise, if there is a top and not
            // a bottom then choose top else choose bottom
	
            if(right && left && top && bottom)
		{
                    float rand_val = (float) rand()/((float) RAND_MAX);
                    int dir = (int) 40*rand_val;
                    if(dir < 10)
                        g = right;
                    else if(dir >= 10 && dir < 20)
                        g = left;
                    else if(dir >= 20 && dir < 30)
                        g = top;
                    else
                        g = bottom;
		}
            else if(right)
                g = right;
            else if (left)
                g = left;
            else if (top)
                g = top;
            else if (bottom)
                g = bottom;

            // If moving in NORTH
            if(direction == NORTHEAST)
                direction = SOUTHWEST; // Reverse direction and go west
            else if(direction == SOUTHEAST)
                direction = NORTHWEST;
            else if(direction == SOUTHWEST)
                direction = NORTHEAST;
            else if(direction == NORTHWEST)
                direction = SOUTHEAST;

            //Decrement energy level by 10 due to
            //movement
            energyLevel -= 25;
            d->setEnergyLevel(energyLevel);

            //If the energy level reaches 0
            if(energyLevel <= 0) {
                //mark the DOCO as dead
                d->setDead();
                //Ask the world for the gridItem
                //at this DOCO's position
                g = w->getgridItem(xpos, ypos);
                //Remove the DOCO from the world
                g->setDOCO(0);

                return;
            }

            //Update the position of the DOCO
            if(g == right)
                d->setPosition(xpos + 1,ypos);
            else if(g == left)
                d->setPosition(xpos - 1,ypos);
            else if(g == top)
                d->setPosition(xpos,ypos - 1);
            else if(g == bottom)
                d->setPosition(xpos,ypos + 1);

            //Set the DOCO for the neigboring cell
            //to be this DOCO
            g->setDOCO(d);
            //Ask the world for the gridItem 
            //at this DOCOs position
            g = w->getgridItem(xpos, ypos);
            //Remove the DOCO from previous location
            g->setDOCO(0);

            return;
	}

    // If have a gridItem in the opposite direction to the one the
    // DOCO is moving then reverse the direction
    if(opposite != 0)
	{
            g = opposite;

            if(direction == NORTHEAST)
                direction = SOUTHWEST; // Reverse direction and go west
            else if(direction == SOUTHEAST)
                direction = NORTHWEST; // Reverse direction and go east
            else if(direction == SOUTHWEST)
                direction = NORTHEAST; // Reverse direction and go east
            else if(direction == NORTHWEST)
                direction = SOUTHEAST; // Reverse direction and go east
	}

    //Decrement energy level by 10 due to
    //movement
    energyLevel -= 25;
    d->setEnergyLevel(energyLevel);

    //If the energy level reaches 0
    if(energyLevel <= 0) {
        //mark the DOCO as dead
        d->setDead();
        //Ask the world for the gridItem
        //at this DOCO's position
        g = w->getgridItem(xpos, ypos);
        //Remove the DOCO from the world
        g->setDOCO(0);

        return;
    }

    // Update the position of the DOCO
    if(g == opposite) {
        if(direction == NORTHEAST)
            {
                d->setPosition(xpos + 1,ypos - 1);
            }
        else if(direction == SOUTHEAST) 
            {
                d->setPosition(xpos + 1,ypos + 1);
            }
        else if(direction == SOUTHWEST) 
            {
                d->setPosition(xpos - 1,ypos + 1);
            }
        else if(direction == NORTHWEST)
            {
                d->setPosition(xpos - 1,ypos - 1);
            }
    }
    else if(right) 
	{
            g = right;
            d->setPosition(xpos + 1,ypos);
	}
    else if(left)
	{
            g = left;
            d->setPosition(xpos - 1,ypos);
	} 
    else if(top)
	{
            g = top;
            d->setPosition(xpos,ypos - 1);
	}
    else if(bottom)
	{
            g = bottom;
            d->setPosition(xpos,ypos + 1);
	}

    //Set the DOCO for the neigboring cell
    //to be this DOCO
    g->setDOCO(d);
    //Ask the world for the gridItem 
    //at this DOCOs position
    g = w->getgridItem(xpos, ypos);
    //Remove the DOCO from previous location
    g->setDOCO(0);

    return;
}
