//===========================================================
// diagonalMovement.h
// Author: Sameera Warsi
//===========================================================

#ifndef DIAGONALMOVEMENT_H
#define DIAGONALMOVEMENT_H

#include "Movement.h"

class diagonalMovement : public Movement
{
    public:
    diagonalMovement();
    virtual ~diagonalMovement();

    virtual void Move(DOCOWorld *w,DOCO *d);
};

#endif

