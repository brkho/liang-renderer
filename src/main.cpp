// The main entry point of the Liang Renderer.
//
// Author: brian@brkho.com

#include "cameras/film.h"
#include "cameras/perspective_camera.h"
#include "core/geometry.h"
#include "core/liang.h"
#include "core/scene.h"
#include "core/transform.h"
#include "filters/filter.h"
#include "filters/box_filter.h"
#include "primitives/aggregate_primitive.h"
#include "primitives/geometric_primitive.h"
#include "primitives/primitive.h"
#include "utils/math.h"

std::shared_ptr<liang::Mesh> CreateUnitCube(liang::Transform *object_to_world) {
  std::shared_ptr<liang::TriangleVertex> vertices(new liang::TriangleVertex[36]);
  vertices.get()[0] = {liang::Point3f(-0.5, -0.5, -0.5), liang::Normal3f(0.0, 0.0, -1.0)};
  vertices.get()[1] = {liang::Point3f(0.5, -0.5, -0.5), liang::Normal3f(0.0, 0.0, -1.0)};
  vertices.get()[2] = {liang::Point3f(0.5, 0.5, -0.5), liang::Normal3f(0.0, 0.0, -1.0)};
  vertices.get()[3] = {liang::Point3f(0.5, 0.5, -0.5), liang::Normal3f(0.0, 0.0, -1.0)};
  vertices.get()[4] = {liang::Point3f(-0.5, 0.5, -0.5), liang::Normal3f(0.0, 0.0, -1.0)};
  vertices.get()[5] = {liang::Point3f(-0.5, -0.5, -0.5), liang::Normal3f(0.0, 0.0, -1.0)};
  vertices.get()[6] = {liang::Point3f(-0.5, -0.5, 0.5), liang::Normal3f(0.0, 0.0, 1.0)};
  vertices.get()[7] = {liang::Point3f(0.5, -0.5, 0.5), liang::Normal3f(0.0, 0.0, 1.0)};
  vertices.get()[8] = {liang::Point3f(0.5, 0.5, 0.5), liang::Normal3f(0.0, 0.0, 1.0)};
  vertices.get()[9] = {liang::Point3f(0.5, 0.5, 0.5), liang::Normal3f(0.0, 0.0, 1.0)};
  vertices.get()[10] = {liang::Point3f(-0.5, 0.5, 0.5), liang::Normal3f(0.0, 0.0, 1.0)};
  vertices.get()[11] = {liang::Point3f(-0.5, -0.5, 0.5), liang::Normal3f(0.0, 0.0, 1.0)};
  vertices.get()[12] = {liang::Point3f(-0.5, 0.5, 0.5), liang::Normal3f(-1.0, 0.0, 0.0)};
  vertices.get()[13] = {liang::Point3f(-0.5, 0.5, -0.5), liang::Normal3f(-1.0, 0.0, 0.0)};
  vertices.get()[14] = {liang::Point3f(-0.5, -0.5, -0.5), liang::Normal3f(-1.0, 0.0, 0.0)};
  vertices.get()[15] = {liang::Point3f(-0.5, -0.5, -0.5), liang::Normal3f(-1.0, 0.0, 0.0)};
  vertices.get()[16] = {liang::Point3f(-0.5, -0.5, 0.5), liang::Normal3f(-1.0, 0.0, 0.0)};
  vertices.get()[17] = {liang::Point3f(-0.5, 0.5, 0.5), liang::Normal3f(-1.0, 0.0, 0.0)};
  vertices.get()[18] = {liang::Point3f(0.5, 0.5, 0.5), liang::Normal3f(1.0, 0.0, 0.0)};
  vertices.get()[19] = {liang::Point3f(0.5, 0.5, -0.5), liang::Normal3f(1.0, 0.0, 0.0)};
  vertices.get()[20] = {liang::Point3f(0.5, -0.5, -0.5), liang::Normal3f(1.0, 0.0, 0.0)};
  vertices.get()[21] = {liang::Point3f(0.5, -0.5, -0.5), liang::Normal3f(1.0, 0.0, 0.0)};
  vertices.get()[22] = {liang::Point3f(0.5, -0.5, 0.5), liang::Normal3f(1.0, 0.0, 0.0)};
  vertices.get()[23] = {liang::Point3f(0.5, 0.5, 0.5), liang::Normal3f(1.0, 0.0, 0.0)};
  vertices.get()[24] = {liang::Point3f(-0.5, -0.5, -0.5), liang::Normal3f(0.0, -1.0, 0.0)};
  vertices.get()[25] = {liang::Point3f(0.5, -0.5, -0.5), liang::Normal3f(0.0, -1.0, 0.0)};
  vertices.get()[26] = {liang::Point3f(0.5, -0.5, 0.5), liang::Normal3f(0.0, -1.0, 0.0)};
  vertices.get()[27] = {liang::Point3f(0.5, -0.5, 0.5), liang::Normal3f(0.0, -1.0, 0.0)};
  vertices.get()[28] = {liang::Point3f(-0.5, -0.5, 0.5), liang::Normal3f(0.0, -1.0, 0.0)};
  vertices.get()[29] = {liang::Point3f(-0.5, -0.5, -0.5), liang::Normal3f(0.0, -1.0, 0.0)};
  vertices.get()[30] = {liang::Point3f(-0.5, 0.5, -0.5), liang::Normal3f(0.0, 1.0, 0.0)};
  vertices.get()[31] = {liang::Point3f(0.5, 0.5, -0.5), liang::Normal3f(0.0, 1.0, 0.0)};
  vertices.get()[32] = {liang::Point3f(0.5, 0.5, 0.5), liang::Normal3f(0.0, 1.0, 0.0)};
  vertices.get()[33] = {liang::Point3f(0.5, 0.5, 0.5), liang::Normal3f(0.0, 1.0, 0.0)};
  vertices.get()[34] = {liang::Point3f(-0.5, 0.5, 0.5), liang::Normal3f(0.0, 1.0, 0.0)};
  vertices.get()[35] = {liang::Point3f(-0.5, 0.5, -0.5), liang::Normal3f(0.0, 1.0, 0.0)};

  std::shared_ptr<uint> elements(new uint[36]);
  for (uint i = 0; i < 36; i++) {
    elements.get()[i] = i;
  }
  return liang::CreateMesh(36, vertices, 36, elements, object_to_world);
}

