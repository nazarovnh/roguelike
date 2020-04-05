#include "game/systems/game_over_system.h"

#include <lib/ecs/entity.h>
#include <lib/ecs/entity_manager.h>
#include <game/components/collider_component.h>
#include <game/components/obstacle_component.h>
#include <game/components/player_control_component.h>

static bool Filter(const Entity& entity) {
  return entity.Contains<ColliderComponent>() && entity.Contains<PlayerControlComponent>();
}

static bool IsGameOver(const Entity& entity) {
  auto cc = entity.Get<ColliderComponent>();

  for (const auto& collision : cc->GetCollisions()) {
    if (collision->Contains<ObstacleComponent>()) {
      return true;
    }
  }

  return false;
}

void GameOverSystem::GameOver() {
  ctx_->scene_ = "game_over";
}

void GameOverSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity) && IsGameOver(entity)) {
      GameOver();
    }
  }
}
