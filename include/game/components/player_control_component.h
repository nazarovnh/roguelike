#pragma once

#include <lib/ecs/component.h>

class PlayerControlComponent : public IComponent {
 public:
  int left_button_;
  int right_button_;
  int up_button_;
  int down_button_;
  PlayerControlComponent(int leftButton, int rightButton, int upButton, int downButton)
      : left_button_(leftButton), right_button_(rightButton), up_button_(upButton), down_button_(downButton) {}
};
