#pragma once
#include "lib/ecs/component.h"

class StepLeftComponent : public IComponent {
 public:
  float step_left_;

  explicit StepLeftComponent(float step_left) : step_left_(step_left) {}
};
