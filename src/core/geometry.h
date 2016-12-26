// This is a header only library defining the core geometry classes of Liang defining a Vector,
// Point, Normal, and Ray. These basic classes are adapted from those of pbrt.
//
// Author: brian@brkho.com

#ifndef LIANG_CORE_GEOMETRY_H
#define LIANG_CORE_GEOMETRY_H

#include "core/liang.h"

namespace liang {

// A Vector representing two elements parameterized for reuse with both floats and integers.
template <typename T>
class Vector2 {
  public:
    // The values of the vector.
    T x, y;

    // Default constructor for a Vector2 that initializes both x and y to 0.
    Vector2() {
      x = 0;
      y = 0;
    }

    // Constructor for a Vector2 that takes an x and y value.
    Vector2(T x, T y) : x(x), y(y) { assert(IsValid()); }

    // Accessing via integer index for reading.
    T operator[](int i) const {
      assert(i == 0 || i == 1);
      return i == 0 ? x : y;
    }

    // Accessing via integer index for assignment.
    T &operator[](int i) {
      assert(i == 0 || i == 1);
      return i == 0 ? x : y;
    }

    // Component-wise addition returning a new Vector2.
    Vector2<T> operator+(const Vector2<T> &that) const {
      return Vector2<T>(x + that.x, y + that.y);
    }

    // Component-wise assignment addition.
    Vector2<T>& operator+(const Vector2<T> &that) {
      x += that.x;
      y += that.y;
      return *this;
    }

    // Pretty prints a Vector2.
    std::string ToString() {
      return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
  private:
    // Returns whether the vector is valid. This returns true if there are no NaNs, else false.
    bool IsValid() const {
      return !std::isnan(x) && !std::isnan(y);
    }
};

}

#endif  // LIANG_CORE_GEOMETRY_H
