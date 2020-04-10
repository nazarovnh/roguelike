#include "game/systems/movement_system.h"

#include <game/components/player_control_component.h>
#include <game/components/scoreboard_component.h>

#include "game/components/movement_component.h"
#include "game/components/transform_component.h"
#include "lib/ecs/entity_manager.h"

static bool Filter(const Entity& entity) {
  return entity.Contains<MovementComponent>() && entity.Contains<PlayerControlComponent>() &&
         entity.Contains<TransformComponent>();
}

void MovementSystem::OnUpdateEntity(Entity* entity) const {
  auto pcc = entity->Get<PlayerControlComponent>();
  auto tc = entity->Get<TransformComponent>();
  auto mc = entity->Get<MovementComponent>();
  //  auto sc = entity->Get<ScoreBoardComponent>(); Не компонента а сущность

  // TODO(Nariman): нормально ли то что movement знает о scoreboard и постоянная строчка sc->score ++
  if (controls_.IsPressed(pcc->left_button_)) {
    tc->pos_.x -= mc->step_.x;
    //  sc->score_++;
  } else if (controls_.IsPressed(pcc->right_button_)) {
    tc->pos_.x += mc->step_.x;
    //  sc->score_++;
  } else if (controls_.IsPressed(pcc->up_button_)) {
    tc->pos_.y -= mc->step_.y;
    //  sc->score_++;
  } else if (controls_.IsPressed(pcc->down_button_)) {
    tc->pos_.y += mc->step_.y;
    //  sc->score_++;
  }
}

void MovementSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (Filter(entity)) {
      // std::cout << "BUM" << std::endl;
      OnUpdateEntity(&entity);
    }
  }
}

MovementSystem::MovementSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                               const Controls& controls)
    : ISystem(entity_manager, system_manager), controls_(controls) {}
