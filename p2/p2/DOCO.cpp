/*******************************************************************
 *   CS 307 Programming Assignment 1
 *   File: DOCO.cpp
 *   Author: Sameera Warsi
 *   Desc: This program will simulate the behavior of Digital One-Celled Organisms (DOCOs) within a simulated world.
 *   Date: October 16th, 2018
 *
 *   I attest that this program is entirely my own work
 *******************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string>

#include "DOCO.h"
#include "DOCOFactory.h"
#include "Movement.h"
#include "gridItem.h"

DOCO::DOCO()
{
    dead = false;
    energyLevel = 500;
    next = 0;
}

DOCO::DOCO(int X, int Y)
{
    dead = false;
    positionX = X;
    positionY = Y;
    energyLevel = 500;
    next = 0;
}

void DOCO::setDirection(int dir) 
{
    mv->setDirection(dir);
}

int DOCO::getDirection() 
{
    return mv->getDirection();
}

void DOCO::setDead() 
{
    dead = true;
}

void DOCO::setLive()
{
    dead = false;
}

bool DOCO::getDead()
{
    return dead;
}

void DOCO::setPosition(int X, int Y) 
{
    positionX = X;
    positionY = Y;
}

void DOCO::getPosition(int & X, int & Y) 
{
    X = positionX;
    Y = positionY;
}

void DOCO::setNext(DOCO *n) 
{
    next = n;
}

DOCO * DOCO::getNext() 
{
    return next;
}

void DOCO::setEnergyLevel(int level)
{
    energyLevel = level;
}

int DOCO::getEnergyLevel()
{
    return energyLevel;
}

void DOCO::Eat(gridItem *g)
{
    // Update energy level by adding 
    //the number of food pellets times 10
    energyLevel += 50.*g->getNumberOfPellets();

    //Once all pellets are consumed, set number
    //of pellets to 0
    g->setNumberOfPellets(0);
}

void DOCO::setMovement(Movement *m)
{
    mv = m;
}

void DOCO::Move(DOCOWorld *w) 
{
    mv->Move(w,this);
}

