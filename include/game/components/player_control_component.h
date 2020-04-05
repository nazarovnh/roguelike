#pragma once

#include <lib/ecs/component.h>

class PlayerControlComponent : public IComponent {
 public:
  int left_button_;

  explicit PlayerControlComponent(int left_button) : left_button_(left_button) {}
};
