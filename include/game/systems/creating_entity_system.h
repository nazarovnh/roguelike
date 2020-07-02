#pragma once
#include <lib/ecs/engine.h>
#include <lib/ecs/system.h>
#include <lib/scenes/context.h>

#include "map"

class CreatingEntitySystem : public ISystem {
  EntityManager* creater_;
  Context* ctx_;
  bool used_counter_ = false;
  int x_next_door = -1;
  int y_next_door = -1;
  int x_prev_door = -1;
  int y_prev_door = -1;
  int count_player_ = 0;
  //  std::map<char, void*> m = {{'#', CreateWall(0, 0)}};

 protected:
  void OnUpdate() override;

 public:
  CreatingEntitySystem(EntityManager* entity_manager, SystemManager* const system_manager, Context* ctx,
                       EntityManager* creater);

  void CreatingEntity(char symbol, int x, int y);

  void CreatePlayer(int x, int y);
  void CreateWall(int x, int y);
  void CreateCoin(int x, int y);
  void CreatePrevDoor(int x, int y);
  void CreateNextDoor(int x, int y);
  void CreateScoreBoard(int x, int y);
};
