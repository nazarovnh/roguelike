#pragma once
#include "lib/context.h"
#include "lib/i_scene.h"

class Controls {
  bool is_exit_ = false;
  bool step_right_ = false;
  bool step_left_ = false;
  bool step_up_ = false;
  bool step_down_ = false;
  bool is_submit_ = false;

 public:
  int step_x = 0;

  bool IsExit() const;

  bool StepRight() const;

  bool StepLeft() const;

  bool StepUp() const;

  bool StepDown() const;

  bool IsSubmit() const;

  void Update();
};
