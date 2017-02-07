// This header defines the Camera interface, an abstraction over some useful properties shared by
// all Camera implementations. In general, a Camera is exactly what it sounds like, an instrument
// with an orientation in world space from which rays are cast to get information about the scene.
//
// Author: brian@brkho.com

#ifndef LIANG_CAMERAS_CAMERA_H
#define LIANG_CAMERAS_CAMERA_H

#include "cameras/film.h"
#include "core/geometry.h"
#include "core/liang.h"
#include "core/transform.h"

namespace liang {

class Camera {
  public:
    // Camera constructor that takes the world to camera transform (probably returned via LookAt)
    // and a shared pointer to a film.
    Camera(Transform world_to_camera, std::shared_ptr<Film> film);

    // Generates a ray given a point on the film. As in pbrt, this returns a float that represents
    // how much we should weight the generated ray.
    virtual float GenerateRay(const Point2f &film_location, Ray3f *ray) const = 0;

  protected:
    // Transform from world space to camera space.
    Transform world_to_camera;
    // Shared pointer to the film we are recording to.
    std::shared_ptr<Film> film;
};

}

#endif  // LIANG_CAMERAS_CAMERA_H