std::shared_ptr<liang::Mesh> CreateUnitCube() {
  liang::Transform *object_to_world = new liang::Transform();
  return CreateUnitCube(object_to_world);
}

std::vector<std::shared_ptr<liang::GeometricPrimitive>> CreateUnitCubePrimitives(
    liang::Transform *object_to_world) {
  std::shared_ptr<liang::Mesh> mesh = CreateUnitCube(object_to_world);
  auto triangles = liang::CreateTriangles(mesh);
  return liang::CreateGeometricPrimitives(triangles);
}

std::vector<std::shared_ptr<liang::GeometricPrimitive>> CreateUnitCubePrimitives() {
  liang::Transform *object_to_world = new liang::Transform();
  return CreateUnitCubePrimitives(object_to_world);
}

// Main point of entry for the code.
int main(int /* argc */, char* /* argv */ []) {
  std::vector<std::shared_ptr<liang::GeometricPrimitive>> geo_prims = CreateUnitCubePrimitives();
  std::vector<std::shared_ptr<liang::Primitive>> prims(geo_prims.begin(), geo_prims.end());
  liang::Scene scene(std::make_shared<liang::AggregatePrimitive>(prims));
  int index = 0;
  for (float theta = 0.f; theta < 2 * PI; theta += (PI / 10.f)) {
    liang::Transform world_to_camera = liang::LookAtTransform(
        liang::Vector3f(std::sin(theta) * 2.f + 0.01f, 2.0f, std::cos(theta) * 2.f),
        liang::Vector3f(0.f, 0.f, 0.f), liang::Vector3f(0.f, 1.f, 0.f));
    auto filter = std::unique_ptr<liang::Filter>(new liang::BoxFilter(1.f));
    auto film = std::make_shared<liang::Film>(512, 512, std::move(filter));
    liang::PerspectiveCamera camera = liang::PerspectiveCamera(world_to_camera, film, 45.f,
        liang::Point2f(-1.f, -1.f), liang::Point2f(1.f, 1.f));
    for (float i = 0.f; i < film->height; i++) {
      for (float j = 0.f; j < film->width; j++) {
        liang::Ray3f ray = liang::Ray3f();
        camera.GenerateRay(liang::Point2f(i, j), &ray);
        bool intersected = scene.Intersect(ray);
        if (intersected) {
          film->AddSample(i, j, 1.f, 1.f, 1.f, 1.f);
        }
      }
    }
    std::string name = index < 10 ? "0" + std::to_string(index) : std::to_string(index);
    film->SaveAsPng("gif/" + name + ".png");
    index++;
  }
  return EXIT_SUCCESS;
}
