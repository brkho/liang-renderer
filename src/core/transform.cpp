#include "core/transform.h"

namespace liang {

Matrix4x4::Matrix4x4() : matrix{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1} {}

Matrix4x4::Matrix4x4(const float m[4][4]) {
  for (int i = 0; i < 16; i++) {
    matrix[i] = m[i / 4][i % 4];
  }
}

Matrix4x4::Matrix4x4(const float m[16]) {
  for (int i = 0; i < 16; i++) {
    matrix[i] = m[i];
  }
}

bool Matrix4x4::operator==(const Matrix4x4 &that) const {
  for (int i = 0; i < 16; i++) {
    // TODO(brianh): Let's try to make this more exact...
    if (std::abs(matrix[i] - that.matrix[i]) > 0.000001) {
      return false;
    }
  }
  return true;
}

bool Matrix4x4::operator!=(const Matrix4x4 &that) const {
  return !(*this == that);
}

float Matrix4x4::operator[](int i) const {
  assert(i >= 0 && i < 16);
  return matrix[i];
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &that) const {
  Matrix4x4 new_matrix;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      new_matrix.Set(i, j, this->Get(i, 0) * that.Get(0, j) + this->Get(i, 1) * that.Get(1, j) +
          this->Get(i, 2) * that.Get(2, j) + this->Get(i, 3) * that.Get(3, j));
    }
  }
  return new_matrix;
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4 &that) {
  Matrix4x4 temp_matrix = *this * that;
  for (int i = 0; i < 16; i++) {
    matrix[i] = temp_matrix.Get(i / 4, i % 4);
  }
  return *this;
}

float Matrix4x4::Get(uint i, uint j) const {
  assert(i < 5 && j < 5);
  return matrix[i * 4 + j];
}

void Matrix4x4::Set(uint i, uint j, float value) {
  assert(i < 5 && j < 5);
  matrix[i * 4 + j] = value;
}

std::string Matrix4x4::ToString() const {
  std::string str = "{ ";
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      str += std::to_string(Get(i, j)) + ",\t";
    }
    str += "\n  ";
  }
  return str + std::to_string(matrix[12]) + ",\t" + std::to_string(matrix[13]) + ",\t" +
      std::to_string(matrix[14]) + ",\t" + std::to_string(matrix[15]) + " }";
}

Matrix4x4 Matrix4x4::Transpose() const {
  float transposed_values[16] = {Get(0, 0), Get(1, 0), Get(2, 0), Get(3, 0), Get(0, 1),
      Get(1, 1), Get(2, 1), Get(3, 1), Get(0, 2), Get(1, 2), Get(2, 2), Get(3, 2),
      Get(0, 3), Get(1, 3), Get(2, 3), Get(3, 3)};
  return Matrix4x4(transposed_values);
}

