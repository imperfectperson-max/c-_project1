//UJEdgeFilter.cpp
#include "UJEdgeFilter.h"
#include <algorithm>
using namespace std;

// Constructor for UJEdgeFilter
UJEdgeFilter::UJEdgeFilter() : UJFilter() {
    InitArray();
}

void UJEdgeFilter::InitArray(){
    // Define the edge detection kernel
    int edgeKernel[3][3] = {
        {-1, -1, -1},
        {-1, 10, -1},
        {-1, -1, -1}
    };

    // Copy the edge detection kernel to the base class's kernel attribute
    for(int i = 0; i < KERNEL_ROWS; i++) {
        for(int j = 0; j < KERNEL_COLS; j++) {
            _kernel[i][j] = edgeKernel[i][j];
        }
    }
}
// Method to apply the edge detection filter to an image
void UJEdgeFilter::applyFilter(CCImage& image, int passes) {
    unsigned int rows = image.getRows();
    unsigned int cols = image.getCols();

    // Determine the maximum possible sum based on the kernel
    int kernelMaxSum = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            kernelMaxSum += _kernel[i][j];
        }
    }

    for (int pass = 0; pass < passes; ++pass) {

        for (unsigned int r = 0; r < rows; ++r) {
            for (unsigned int c = 0; c < cols; ++c) {
                int sumRed = 0, sumGreen = 0, sumBlue = 0;

                // Apply the edge detection kernel
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        int row = r + i;
                        int col = c + j;

                        if (checkRange(row, col, rows, cols)) {
                            RGBColour color = image.getColour(row, col);
                            sumRed += static_cast<int>(color.intRed) * _kernel[i + 1][j + 1];
                            sumGreen += static_cast<int>(color.intGreen) * _kernel[i + 1][j + 1];
                            sumBlue += static_cast<int>(color.intBlue) * _kernel[i + 1][j + 1];
                        }
                    }
                }

                // Normalize the sums
                sumRed = (kernelMaxSum != 0) ? sumRed / kernelMaxSum : sumRed;
                sumGreen = (kernelMaxSum != 0) ? sumGreen / kernelMaxSum : sumGreen;
                sumBlue = (kernelMaxSum != 0) ? sumBlue / kernelMaxSum : sumBlue;

                // Clamp values to the range [0, 255]
                RGBColour newColor;
                newColor.intRed = min(max(sumRed, 0), 255);
                newColor.intGreen = min(max(sumGreen, 0), 255);
                newColor.intBlue = min(max(sumBlue, 0), 255);

                image.setPixelColour(r, c, newColor);  // Set the filtered pixel color
            }
        }


    }


}

