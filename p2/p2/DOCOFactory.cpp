#include "DOCOFactory.h"
#include "DOCO.h"
#include "horizontalMovement.h"
#include "verticalMovement.h"
#include "diagonalMovement.h"

using namespace std;

DOCOFactory::DOCOFactory()
{

}

DOCOFactory::~DOCOFactory() 
{

}

//------------------------------------------------
// Get the singleton instance
//------------------------------------------------
DOCOFactory *DOCOFactory::getInstance()
{
    static DOCOFactory *instance = 0;
    if(instance == 0) // If first time calling
	{
            instance = new DOCOFactory();
	}
    return instance;
}

DOCO * DOCOFactory::createDOCO(std::string type)
{
    DOCO *d = new DOCO();

    Movement * m;
    if(type == "HORIZONTAL") 
	{
            m = new horizontalMovement();
	}
    if(type == "VERTICAL") 
	{
            m = new verticalMovement();
	}
    if(type == "DIAGONAL") 
	{
            m = new diagonalMovement();
	}

    d->setMovement(m);

    return d;
}

