
#include <lib/ecs/system.h>
#include <lib/ecs/entity.h>

class ObstaclesControlSystem : public ISystem {
    float starting_point_;

    bool Filter(const Entity& entity) const;
    void OnEachEntity(Entity* entity) const;

public:
    ObstaclesControlSystem(EntityManager* entity_manager, SystemManager* system_manager, float starting_point);

protected:
    void OnUpdate() override;
};

