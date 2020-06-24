#include "game/systems/pick_up_coin_system.h"

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

auto GivePrice(Entity* entity) {
  auto cc = entity->Get<ColliderComponent>();
  for (auto& collision : cc->GetCollisions()) {
    if (collision->Get<PriceComponent>()) {
      auto a = collision->Get<PriceComponent>();
      collision->Add<StampRemoveComponent>();
      return a;
    }
  }
}

void PickUpCoinSystem::AddCoin(Entity* entity_1, Entity* entity_2) {
  auto pc = GivePrice(entity_1);
  auto sb = entity_2->Get<ScoreBoardComponent>();
  int x = entity_1->Get<TransformComponent>()->pos_.x;
  int y = entity_1->Get<TransformComponent>()->pos_.y;
  if (ctx_->levels_.count(ctx_->level_number) != 0) {
    std::cout << ctx_->levels_.find(ctx_->level_number)->second[x + y * 72] << std::endl;
    ctx_->levels_.find(ctx_->level_number)->second[x + y * 72] = 0;
    std::cout << "coin change " << ctx_->scene_ << std::endl;
  }
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
