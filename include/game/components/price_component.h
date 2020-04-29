#pragma once
#include <lib/ecs/component.h>

class PriceComponent : public IComponent {
 public:
  explicit PriceComponent(int price = 1) : price_(price) {}
  int price_;
};
