#pragma once

class Controls {
  int step_x = 0;
  bool is_jump_ = false;
  bool is_exit_ = false;
  bool step_right_ = false;
  bool step_left_ = false;
  bool is_submit_ = false;

 public:
  bool IsJump() const;

  bool IsExit() const;

  bool StepRight() const;

  bool StepLeft() const;

  bool IsSubmit() const;

  void Update();
};
