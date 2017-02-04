#include "shapes/mesh.h"

namespace liang {

std::shared_ptr<Mesh> CreateMesh(uint num_vertices, const std::shared_ptr<TriangleVertex> vertices,
    uint num_elements, const std::shared_ptr<uint> elements, const Transform *object_to_world) {
  assert(num_elements % 3 == 0);
  for (uint i = 0; i < num_elements; i++) {
    assert(elements.get()[i] < num_vertices);
  }
  return std::shared_ptr<Mesh>(
      new Mesh{num_vertices, vertices, num_elements, elements, object_to_world});
}

std::vector<std::shared_ptr<Triangle>> CreateTriangles(std::shared_ptr<Mesh> mesh) {
  std::vector<std::shared_ptr<Triangle>> triangles;
  for (uint i = 0; i < mesh->num_elements; i += 3) {
    uint triangle_index = i / 3;
    triangles.push_back(std::make_shared<Triangle>(mesh, triangle_index));
  }
  return triangles;
}

Triangle::Triangle(std::shared_ptr<Mesh> parent, uint triangle_index) :
    Shape(parent->object_to_world), parent{parent}, triangle_index{triangle_index} {}

TriangleVertex Triangle::GetVertex(uint n) const {
  assert(n < 3);
  return parent->vertices.get()[parent->elements.get()[triangle_index * 3 + n]];
}

AABB3f Triangle::ObjectBounds() const {
  return Union(AABB3f(GetVertex(0).position, GetVertex(1).position), AABB3f(GetVertex(2).position));
}

AABB3f Triangle::WorldBounds() const {
  return Union(AABB3f((*object_to_world)(GetVertex(0).position),
      (*object_to_world)(GetVertex(1).position)),
      AABB3f((*object_to_world)(GetVertex(2).position)));
}

bool Triangle::Intersect(Ray3f ray) const {
  // Find a new coordinate space where the ray origin is (0, 0, 0).
  Transform translation = TranslationTransform(Point3f() - ray.origin);
  Point3f original_v0 = (*object_to_world)(GetVertex(0).position);
  Point3f original_v1 = (*object_to_world)(GetVertex(1).position);
  Point3f original_v2 = (*object_to_world)(GetVertex(2).position);
  Point3f translated_p0 = translation(original_v0);
  Point3f translated_p1 = translation(original_v1);
  Point3f translated_p2 = translation(original_v2);

  // Find the largest dimension of the ray's direction and swap it with the z axis.
  uint max_index = 0;
  for (uint i = 0; i < 3; i++) {
    if (abs(ray.direction[i]) > abs(ray.direction[max_index])) {
      max_index = i;
    }
  }
  Point3f swapped_p0 = translated_p0;
  swapped_p0.z = swapped_p0[max_index];
  swapped_p0[max_index] = translated_p0.z;
  Point3f swapped_p1 = translated_p1;
  swapped_p1.z = swapped_p1[max_index];
  swapped_p1[max_index] = translated_p1.z;
  Point3f swapped_p2 = translated_p2;
  swapped_p2.z = swapped_p2[max_index];
  swapped_p2[max_index] = translated_p2.z;
  Vector3f swapped_dir = ray.direction;
  swapped_dir.z = swapped_dir[max_index];
  swapped_dir[max_index] = ray.direction.z;

  // Shear the coordinate space s.t. the Z axis corresponds to the ray's direction.
  float shear_x = -swapped_dir.x / swapped_dir.z;
  float shear_y = -swapped_dir.y / swapped_dir.z;
  float shear_z = 1.0 / swapped_dir.z;
  Point3f sheared_p0 = Point3f(
      swapped_p0.x + (shear_x * swapped_p0.z),
      swapped_p0.y + (shear_y * swapped_p0.z),
      shear_z * swapped_p0.z);
  Point3f sheared_p1 = Point3f(
      swapped_p1.x + (shear_x * swapped_p1.z),
      swapped_p1.y + (shear_y * swapped_p1.z),
      shear_z * swapped_p1.z);
  Point3f sheared_p2 = Point3f(
      swapped_p2.x + (shear_x * swapped_p2.z),
      swapped_p2.y + (shear_y * swapped_p2.z),
      shear_z * swapped_p2.z);

  // Test intersection using this new coordinate space.
  float e0 = (sheared_p1.x * sheared_p2.y) - (sheared_p1.y * sheared_p2.x);
  float e1 = (sheared_p2.x * sheared_p0.y) - (sheared_p2.y * sheared_p0.x);
  float e2 = (sheared_p0.x * sheared_p1.y) - (sheared_p0.y * sheared_p1.x);
  // These asserts should be explicitly handled.
  assert(e0 != 0);
  assert(e1 != 0);
  assert(e2 != 0);
  if (!((e0 > 0 && e1 > 0 && e2 > 0) || (e0 < 0 && e1 < 0 && e2 < 0))) {
    return false;
  }
  float determinant = e0 + e1 + e2;
  if (determinant == 0) {
    return false;
  }
  float t_scaled = e0 * sheared_p0.z + e1 * sheared_p1.z + e2 * sheared_p2.z;
  if ((determinant < 0 && (t_scaled >= 0 || t_scaled < ray.max_t * determinant)) ||
      (determinant > 0 && (t_scaled <= 0 || t_scaled > ray.max_t * determinant))) {
    return false;
  }
  return true;
}

}
