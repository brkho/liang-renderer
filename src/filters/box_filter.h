// This header defines the BoxFilter, a reconstruction filter that averages all samples equally.
// This is mainly included for completeness; it is not a good filter and should not be used in
// creating photorealistic renders.
//
// Author: brian@brkho.com

#ifndef LIANG_FILTERS_BOX_FILTER_H
#define LIANG_FILTERS_BOX_FILTER_H

#include "core/geometry.h"
#include "core/liang.h"
#include "filters/filter.h"

namespace liang {

class BoxFilter : public Filter {
  public:
    // BoxFilter constructor that takes a radius and precomputes its inverse.
    BoxFilter(float radius);

    // Equal weighting, so always return 1.
    float Evaluate(const Point2f &location) const;
};

}

#endif  // LIANG_FILTERS_BOX_FILTER_H
