#pragma once
#include <lib/ecs/component.h>

class ScoreBoardComponent : public IComponent {
 public:
  int score_;

  explicit ScoreBoardComponent(int score) : score_(score) {}
};
