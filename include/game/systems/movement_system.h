#pragma once

#include <game/controls.h>
#include <lib/ecs/system.h>

class Entity;

class MovementSystem : public ISystem {
  const Controls& controls_;
  void OnUpdateEntity(Entity* entity) const;

 protected:
  void OnUpdate() override;

 public:
  MovementSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls);
};
