#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "camera/camera.h"

namespace graphics::camera {
class QuaternionCamera final : public Camera {
 public:
  explicit QuaternionCamera(glm::vec3 _position) : Camera(_position), rotation(glm::identity<glm::quat>()) {}
  void move(GLFWwindow* window) override;
  void updateView() override;
  void updateProjection(float aspectRatio) override;

 private:
  glm::quat rotation;
  // TODO (optional): Change these values if your WASD or mouse move too slow or too fast.
  constexpr static float keyboardMoveSpeed = 10.0f;
  constexpr static float mouseMoveSpeed = 0.1f;
};
}  // namespace graphics::camera
