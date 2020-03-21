#include "game/coins.h"
#include <BearLibTerminal.h>

int ToPos(float x);

void Coins::Update() {
  terminal_put(ToPos(x_), ToPos(y_), sybmol_);
}
