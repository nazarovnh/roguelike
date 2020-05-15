#pragma once
#include <lib/ecs/component.h>

class ScoreBoardComponent : public IComponent {
 public:
  int score_steps_ = 0;
  int score_coins_ = 0;
};
