// This header defines the Matrix4x4 class and the Transform class and opeations. Like the
// geometry files, this is heavily based off the classes in pbrt.
//
// Author: brian@brkho.com

#ifndef LIANG_CORE_TRANSFORM_H
#define LIANG_CORE_TRANSFORM_H

#include "core/liang.h"

namespace liang {

class Matrix4x4 {
  public:
    // Initialize the matrix to the identity matrix.
    Matrix4x4();

    // Initialize the matrix given a C-style 2D array of 16 floats.
    Matrix4x4(float m[4][4]);

    // Initialize the matrix given a C-style 1D array of 16 floats.
    Matrix4x4(float m[16]);

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


}

#endif  // LIANG_CORE_TRANSFORM_H
