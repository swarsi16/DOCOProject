#ifndef DOCOFACTORY_H
#define DOCOFACTORY_H

#include <string>
#include "DOCO.h"

class DOCOFactory 
{
 private:
    DOCOFactory();
	
 public:
    ~DOCOFactory();
    static DOCOFactory * getInstance();
    DOCO * createDOCO(std::string type);
};

#endif
