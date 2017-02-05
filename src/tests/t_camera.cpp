#include "cameras/perspective_camera.h"
#include "tests/util.h"
#include "tests/test.h"


#include "primitives/aggregate_primitive.h"
#include "primitives/primitive.h"
#include "core/scene.h"

TEST(PerspectiveCameraTest, Creation) {
  liang::Transform world_to_camera = liang::LookAtTransform(liang::Vector3f(5.f, 5.f, 5.f),
      liang::Vector3f(0.f, 0.f, 0.f), liang::Vector3f(0.f, 0.f, 1.f));
  ASSERT_NO_THROW({liang::PerspectiveCamera(world_to_camera, 45.f, liang::Point2f(-1.f, -1.f),
      liang::Point2f(1.f, 1.f));});
}

TEST(PerspectiveCameraTest, GenerateRay) {
  std::vector<std::shared_ptr<liang::GeometricPrimitive>> geo_prims = CreateUnitCubePrimitives();
  std::vector<std::shared_ptr<liang::Primitive>> prims(geo_prims.begin(), geo_prims.end());
  liang::Scene scene(std::make_shared<liang::AggregatePrimitive>(prims));

  liang::Transform world_to_camera = liang::LookAtTransform(liang::Vector3f(5.01f, 5.0f, 0.f),
      liang::Vector3f(0.f, 0.f, 0.f), liang::Vector3f(0.f, 0.f, 1.f));
  liang::PerspectiveCamera camera = liang::PerspectiveCamera(world_to_camera, 45.f,
      liang::Point2f(-1.f, -1.f), liang::Point2f(1.f, 1.f));

  // // liang::Ray3f ray = liang::Ray3f(liang::Point3f(0.2, -0.2, 0.2), liang::Vector3f(0.0, 0.0, -1.0));
  // // ASSERT_TRUE(scene.Intersect(ray));
  // for (float i = 0.f; i < 32.f; i++) {
  //   for (float j = 0.f; j < 32.f; j++) {
  //     liang::Ray3f ray = liang::Ray3f();
  //     camera.GenerateRay(liang::Point2f(i, j), &ray);
  //     std::string letter = scene.Intersect(ray) ? "■■" : "  ";
  //     std::cout << letter;
  //   }
  //   std::cout << "|" << std::endl;
  // }
}
