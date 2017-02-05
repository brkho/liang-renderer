// This is a header only library defining the core geometry classes of Liang defining a Vector,
// Point, Normal, and Ray. These basic classes are adapted from those of pbrt.
//
// Author: brian@brkho.com

#ifndef LIANG_UTILS_MATH_H
#define LIANG_UTILS_MATH_H

#include "core/liang.h"

#define PI 3.1415926535897932

namespace liang {

inline float DegreesToRadians(float degrees) {
  return (degrees * PI) / 180.f;
}

inline float RadiansToDegrees(float radians) {
  return (radians * 180.f) / PI;
}

}

#endif  // LIANG_UTILS_MATH_H
