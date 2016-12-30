// This header defines the Matrix4x4 class and the Transform class and opeations. Like the
// geometry files, this is heavily based off the classes in pbrt.
//
// Author: brian@brkho.com

#ifndef LIANG_CORE_TRANSFORM_H
#define LIANG_CORE_TRANSFORM_H

#include "core/geometry.h"
#include "core/liang.h"

namespace liang {

class Matrix4x4 {
  public:
    // Initialize the matrix to the identity matrix.
    Matrix4x4();

    // Initialize the matrix given a C-style 2D array of 16 floats.
    Matrix4x4(const float m[4][4]);

    // Initialize the matrix given a C-style 1D array of 16 floats.
    Matrix4x4(const float m[16]);

    // Component-wise equality comparison by overloading the appropriate operator.
    bool operator==(const Matrix4x4 &that) const;

    // Component-wise inequality comparison by overloading the appropriate operator.
    bool operator!=(const Matrix4x4 &that) const;

    // Accessing via integer index for reading. This does not allow for writing via index, however.
    float operator[](int i) const;

    // Multiply two matrices (this * that). This is not communative!
    Matrix4x4 operator*(const Matrix4x4 &that) const;

    // Multiply two matrices (this * that) and set this equal to the result.
    Matrix4x4 &operator*=(const Matrix4x4 &that);

    // Gets the element at the ith row and jth column.
    float Get(uint i, uint j) const;

    // Sets the element at the ith row and jth column.
    void Set(uint i, uint j, float value);

    // Pretty prints a Matrix4x4.
    std::string ToString() const;

  private:
    // Private member variable storing the data. This should only be accessed using Matrix4x4
    // methods to eliminate indexing errors.
    float matrix[16];
};

// Given a matrix, output its transpose.
Matrix4x4 Transpose(const Matrix4x4& m);

// Get the inverse of the matrix. Note: this is slow.
Matrix4x4 Inverse(const Matrix4x4& m);

// A 3D transformation backed by a Matrix4x4 used to transform points, vecttors, normals, rays, and
// bounding boxes.
class Transform {
  public:
    // Default constructor initializing the transform to the identity matrix.
    Transform();

    // Constructor initializing the transform with a single matrix representing the transform. The
    // inverse is then explicitly computed.
    Transform(const Matrix4x4& m);

    // Constructor initializing the transform with a matrix and its transform.
    Transform(const Matrix4x4& m, const Matrix4x4& m_inverse);

    // Returns a transform that is the inverse of the one provided.
    friend Transform Inverse(const Transform &t);

    // Returns a transform that is the transpose of the one provided.
    friend Transform Transpose(const Transform &t);

    // Transforms a point by multiplying the point with the matrix.
    template <typename T>
    Point3<T> operator()(const Point3<T> &p) const;

    // Transforms a vector by multiplying the vector with the matrix. Vectors are not affected by
    // translation.
    template <typename T>
    Vector3<T> operator()(const Vector3<T> &v) const;

    // Transforms a normal by multiplying with the transpose of the inverse of the matrix. Normals
    // are a special case of vectors, so they are likewise not affected by translation.
    template <typename T>
    Normal3<T> operator()(const Normal3<T> &n) const;

    // Transforms a ray by transforming its origin and direction.
    Ray3f operator()(const Ray3f &r) const;

    // Transforms a bounding box by transforming each one of its corners and computing a new
    // bounding box that encompasses the resulting points.
    template <typename T>
    AABB3<T> operator()(const AABB3<T> &b) const;

    // Multiply two Transforms together (aka multiplying their matrices) to compose them.
    Transform operator*(const Transform &that) const;

  private:
    // The matrix backing the transform and its inverse.
    Matrix4x4 matrix, matrix_inverse;
};

// Returns a transform that translates in the given direction.
Transform TranslationTransform(const Vector3f &delta);

// Returns a transform that scales along the x, y, and z axes.
Transform ScaleTransform(float x, float y, float z);

// Returns a transform that rotates along the x axis.
Transform RotateXTransform(float theta);

// Returns a transform that rotates along the y axis.
Transform RotateYTransform(float theta);

// Returns a transform that rotates along the z axis.
Transform RotateZTransform(float theta);

// Returns a transform that is a rotation along an arbitrary axis.
Transform RotateArbitraryAxisTransform(const Vector3f &axis, float theta);

// Returns a look at transformation.
Transform LookAtTransformation(const Vector3f &pos, const Vector3f &target, const Vector3f &up);

}

#endif  // LIANG_CORE_TRANSFORM_H
