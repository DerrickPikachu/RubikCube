#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace graphics::camera {

class Camera {
 public:
  explicit Camera(glm::vec3 position);
  virtual ~Camera() = default;

  const float* getProjectionMatrix() const { return glm::value_ptr(projectionMatrix); }
  const float* getViewMatrix() const { return glm::value_ptr(viewMatrix); }
  void initialize(float aspectRatio);
  virtual void move(GLFWwindow* window) = 0;
  virtual void updateProjection(float aspectRatio) = 0;

 protected:
  virtual void updateView() = 0;
  glm::vec3 position;
  glm::vec3 up;
  glm::vec3 front;
  glm::vec3 right;
  glm::mat4 projectionMatrix;
  glm::mat4 viewMatrix;
};
}  // namespace graphics::camera
