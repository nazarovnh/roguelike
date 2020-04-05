#pragma once
#include <lib/ecs/component.h>
#include <lib/math/vec2.h>

class MovementComponent : public IComponent {
 public:
  float step_;

  explicit MovementComponent(float step) : step_(step) {}
};
