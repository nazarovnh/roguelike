#include <BearLibTerminal.h>
#include <game/controls.h>

void Controls::Update() {
  is_jump_ = false;
  is_exit_ = false;
  step_right_ = false;
  step_left_ = false;

  while (terminal_has_input()) {
    auto key = terminal_read();
    if (key == TK_SPACE) {
      is_jump_ = true;
      step_x += 1;
    }
    if (key == TK_CLOSE) {
      is_exit_ = true;
    }
    if (key == TK_ENTER) {
      is_submit_ = true;
    }
    if (key == TK_LEFT) {
      step_left_ = true;
    }
    if (key == TK_RIGHT) {
      step_right_ = true;
      step_x += 1;
    }
  }
}

bool Controls::IsJump() const {
  return is_jump_;
}

bool Controls::IsExit() const {
  return is_exit_;
}

bool Controls::StepRight() const {
  return step_right_;
}

bool Controls::StepLeft() const {
  return step_left_;
}

bool Controls::IsSubmit() const {
  return is_submit_;
}
