#pragma once
#include <lib/ecs/component.h>

class ScoreBoardComponent : public IComponent {
 public:
  int score_steps_;
  int score_coins_;

  explicit ScoreBoardComponent(int score_steps = 0, int score_coins = 0)
      : score_steps_(score_steps), score_coins_(score_coins) {}
};
