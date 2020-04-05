#pragma once

#include <lib/ecs/system.h>
class CollisionSystem : public ISystem {
 public:
  CollisionSystem(EntityManager* entity_manager, SystemManager* system_manager);

 protected:
  void OnUpdate() override;
};
