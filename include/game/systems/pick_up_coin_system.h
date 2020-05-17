#pragma once

#include <game/controls.h>
#include <lib/ecs/entity.h>
#include <lib/ecs/system.h>
#include <lib/scenes/context.h>

class PickUpCoinSystem : public ISystem {
  const Controls& controls_;
  Context* ctx_;

 public:
  PickUpCoinSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls,
                   Context* ctx);

 protected:
  void AddCoin(Entity* entity_1, Entity* entity_2);
  bool IsCoin(const Entity& entity);
  void OnUpdate() override;
};
