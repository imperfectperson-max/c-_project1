// UJFilter.h
#ifndef UJFILTER_H_INCLUDED
#define UJFILTER_H_INCLUDED

#include "CCImage.h"
#include <cassert>

class UJFilter {
protected:
    static const int KERNEL_ROWS = 3;
    static const int KERNEL_COLS = 3;
    int** _kernel;
    void alloc();
    void dealloc();

public:
    UJFilter();
    virtual ~UJFilter(); // virtual destructor
    virtual void applyFilter(CCImage& image, int passes) = 0; //Pure virtual function
    bool checkRange(int intRow, int intCol, int intRows, int intCols);
};


#endif // UJFILTER_H_INCLUDED
