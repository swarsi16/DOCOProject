//===========================================================
// DOCO.h
// Author: Sameera Warsi
//===========================================================
#ifndef DOCO_H
#define DOCO_H

#include "DOCOWorld.h"

class Movement;
class gridItem;

class DOCO 
{
 protected:
    bool dead;
    int positionX, positionY;
    int energyLevel; //Energy level for this DOCO
    int direction; //Direction in which this DOCO can move
    // Pointers to previous and next DOCO’s in a doubly linked list
    Movement *mv;
    DOCO *next;
 public:
    //Constructors
    DOCO();

    DOCO(int X, int Y); //Construct a DOCO given its position

    void setDirection(int dir);

    int getDirection();

    // Set the DOCO as dead
    void setDead();

    void setLive();

    bool getDead();

    // Set the position of this DOCO in the world grid
    // [In] X, Y are the values to set the position in the world grid
    void setPosition(int X, int Y);

    // Get the position of this DOCO in the world grid
    // [Out] X,Y are returned positions
    void getPosition(int & X, int & Y);

    void setEnergyLevel(int level);

    int getEnergyLevel();

    // Methods to set next pointers for linked list
    void setNext(DOCO *n);

    DOCO *getNext();

    void setMovement(Movement *m);

    //Method to move
    virtual void Move(DOCOWorld *w); 

    // Method to eat
    void Eat(gridItem *g);
};

#endif
