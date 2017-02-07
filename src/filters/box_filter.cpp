#include "filters/box_filter.h"

namespace liang {

BoxFilter::BoxFilter(float radius) : Filter(radius) {}

float BoxFilter::Evaluate(const Point2f &location) const {
  return 1.f;
}

}
