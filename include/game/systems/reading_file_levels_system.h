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
  std::vector<int> m_data;
  std::map<int, std::string> path_file_ = {{0, "levels/level_1"}, {1, "levels/level_2"}, {2, "levels/level_3"}};

 protected:
  void OnUpdate() override;

  void OnPostUpdate() override;

  void SizeFile();

 public:
  std::string s;

  ReadingFileLevelsSystem(EntityManager *entityManager, SystemManager *systemManager, Context *ctx,
                          CreatingEntitySystem *creatingEntitySystem)
      : ISystem(entityManager, systemManager), ctx_(ctx), creatingEntitySystem_(creatingEntitySystem) {}
};
