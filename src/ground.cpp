//
// Created by nariman on 20.02.20.
//
#include "game/ground.h"

#include <BearLibTerminal.h>

void Ground::Update() {
  for (int i = 0; i < width_; i++) {
    terminal_put(i, y_ + 1, '^');
  }
}
