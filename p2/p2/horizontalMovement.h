//===========================================================
// horizontalMovement.h
// Author: Sameera Warsi
//===========================================================

#ifndef HORIZONTALMOVEMENT_H
#define HORIZONTALMOVEMENT_H

#include "Movement.h"

class horizontalMovement : public Movement
{
    public:
    horizontalMovement();
    virtual ~horizontalMovement();

    virtual void Move(DOCOWorld *w,DOCO *d);
};

#endif

