#pragma once

#include <lib/ecs/engine.h>
#include <lib/ecs/system.h>

#include <string>

#include "game/systems/creating_entity_system.h"
#include "vector"
class ReadingFileLevelsSystem : public ISystem {
  CreatingEntitySystem *creatingEntitySystem_;

 protected:
  void OnUpdate() override;

  void ReadFile();

 public:
  std::string s;
  static std::vector<std::vector<char>> levelfile;
  static std::vector<std::vector<char>> GetLevel();

  ReadingFileLevelsSystem(EntityManager *entityManager, SystemManager *systemManager,
                          CreatingEntitySystem *creatingEntitySystem)
      : ISystem(entityManager, systemManager), creatingEntitySystem_(creatingEntitySystem) {}
};
