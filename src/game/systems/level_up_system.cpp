#include "game/systems/level_up_system.h"

#include <game/components/collider_component.h>
#include <game/components/player_control_component.h>
#include <game/components/texture_component.h>
#include <lib/ecs/entity.h>
#include <lib/ecs/entity_manager.h>

void LevelUpSystem::LevelUp() {
  ctx_->scene_ = "result_scene";
}

static bool Filter(const Entity& entity) {
  return entity.Contains<ColliderComponent>() && entity.Contains<PlayerControlComponent>();
}

static bool IsLevelUp(const Entity& entity) {
  auto cc = entity.Get<ColliderComponent>();
  for (const auto& collision : cc->GetCollisions()) {
    if (collision->Get<TextureComponent>()->symbol_ == '>') {
      return true;
    }
  }

  return false;
}

void LevelUpSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity) && IsLevelUp(entity)) {
      LevelUp();
    }
  }
}
