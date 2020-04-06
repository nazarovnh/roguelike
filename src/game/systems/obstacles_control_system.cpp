#include "game/systems/obstacles_control_system.h"

#include "game/components/obstacle_component.h"
#include "game/components/transform_component.h"
#include "lib/ecs/entity_manager.h"

/**
 * Пример использования компонента как тэга - ObstaclesControlSystem
 * позволяет отфильтровать сущности по факту наличия возможности столкновения
 */
bool ObstaclesControlSystem::Filter(const Entity& entity) const {
    return entity.Contains<ObstaclesControlSystem>() && entity.Contains<TransformComponent>();
}
void ObstaclesControlSystem::OnEachEntity(Entity* entity) const {
    auto tc = entity->Get<TransformComponent>();

    if (tc->pos_.x < 0) {
        tc->pos_.x = starting_point_;
    }
}
void ObstaclesControlSystem::OnUpdate() {
    for (auto& entity : GetEntityManager()) {
        if (Filter(entity)) {
            OnEachEntity(&entity);
        }
    }
}
ObstaclesControlSystem::ObstaclesControlSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                               float starting_point)
        : ISystem(entity_manager, system_manager), starting_point_(starting_point) {}
