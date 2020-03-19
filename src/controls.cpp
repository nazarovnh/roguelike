#include <BearLibTerminal.h>
#include <game/controls.h>

void Controls::Update() {
  is_exit_ = false;
  step_right_ = false;
  step_left_ = false;
  step_up_ = false;
  step_down_ = false;

  while (terminal_has_input()) {
    auto key = terminal_read();
    if (key == TK_CLOSE) {
      is_exit_ = true;
    }
    if (key == TK_ENTER) {
      is_submit_ = true;
    }
    if (key == TK_LEFT) {
      step_left_ = true;
      step_x += 1;
    }
    if (key == TK_RIGHT) {
      step_right_ = true;
      step_x += 1;
    }
    if (key == TK_UP) {
      step_up_ = true;
      step_x += 1;
    }
    if (key == TK_DOWN) {
      step_down_ = true;
      step_x += 1;
    }
  }
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
bool Controls::StepUp() const {
  return step_up_;
}
bool Controls::StepDown() const {
  return step_down_;
}
