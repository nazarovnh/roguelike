#include "game/systems/creating_entity_system.h"

#include <game/components/collider_component.h>
#include <game/components/obstacle_component.h>
#include <game/components/texture_component.h>
#include <game/components/transform_component.h>

void CreatingEntitySystem::CreatingEntity(char symbol, int i, int j) {
  if (symbol == '#') {
    auto wall = creater_->CreateEntity();
    wall->Add<TransformComponent>(Vec2(i, j));
    wall->Add<TextureComponent>('#');
    wall->Add<ObstacleComponent>();
    wall->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  }
}

void CreatingEntitySystem::OnUpdate() {}

CreatingEntitySystem::CreatingEntitySystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                           EntityManager* creater)
    : ISystem(entity_manager, system_manager), creater_(creater) {}

// CreatingEntitySystem::CreatingEntitySystem(EntityManager* entityManager, SystemManager* systemManager,
//                                           EntityManager* const pManager, SystemManager* pManager1,
//                                           EntityManager* pManager2, Context* const pContext)
//    : ISystem(entityManager, systemManager) {}
// CreatingEntitySystem::CreatingEntitySystem(EntityManager* const pManager, SystemManager* pManager1,
//                                           EntityManager* pManager2, Context* const pContext,
//                                           SystemManager* systemManager) {}
