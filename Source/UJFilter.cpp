// UJFilter.cpp
#include "UJFilter.h"

// Default constructor initializes an identity kernel (no effect)
UJFilter::UJFilter() {
    alloc();
}

UJFilter::~UJFilter() {
    dealloc();
}

void UJFilter::alloc() {
    _kernel = new int*[KERNEL_ROWS];
    for (int i = 0; i < KERNEL_ROWS; ++i) {
        _kernel[i] = new int[KERNEL_COLS];
        for (int j = 0; j < KERNEL_COLS; ++j) {
            _kernel[i][j] = 0;
        }
    }
}

void UJFilter::dealloc() {
    for (int i = 0; i < 3; ++i) {
        delete [] _kernel[i];
    }
    delete [] _kernel;
    _kernel = nullptr;
}

bool UJFilter::checkRange(int intRow, int intCol, int intRows, int intCols) {
    return intRow >= 0 && intRow < intRows && intCol >= 0 && intCol < intCols;
}

// Apply default filter
void UJFilter::applyFilter(CCImage& image, int passes){

    RGBColour recFiltered = {0, 0, 0}; // Will store the new RGBColour value

    unsigned int intRow = image.getRows();
    unsigned int intCol = image.getCols();

    int intKernelRow = 0;
    int intKernelCol = 0;
    int intKernelSum = 0;

    for(unsigned int r = intRow - 1; r <= intRow + 1; r++){
        intKernelRow %= 3; // Keep a maximum value of 3

        for(unsigned int c = intCol - 1; c <= intCol + 1; c++){
            intKernelCol %= 3; // Keep a maximum value of 3
            // If in range
            if(checkRange(r, c, intRow, intCol)){

            intKernelSum += _kernel[intKernelRow][intKernelCol];
            recFiltered.intRed += (int)(_kernel[intKernelRow][intKernelCol] * image.getColour(r, c).intRed);
            recFiltered.intGreen += (int)(_kernel[intKernelRow][intKernelCol] * image.getColour(r, c).intGreen);
            recFiltered.intBlue += (int)(_kernel[intKernelRow][intKernelCol] * image.getColour(r, c).intBlue);
            }
        intKernelCol++; // Next Column
    }
    intKernelRow++; // Next Row
    }

    recFiltered.intRed /= intKernelSum;
    recFiltered.intGreen /= intKernelSum;
    recFiltered.intBlue /= intKernelSum;

    for (int i = 0; i < passes; i++){
        for (unsigned int r = 0; r < intRow; r++){
            for (unsigned int c = 0; c < intCol; c++){
                image.setPixelColour(r, c, recFiltered);
            }
        }
    }

}
