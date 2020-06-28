#include "game/systems/pick_up_coin_system.h"

#include <game/components/collider_component.h>
#include <game/components/player_control_component.h>
#include <game/components/price_component.h>
#include <game/components/scoreboard_component.h>
#include <game/components/stamp_remove_component.h>
#include <game/components/texture_component.h>
#include <game/systems/generate_random_map_system.h>
#include <game/systems/reading_file_levels_system.h>
#include <lib/ecs/entity.h>
#include <lib/ecs/entity_manager.h>

static bool Filter(const Entity& entity) {
  return entity.Contains<ColliderComponent>() && entity.Contains<PlayerControlComponent>();
}

static bool Filter2(const Entity& entity) {
  return entity.Contains<ColliderComponent>() && entity.Contains<ScoreBoardComponent>();
}

bool PickUpCoinSystem::IsCoin(const Entity& entity) {
  auto cc = entity.Get<ColliderComponent>();
  for (const auto& collision : cc->GetCollisions()) {
    if (collision->Get<TextureComponent>()->symbol_ == '$') {
      return true;
    }
  }
}
// TODO(Nariman) : хорошо ли что возращает auto по-другому нужно будет добавлять Template(template<typename Component> и
// возращать Component*
auto GetPrice(Entity* entity) {
  auto cc = entity->Get<ColliderComponent>();
  for (auto& collision : cc->GetCollisions()) {
    if (collision->Get<PriceComponent>()) {
      auto price_entity = collision->Get<PriceComponent>();
      collision->Add<StampRemoveComponent>();
      return price_entity;
    }
  }
}

void PickUpCoinSystem::AddCoin(Entity* entity_1, Entity* entity_2) {
  auto pc = GetPrice(entity_1);
  auto sb = entity_2->Get<ScoreBoardComponent>();
  ctx_->levels_.find(ctx_->level_number)
      ->second[entity_1->Get<TransformComponent>()->pos_.x +
               entity_1->Get<TransformComponent>()->pos_.y * ctx_->width_] = 1;
  sb->score_coins_ += pc->price_;
  ctx_->score_coins += pc->price_;
}

void PickUpCoinSystem::OnUpdate() {
  for (auto& entity_1 : GetEntityManager()) {
    if (Filter(entity_1) && IsCoin(entity_1)) {
      for (auto& entity_2 : GetEntityManager()) {
        if (Filter2(entity_2)) {
          AddCoin(&entity_1, &entity_2);
        }
      }
    }
  }
}
PickUpCoinSystem::PickUpCoinSystem(EntityManager* entity_manager, SystemManager* system_manager,
                                   const Controls& controls, Context* ctx)
    : ISystem(entity_manager, system_manager), controls_(controls), ctx_(ctx) {}
