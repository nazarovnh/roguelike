#include "game/systems/scoreboard_system.h"

#include <game/components/collider_component.h>
#include <game/components/movement_component.h>
#include <game/components/obstacle_component.h>
#include <game/components/player_control_component.h>
#include <game/components/scoreboard_component.h>
#include <game/components/texture_component.h>
#include <game/components/transform_component.h>

#include <iostream>

#include "lib/ecs/entity_manager.h"

ScoreBoardSystem::ScoreBoardSystem(EntityManager* entity_manager, SystemManager* system_manager,
                                   ScoreBoardComponent* scoreboardcomponent)
    : ISystem(entity_manager, system_manager), scoreboardcomponent_(scoreboardcomponent) {}

bool ScoreBoardSystem::Filter(const Entity& entity) const {
  return entity.Contains<ColliderComponent>();
}

static bool IsCoin(const Entity& entity) {
  auto cc = entity.Get<ColliderComponent>();
  // TODO(Nariman): Сложно уже пошли ошибки с проектирование!
  for (const auto& collision : cc->GetCollisions()) {
    if (collision->Get<TextureComponent>()->symbol_ == '$') {
      return true;
    }
  }
}

void ScoreBoardSystem::AddCoin() {
  scoreboardcomponent_->score_coins_++;
}

void ScoreBoardSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity) && IsCoin(entity)) {
      AddCoin();
    }
  }
}
