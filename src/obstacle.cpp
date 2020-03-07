#include <BearLibTerminal.h>
#include <game/obstacle.h>

int ToPos(float x);

void Obstacle::Update() {
  terminal_put(ToPos(x_), ToPos(y_), symbol_);
}
