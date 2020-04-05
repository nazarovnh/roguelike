#pragma once
#include <lib/ecs/component.h>
#include <lib/math/vec2.h>

class TransformComponent : public IComponent {
 public:
  Vec2 pos_;

  explicit TransformComponent(const Vec2& pos) : pos_(pos) {}
};
