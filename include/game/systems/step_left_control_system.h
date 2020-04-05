#pragma once

#include "game/controls.h"
#include "lib/ecs/system.h"

class Entity;

class StepLeftControlSystem : public ISystem {
  const Controls& controls_;
  void OnUpdateEntity(Entity* entity) const;

 protected:
  void OnUpdate() override;

 public:
  StepLeftControlSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls);
};
