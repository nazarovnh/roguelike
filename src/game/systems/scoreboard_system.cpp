#include "game/systems/scoreboard_system.h"
#include <game/components/transform_component.h>
#include "lib/ecs/entity_manager.h"


ScoreBoardSystem::ScoreBoardSystem(EntityManager* entity_manager, SystemManager* system_manager)
    : ISystem(entity_manager, system_manager) {}

bool ScoreBoardSystem::Filter(const Entity& entity) const {
  return entity.Contains<ScoreBoardSystem()>() && entity.Contains<TransformComponent>();
}

void ScoreBoardSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (!Filter(entity)) {
      // TODO(Nariman): Does the system need? Yes - expeption. No - delete cpp
      // exit(-1);
    }
  }
}
