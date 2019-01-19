//===========================================================
// Movement.cpp
// Author: Sameera Warsi
//===========================================================

#include "DOCO.h"
#include "Movement.h"
#include "gridItem.h"

Movement::Movement()
{
    direction = -1;
}

Movement::~Movement()
{
}

void Movement::setDirection(int dir)
{
    direction = dir;
}

int Movement::getDirection()
{
    return direction;
}

void Movement::Move(DOCOWorld *,DOCO *)
{
}
