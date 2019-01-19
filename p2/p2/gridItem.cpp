/*******************************************************************
 *   CS 307 Programming Assignment 1
 *   File: gridItem.cpp
 *   Author: Sameera Warsi
 *   Desc: This program will simulate the behavior of Digital One-Celled Organisms (DOCOs) within a simulated world.
 *   Date: October 16th, 2018
 *
 *   I attest that this program is entirely my own work
 *******************************************************************/
#include "gridItem.h"

gridItem::gridItem()
{
    d = 0;
    dc = 0;
    numofPellets = 0;
    obstacle = false;
}

void gridItem::setDOCO(DOCO *D)
{
    if(D == 0) {
        d = dc;
        dc = 0;
    }
    else
        d = D;
}

void gridItem::setDOCOClone(DOCO *D)
{
    dc = D;
}

DOCO * gridItem::getDOCO() 
{
    return d;
}

void gridItem::setObstacle() 
{
    obstacle = true;
}

bool gridItem::getObstacle()
{
    return obstacle;
}

void gridItem::setNumberOfPellets(int npellets) 
{
    numofPellets = npellets;
}

int gridItem::getNumberOfPellets() 
{
    return numofPellets;
}
		
void gridItem::addPellet()
{
    numofPellets++;
}

bool gridItem::isEmpty()
{
    if(d == 0 && obstacle == 0)
        return true;

    return false;
}
