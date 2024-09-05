// CCImage.h
#ifndef CCIMAGE_H_INCLUDED
#define CCIMAGE_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include "UJUtilLib.h"

using namespace std;

class CCImage{
public:
    CCImage();
    CCImage(unsigned int intRows, unsigned int intCols);
    CCImage(const CCImage& objOriginal);
    ~CCImage();

    // Accessors / Getters
    unsigned int getRows() const;
    unsigned int getCols() const;
    RGBColour getColour(unsigned int intRow, unsigned int intCol) const;

    // Mutators / Setters
    void setImageColour(RGBColour recColour);
    void setPixelColour(unsigned int intRow, unsigned int intCol, RGBColour recColour);

    string toPPM() const;

private:
    unsigned int _intRows;
    unsigned int _intCols;
    RGBColour** _recPixels;

    // Utility Methods
    void allocMemory(unsigned int intRows, unsigned int intCols);
    void deallocMemory();
    void clone(const CCImage& objOriginal);
};

#endif // CCIMAGE_H_INCLUDED
