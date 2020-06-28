#pragma once

#include <lib/ecs/entity.h>
#include <lib/ecs/system.h>

class ObstaclesControlSystem : public ISystem {
  float starting_point_{};

  bool Filter(const Entity& entity) const;

 public:
  ObstaclesControlSystem(EntityManager* entity_manager, SystemManager* system_manager);

 protected:
  void OnUpdate() override;
};
