//
// Created by nariman on 29.04.2020.
//

#pragma once

#include <lib/ecs/entity.h>
#include <lib/ecs/system.h>
class StepsCountSystem : public ISystem{
 public:
  StepsCountSystem(EntityManager *entityManager, SystemManager *systemManager);

  void AddStep(Entity* entity);
};
