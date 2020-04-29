#pragma once

#include <game/components/scoreboard_component.h>
#include <lib/ecs/entity.h>
#include <lib/ecs/system.h>

class ScoreBoardSystem : public ISystem {
  bool Filter(const Entity& entity) const;

 public:
  ScoreBoardSystem(EntityManager* entity_manager, SystemManager* system_manager);

  void AddCoin();

 protected:
  void OnUpdate() override;
};
