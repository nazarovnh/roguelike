#pragma once

#include <lib/ecs/entity.h>
#include <lib/ecs/system.h>

class PickUpCoinSystem : public ISystem {
 public:
  PickUpCoinSystem(EntityManager *entityManager, SystemManager *systemManager)
      : ISystem(entityManager, systemManager) {}

  static void AddCoin(Entity *entity_1, Entity *entity_2);

  bool IsCoin(const Entity &entity);


 protected:
  void OnUpdate() override;
};
