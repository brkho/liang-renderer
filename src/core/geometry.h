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
    Vector2<T> &operator+=(const Vector2<T> &that) {
      x += that.x;
      y += that.y;
      assert(IsValid());
      return *this;
    }

    // Component-wise subtraction returning a new Vector2.
    Vector2<T> operator-(const Vector2<T> &that) const {
      return Vector2<T>(x - that.x, y - that.y);
    }

    // Component-wise assignment subtraction.
    Vector2<T> &operator-=(const Vector2<T> &that) {
      x -= that.x;
      y -= that.y;
      assert(IsValid());
      return *this;
    }

    // Component-wise multiplication with a scalar returning a new Vector2.
    Vector2<T> operator*(T scalar) const {
      return Vector2<T>(x * scalar, y * scalar);
    }

    // Component-wise assignment multiplication with a scalar.
    Vector2<T> &operator*=(T scalar) {
      x *= scalar;
      y *= scalar;
      assert(IsValid());
      return *this;
    }

    // Component-wise division with a scalar returning a new Vector2.
    Vector2<T> operator/(T scalar) const {
      assert(scalar != 0);
      float inverse = 1.0 / scalar;
      return Vector2<T>(x * inverse, y * inverse);
    }

    // Component-wise assignment division with a scalar.
    Vector2<T> &operator/=(T scalar) {
      assert(scalar != 0);
      float inverse = 1.0 / scalar;
      x *= inverse;
      y *= inverse;
      assert(IsValid());
      return *this;
    }

    // Returns the squared length of the vector.
    float LengthSquared() const {
      return x * x + y * y;
    }

    // Returns the length of the vector.
    float Length() const {
      return std::sqrt(LengthSquared());
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

// Returns the dot product of two Vector2s.
template <typename T>
inline T Dot(const Vector2<T> &vec1, const Vector2<T> &vec2) {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

// Returns the component-wise absolute value of a Vector2.
template <typename T>
inline Vector2<T> Abs(const Vector2<T> &vec) {
  return Vector2<T>(std::abs(vec.x), std::abs(vec.y));
}

// Normalizes a Vector2 so its length is 1.
template <typename T>
inline Vector2<T> Normalize(const Vector2<T> &vec) {
  return vec / vec.Length();
}

// Some type declarations for common usages of Vector2.
typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;

// A Vector representing three elements parameterized for reuse with both floats and integers.
template <typename T>
class Vector3 {
  public:
    // The values of the vector.
    T x, y, z;

    // Default constructor for a Vector3 that initializes x, y, and z to 0.
    Vector3() {
      x = 0;
      y = 0;
      z = 0;
    }

    // Constructor for a Vector3 that takes an x, y, and z value.
    Vector3(T x, T y, T z) : x(x), y(y), z(z) { assert(IsValid()); }

    // Accessing via integer index for reading.
    T operator[](int i) const {
      assert(i >= 0 && i <= 2);
      return i == 0 ? x : (i == 1 ? y : z);
    }

    // Accessing via integer index for assignment.
    T &operator[](int i) {
      assert(i >= 0 && i <= 2);
      return i == 0 ? x : (i == 1 ? y : z);
    }

    // Component-wise addition returning a new Vector3.
    Vector3<T> operator+(const Vector3<T> &that) const {
      return Vector3<T>(x + that.x, y + that.y, z + that.z);
    }

    // Component-wise assignment addition.
    Vector3<T> &operator+=(const Vector3<T> &that) {
      x += that.x;
      y += that.y;
      z += that.z;
      assert(IsValid());
      return *this;
    }

    // Component-wise subtraction returning a new Vector3.
    Vector3<T> operator-(const Vector3<T> &that) const {
      return Vector3<T>(x - that.x, y - that.y, z - that.z);
    }

    // Component-wise assignment subtraction.
    Vector3<T> &operator-=(const Vector3<T> &that) {
      x -= that.x;
      y -= that.y;
      z -= that.z;
      assert(IsValid());
      return *this;
    }

    // Component-wise multiplication with a scalar returning a new Vector3.
    Vector3<T> operator*(T scalar) const {
      return Vector3<T>(x * scalar, y * scalar, z * scalar);
    }

    // Component-wise assignment multiplication with a scalar.
    Vector3<T> &operator*=(T scalar) {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      assert(IsValid());
      return *this;
    }

    // Component-wise division with a scalar returning a new Vector3.
    Vector3<T> operator/(T scalar) const {
      assert(scalar != 0);
      float inverse = 1.0 / scalar;
      return Vector3<T>(x * inverse, y * inverse, z * inverse);
    }

    // Component-wise assignment division with a scalar.
    Vector3<T> &operator/=(T scalar) {
      assert(scalar != 0);
      float inverse = 1.0 / scalar;
      x *= inverse;
      y *= inverse;
      z *= inverse;
      assert(IsValid());
      return *this;
    }

    // Returns the squared length of the vector.
    float LengthSquared() const {
      return x * x + y * y + z * z;
    }

    // Returns the length of the vector.
    float Length() const {
      return std::sqrt(LengthSquared());
    }

    // Pretty prints a Vector3.
    std::string ToString() {
      return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }
  private:
    // Returns whether the vector is valid. This returns true if there are no NaNs, else false.
    bool IsValid() const {
      return !std::isnan(x) && !std::isnan(y) && !std::isnan(z);
    }
};

// Returns the dot product of two Vector3s.
template <typename T>
inline T Dot(const Vector3<T> &vec1, const Vector3<T> &vec2) {
  return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

// Returns the cross product of two Vector3s.
template <typename T>
inline Vector3<T> Cross(const Vector3<T> &vec1, const Vector3<T> &vec2) {
  // Convert to double before performing the operation to guard against floating point errors as
  // described in pbrt.
  double v1x = vec1.x;
  double v1y = vec1.y;
  double v1z = vec1.z;
  double v2x = vec2.x;
  double v2y = vec2.y;
  double v2z = vec2.z;
  return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
      (v1x * v2y) - (v1y * v2x));
}

// Returns the component-wise absolute value of a Vector3.
template <typename T>
inline Vector3<T> Abs(const Vector3<T> &vec) {
  return Vector3<T>(std::abs(vec.x), std::abs(vec.y), std::abs(vec.z));
}

// Normalizes a Vector3 so its length is 1.
template <typename T>
inline Vector3<T> Normalize(const Vector3<T> &vec) {
  return vec / vec.Length();
}

// Constructs a local coordinate system given a normalized 3D vector, outputting the other two
// orthonormal vectors through the pointer arguments.
template <typename T>
inline void CreateCoordSystem(const Vector3<T> &vec1, Vector3<T> *vec2, Vector3<T> *vec3) {
  *vec2 = std::abs(vec1.x) > std::abs(vec1.y) ? Normalize(Vector3<T>(-vec1.z, 0.0, vec1.x)) :
      Normalize(Vector3<T>(0.0, vec1.z, -vec1.y));
  *vec3 = Cross(vec1, *vec2);
}

// Some type declarations for common usages of Vector3.
typedef Vector3<int> Vector3i;
typedef Vector3<float> Vector3f;

}

#endif  // LIANG_CORE_GEOMETRY_H