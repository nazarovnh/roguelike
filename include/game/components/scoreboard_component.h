#pragma once
#include <lib/ecs/component.h>
#include <lib/scenes/context.h>
class ScoreBoardComponent : public IComponent {
 public:
  Context* ctx_;
  int score_steps_;
  int score_coins_;
  explicit ScoreBoardComponent(Context* ctx) : ctx_(ctx) {
    score_steps_ = ctx_->score_steps;
    score_coins_ = ctx_->score_coins;
  }
};
