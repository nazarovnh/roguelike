#pragma once

#include <lib/ecs/system.h>
#include <lib/scenes/context.h>
class LevelUpSystem : public ISystem {
 private:
  Context* ctx_;

  void LevelUp();
  void LevelDown();

 protected:
  void OnUpdate() override;

 public:
  LevelUpSystem(EntityManager* const entity_manager, SystemManager* const system_manager, Context* ctx)
      : ISystem(entity_manager, system_manager), ctx_(ctx) {}
};
