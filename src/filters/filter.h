// This header defines the Filter interface, an abstraction over a reconstruction filter. Each
// filter is required to implement a single function "Evaluate()" which takes a point relative to
// (0, 0) and returns the weight of that point.
//
// Author: brian@brkho.com

#ifndef LIANG_FILTERS_FILTER_H
#define LIANG_FILTERS_FILTER_H

#include "core/geometry.h"
#include "core/liang.h"

namespace liang {

class Filter {
  public:
    // Filter constructor that takes a radius and precomputes its inverse.
    Filter(float radius);

    // Takes a point relative to (0, 0) and returns it contribution based on the filter.
    virtual float Evaluate(const Point2f &location) const = 0;

  protected:
    // The radius/extent of the filter. All points further than the radius will have 0 contribution.
    float radius;

    // Inverse of the radius (a-la pbrt) precomputed for better performance.
    float radius_inverse;
};

}

#endif  // LIANG_FILTERS_FILTER_H
