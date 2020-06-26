#include "game/systems/creating_entity_system.h"

#include <BearLibTerminal.h>
#include <game/components/collider_component.h>
#include <game/components/movement_component.h>
#include <game/components/obstacle_component.h>
#include <game/components/scoreboard_component.h>
#include <game/components/texture_component.h>
#include <game/components/transform_component.h>
#include <game/systems/generate_random_map_system.h>
#include <game/systems/reading_file_levels_system.h>

void CreatingEntitySystem::CreatePlayer(int x, int y) {
  auto player = creater_->CreateEntity();
  if (GetSystemManagerPtr()->Have<ReadingFileLevelsSystem>()) {
    if (ctx_->prev_scene_ == "title") {
      player->Add<TransformComponent>(Vec2(2, 2));
    } else if (ctx_->scene_ < ctx_->prev_scene_ && ctx_->prev_scene_ != "result_scene") {
      player->Add<TransformComponent>(Vec2(x_next_door - 1, y_next_door));
    } else if (ctx_->prev_scene_ == "result_scene") {
      player->Add<TransformComponent>(Vec2(x_prev_door, y_prev_door + 1));
    }
  } else if (GetSystemManagerPtr()->Have<GenerateRandomMapSystem>()) {
    player->Add<TransformComponent>(Vec2(x, y));
  }
  player->Add<TextureComponent>('@');
  player->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  player->Add<PlayerControlComponent>(TK_LEFT, TK_RIGHT, TK_UP, TK_DOWN);
  player->Add<MovementComponent>(Vec2(1, 1));
}

void CreatingEntitySystem::CreateWall(int x, int y) {
  auto wall = creater_->CreateEntity();
  wall->Add<TransformComponent>(Vec2(x, y));
  wall->Add<TextureComponent>('#');
  wall->Add<ObstacleComponent>();
  wall->Add<ColliderComponent>(OnesVec2, ZeroVec2);
}
void CreatingEntitySystem::CreateCoin(int x, int y) {
  auto coin = creater_->CreateEntity();
  coin->Add<TransformComponent>(Vec2(x, y));
  coin->Add<TextureComponent>('$');
  coin->Add<ObstacleComponent>();
  coin->Add<PriceComponent>();
  coin->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  std::cout << "create "
            << "x " << x << " y " << y << std::endl;
}

void CreatingEntitySystem::CreatePrevDoor(int x, int y) {
  auto door = creater_->CreateEntity();
  door->Add<TransformComponent>(Vec2(x, y));
  door->Add<TextureComponent>('<');
  door->Add<ObstacleComponent>();
  door->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  x_prev_door = x;
  y_prev_door = y;
}

void CreatingEntitySystem::CreateNextDoor(int x, int y) {
  auto door = creater_->CreateEntity();
  door->Add<TransformComponent>(Vec2(x, y));
  door->Add<TextureComponent>('>');
  door->Add<ObstacleComponent>();
  door->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  x_next_door = x;
  y_next_door = y;
}
void CreatingEntitySystem::CreateScoreBoard(int x, int y) {
  auto scoreboard_coins = creater_->CreateEntity();
  scoreboard_coins->Add<TransformComponent>(Vec2(x, y));
  scoreboard_coins->Add<TextureComponent>('$');
  scoreboard_coins->Add<ScoreBoardComponent>(ctx_);
  scoreboard_coins->Add<ColliderComponent>(OnesVec2, ZeroVec2);
}

void CreatingEntitySystem::CreatingEntity(char symbol, int x, int y) {
  //    if (m.find(symbol) != m.end()){
  //      m.find(symbol)->second();
  //  }
  //    else{
  //      std::cout << "not found\n";
  //  }

  if (symbol == '#') {
    CreateWall(x, y);
  } else if (symbol == '@') {
    CreatePlayer(x, y);
  } else if (symbol == '$') {
    CreateCoin(x, y);
  } else if (symbol == '>') {
    CreateNextDoor(x, y);
  } else if (symbol == '<') {
    CreatePrevDoor(x, y);
    count_player_++;
  }
  // else if (count_player_ == 2) {
  //    std::cout << "x_prev_door " << x_prev_door << std::endl;
  //    std::cout << "y_prev_door " << y_prev_door << std::endl;
  //    std::cout << "x_next_door " << x_next_door << std::endl;
  //    std::cout << "y_next_door " << y_next_door << std::endl;
  //    CreatePlayer(x, y);
  //    count_player_++;
  //  }

  if (!used_counter_) {
    CreateScoreBoard(73, 2);
    used_counter_ = true;
  }
}
void CreatingEntitySystem::OnUpdate() {}
CreatingEntitySystem::CreatingEntitySystem(EntityManager* entity_manager, SystemManager* const system_manager,
                                           Context* ctx, EntityManager* creater)
    : ISystem(entity_manager, system_manager), ctx_(ctx), creater_(creater) {}

// CreatingEntitySystem::CreatingEntitySystem(EntityManager* entityManager, SystemManager* systemManager,
//                                           EntityManager* const pManager, SystemManager* pManager1,
//                                           EntityManager* pManager2, Context* const pContext)
//    : ISystem(entityManager, systemManager) {}
// CreatingEntitySystem::CreatingEntitySystem(EntityManager* const pManager, SystemManager* pManager1,
//                                           EntityManager* pManager2, Context* const pContext,
//                                           SystemManager* systemManager) {}
