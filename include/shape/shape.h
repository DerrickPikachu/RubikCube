#pragma once

#include "utils.h"

namespace graphics::shape {

enum class Axis { X = 0, Y = 1, Z = 2 };
class Shape {
 public:
  virtual ~Shape() = default;
  virtual void setupModel() noexcept = 0;
  virtual void draw() const noexcept = 0;
  CONSTEXPR_VIRTUAL virtual const char* getTypeName() const noexcept = 0;
};
}  // namespace graphics::shape
