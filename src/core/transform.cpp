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
    if (matrix[i] != that.matrix[i]) {
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

Matrix4x4 Transpose(const Matrix4x4& m) {
  float transposed_values[16] = {m.Get(0, 0), m.Get(1, 0), m.Get(2, 0), m.Get(3, 0), m.Get(0, 1),
      m.Get(1, 1), m.Get(2, 1), m.Get(3, 1), m.Get(0, 2), m.Get(1, 2), m.Get(2, 2), m.Get(3, 2),
      m.Get(0, 3), m.Get(1, 3), m.Get(2, 3), m.Get(3, 3)};
  return Matrix4x4(transposed_values);
}

// Adapted from GLU's MESA implementation.
Matrix4x4 Inverse(const Matrix4x4& m) {
  float inverse_values[16];
  inverse_values[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] *
      m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
  inverse_values[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] *
      m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
  inverse_values[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] *
      m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
  inverse_values[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] *
      m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
  inverse_values[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] *
      m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
  inverse_values[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] *
      m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
  inverse_values[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] *
      m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
  inverse_values[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] *
      m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
  inverse_values[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] *
      m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
  inverse_values[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] *
      m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
  inverse_values[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] *
      m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
  inverse_values[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] *
      m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
  inverse_values[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] *
      m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
  inverse_values[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] *
      m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
  inverse_values[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] *
      m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
  inverse_values[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] *
      m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];
  float det = m[0] * inverse_values[0] + m[1] * inverse_values[4] + m[2] * inverse_values[8] +
      m[3] * inverse_values[12];
  // TODO(brkho): Use a more numerically stable method here.
  assert(std::abs(det) > 0.000001);

  det = 1.0 / det;
  for (int i = 0; i < 16; i++) {
    inverse_values[i] *= det;
  }
  return Matrix4x4(inverse_values);
}

Transform::Transform() : matrix{Matrix4x4()}, matrix_inverse{Matrix4x4()} {}

Transform::Transform(const Matrix4x4& m) : matrix(m), matrix_inverse{Inverse(m)} {}

Transform::Transform(const Matrix4x4& m, const Matrix4x4& m_inverse) : matrix{m},
    matrix_inverse{m_inverse} {}

Transform Inverse(const Transform &t) {
  return Transform(t.matrix_inverse, t.matrix);
}

Transform Transpose(const Transform &t) {
  return Transform(Transpose(t.matrix), Transpose(t.matrix_inverse));
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
  return Transform(matrix, Transpose(matrix));
}

Transform RotateYTransform(float theta) {
  float sin_theta = std::sin(theta);
  float cos_theta = std::cos(theta);
  float values[16] = {cos_theta, 0, sin_theta, 0, 0, 1, 0, 0, -sin_theta, 0, cos_theta, 0,
      0, 0, 0, 1};
  Matrix4x4 matrix = Matrix4x4(values);
  return Transform(matrix, Transpose(matrix));
}

Transform RotateZTransform(float theta) {
  float sin_theta = std::sin(theta);
  float cos_theta = std::cos(theta);
  float values[16] = {cos_theta, -sin_theta, 0, 0, sin_theta, cos_theta, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 1};
  Matrix4x4 matrix = Matrix4x4(values);
  return Transform(matrix, Transpose(matrix));
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
  return Transform(matrix, Transpose(matrix));
}

// Returns a look at transformation, also adapted from pbrt.
Transform LookAtTransformation(const Vector3f &pos, const Vector3f &target, const Vector3f &up) {
  Vector3f direction = Normalize(target - pos);
  Vector3f left = Normalize(Cross(Normalize(up), direction));
  Vector3f new_up = Cross(direction, left);
  float inverse_values[16] = {left.x, new_up.x, direction.x, pos.x, left.y, new_up.y, direction.y,
      pos.y, left.z, new_up.z, direction.z, pos.z, 0, 0, 0, 1};
  Matrix4x4 inverse_matrix = Matrix4x4(inverse_values);
  return Transform(Inverse(inverse_matrix), inverse_matrix);
}

}
