#include "game/systems/level_up_system.h"

#include <game/components/collider_component.h>
#include <game/components/player_control_component.h>
#include <game/components/texture_component.h>
#include <lib/ecs/entity.h>
#include <lib/ecs/entity_manager.h>

void LevelUpSystem::LevelUp() {
  if (ctx_->scene_ == "game_lv1") {
    ctx_->prev_scene_ = "game_lv1";
    ctx_->scene_ = "result_scene";
  } else if (ctx_->scene_ == "game_lv2") {
    ctx_->prev_scene_ = "game_lv2";
    ctx_->scene_ = "result_scene";
  } else if (ctx_->scene_ == "game_lv3") {
    ctx_->prev_scene_ = "game_lv3";
    ctx_->scene_ = "game_over";
  }
}

void LevelUpSystem::LevelDown() {
  if (ctx_->scene_ == "game_lv2") {
    ctx_->scene_ = "game_lv1";
    ctx_->prev_scene_ = "game_lv2";
  } else if (ctx_->scene_ == "game_lv3") {
    ctx_->scene_ = "game_lv2";
    ctx_->prev_scene_ = "game_lv3";
    std::cout << "ctx_->scene_" << ctx_->scene_ << std::endl;
  }
  ctx_->level_number--;
}

static bool Filter(const Entity& entity) {
  return entity.Contains<ColliderComponent>() && entity.Contains<PlayerControlComponent>();
}

// TODO(Nariman) : оптимизировать перебор ColliderComponent + сравнивать не с элементом а добавить component
static bool IsLevelUp(const Entity& entity) {
  auto cc = entity.Get<ColliderComponent>();
  for (const auto& collision : cc->GetCollisions()) {
    if (collision->Contains<TextureComponent>()) {
      if (collision->Get<TextureComponent>()->symbol_ == '>') {
        return true;
      }
    }
  }
  return false;
}

// TODO(Nariman) : оптимизировать перебор ColliderComponent + сравнивать не с элементом а добавить component
static bool IsLevelDown(const Entity& entity) {
  auto cc = entity.Get<ColliderComponent>();
  for (const auto& collision : cc->GetCollisions()) {
    if (collision->Contains<TextureComponent>()) {
      if (collision->Get<TextureComponent>()->symbol_ == '<') {
        return true;
      }
    }
  }
  return false;
}
void LevelUpSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity) && IsLevelUp(entity)) {
      LevelUp();
    } else if (Filter(entity) && IsLevelDown(entity)) {
      LevelDown();
    }
  }
}