// Adapted from GLU's MESA implementation.
Matrix4x4 Matrix4x4::Inverse() const {
  float inverse_values[16];
  inverse_values[0] = matrix[5] * matrix[10] * matrix[15] - matrix[5] * matrix[11] * matrix[14] -
      matrix[9] * matrix[6] * matrix[15] + matrix[9] * matrix[7] * matrix[14] + matrix[13] *
      matrix[6] * matrix[11] - matrix[13] * matrix[7] * matrix[10];
  inverse_values[4] = -matrix[4] * matrix[10] * matrix[15] + matrix[4] * matrix[11] * matrix[14] +
      matrix[8] * matrix[6] * matrix[15] - matrix[8] * matrix[7] * matrix[14] - matrix[12] *
      matrix[6] * matrix[11] + matrix[12] * matrix[7] * matrix[10];
  inverse_values[8] = matrix[4] * matrix[9] * matrix[15] - matrix[4] * matrix[11] * matrix[13] -
      matrix[8] * matrix[5] * matrix[15] + matrix[8] * matrix[7] * matrix[13] + matrix[12] *
      matrix[5] * matrix[11] - matrix[12] * matrix[7] * matrix[9];
  inverse_values[12] = -matrix[4] * matrix[9] * matrix[14] + matrix[4] * matrix[10] * matrix[13] +
      matrix[8] * matrix[5] * matrix[14] - matrix[8] * matrix[6] * matrix[13] - matrix[12] *
      matrix[5] * matrix[10] + matrix[12] * matrix[6] * matrix[9];
  inverse_values[1] = -matrix[1] * matrix[10] * matrix[15] + matrix[1] * matrix[11] * matrix[14] +
      matrix[9] * matrix[2] * matrix[15] - matrix[9] * matrix[3] * matrix[14] - matrix[13] *
      matrix[2] * matrix[11] + matrix[13] * matrix[3] * matrix[10];
  inverse_values[5] = matrix[0] * matrix[10] * matrix[15] - matrix[0] * matrix[11] * matrix[14] -
      matrix[8] * matrix[2] * matrix[15] + matrix[8] * matrix[3] * matrix[14] + matrix[12] *
      matrix[2] * matrix[11] - matrix[12] * matrix[3] * matrix[10];
  inverse_values[9] = -matrix[0] * matrix[9] * matrix[15] + matrix[0] * matrix[11] * matrix[13] +
      matrix[8] * matrix[1] * matrix[15] - matrix[8] * matrix[3] * matrix[13] - matrix[12] *
      matrix[1] * matrix[11] + matrix[12] * matrix[3] * matrix[9];
  inverse_values[13] = matrix[0] * matrix[9] * matrix[14] - matrix[0] * matrix[10] * matrix[13] -
      matrix[8] * matrix[1] * matrix[14] + matrix[8] * matrix[2] * matrix[13] + matrix[12] *
      matrix[1] * matrix[10] - matrix[12] * matrix[2] * matrix[9];
  inverse_values[2] = matrix[1] * matrix[6] * matrix[15] - matrix[1] * matrix[7] * matrix[14] -
      matrix[5] * matrix[2] * matrix[15] + matrix[5] * matrix[3] * matrix[14] + matrix[13] *
      matrix[2] * matrix[7] - matrix[13] * matrix[3] * matrix[6];
  inverse_values[6] = -matrix[0] * matrix[6] * matrix[15] + matrix[0] * matrix[7] * matrix[14] +
      matrix[4] * matrix[2] * matrix[15] - matrix[4] * matrix[3] * matrix[14] - matrix[12] *
      matrix[2] * matrix[7] + matrix[12] * matrix[3] * matrix[6];
  inverse_values[10] = matrix[0] * matrix[5] * matrix[15] - matrix[0] * matrix[7] * matrix[13] -
      matrix[4] * matrix[1] * matrix[15] + matrix[4] * matrix[3] * matrix[13] + matrix[12] *
      matrix[1] * matrix[7] - matrix[12] * matrix[3] * matrix[5];
  inverse_values[14] = -matrix[0] * matrix[5] * matrix[14] + matrix[0] * matrix[6] * matrix[13] +
      matrix[4] * matrix[1] * matrix[14] - matrix[4] * matrix[2] * matrix[13] - matrix[12] *
      matrix[1] * matrix[6] + matrix[12] * matrix[2] * matrix[5];
  inverse_values[3] = -matrix[1] * matrix[6] * matrix[11] + matrix[1] * matrix[7] * matrix[10] +
      matrix[5] * matrix[2] * matrix[11] - matrix[5] * matrix[3] * matrix[10] - matrix[9] *
      matrix[2] * matrix[7] + matrix[9] * matrix[3] * matrix[6];
  inverse_values[7] = matrix[0] * matrix[6] * matrix[11] - matrix[0] * matrix[7] * matrix[10] -
      matrix[4] * matrix[2] * matrix[11] + matrix[4] * matrix[3] * matrix[10] + matrix[8] *
      matrix[2] * matrix[7] - matrix[8] * matrix[3] * matrix[6];
  inverse_values[11] = -matrix[0] * matrix[5] * matrix[11] + matrix[0] * matrix[7] * matrix[9] +
      matrix[4] * matrix[1] * matrix[11] - matrix[4] * matrix[3] * matrix[9] - matrix[8] *
      matrix[1] * matrix[7] + matrix[8] * matrix[3] * matrix[5];
  inverse_values[15] = matrix[0] * matrix[5] * matrix[10] - matrix[0] * matrix[6] * matrix[9] -
      matrix[4] * matrix[1] * matrix[10] + matrix[4] * matrix[2] * matrix[9] + matrix[8] *
      matrix[1] * matrix[6] - matrix[8] * matrix[2] * matrix[5];
  float det = matrix[0] * inverse_values[0] + matrix[1] * inverse_values[4] + matrix[2] *
      inverse_values[8] + matrix[3] * inverse_values[12];
  // TODO(brkho): Use a more numerically stable method here.
  assert(std::abs(det) > 0.000001);

  det = 1.0 / det;
  for (int i = 0; i < 16; i++) {
    inverse_values[i] *= det;
  }
  return Matrix4x4(inverse_values);
}

