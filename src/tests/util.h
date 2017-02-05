// The main include of the Liang Renderer testing suite. This defines constants and global includes.
//
// Author: brian@brkho.com

#ifndef LIANG_TEST_UTIL
#define LIANG_TEST_UTIL

#include "core/geometry.h"
#include "core/liang.h"
#include "core/transform.h"
#include "primitives/geometric_primitive.h"
#include "shapes/mesh.h"

extern void Vector2IntEquals(liang::Vector2i vec, int x, int y);

extern void Vector2FloatEquals(liang::Vector2f vec, float x, float y);

extern void Vector3IntEquals(liang::Vector3i vec, int x, int y, int z);

extern void Vector3FloatEquals(liang::Vector3f vec, float x, float y, float z);

extern void Point2IntEquals(liang::Point2i point, int x, int y);

extern void Point2FloatEquals(liang::Point2f point, float x, float y);

extern void Point3IntEquals(liang::Point3i point, int x, int y, int z);

extern void Point3FloatEquals(liang::Point3f point, float x, float y, float z);

extern void Normal3FloatEquals(liang::Normal3f normal, float x, float y, float z);

extern void AABB3FloatEquals(liang::AABB3f box, float min_x, float min_y, float min_z, float max_x,
    float max_y, float max_z);

extern void AssertMatEquals(const liang::Matrix4x4 &matrix, const std::vector<float> &values);

// This is ugly and leaks memory. Clean this up when we have a real model loading system.
extern std::shared_ptr<liang::Mesh> CreateUnitCube(liang::Transform *object_to_world);

extern std::shared_ptr<liang::Mesh> CreateUnitCube();

extern std::vector<std::shared_ptr<liang::GeometricPrimitive>> CreateUnitCubePrimitives(
    liang::Transform *object_to_world);

extern std::vector<std::shared_ptr<liang::GeometricPrimitive>> CreateUnitCubePrimitives();

#endif  // LIANG_TEST_UTIL
