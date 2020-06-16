#pragma once
#include <lib/ecs/engine.h>
#include <lib/ecs/system.h>

#include <algorithm>
#include <vector>

#include "game/systems/creating_entity_system.h"
#include "lib/math/math-utils.h"

class GenerateRandomMapSystem : public ISystem {
  CreatingEntitySystem *creatingEntitySystem_;
  unsigned int a = 20;
  unsigned int *b = &a;

 public:
  struct Room {
    int x, y, w, h;
    bool intersect(const Room &r) const;
  };

  struct Point {
    int x, y, cost;

    bool operator==(const Point &p) const {
      return x == p.x && y == p.y;
    }

    bool operator<(const Point &p) const {
      return cost > p.cost;
    }
  };

  int m_width, m_height;      // размеры карты
  std::vector<int> m_data;    // финальные данные карты
  std::vector<Room> m_rooms;  // комнаты

 public:
  GenerateRandomMapSystem(EntityManager *entityManager, SystemManager *systemManager,
                          CreatingEntitySystem *creatingEntitySystem, int width, int height)
      : ISystem(entityManager, systemManager),
        creatingEntitySystem_(creatingEntitySystem),
        m_width(width),
        m_height(height) {
    m_data.resize(width * height, 0);
  }

  void generate(int roomsCount);
  void generatePassage(const Point &start, const Point &finish);
  void generateWalls();
  void generateCoins();

 protected:
  void OnUpdate() override;
  void OnPostUpdate() override;
};
