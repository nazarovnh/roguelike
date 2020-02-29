//
// Created by nariman on 27.02.2020.
//
#include "game/coins.h"

#include <BearLibTerminal.h>

#include "game/math-utils.h"

void Coins::Update() {
  terminal_put(to_pos(x), to_pos(y), sybmol);
}
