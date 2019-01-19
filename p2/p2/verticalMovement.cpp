//===========================================================
// verticalMovement.cpp
// Author: Sameera Warsi
//===========================================================

#include <iostream>
#include <stdlib.h>

#include "verticalMovement.h"
#include "DOCO.h"
#include "DOCOFactory.h"
#include "gridItem.h"

verticalMovement::verticalMovement()
{
    float rand_val = (float) rand()/((float) RAND_MAX);
    int i = (int) (rand_val * 10.f);
    if(i <= 4) 
        setDirection(0);
    else
        setDirection(4);
}

verticalMovement::~verticalMovement()
{
}

void verticalMovement::Move(DOCOWorld *w,DOCO *d) 
{
    int width, height, xpos, ypos;
    int i, locx[8], locy[8];
    gridItem *g, *right,*left, *opposite;
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
                //Take 25 units of energy away 
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

                    move = "VERTICAL";;

                    newdoco = DOCOFactory::getInstance()->createDOCO(move);
                    newdoco->setPosition(locx[i],locy[i]);
                    newdoco->setEnergyLevel(375);
                    newdoco->setLive();
                    //When the DOCO is cloned, it will take
                    //the opposite direction of the DOCO its
                    //cloned from

                    if (direction == NORTH)
                        newdoco->setDirection(SOUTH);
                    else if (direction == SOUTH)
                        newdoco->setDirection(NORTH);

                    g->setDOCOClone(newdoco);

                    d->setNext(newdoco);
                    newdoco->setNext(n);
                }			//Ask the world for the gridItem
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
    if(locy[direction] >= 0 && locy[direction] != height) 
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

    right = 0;
    left = 0;
    opposite = 0;

    if(locx[WEST] >= 0)
	{
            g = w->getgridItem(locx[WEST], ypos);
            if(g->isEmpty())
                left = g;
	}

    if(locx[EAST] != width)
	{
            g = w->getgridItem(locx[EAST], ypos);
            if(g->isEmpty())
                right = g;
	}

    if(direction == NORTH && locy[SOUTH] < height)
	{
            g = w->getgridItem(xpos, locy[SOUTH]);
            if(g->isEmpty())
                opposite = g;
	}

    if(direction == SOUTH && locy[NORTH] >= 0)
	{
            g = w->getgridItem(xpos, locy[NORTH]);
            if(g->isEmpty())
                opposite = g;
	}

    // See if were on the edge in either the EAST or WEST
    // direction
    if(locy[direction] < 0 || locy[direction] == height)
	{
            // If we have both a top and bottom then choose randomly
            // between the two. Otherwise, if there is a top and not
            // a bottom then choose top else choose bottom

            if(right && left){
                float rand_val = (float) rand()/((float) RAND_MAX);
                if((int) 20*rand_val < 10)
                    g = right;
                else
                    g = left;
            }else if(right)
                g = right;
            else
                g = left;

            // If moving in NORTH
            if(direction == NORTH)
                direction = SOUTH; // Reverse direction and go west
            else
                direction = NORTH;

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
                d->setPosition(xpos+1,ypos);
            else
                d->setPosition(xpos-1,ypos);

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

            if(direction == NORTH)
                direction = SOUTH; // Reverse direction and go west
            else
                direction = NORTH; // Reverse direction and go east
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
        if(direction == NORTH)
            d->setPosition(xpos,ypos-1);
        else
            d->setPosition(xpos,ypos+1);
    }else if(right) {
        g = right;
        d->setPosition(xpos+1,ypos);
    }else {
        g = left;
        d->setPosition(xpos-1,ypos);
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
