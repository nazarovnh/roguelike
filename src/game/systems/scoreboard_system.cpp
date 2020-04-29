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

bool ScoreBoardSystem::Filter(const Entity& entity) const {
  return entity.Contains<ColliderComponent>();
}

static bool IsCoin(Entity* entity) {
  auto cc = entity->Get<ColliderComponent>();
  for (const auto& collision : cc->GetCollisions()) {
    if (collision->Get<TextureComponent>()->symbol_ == '$') {
      return true;
    }
  }
}

void ScoreBoardSystem::AddCoin() {}

void ScoreBoardSystem::OnUpdate() {
  //  for (auto& entity : GetEntityManager()) {
  //    if (Filter(entity) && IsCoin(&entity)) {
  //      AddCoin();
  //    }
  //  }
}
ScoreBoardSystem::ScoreBoardSystem(EntityManager* entity_manager, SystemManager* system_manager)
    : ISystem(entity_manager, system_manager) {}
