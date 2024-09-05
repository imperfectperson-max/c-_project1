// UJBlurFilter.cpp
#include "UJBlurFilter.h"
#include <algorithm>
#include <cmath>
using namespace std;

// Constructor for UJBlurFilter
UJBlurFilter::UJBlurFilter() : UJFilter() {
    InitArray();
}

void UJBlurFilter::InitArray(){
    // Define the blur kernel
    int blurKernel[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };

    // Copy the blur kernel to the base class's kernel attribute
    for(int i = 0; i < KERNEL_ROWS; i++) {
        for(int j = 0; j < KERNEL_COLS; j++) {
            _kernel[i][j] = blurKernel[i][j];
        }
    }
}
// Method to apply the blur filter to an image
void UJBlurFilter::applyFilter(CCImage& image, int passes) {
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

                // Apply the blur kernel
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

                if (kernelMaxSum == 0) kernelMaxSum = 1;  // Avoid division by zero

                // Normalize and clamp values
                RGBColour newColor;
                newColor.intRed = min(max(static_cast<int>(round(sumRed / static_cast<float>(kernelMaxSum))), 0), 255);
                newColor.intGreen = min(max(static_cast<int>(round(sumGreen / static_cast<float>(kernelMaxSum))), 0), 255);
                newColor.intBlue = min(max(static_cast<int>(round(sumBlue / static_cast<float>(kernelMaxSum))), 0), 255);

                image.setPixelColour(r, c, newColor);  // Set the filtered pixel color
            }
        }

    }
}


 //cout << image.getColour(0, 0).intRed << " " << image.getColour(0, 0).intGreen << " " << image.getColour(0, 0).intBlue << endl;
