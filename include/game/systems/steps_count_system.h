
#pragma once

#include <game/controls.h>
#include <lib/ecs/system.h>
#include <lib/scenes/context.h>

class Entity;

class StepsCountSystem : public ISystem {
  const Controls& controls_;
  bool InMoveEntity(Entity* entity) const;
  Context* ctx_;

 protected:
  void OnUpdate() override;
  void AddStep(Entity* entity);

 public:
  StepsCountSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls,
                   Context* ctx);
};
