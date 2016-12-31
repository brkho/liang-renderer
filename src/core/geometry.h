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
    Vector2() : x{0}, y{0} {}

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
    std::string ToString() const {
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
    Vector3() : x{0}, y{0}, z{0} {}

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
    std::string ToString() const {
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

// A Point representing a position in 2D space.
template <typename T>
class Point2 {
  public:
    // The coordinates of the point.
    T x, y;

    // Default constructor initializing the Point2 to the origin.
    Point2() : x{0}, y{0} {}

    // Constructor initializing the Point2 with the provided values.
    Point2(T x, T y) : x{x}, y{y} { assert(IsValid()); }

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

    // Addition operator overload to offset a Point2 in a given direction represented by a Vector2
    // returning a new Point2.
    Point2<T> operator+(const Vector2<T> &that) const {
      return Point2<T>(x + that.x, y + that.y);
    }

    // Addition assignment operator overload to offset the current Point2 in a given direction
    // represented by a Vector2.
    Point2<T> &operator+=(const Vector2<T> &that) {
      x += that.x;
      y += that.y;
      assert(IsValid());
      return *this;
    }

    // Subtraction operator overload to offset a Point2 in a given direction represented by a
    // Vector2 returning a new Point2.
    Point2<T> operator-(const Vector2<T> &that) const {
      return Point2<T>(x - that.x, y - that.y);
    }

    // Subtraction assignment operator overload to offset the current Point2 in a given direction
    // represented by a Vector2.
    Point2<T> &operator-=(const Vector2<T> &that) {
      x -= that.x;
      y -= that.y;
      assert(IsValid());
      return *this;
    }

    // Subtraction operator overload to get the distance between the two points as a vector. I don't
    // think we need to override the subtraction assignment operator as well...
    Vector2<T> operator-(const Point2<T> &that) const {
      return Vector2<T>(x - that.x, y - that.y);
    }

    // Pretty prints a Point2.
    std::string ToString() const {
      return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }

  private:
    // Returns whether the Point2 is valid. This returns true if there are no NaNs, else false.
    bool IsValid() const {
      return !std::isnan(x) && !std::isnan(y);
    }
};

// Gets the distance between two Point2s.
template <typename T>
inline float Distance(const Point2<T> &p1, const Point2<T> &p2) {
  return (p1 - p2).Length();
}

// Gets the squared distance between two Point2s.
template <typename T>
inline float DistanceSquared(const Point2<T> &p1, const Point2<T> &p2) {
  return (p1 - p2).LengthSquared();
}

// Linearly interpolates between two points (0.0 = p1, 1.0 = p2).
template <typename T>
inline Point2<T> Lerp(const Point2<T> &p1, const Point2<T> &p2, float t) {
  assert(t >= 0.0 && t <= 1.0);
  float t_inv = 1.0 - t;
  return Point2<T>(p1.x * t_inv + p2.x * t, p1.y * t_inv + p2.y * t);
}

// Some type declarations for common usages of Point2.
typedef Point2<int> Point2i;
typedef Point2<float> Point2f;

// A Point representing a position in 2D space.
template <typename T>
class Point3 {
  public:
    // The coordinates of the point.
    T x, y, z;

    // Default constructor initializing the Point3 to the origin.
    Point3() : x{0}, y{0}, z{0} {}

    // Constructor initializing the Point3 with the provided values.
    Point3(T x, T y, T z) : x{x}, y{y}, z{z} { assert(IsValid()); }

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

    // Addition operator overload to offset a Point3 in a given direction represented by a Vector3
    // returning a new Point3.
    Point3<T> operator+(const Vector3<T> &that) const {
      return Point3<T>(x + that.x, y + that.y, z + that.z);
    }

    // Addition assignment operator overload to offset the current Point3 in a given direction
    // represented by a Vector3.
    Point3<T> &operator+=(const Vector3<T> &that) {
      x += that.x;
      y += that.y;
      z += that.z;
      assert(IsValid());
      return *this;
    }

    // Subtraction operator overload to offset a Point3 in a given direction represented by a
    // Vector3 returning a new Point3.
    Point3<T> operator-(const Vector3<T> &that) const {
      return Point3<T>(x - that.x, y - that.y, z - that.z);
    }

    // Subtraction assignment operator overload to offset the current Point3 in a given direction
    // represented by a Vector3.
    Point3<T> &operator-=(const Vector3<T> &that) {
      x -= that.x;
      y -= that.y;
      z -= that.z;
      assert(IsValid());
      return *this;
    }

    // Subtraction operator overload to get the distance between the two points as a vector. I don't
    // think we need to override the subtraction assignment operator as well...
    Vector3<T> operator-(const Point3<T> &that) const {
      return Vector3<T>(x - that.x, y - that.y, z - that.z);
    }

    // Pretty prints a Point3.
    std::string ToString() const {
      return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }

  private:
    // Returns whether the Point3 is valid. This returns true if there are no NaNs, else false.
    bool IsValid() const {
      return !std::isnan(x) && !std::isnan(y) && !std::isnan(z);
    }
};

// Gets the distance between two Point3s.
template <typename T>
inline float Distance(const Point3<T> &p1, const Point3<T> &p2) {
  return (p1 - p2).Length();
}

// Gets the squared distance between two Point3s.
template <typename T>
inline float DistanceSquared(const Point3<T> &p1, const Point3<T> &p2) {
  return (p1 - p2).LengthSquared();
}

// Linearly interpolates between two points (0.0 = p1, 1.0 = p2).
template <typename T>
inline Point3<T> Lerp(const Point3<T> &p1, const Point3<T> &p2, float t) {
  assert(t >= 0.0 && t <= 1.0);
  float t_inv = 1.0 - t;
  return Point3<T>(p1.x * t_inv + p2.x * t, p1.y * t_inv + p2.y * t, p1.z * t_inv + p2.z * t);
}

// Some type declarations for common usages of Point3.
typedef Point3<int> Point3i;
typedef Point3<float> Point3f;

// A surface normal vector. This inherits from Vector3 since it is a specific type of Vector3.
template <typename T>
class Normal3 : public Vector3<T> {
  public:
    // Default constructor initializing components to 0.
    Normal3() : Vector3<T>() {}

    // Constructor initializing components to provided values.
    Normal3(T x, T y, T z) : Vector3<T>(x, y, z) {}
};

// A type declaration for the most common useage of Normal3.
typedef Normal3<float> Normal3f;

// A Ray3f consists of an origin point represented as a Point3 and a direction represented as a
// Vector3.
class Ray3f {
  public:
    // The origin of the ray.
    Point3f origin;
    // The direction of the ray.
    Vector3f direction;
    // The maximum value for t recorded.
    mutable float max_t;

    // Construct a ray given an origin, a direction, and a max t value.
    Ray3f(Point3f origin, Vector3f direction, float max_t) : origin{origin}, direction{direction},
        max_t{max_t} {
      assert(max_t >= 0.0);
    }

    // Construct a ray given an origin and a direction, initialing max t to infinity.
    Ray3f(Point3f origin, Vector3f direction) : Ray3f(origin,
        direction, std::numeric_limits<float>::infinity()) {}

    // Parameterized by t, return the point that the ray represents.
    Point3f operator()(float t) const {
      assert(t >= 0.0);
      return origin + (direction * t);
    }

    // Pretty prints a Ray3f.
    std::string ToString() const {
      return "(o: " + origin.ToString() + ", d: " + direction.ToString() + ")";
    }
};

// An axis-aligned bounding box described by two points.
template <typename T>
class AABB3 {
  public:
    // The minimum and maximum points describing the AABB. Every component of the min_point must
    // be less than or equal to its corresponding component in the max_point.
    Point3<T> min_point, max_point;

    // Doesn't make sense to initialize an AABB3 without without a point, so disable default
    // constructor.
    AABB3() = delete;

    // Initialize an AABB enclosing a single point.
    AABB3(const Point3<T> &point) : min_point(point), max_point(point) {}

    // Initialize an AABB defined by two points, taking the component-wise minimum and maximum
    // to get min_point and max_point.
    AABB3(const Point3<T> &p1, const Point3<T> &p2) : min_point{std::min(p1.x, p2.x),
        std::min(p1.y, p2.y), std::min(p1.z, p2.z)}, max_point{std::max(p1.x, p2.x),
        std::max(p1.y, p2.y), std::max(p1.z, p2.z)} {}

    // Returns one of the 8 corners of the AABB.
    Point3<T> Corner(uint i) const {
      assert(i < 8);
      bool use_min_x = !(bool)(i / 4);
      bool use_min_y = !(bool)((i % 4) / 2);
      bool use_min_z = !(bool)(i % 2);
      return Point3<T>(use_min_x ? min_point.x : max_point.x, use_min_y ? min_point.y : max_point.y,
          use_min_z ? min_point.z : max_point.z);
    }

    // Every component of the min_point must be less than or equal to its corresponding component
    // in the max_point, else the AABB is considered empty.
    bool IsEmpty() const {
      return min_point.x > max_point.x || min_point.y > max_point.y || min_point.z > max_point.z;
    }

    // Expands the AABB3 in all directions by a given delta.
    void Expand(T delta) {
      min_point -= Vector3<T>(delta, delta, delta);
      max_point += Vector3<T>(delta, delta, delta);
    }

    // Returnds the vector along the diagonal of the AABB.
    Vector3<T> Diagonal() const {
      if (IsEmpty()) {
        return Vector3<T>();
      }
      return max_point - min_point;
    }

    // Returns the surface area of the bounding box.
    T SurfaceArea() const {
      Vector3<T> d = Diagonal();
      return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
    }

    // Returns the volume of the bounding box.
    T Volume() const {
      Vector3<T> d = Diagonal();
      return d.x * d.y * d.z;
    }

    // Pretty prints an AABB3.
    std::string ToString() const {
      return "(min: " + min_point.ToString() + ", max: " + max_point.ToString() + ")";
    }
};

// Computes the union of two AABBs, an AABB that encloses both.
template <typename T>
AABB3<T> Union(const AABB3<T> &b1, const AABB3<T> &b2) {
  // A union with an empty AABB is a no-op.
  if (b1.IsEmpty()) {
    return b2;
  }
  if (b2.IsEmpty()) {
    return b1;
  }
  Point3<T> new_min = Point3<T>(std::min(b1.min_point.x, b2.min_point.x),
      std::min(b1.min_point.y, b2.min_point.y), std::min(b1.min_point.z, b2.min_point.z));
  Point3<T> new_max = Point3<T>(std::max(b1.max_point.x, b2.max_point.x),
      std::max(b1.max_point.y, b2.max_point.y), std::max(b1.max_point.z, b2.max_point.z));
  return AABB3<T>(new_min, new_max);
}

// Computes the intersection of two AABBs. This may result in an invalid AABB representing no
// intersection.
template <typename T>
AABB3<T> Intersect(const AABB3<T> &b1, const AABB3<T> &b2) {
  // An intersection with an empty AABB returns an empty AABB.
  if (b1.IsEmpty()) {
    return b1;
  }
  if (b2.IsEmpty()) {
    return b2;
  }
  Point3<T> new_min = Point3<T>(std::max(b1.min_point.x, b2.min_point.x),
      std::max(b1.min_point.y, b2.min_point.y), std::max(b1.min_point.z, b2.min_point.z));
  Point3<T> new_max = Point3<T>(std::min(b1.max_point.x, b2.max_point.x),
      std::min(b1.max_point.y, b2.max_point.y), std::min(b1.max_point.z, b2.max_point.z));
  // A bit of a strange construction here to maintain empty AABB state.
  AABB3<T> new_box = AABB3<T>(new_min);
  new_box.max_point = new_max;
  return new_box;
}

// Returns whether the bouding boxes overlap.
template <typename T>
bool Overlaps(const AABB3<T> &b1, const AABB3<T> &b2) {
  if (b1.IsEmpty() || b2.IsEmpty()) {
    return false;
  }
  return ((b1.max_point.x >= b2.min_point.x && b1.min_point.x <= b2.max_point.x) &&
      (b1.max_point.y >= b2.min_point.y && b1.min_point.y <= b2.max_point.y) &&
      (b1.max_point.z >= b2.min_point.z && b1.min_point.z <= b2.max_point.z));
}

// Returns whether the point is inside the bounding box.
template <typename T>
bool Contains(const AABB3<T> &box, const Point3<T> &point) {
  if (box.IsEmpty()) {
    return false;
  }
  return point.x >= box.min_point.x && point.x <= box.max_point.x &&
      point.y >= box.min_point.y && point.y <= box.max_point.y &&
      point.z >= box.min_point.z && point.z <= box.max_point.z;
}

// Some type declarations for common usages of AABB3.
typedef AABB3<int> AABB3i;
typedef AABB3<float> AABB3f;

}

#endif  // LIANG_CORE_GEOMETRY_H
