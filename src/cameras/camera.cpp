#include "cameras/camera.h"

namespace liang {

Camera::Camera(const Transform world_to_camera, std::shared_ptr<Film> film) :
    world_to_camera{world_to_camera}, film{film} {}

}
