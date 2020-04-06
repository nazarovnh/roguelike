#include "game/systems/game_over_system.h"

#include <game/components/collider_component.h>
#include <game/components/obstacle_control_system.h>
#include <game/components/player_control_component.h>
#include <lib/ecs/entity.h>
#include <lib/ecs/entity_manager.h>

static bool Filter(const Entity& entity) {
  return entity.Contains<ColliderComponent>() && entity.Contains<PlayerControlComponent>();
}

static bool IsGameOver(const Entity& entity) {
  auto cc = entity.Get<ColliderComponent>();

  for (const auto& collision : cc->GetCollisions()) {
    if (collision->Contains<ObstaclesControlSystem>()) {
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
      std::cout << "BUM" << std::endl;
      GameOver();
    }
  }
}
