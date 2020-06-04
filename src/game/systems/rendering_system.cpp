#include "game/systems/rendering_system.h"

#include <BearLibTerminal.h>
#include <game/components/scoreboard_component.h>

#include "game/components/texture_component.h"
#include "game/components/transform_component.h"
#include "lib/ecs/entity_manager.h"
#include "lib/math/math-utils.h"

void RenderingSystem::OnUpdate() {
  for (auto& e : GetEntityManager()) {
    if (e.Contains<TransformComponent>() && e.Contains<TextureComponent>()) {
      if (e.Contains<ScoreBoardComponent>()) {
        auto scoreboard = e.Get<ScoreBoardComponent>();
        auto transform = e.Get<TransformComponent>();

        char str_1[20];
        char str_2[20];

        snprintf(str_1, sizeof(str_1), "%d", scoreboard->score_steps_);
        snprintf(str_2, sizeof(str_2), "%d", scoreboard->score_coins_);
        terminal_print(ToPos(transform->pos_.x + 2), ToPos(transform->pos_.y - 2), str_1);
        terminal_print(ToPos(transform->pos_.x + 2), ToPos(transform->pos_.y), str_2);
        terminal_put(ToPos(transform->pos_.x), ToPos(transform->pos_.y - 2), '@');
      }
      auto texture = e.Get<TextureComponent>();
      auto transform = e.Get<TransformComponent>();
      terminal_put(ToPos(transform->pos_.x), ToPos(transform->pos_.y), texture->symbol_);
    }
  }
}
void RenderingSystem::OnPreUpdate() {
  terminal_clear();
}
void RenderingSystem::OnPostUpdate() {
  terminal_refresh();
}
RenderingSystem::RenderingSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}
