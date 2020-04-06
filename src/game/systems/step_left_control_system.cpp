#include "game/systems/step_left_control_system.h"

#include <game/components/movement_component.h>
#include <game/components/player_control_component.h>
#include <game/components/transform_component.h>

#include "game/components/step_left_component.h"
#include "iostream"
#include "lib/ecs/entity_manager.h"
static bool Filter(const Entity& entity) {
  return entity.Contains<StepLeftComponent>() && entity.Contains<PlayerControlComponent>() &&
         entity.Contains<TransformComponent>();
}

void StepLeftControlSystem::OnUpdateEntity(Entity* entity) const {
  auto pcc = entity->Get<PlayerControlComponent>();
  auto tc = entity->Get<TransformComponent>();


  if (controls_.IsPressed(pcc->left_button_)) {
      //  tc->pos_ = tc->pos_ + tc->pos_
      tc->pos_.x -= 1;
  }
}
void StepLeftControlSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity)) {
      OnUpdateEntity(&entity);
    }
  }
}
StepLeftControlSystem::StepLeftControlSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                             const Controls& controls)
    : ISystem(entity_manager, system_manager), controls_(controls) {}
