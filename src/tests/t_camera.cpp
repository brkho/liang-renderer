#include "cameras/film.h"
#include "cameras/perspective_camera.h"
#include "core/scene.h"
#include "filters/filter.h"
#include "filters/box_filter.h"
#include "primitives/aggregate_primitive.h"
#include "primitives/primitive.h"
#include "tests/util.h"
#include "tests/test.h"

TEST(PerspectiveCameraTest, Creation) {
  liang::Transform world_to_camera = liang::LookAtTransform(liang::Vector3f(5.f, 5.f, 5.f),
      liang::Vector3f(0.f, 0.f, 0.f), liang::Vector3f(0.f, 0.f, 1.f));
  auto filter = std::unique_ptr<liang::Filter>(new liang::BoxFilter(1.f));
  auto film = std::make_shared<liang::Film>(32, 32, std::move(filter));
  ASSERT_NO_THROW(liang::PerspectiveCamera camera = liang::PerspectiveCamera(world_to_camera, film, 45.f,
      liang::Point2f(-1.f, -1.f), liang::Point2f(1.f, 1.f)););
}

TEST(PerspectiveCameraTest, GenerateRay) {
  std::vector<std::shared_ptr<liang::GeometricPrimitive>> geo_prims = CreateUnitCubePrimitives();
  std::vector<std::shared_ptr<liang::Primitive>> prims(geo_prims.begin(), geo_prims.end());
  liang::Scene scene(std::make_shared<liang::AggregatePrimitive>(prims));
  liang::Transform world_to_camera = liang::LookAtTransform(liang::Vector3f(5.01f, 5.0f, 0.f),
      liang::Vector3f(0.f, 0.f, 0.f), liang::Vector3f(0.f, 0.f, 1.f));
  auto filter = std::unique_ptr<liang::Filter>(new liang::BoxFilter(1.f));
  auto film = std::make_shared<liang::Film>(32, 32, std::move(filter));
  liang::PerspectiveCamera camera = liang::PerspectiveCamera(world_to_camera, film, 45.f,
      liang::Point2f(-1.f, -1.f), liang::Point2f(1.f, 1.f));

  // int x, y, n;
  // unsigned char *data = stbi_load("assets/test.png", &x, &y, &n, 0);
  // for (int i = 0; i < x; i++) {
  //   for (int j = 0; j < y; j++) {
  //     for (int k = 0; k < n - 1; k++) {
  //       // data[i * x + j * y + k]
  //       unsigned char color = data[i * x * n + j * n + k];
  //       data[i * x * n + j * n + k] = 255 - color;
  //       // std::cout << (int)data[i * x + j * y + k] << " ";
  //     }
  //   }
  //   // std::cout << std::endl;
  // }
  // std::cout << stbi_write_png("assets/out.png", x, y, 4, data, x * 4) << std::endl;



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

TEST(FilmTest, Creation) {
  std::vector<std::shared_ptr<liang::GeometricPrimitive>> geo_prims = CreateUnitCubePrimitives();
  std::vector<std::shared_ptr<liang::Primitive>> prims(geo_prims.begin(), geo_prims.end());
  liang::Scene scene(std::make_shared<liang::AggregatePrimitive>(prims));
  int index = 0;
  float PI = 3.1415926535897932;
  for (float theta = 0.f; theta < 2 * PI; theta += (PI / 10.f)) {
    liang::Transform world_to_camera = liang::LookAtTransform(liang::Vector3f(std::sin(theta) * 2.f + 0.01f, 2.0f, std::cos(theta) * 2.f),
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
}
