//===========================================================
// Movement.h
// Author: Sameera Warsi
//===========================================================

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "DOCOWorld.h"

class gridItem;

class Movement
{
    protected:
    int direction;

    public:
    Movement();
    virtual ~Movement();
    
    void setDirection(int dir);

    int getDirection();

    virtual void Move(DOCOWorld *w,DOCO *d);
};

#endif
