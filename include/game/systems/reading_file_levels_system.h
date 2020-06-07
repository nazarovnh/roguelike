#pragma once

#include <lib/ecs/engine.h>
#include <lib/ecs/system.h>

#include <string>

#include "game/systems/creating_entity_system.h"
#include "map"
#include "vector"
class ReadingFileLevelsSystem : public ISystem {
  CreatingEntitySystem *creatingEntitySystem_;
  Context *ctx_;
  std::map<std::string, std::string> path_file_ = {
      {"game_lv1", "levels/level_1"}, {"game_lv2", "levels/level_2"}, {"game_lv3", "levels/level_3"}};

 protected:
  void OnUpdate() override;

  void OnPostUpdate() override;

 public:
  std::string s;

  ReadingFileLevelsSystem(EntityManager *entityManager, SystemManager *systemManager, Context *ctx,
                          CreatingEntitySystem *creatingEntitySystem)
      : ISystem(entityManager, systemManager), ctx_(ctx), creatingEntitySystem_(creatingEntitySystem) {}
};
