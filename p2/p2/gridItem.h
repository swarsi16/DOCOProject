//===========================================================
// gridItem.h
// Author: Sameera Warsi
//===========================================================
#ifndef GRIDITEM_H
#define GRIDITEM_H

class DOCO;

class gridItem 
{
 private:
    DOCO *d, *dc; // 	
    int numofPellets; // Number of food pellets in this cell
    bool obstacle;
 public:
    // Constructors
    // Default constructor
    gridItem();
    // Constructor to set all data for a grid item
    //gridItem(int X, int Y, bool doco, int npellets);

    // Methods

    // Set the DOCO for this gridItem
    void setDOCO(DOCO *d);

    void setDOCOClone(DOCO *d);

    // [Return] whether the DOCO is contained 
    //in this gridItem
    DOCO * getDOCO();

    void setObstacle();
    bool getObstacle();

    // Set/Get number of food pellets in the grid item
    void setNumberOfPellets(int npellets);
    int getNumberOfPellets();
    void addPellet();	

    bool isEmpty();
};

#endif
