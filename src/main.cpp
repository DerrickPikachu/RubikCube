#include <algorithm>
#include <memory>
#include <vector>
#include <iostream>
#include <stdio.h>

#include <GLFW/glfw3.h>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION
#include <glm/glm.hpp>

#include "camera/quat_camera.h"
#include "context_manager.h"
#include "shape/cube.h"

// Unnamed namespace for global variables
namespace {
std::vector<std::unique_ptr<graphics::shape::Cube>> cubes;
}  // namespace

void rotateLayer(graphics::shape::Axis& axis, int layerPosition) {
  using Axis = graphics::shape::Axis;
  for (auto& cube : cubes) {
    if (cube->getPosition(axis) == layerPosition) {
      cube->rotate(axis);
    }
  }
  std::cout << std::endl;
}

void rotateHoleCube(const graphics::shape::Axis& axis) {
  for (auto& cube : cubes) {
    cube->rotate(axis);
  }
}

void keyCallback(GLFWwindow* window, int key, int, int action, int) {
  // There are three actions: press, release, hold
  if (action != GLFW_PRESS) return;
  // Press ESC to close the window.
  if (key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
    return;
  }
  // Check all cubes are not rotating
  bool idle = std::all_of(cubes.begin(), cubes.end(), [](const auto& cube) { return cube->isIdle(); });
  if (!idle) return;
  // There are three Axis: X, Y, Z
  using Axis = graphics::shape::Axis;
  // TODO: Detect key-events, perform rotation
  //       1. Use switch/case to find the key you want.
  //       2. Iterate through all cubes, perform rotation on those you want to rotate.
  // Hint:
  //       1. You can get the cube's layer by calling getPosition with Axis ( cube->getPosition(Axis::X) ),
  //          the return value can be {-1, 0, 1}, representing three layers
  //       2. You can rotate it by calling rotate with Axis ( cube->rotate(Axis::X) )
  //       3. glfw3's key list (https://www.glfw.org/docs/3.3/group__keys.html)
  // Note:
  //       You should finish your cube rendering first.
  //       Otherwise you will spend a lot of time debugging this with a black screen.
  Axis axis;
  switch (key) {
    case GLFW_KEY_1:
      axis = Axis::X;
      rotateLayer(axis, 1);
      break;
    case GLFW_KEY_2:
      axis = Axis::X;
      rotateLayer(axis, 0);
      break;
    case GLFW_KEY_3:
      axis = Axis::X;
      rotateLayer(axis, -1);
      break;
    case GLFW_KEY_4:
      axis = Axis::Y;
      rotateLayer(axis, 1);
      break;
    case GLFW_KEY_5:
      axis = Axis::Y;
      rotateLayer(axis, 0);
      break;
    case GLFW_KEY_6:
      axis = Axis::Y;
      rotateLayer(axis, -1);
      break;
    case GLFW_KEY_7:
      axis = Axis::Z;
      rotateLayer(axis, 1);
      break;
    case GLFW_KEY_8:
      axis = Axis::Z;
      rotateLayer(axis, 0);
      break;
    case GLFW_KEY_9:
      axis = Axis::Z;
      rotateLayer(axis, -1);
      break;
    case GLFW_KEY_Z:
      axis = Axis::Z;
      rotateHoleCube(axis);
      break;
    case GLFW_KEY_X:
      axis = Axis::X;
      rotateHoleCube(axis);
      break;
    case GLFW_KEY_Y:
      axis = Axis::Y;
      rotateHoleCube(axis);
      break;
    default:
      break;
  }
}

void resizeCallback(GLFWwindow* window, int width, int height) {
  OpenGLContext::framebufferResizeCallback(window, width, height);
  auto ptr = static_cast<graphics::camera::Camera*>(glfwGetWindowUserPointer(window));
  if (ptr != nullptr) {
    ptr->updateProjection(OpenGLContext::getAspectRatio());
  }
}

int main() {
  // Initialize OpenGL context, details are wrapped in class.
#ifdef __APPLE__
  // MacOS need explicit request legacy support
  OpenGLContext::createContext(21, GLFW_OPENGL_ANY_PROFILE);
#else
  OpenGLContext::createContext(43, GLFW_OPENGL_COMPAT_PROFILE);
#endif
  GLFWwindow* window = OpenGLContext::getWindow();
  glfwSetWindowTitle(window, "HW1");
  glfwSetKeyCallback(window, keyCallback);
  glfwSetFramebufferSizeCallback(window, resizeCallback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#ifndef NDEBUG
  OpenGLContext::printSystemInfo();
  // This is useful if you want to debug your OpenGL API calls.
  OpenGLContext::enableDebugCallback();
#endif
  // Setup camera.
  graphics::camera::QuaternionCamera camera(glm::vec3(0, 0, 15));
  camera.initialize(OpenGLContext::getAspectRatio());
  glfwSetWindowUserPointer(window, &camera);
  // Generate all mini-cubes
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      for (int k = -1; k <= 1; ++k) {
        cubes.emplace_back(std::make_unique<graphics::shape::Cube>(glm::vec3(i, j, k)));
      }
    }
  }
  // Main rendering loop
  while (!glfwWindowShouldClose(window)) {
    // Polling events.
    glfwPollEvents();
    camera.move(window);
    // GL_XXX_BIT can simply "OR" together to use.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(camera.getProjectionMatrix());
    // ModelView Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(camera.getViewMatrix());
    // TODO: Render Rubik's cube
    //       1. Iterate through all cube in cubes.
    //       2. For each cube, call cube->setupModel() and cube->draw().
    //       3. You can use glPushMatrix, glPopMatrix to 'cache' the current matrix.
    // Hint:
    //       glPushMatrix/glPopMatrix   (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glPushMatrix.xml)
    // Note:
    //       You can implement this section using less than 10 lines of code.
    for (const auto& cube : cubes) {
      glMatrixMode(GL_MODELVIEW);
      glLoadMatrixf(camera.getViewMatrix());
      cube->setupModel();
      cube->draw();
    }
#ifdef __APPLE__
    // Some platform need explicit glFlush
    glFlush();
#endif
    glfwSwapBuffers(window);
  }
  return 0;
}
