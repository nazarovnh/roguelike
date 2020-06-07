#pragma once
#include <lib/ecs/component.h>

class ScoreBoardComponent : public IComponent {
 public:
  int score_steps_;
  int score_coins_;
};