Transform::Transform() : matrix{Matrix4x4()}, matrix_inverse{Matrix4x4()} {}

Transform::Transform(const Matrix4x4& m) : matrix(m), matrix_inverse{m.Inverse()} {}

Transform::Transform(const Matrix4x4& m, const Matrix4x4& m_inverse) : matrix{m},
    matrix_inverse{m_inverse} {}

Transform Transform::Inverse() const {
  return Transform(matrix_inverse, matrix);
}

Transform Transform::Transpose() const {
  return Transform(matrix.Transpose(), matrix_inverse.Transpose());
}

// TODO(brianh): Needs test.
bool Transform::SwapsHandedness() const {
  float det = matrix.Get(0, 0) * (matrix.Get(1, 1) * matrix.Get(2, 2) - matrix.Get(1, 2) *
      matrix.Get(2, 1)) - matrix.Get(0, 1) * (matrix.Get(1, 0) * matrix.Get(2, 2) -
      matrix.Get(1, 2) * matrix.Get(2, 0)) + matrix.Get(0, 2) * (matrix.Get(1, 0) *
      matrix.Get(2, 1) - matrix.Get(1, 1) * matrix.Get(2, 0));
  return det < 0;
}

bool Transform::operator==(const Transform &that) const {
  return matrix == that.matrix && matrix_inverse == that.matrix_inverse;
}

Transform TranslationTransform(const Vector3f &delta) {
  float values[16] = {1, 0, 0, delta.x, 0, 1, 0, delta.y, 0, 0, 1, delta.z, 0, 0, 0, 1};
  float inverse_values[16] = {1, 0, 0, -delta.x, 0, 1, 0, -delta.y, 0, 0, 1, -delta.z, 0, 0, 0, 1};
  return Transform(Matrix4x4(values), Matrix4x4(inverse_values));
}

Transform ScaleTransform(float x, float y, float z) {
  float values[16] = {x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1};
  float inverse_values[16] = {1.0f / x, 0, 0, 0, 0, 1.0f / y, 0, 0, 0, 0, 1.0f / z, 0, 0, 0, 0, 1};
  return Transform(Matrix4x4(values), Matrix4x4(inverse_values));
}

Transform RotateXTransform(float theta) {
  float sin_theta = std::sin(theta);
  float cos_theta = std::cos(theta);
  float values[16] = {1, 0, 0, 0, 0, cos_theta, -sin_theta, 0, 0, sin_theta, cos_theta, 0,
      0, 0, 0, 1};
  Matrix4x4 matrix = Matrix4x4(values);
  return Transform(matrix, matrix.Transpose());
}

Transform RotateYTransform(float theta) {
  float sin_theta = std::sin(theta);
  float cos_theta = std::cos(theta);
  float values[16] = {cos_theta, 0, sin_theta, 0, 0, 1, 0, 0, -sin_theta, 0, cos_theta, 0,
      0, 0, 0, 1};
  Matrix4x4 matrix = Matrix4x4(values);
  return Transform(matrix, matrix.Transpose());
}

