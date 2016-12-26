#include "core/geometry.h"
#include "core/liang.h"

#include <gtest/gtest.h>

TEST(GeometryVector2Test, Creation) {
  liang::Vector2<int> default_int_vector = liang::Vector2<int>();
  ASSERT_EQ(default_int_vector.x, 0);
  ASSERT_EQ(default_int_vector.y, 0);

  liang::Vector2<int> initialized_int_vector = liang::Vector2<int>(-5, 5);
  ASSERT_EQ(initialized_int_vector.x, -5);
  ASSERT_EQ(initialized_int_vector.y, 5);

  liang::Vector2<float> default_float_vector = liang::Vector2<float>();
  ASSERT_EQ(default_float_vector.x, 0.0);
  ASSERT_EQ(default_float_vector.y, 0.0);

  liang::Vector2<float> initialized_float_vector = liang::Vector2<float>(-5.0, 5.0);
  ASSERT_EQ(initialized_float_vector.x, -5.0);
  ASSERT_EQ(initialized_float_vector.y, 5.0);
}
