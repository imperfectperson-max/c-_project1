// UJBlurFilter.h
#ifndef UJBLURFILTER_H_INCLUDED
#define UJBLURFILTER_H_INCLUDED

#include "UJFilter.h"

class UJBlurFilter : public UJFilter {
public:
    UJBlurFilter();
    void applyFilter(CCImage& image, int passes);

private:
    void InitArray();
};

#endif // UJBLURFILTER_H_INCLUDED
