//UJEdgeFilter.h
#ifndef UJEDGEFILTER_H_INCLUDED
#define UJEDGEFILTER_H_INCLUDED

#include "UJFilter.h"

class UJEdgeFilter : public UJFilter {
public:
    UJEdgeFilter();
    void applyFilter(CCImage& image, int passes);

private:
    void InitArray();
};

#endif // UJEDGEFILTER_H_INCLUDED
