/*******************************************************************
*   CS 307 Programming Assignment 1
*   File: DOCOWorld.cpp
*   Author: Sameera Warsi
*   Desc: This program will simulate the behavior of Digital One-Celled Organisms (DOCOs) within a simulated world.
*   Date: October 16th, 2018
*
*   I attest that this program is entirely my own work
*******************************************************************/
#include "DOCOWorld.h"
#include "gridItem.h"
#include "DOCO.h"

DOCOWorld::DOCOWorld(int width, int height)
{
	// This is the constructor for the DOCOWorld

	// Based on the given size of the world set the width and height
	maxi = width;
	maxj = height;

	// Now allocate the gridItems for the world in a 1D array of gridItems
	grid = new gridItem[maxi * maxj];

	// Initially there are no DOCO's so set the head pointer
	// to be NULL
	head = 0;
}
void DOCOWorld::getWidthAndHeight(int & w, int & h)
{
	w = maxi;
	h = maxj;
}

gridItem * DOCOWorld::getgridItem(int X, int Y) 
{
	// Given a cell index such as (X=3,Y=2) get the gridItem
	// associated with this cell

	// First check to see if the given cell index is out of
	// range of the world grid
	if(X < 0 || X >= maxi)
		return 0;
	if(Y < 0 || Y >= maxj)
		return 0;

	// Find the index in the 1D grid array for the gridItem associated
	// with the given cell indicies X,Y
	int I = X + Y * maxi;

	return &grid[I];

}

void DOCOWorld::removeDOCO(DOCO *doco)
{
	int i, X, Y;
	gridItem *g;

	// Query the doco for its indicies in the world grid
	doco->getPosition(X,Y);

	// Find the index in the 1D grid array for the gridItem associated
	// with the given cell indicies X,Y
	i = X + Y * maxi;

	// Get the pointer to the gridItem in the cell
	g = &grid[i];

	// Set the gridItem to indicate that there is no DOCO
	// in this cell
	g->setDOCO(0);

	// Set the dead flag for the DOCO to be true to indicate
	// that this DOCO no longer lives
	doco->setDead();
}

void DOCOWorld::setHead(DOCO *h) 
{
	head = h;
}

DOCO * DOCOWorld::getHead()
{
	return head;
}

