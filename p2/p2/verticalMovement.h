//===========================================================
// verticalMovement.h
// Author: Sameera Warsi
//===========================================================

#ifndef VERTICALMOVEMENT_H
#define VERTICALMOVEMENT_H

#include "Movement.h"

class verticalMovement : public Movement
{
    public:
    verticalMovement();
    virtual ~verticalMovement();

    virtual void Move(DOCOWorld *w,DOCO *d);
};

#endif

