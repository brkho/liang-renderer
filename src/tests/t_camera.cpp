#include "cameras/film.h"
#include "cameras/perspective_camera.h"
#include "core/scene.h"
#include "filters/filter.h"
#include "filters/box_filter.h"
#include "primitives/aggregate_primitive.h"
#include "primitives/geometric_primitive.h"
#include "primitives/primitive.h"
#include "tests/util.h"
#include "tests/test.h"

TEST(PerspectiveCameraTest, Creation) {
  liang::Transform world_to_camera = liang::LookAtTransform(liang::Vector3f(5.f, 5.f, 5.f),
      liang::Vector3f(0.f, 0.f, 0.f), liang::Vector3f(0.f, 0.f, 1.f));
  auto filter = std::unique_ptr<liang::Filter>(new liang::BoxFilter(1.f));
  auto film = std::make_shared<liang::Film>(32, 32, std::move(filter));
  ASSERT_NO_THROW(liang::PerspectiveCamera camera = liang::PerspectiveCamera(world_to_camera, film,
      45.f, liang::Point2f(-1.f, -1.f), liang::Point2f(1.f, 1.f)););
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
  liang::Ray3f ray = liang::Ray3f();
  camera.GenerateRay(liang::Point2f(15, 18), &ray);
  Point3FloatEquals(ray.origin, 5.01, 5.0, 0.0);
  Vector3FloatEquals(ray.direction, -0.724887, -0.686926, -0.051690);
}

TEST(FilmTest, Creation) {
  auto filter = std::unique_ptr<liang::Filter>(new liang::BoxFilter(1.f));
  auto film = std::make_shared<liang::Film>(8, 16, std::move(filter));
  for (uint x = 0; x < 8; x++) {
    for (uint y = 0; y < 16; y++) {
      liang::Pixel pixel = film->GetPixel(x, y);
      ASSERT_EQ(0.f, pixel.r);
      ASSERT_EQ(0.f, pixel.g);
      ASSERT_EQ(0.f, pixel.b);
      ASSERT_EQ(0.f, pixel.weight_sum);
    }
  }
  ASSERT_DEATH({ film->GetPixel(8, 0); }, ASSERTION_FAILURE);
  ASSERT_DEATH({ film->GetPixel(0, 16); }, ASSERTION_FAILURE);
}

TEST(FilmTest, AddSample) {
  auto filter = std::unique_ptr<liang::Filter>(new liang::BoxFilter(1.f));
  auto film = std::make_shared<liang::Film>(2, 4, std::move(filter));
  for (uint x = 0; x < 2; x++) {
    for (uint y = 0; y < 4; y++) {
      float value = (float)y * 2.f + (float)x;
      film->AddSample((float)x, (float)y, value, value, value, 1.f);
    }
  }
  for (uint x = 0; x < 2; x++) {
    for (uint y = 0; y < 4; y++) {
      float value = (float)y * 2.f + (float)x;
      liang::Pixel pixel = film->GetPixel(x, y);
      ASSERT_EQ(value, pixel.r);
      ASSERT_EQ(value, pixel.g);
      ASSERT_EQ(value, pixel.b);
      ASSERT_EQ(1.f, pixel.weight_sum);
    }
  }
  ASSERT_DEATH(film->AddSample(10.f, 0.f, 1.f, 1.f, 1.f, 1.f), ASSERTION_FAILURE);
  ASSERT_DEATH(film->AddSample(0.f, 10.f, 1.f, 1.f, 1.f, 1.f), ASSERTION_FAILURE);
}

TEST(FilmTest, ClearFilm) {
  auto filter = std::unique_ptr<liang::Filter>(new liang::BoxFilter(1.f));
  auto film = std::make_shared<liang::Film>(2, 4, std::move(filter));
  for (uint x = 0; x < 2; x++) {
    for (uint y = 0; y < 4; y++) {
      film->AddSample((float)x, (float)y, 1.f, 1.f, 1.f, 1.f);
    }
  }
  for (uint x = 0; x < 2; x++) {
    for (uint y = 0; y < 4; y++) {
      liang::Pixel pixel = film->GetPixel(x, y);
      ASSERT_EQ(1.f, pixel.r);
      ASSERT_EQ(1.f, pixel.g);
      ASSERT_EQ(1.f, pixel.b);
      ASSERT_EQ(1.f, pixel.weight_sum);
    }
  }
  film->ClearFilm();
  for (uint x = 0; x < 2; x++) {
    for (uint y = 0; y < 4; y++) {
      liang::Pixel pixel = film->GetPixel(x, y);
      ASSERT_EQ(0.f, pixel.r);
      ASSERT_EQ(0.f, pixel.g);
      ASSERT_EQ(0.f, pixel.b);
      ASSERT_EQ(0.f, pixel.weight_sum);
    }
  }
}