Transform RotateZTransform(float theta) {
  float sin_theta = std::sin(theta);
  float cos_theta = std::cos(theta);
  float values[16] = {cos_theta, -sin_theta, 0, 0, sin_theta, cos_theta, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 1};
  Matrix4x4 matrix = Matrix4x4(values);
  return Transform(matrix, matrix.Transpose());
}

// Fancy vector algebra lifted from pbrt.
Transform RotateArbitraryAxisTransform(const Vector3f &axis, float theta) {
  Vector3f a = Normalize(axis);
  float sin_theta = std::sin(theta);
  float cos_theta = std::cos(theta);
  float values[16] = {a.x * a.x + (1 - a.x * a.x) * cos_theta,
      a.x * a.y * (1 - cos_theta) - a.z * sin_theta, a.x * a.z * (1 - cos_theta) + a.y * sin_theta,
      0, a.x * a.y * (1 - cos_theta) + a.z * sin_theta, a.y * a.y + (1 - a.y * a.y) * cos_theta,
      a.y * a.z * (1 - cos_theta) - a.x * sin_theta, 0,
      a.x * a.z * (1 - cos_theta) - a.y * sin_theta, a.y * a.z * (1 - cos_theta) + a.x * sin_theta,
      a.z * a.z + (1 - a.z * a.z) * cos_theta, 0, 0, 0, 0, 1};
  Matrix4x4 matrix = Matrix4x4(values);
  return Transform(matrix, matrix.Transpose());
}

// Returns a look at transformation, also adapted from pbrt.
Transform LookAtTransformation(const Vector3f &pos, const Vector3f &target, const Vector3f &up) {
  Vector3f direction = Normalize(target - pos);
  Vector3f left = Normalize(Cross(Normalize(up), direction));
  Vector3f new_up = Cross(direction, left);
  float inverse_values[16] = {left.x, new_up.x, direction.x, pos.x, left.y, new_up.y, direction.y,
      pos.y, left.z, new_up.z, direction.z, pos.z, 0, 0, 0, 1};
  Matrix4x4 inverse_matrix = Matrix4x4(inverse_values);
  return Transform(inverse_matrix.Inverse(), inverse_matrix);
}

template <typename T>
Point3<T> Transform::operator()(const Point3<T> &p) const {
  T x = matrix.Get(0, 0) * p.x + matrix.Get(0, 1) * p.y + matrix.Get(0, 2) * p.z + matrix.Get(0, 3);
  T y = matrix.Get(1, 0) * p.x + matrix.Get(1, 1) * p.y + matrix.Get(1, 2) * p.z + matrix.Get(1, 3);
  T z = matrix.Get(2, 0) * p.x + matrix.Get(2, 1) * p.y + matrix.Get(2, 2) * p.z + matrix.Get(2, 3);
  T w = matrix.Get(3, 0) * p.x + matrix.Get(3, 1) * p.y + matrix.Get(3, 2) * p.z + matrix.Get(3, 3);
  float divisor = 1.0f / w;
  return w == 1 ? Point3<T>(x, y, z) : Point3<T>(x * divisor, y * divisor, z * divisor);
}

template <typename T>
Vector3<T> Transform::operator()(const Vector3<T> &v) const {
  T x = matrix.Get(0, 0) * v.x + matrix.Get(0, 1) * v.y + matrix.Get(0, 2) * v.z;
  T y = matrix.Get(1, 0) * v.x + matrix.Get(1, 1) * v.y + matrix.Get(1, 2) * v.z;
  T z = matrix.Get(2, 0) * v.x + matrix.Get(2, 1) * v.y + matrix.Get(2, 2) * v.z;
  return Vector3<T>(x, y, z);
}


Ray3f Transform::operator()(const Ray3f &r) const {
  return Ray3f((*this)(r.origin), (*this)(r.direction), r.max_t);
}

Transform Transform::operator*(const Transform &that) const {
  return Transform(matrix * that.matrix, that.matrix_inverse * matrix_inverse);
}

std::string Transform::ToString() const {
  return "{\n" + matrix.ToString() + ",\n" + matrix_inverse.ToString() + "\n}";
}

}
