#include "game/systems/pick_up_coin.h"

#include <game/components/collider_component.h>
#include <game/components/player_control_component.h>
#include <game/components/price_component.h>
#include <game/components/scoreboard_component.h>
#include <game/components/stamp_remove_component.h>
#include <game/components/texture_component.h>
#include <lib/ecs/entity.h>
#include <lib/ecs/entity_manager.h>

static bool Filter(const Entity& entity) {
  return entity.Contains<ColliderComponent>() && entity.Contains<PlayerControlComponent>();
}

static bool Filter2(const Entity& entity) {
  return entity.Contains<ColliderComponent>() && entity.Contains<ScoreBoardComponent>();
}

// TODO(Nariman): Добавить у entity метод Have, чтобы проверит наличие компоненты, и изменить функцию IsCoin
bool PickUpCoinSystem::IsCoin(const Entity& entity) {
  auto cc = entity.Get<ColliderComponent>();
  for (const auto& collision : cc->GetCollisions()) {
    if (collision->Get<TextureComponent>()->symbol_ == '$') {
      return true;
    }
  }
}

// auto AddRemoveComponent(Entity* entity) {
//  auto cc = entity->Get<ColliderComponent>();
//  for (auto& collision : cc->GetCollisions()) {
//    if (collision->Get<PriceComponent>()) {
//      return collision;
//    }
//  }
//  }
// PriceComponent*
auto GivePrice(Entity* entity) {
  auto cc = entity->Get<ColliderComponent>();
  for (auto& collision : cc->GetCollisions()) {
    if (collision->Get<PriceComponent>()) {
      auto a = collision->Get<PriceComponent>();
      collision->Add<StampRemoveComponent>();
      (*collision).Add<StampRemoveComponent>();
      //  delete collision;
      return a;
    }
  }
}

void PickUpCoinSystem::AddCoin(Entity* entity_1, Entity* entity_2) {
  auto pc = GivePrice(entity_1);
  auto sb = entity_2->Get<ScoreBoardComponent>();
  sb->score_coins_ += pc->price_;
}

void PickUpCoinSystem::OnUpdate() {
  for (auto& entity_1 : GetEntityManager()) {
    if (Filter(entity_1) && IsCoin(entity_1)) {
      for (auto& entity_2 : GetEntityManager()) {
        if (Filter2(entity_2)) {
          AddCoin(&entity_1, &entity_2);
          //          for (auto& entity_3 : GetEntityManager()) {
          //            if (entity_3.Get<TextureComponent>()->symbol_ == '$') {
          //              entity_3.Add<StampRemoveComponent>();
          //            }
          //          }
        }
      }
    }
  }
}
