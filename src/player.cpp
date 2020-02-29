//
// Created by nariman on 20.02.20.
//

#include <BearLibTerminal.h>
#include <game/player.h>

#include "game/math-utils.h"

void Player::Move() {
  if (controls.IsJump() && !IsFlying()) {
    speed_y = max_speed_y_;
  }
  if (controls.StepRight() && !IsFlying()) {
    x_ -= 1;
  }
  if (controls.StepLeft() && !IsFlying()) {
    x_ += 1;
  }
  if (y_ >= ground_y_) {
    y_ = ground_y_;
  }
  if (y_ <= ground_y_ - max_jump_height_) {
    speed_y = 0;
  }

  y_ -= speed_y;
  y_ += gravity_;
}

void Player::Render() {
  terminal_put(x_, to_pos(y_), symbol);
}

bool Player::IsFlying() const {
  return y_ < ground_y_;
}

void Player::Update() {
  Move();
  Render();
}

int Player::GetX() const {
  return to_pos(x_);
}

int Player::GetY() const {
  return to_pos(y_);
}
