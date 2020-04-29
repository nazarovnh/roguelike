//
// Created by nariman on 29.04.2020.
//

#include "game/systems/steps_count_system.h"

#include <game/components/scoreboard_component.h>
StepsCountSystem::StepsCountSystem(EntityManager *entityManager, SystemManager *systemManager)
    : ISystem(entityManager, systemManager) {}
void StepsCountSystem::AddStep(Entity *entity) {
  auto sc = entity->Get<ScoreBoardComponent>();
  sc->score_steps_++;
}
