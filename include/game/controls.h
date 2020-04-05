#pragma once

#include <BearLibTerminal.h>

#include <map>
#include <vector>
class Controls {
  std::map<int, bool> is_pressed_{};

 public:
  void Press(int btn_key) {
    is_pressed_[btn_key] = true;
  }
  bool IsPressed(int btn_key) const {
    if (is_pressed_.count(btn_key) == 0) {
      return false;
    }
    return is_pressed_.at(btn_key);
  }
  void Reset() {
    for (auto& btn : is_pressed_) {
      btn.second = false;
    }
  }

  void OnUpdate() {
    while (terminal_has_input()) {
      auto key = terminal_read();
      is_pressed_[key] = true;
    }
  }
};

//  #include <BearLibTerminal.h>
//
//  #include <map>
//  #include <vector>
//
//  #include "lib/scenes/context.h"
//  #include "lib/scenes/i_scene.h"
//
// class Controls {
//  bool is_exit_ = false;
//  bool step_right_ = false;
//  bool step_left_ = false;
//  bool step_up_ = false;
//  bool step_down_ = false;
//  bool is_submit_ = false;
//
//  std::map<int, bool> is_pressed_{};
//
// public:
//  int step_x = 0;
//
//  bool IsExit() const;
//
//  bool StepRight() const;
//
//  bool StepLeft() const;
//
//  bool StepUp() const;
//
//  bool StepDown() const;
//
//  bool IsSubmit() const;
//
//  void Update();
//
//  void Press(int btn_key) {
//    is_pressed_[btn_key] = true;
//  }
//  bool IsPressed(int btn_key) const {
//    if (is_pressed_.count(btn_key) == 0) {
//      return false;
//    }
//    return is_pressed_.at(btn_key);
//  }
//  void Reset() {
//    for (auto& btn : is_pressed_) {
//      btn.second = false;
//    }
//  }
//
//  void OnUpdate() {
//    while (terminal_has_input()) {
//      auto key = terminal_read();
//      is_pressed_[key] = true;
//    }
//  }
//  };
