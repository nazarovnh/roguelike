#pragma once
#include <lib/ecs/component.h>
#include <lib/math/vec2.h>

class MovementComponent : public IComponent {
 public:
  Vec2 step_;
  explicit MovementComponent(const Vec2& step) : step_(step) {}
};
