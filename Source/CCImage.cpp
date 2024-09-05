//CCImage.cpp
#include "CCImage.h"

#include <sstream>

CCImage::CCImage() : CCImage(NUM_ROWS, NUM_COLS){}

CCImage::CCImage(unsigned int intRows, unsigned int intCols){
    allocMemory(intRows, intCols);
}

CCImage::CCImage(const CCImage& objOriginal) : CCImage(objOriginal._intRows, objOriginal._intCols){
    // Clone - Deep Copy
    clone(objOriginal);
}

CCImage::~CCImage(){
    deallocMemory();
}

// Accessors / Getters

unsigned int CCImage::getRows() const{
    return _intRows;
}

unsigned int CCImage::getCols() const{
    return _intCols;
}

RGBColour CCImage::getColour(unsigned int intRow, unsigned int intCol) const{
    /**
	** TODO: Always Check to make sure intRow and intCol are in range
	**/
    return _recPixels[intRow][intCol];
}

// Mutators / Setters


void CCImage::setImageColour(RGBColour recColour) {
    for(unsigned int r = 0; r < _intRows; r++) {
        for(unsigned int c = 0; c < _intCols; c++) {
            _recPixels[r][c] = recColour;
        }
    }
}

void CCImage::setPixelColour(unsigned int intRow, unsigned int intCol, RGBColour recColour){
    // Check to make sure intRow and intCol are in range
    if (intRow >= 0 && intRow < _intRows && intCol >= 0 && intCol < _intCols)
    _recPixels[intRow][intCol] = recColour;
}

string CCImage::toPPM() const {
    if (_recPixels == nullptr) {
        cerr << "Pixel data is not allocated." << endl;
        exit(ERROR_PPM_FILE);
    }

    stringstream ssPPM;

    ssPPM << "P3" << endl
          << _intCols << " " << _intRows << endl
          << "255" << endl;

    for (unsigned int r = 0; r < _intRows; r++) {
        for (unsigned int c = 0; c < _intCols; c++) {  // Index starts from 0
            // Ensure values are within the expected range
            if (_recPixels[r][c].intRed < 0 || _recPixels[r][c].intRed > 255 ||
                _recPixels[r][c].intGreen < 0 || _recPixels[r][c].intGreen > 255 ||
                _recPixels[r][c].intBlue < 0 || _recPixels[r][c].intBlue > 255) {
                cerr << "Invalid pixel value at (" << r << ", " << c << ")" << endl;
                cerr << "Pixel values: R=" << _recPixels[r][c].intRed
                     << ", G=" << _recPixels[r][c].intGreen
                     << ", B=" << _recPixels[r][c].intBlue << endl;
                exit(ERROR_PPM_FILE);
            }

            ssPPM << _recPixels[r][c].intRed << " "
                  << _recPixels[r][c].intGreen << " "
                  << _recPixels[r][c].intBlue << " ";
        }

        ssPPM << endl;  // Move to the next line after completing a row
    }

    return ssPPM.str();
}


// Utility Methods
void CCImage::allocMemory(unsigned int intRows, unsigned int intCols){
    _intRows = intRows;
    _intCols = intCols;
    _recPixels = new RGBColour*[intRows];
    for(unsigned int r = 0; r < intRows; r++){
        _recPixels[r] = new RGBColour[intCols];
        for(unsigned int c = 0; c < intCols; c++){
            _recPixels[r][c] = DEFAULT_COLOUR;
        }
    }
}

void CCImage::deallocMemory(){
    for(unsigned int r = 0; r < _intRows; r++){
        delete [] _recPixels[r];
    }
    delete [] _recPixels;
    _recPixels = nullptr;
}

void CCImage::clone(const CCImage& objOriginal){
    for(unsigned int r = 0; r < _intRows; r++){
        for(unsigned int c = 0; c < _intCols; c++){
            _recPixels[r][c].intRed = objOriginal._recPixels[r][c].intRed;
            _recPixels[r][c].intGreen = objOriginal._recPixels[r][c].intGreen;
            _recPixels[r][c].intBlue = objOriginal._recPixels[r][c].intBlue;
        }
    }
}
