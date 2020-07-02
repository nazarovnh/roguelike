#include "game/systems/steps_count_system.h"

#include <game/components/player_control_component.h>
#include <game/components/scoreboard_component.h>

#include "game/components/movement_component.h"
#include "game/systems/movement_system.h"
#include "lib/ecs/entity_manager.h"

static bool Filter(const Entity& entity) {
  return entity.Contains<MovementComponent>() && entity.Contains<PlayerControlComponent>();
}

static bool Filter_2(const Entity& entity) {
  return entity.Contains<ScoreBoardComponent>();
}

bool StepsCountSystem::InMoveEntity(Entity* entity) const {
  auto pcc = entity->Get<PlayerControlComponent>();

  return controls_.IsPressed(pcc->left_button_) || controls_.IsPressed(pcc->right_button_) ||
         controls_.IsPressed(pcc->up_button_) || controls_.IsPressed(pcc->down_button_);
}

void StepsCountSystem::AddStep(Entity* entity) {
  auto sc = entity->Get<ScoreBoardComponent>();
  sc->score_steps_++;
  ctx_->score_steps++;
}

void StepsCountSystem::OnUpdate() {
  for (auto& entity_1 : GetEntityManager()) {
    if (Filter(entity_1)) {
      if (InMoveEntity(&entity_1)) {
        for (auto& entity_2 : GetEntityManager()) {
          if (Filter_2(entity_2)) {
            AddStep(&entity_2);
          }
        }
      }
    }
  }
}
StepsCountSystem::StepsCountSystem(EntityManager* entity_manager, SystemManager* system_manager,
                                   const Controls& controls, Context* ctx)
    : ISystem(entity_manager, system_manager), controls_(controls), ctx_(ctx) {}
