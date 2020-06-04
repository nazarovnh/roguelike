#pragma once
#include <lib/ecs/engine.h>
#include <lib/ecs/system.h>
#include <lib/scenes/context.h>

class CreatingEntitySystem : public ISystem {
  EntityManager* creater_;
  //  const sizeMap = Map([ [ "#", "37-38" ] ]);

 protected:
  void OnUpdate() override;

 public:
  CreatingEntitySystem(EntityManager* entity_manager, SystemManager* const system_manager, EntityManager* creater);

  // TODO(Nariman) : name function

  //  CreatingEntitySystem(EntityManager* const entityManager, SystemManager* systemManager, EntityManager* pManager,
  //                       SystemManager* pManager1, EntityManager* pManager2, Context* const pContext);
  //  CreatingEntitySystem(EntityManager* const pManager, SystemManager* pManager1, EntityManager* pManager2,
  //                       Context* const pContext);
  void CreatingEntity(char symbol, int i, int j);
};
