// This header defines the PerspectiveCamera, an ideal and non-photorealistic Camera implementation
// based on a Perspective transform.
//
// Author: brian@brkho.com

#ifndef LIANG_CAMERAS_PERSPECTIVE_CAMERA_H
#define LIANG_CAMERAS_PERSPECTIVE_CAMERA_H

#include "cameras/camera.h"
#include "core/geometry.h"
#include "core/liang.h"
#include "core/transform.h"

namespace liang {

class PerspectiveCamera : public Camera {
  public:
    // The distance to the near plane.
    const float NEAR_PLANE = 0.01;
    // The distance to the far plane.
    const float FAR_PLANE = 1000.0;

    // PerspectiveCamera constructor that takes the world to camera transform, the size of the
    // screen, and a film.
    PerspectiveCamera(Transform world_to_camera, float fov, Point2f screen_min,
        Point2f screen_max);

    // Generates a ray given a point on the film. As in pbrt, this returns a float that represents
    // how much we should weight the generated ray.
    float GenerateRay(const Point2f &film_location, Ray3f *ray) const;

  private:
    // Transform from camera space to screen space.
    Transform camera_to_screen;

    // Transform from screen space to raster space.
    Transform screen_to_raster;

    // Transforms from raster space to camera space.
    Transform raster_to_camera;
};

}

#endif  // LIANG_CAMERAS_PERSPECTIVE_CAMERA_H
