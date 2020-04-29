#pragma once

#include <bits/unique_ptr.h>
#include <game/components/coin_component.h>
#include <game/components/price_component.h>
#include <game/components/scoreboard_component.h>
//  #include <lib/ecs/component.h>
#include <lib/ecs/system.h>

#include <map>

class TextureComponent;
class IComponent;

class CollisionSystem : public ISystem {
  //  std::map<IComponent&, void (*)()> action = {PriceComponent, ScoreBoardComponent.AddCoin()};
  //  std::map<IComponent*, void (*)()> action = {&TextureComponent, ScoreBoardComponent().AddCoin()};

 public:
  CollisionSystem(EntityManager* entity_manager, SystemManager* system_manager);

 protected:
  void OnUpdate() override;
};
