#include "cameras/camera.h"
#include "cameras/perspective_camera.h"

namespace liang {

PerspectiveCamera::PerspectiveCamera(Transform world_to_camera, float fov, Point2f screen_min,
    Point2f screen_max) : Camera{world_to_camera},
    camera_to_screen{PerspectiveTransform(fov, NEAR_PLANE, FAR_PLANE)} {
  Transform screen_to_translated = TranslationTransform(Vector3f(-screen_min.x, -screen_max.y, 0));
  Transform translated_to_ndc = ScaleTransform(1.f / (screen_max.x - screen_min.x),
      1.f / (screen_min.y - screen_max.y), 1.f);
  // When Film is implemented, use the dimensions from there instead of hard coding.
  Transform ndc_to_raster = ScaleTransform(32.f, 32.f, 1.f);
  screen_to_raster = ndc_to_raster * translated_to_ndc * screen_to_translated;
  raster_to_camera = camera_to_screen.Inverse() * screen_to_raster.Inverse();
}

float PerspectiveCamera::GenerateRay(const Point2f &film_location, Ray3f *ray) const {
  Point3f film_posititon = raster_to_camera(Point3f(film_location.x, film_location.y, 0.f));
  *ray = liang::Ray3f(Point3f(0.f, 0.f, 0.f), Normalize(Vector3f(film_posititon.x,
      film_posititon.y, film_posititon.z)));
  *ray = (world_to_camera.Inverse())(*ray);
  return 1.f;
  }
}
