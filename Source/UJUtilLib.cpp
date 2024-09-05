// UJUtilLib.cpp
#include "UJUtilLib.h"
#include "CCImage.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

// Read CCImage
CCImage loadPPMImage(string strFileName){
    // Open File Stream
    ifstream iPPM(strFileName.c_str());
    if(iPPM.fail()){
        cerr << "Could not open PPM file." << endl;
        exit(ERROR_PPM_FILE);
    }
    // "P3" Magic Number
    string strMagicNum = "";
    iPPM >> strMagicNum;
    if(strMagicNum != "P3"){
        cerr << "Expected P3 File" << endl;
        exit(ERROR_PPM_FILE);
    }
    // Rows and Columns
    int intRows = 0, intCols = 0, intMaxVal = 0;
    iPPM >> intCols >> intRows >> intMaxVal;
    if(intMaxVal > 255){
        cerr << "Maximum value should be 255." << endl;
        exit(ERROR_PPM_FILE);
    }
    // Create CCImage Object
    CCImage objImage(intRows, intCols);

    RGBColour recPixel;
    for(int r = 0; r < intRows; r++){
        for(int c = 0; c < intCols; c++){
            iPPM >> recPixel.intRed >> recPixel.intGreen >> recPixel.intBlue;
            // If fails to read Pixel
            if(iPPM.fail()){
                cerr << "Invalid Pixel data" << endl;
                exit(ERROR_PPM_FILE);
            }
            objImage.setPixelColour(r, c, recPixel);
        }
    }

    // Close Stream
    iPPM.close();

    return objImage;
}

// char* / string to int
int covStrToInt(char* chString){
    stringstream ss{chString};
    int intNum = 0;
    ss >> intNum;
    if(ss.fail()){
        cerr << "Failed to convert to Integer." << endl;
        exit(ERROR_CONVERSION);
    }
    return intNum;
}
