#pragma once

#include <game/components/scoreboard_component.h>
#include <lib/ecs/entity.h>
#include <lib/ecs/system.h>

class ScoreBoardSystem : public ISystem {
  ScoreBoardComponent* scoreboardcomponent_;
  bool Filter(const Entity& entity) const;

 public:
  ScoreBoardSystem(EntityManager* entity_manager, SystemManager* system_manager,
                   ScoreBoardComponent* scoreboardcomponent);

  void AddCoin();

 protected:
  void OnUpdate() override;
};
