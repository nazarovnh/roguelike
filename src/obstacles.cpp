//
// Created by nariman on 20.02.20.
//
#include <BearLibTerminal.h>
#include <obstacles.h>
#include "math-utils.h"

void Obstacles::Update() {
    terminal_put(to_pos(x), to_pos(y), sybmol);
}
