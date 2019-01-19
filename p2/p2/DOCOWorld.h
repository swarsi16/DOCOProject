//===========================================================
// DOCOWorld.h
// Purpose: Creating the dimensions for DOCO World.
// Author: Sameera Warsi
//===========================================================
#ifndef DOCOWORLD_H
#define DOCOWORLD_H

enum {
	NORTH=0,
	NORTHEAST,
	EAST,
	SOUTHEAST,
	SOUTH,
	SOUTHWEST,
	WEST,
	NORTHWEST
};

class gridItem;
class DOCO;

class DOCOWorld 
{
private:
	int maxi, maxj;
	gridItem * grid;
	DOCO *head;

public:
	DOCOWorld(int width, int height);
	void getWidthAndHeight(int & w, int & h);
	gridItem * getgridItem(int X, int Y);
	void removeDOCO(DOCO *doco);
	void setHead(DOCO *h);
	DOCO * getHead();
};

#endif
