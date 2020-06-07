#include "game/systems/collision_system.h"

#include <game/components/collider_component.h>
#include <game/components/texture_component.h>
#include <game/components/transform_component.h>
#include <lib/ecs/entity.h>
#include <lib/ecs/entity_manager.h>
#include <lib/math/math-utils.h>

CollisionSystem::CollisionSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}

static bool Filter(const Entity& entity) {
  return entity.Contains<ColliderComponent>() && entity.Contains<TransformComponent>();
}

static bool CollisionWall(const Entity* entity) {
  return entity->Get<TextureComponent>()->symbol_ == '#';
}

static bool CollisionCoin(const Entity* entity) {
  return entity->Contains<PriceComponent>();
}
static bool CollisionDoor(const Entity* entity) {
  return entity->Get<TextureComponent>()->symbol_ == '>' || entity->Get<TextureComponent>()->symbol_ == '<';
}

static void Collide(Entity* entity_1, Entity* entity_2) {
  if (entity_1->GetId() == entity_2->GetId()) {
    return;
  }

  auto cc2 = entity_2->Get<ColliderComponent>();
  auto tc1 = entity_1->Get<TransformComponent>();
  auto tc2 = entity_2->Get<TransformComponent>();
  if (ToPos(tc1->pos_.x) == ToPos(tc2->pos_.x) && ToPos(tc1->pos_.y) == ToPos(tc2->pos_.y)) {
    if (CollisionWall(entity_1)) {
      cc2->Collide(entity_1);
    } else if (CollisionDoor(entity_1)) {
      cc2->Collide(entity_1);
    } else if (CollisionCoin(entity_1)) {
      cc2->Collide(entity_1);
    }
  }
}

void CollisionSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (entity.Contains<ColliderComponent>()) {
      entity.Get<ColliderComponent>()->Clear();
    }
  }

  for (auto& entity_1 : GetEntityManager()) {
    if (Filter(entity_1)) {
      for (auto& entity_2 : GetEntityManager()) {
        if (Filter(entity_2)) {
          Collide(&entity_1, &entity_2);
        }
      }
    }
  }
}
