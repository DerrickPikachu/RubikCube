#include "shape/cube.h"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "utils.h"

namespace graphics::shape {
// TODO (optional): If your cube rotates very slow or fast, you can change rotation_speed.
int Cube::rotation_speed = 60;

glm::quat Cube::base_rotation[3] = {glm::angleAxis(utils::PI_2<float>() / rotation_speed, glm::vec3(1, 0, 0)),
                                    glm::angleAxis(utils::PI_2<float>() / rotation_speed, glm::vec3(0, 1, 0)),
                                    glm::angleAxis(utils::PI_2<float>() / rotation_speed, glm::vec3(0, 0, 1))};

Cube::Cube(glm::vec3 _position) noexcept
    : rotation_progress(rotation_speed),
      position(_position),
      translation(glm::translate(glm::identity<glm::mat4>(), position * scale)),
      rotation(glm::identity<glm::quat>()) {}

void Cube::setupModel() noexcept {
  if (rotation_direction) {
    if (rotation_progress == 0) {
      rotation_direction = std::nullopt;
      rotation_progress = rotation_speed;
    } else {
      --rotation_progress;
      rotation = base_rotation[*rotation_direction] * rotation;
    }
  }
  // TODO: Update model matrix
  //       1. You need this->rotation and this->translation
  //       2. Your model matrix should translate first, then rotate
  //       3. Multiply current ModelView matrix with your model matrix using glMultMatrix
  // Hint:
  //       glMultMatrix  (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glMultMatrix.xml)
  // Note:
  //       1. How to transform quaternion into a 4x4 rotation_matrix?
  //           -> glm::mat4 rotation_matrix = glm::mat4_cast(rotation)
  //       2. How to access float* pointer of glm::mat4 matrix?
  //           -> const float * ptr = glm::value_ptr(matrix)
  //       You can implement this section using less than 5 lines of code.
  glm::mat4 rotationMatrix = glm::mat4_cast(rotation);
  glm::mat4 modelMatrix = translation * rotationMatrix;
  glMultMatrixf(glm::value_ptr(modelMatrix));
}

void Cube::draw() const noexcept {
  // Green, top
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(0.0f, 1.0f, 0.0f);
  glNormal3f(0.0f, 1.0f, 0.0f);

  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glEnd();
  // TODO: Render other 5 face
  //       1. Setup vertex color
  //       2. Setup vertex normal
  //       3. Setup vertex position
  //       You must use one of these enum in glBegin call (No GL_QUADS)
  //       GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY
  // Hint:
  //       glBegin/glEnd  (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glBegin.xml)
  //       glColor        (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glColor.xml)
  //       glNormal       (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glNormal.xml)
  //       glVertex       (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glVertex.xml)
  // Note:
  //       You can copy-paste sample code above, but you must change its parameters to render correctly.

  // Blue, bottom
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(0.0f, 0.0f, 1.0f);
  glNormal3f(0.1f, 0.0f, 0.0f);

  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glEnd();
  // Red, right
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(1.0f, 0.0f, 0.0f);
  glNormal3f(0.0f, 0.0f, 1.0f);

  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glEnd();
  // Orange, left
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(1.0f, 0.5f, 0.0f);
  glNormal3f(0.0f, 0.0f, -1.0f);

  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glEnd();
  // Yellow, front
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(1.0f, 1.0f, 0.0f);
  glNormal3f(-1.0f, 0.0f, 0.0f);

  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glEnd();
  // White, back
  glBegin(GL_TRIANGLE_STRIP);
  glColor3f(1.0f, 1.0f, 1.0f);
  glNormal3f(0.0f, -1.0f, 0.0f);

  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glEnd();
}

void Cube::rotate(Axis axis) { rotation_direction = static_cast<int>(axis); }
}  // namespace graphics::shape
