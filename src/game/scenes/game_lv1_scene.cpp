#include "game/scenes/game_lv1_scene.h"

#include <game/components/collider_component.h>
#include <game/components/movement_component.h>
#include <game/components/obstacle_component.h>
#include <game/components/player_control_component.h>
#include <game/components/scoreboard_component.h>
#include <game/systems/collision_system.h>
#include <game/systems/creating_entity_system.h>
#include <game/systems/game_over_system.h>
#include <game/systems/level_up_system.h>
#include <game/systems/pick_up_coin_system.h>
#include <game/systems/reading_file_levels_system.h>
#include <game/systems/steps_count_system.h>

#include "game/components/texture_component.h"
#include "game/components/transform_component.h"
#include "game/systems/movement_system.h"
#include "game/systems/obstacles_control_system.h"
#include "game/systems/rendering_system.h"
#include "lib/math/vec2.h"

/**
 * На каждую игровую сцену приходится свой набор сущностей и систем
 * Так, например, здесь у нас есть сущности игрока, кактусов и земли,
 * у каждой сущнности есть свой набор компонентов
 * (обратите внимание, что и аргументы у каждого соответствующие)
 *
 * После инициализации всех сущностей (а они хранятся в движке ECS),
 * происходит инициализация всех необходимых систем. Как и сущности,
 * они хранятся в движке ECS. Благодаря этому, при вызове OnUpdate()
 * у сцены достаточно вызвать только обновление движка ECS
 *
 * После того, как сцена заканчивает свою работу, содержимое движка ECS
 * очищается, чтобы другая сцена могла заполнить его своими компонентам
 * и системами
 */
void GameSceneLv1::OnCreate() {
  auto sys = engine.GetSystemManager();
  sys->AddSystem<CreatingEntitySystem>(engine.GetEntityManager());
  sys->AddSystem<RenderingSystem>();
  sys->AddSystem<MovementSystem>(controls);
  sys->AddSystem<StepsCountSystem>(controls, ctx_);
  sys->AddSystem<ObstaclesControlSystem>(width_);
  sys->AddSystem<CollisionSystem>();
  sys->AddSystem<PickUpCoinSystem>(controls, ctx_);
  sys->AddSystem<LevelUpSystem>(ctx_);
  sys->AddSystem<GameOverSystem>(ctx_);
  sys->AddSystem<ReadingFileLevelsSystem>(engine.GetSystemManager()->GetSystem<CreatingEntitySystem>());

  //  auto levell = engine.GetSystemManager() auto a = levell->Get<ReadingFileLevelsSystem>();
  //  if (level[0][0] = '#') {
  //    auto wall = engine.GetEntityManager()->CreateEntity();
  //    wall->Add<TransformComponent>(Vec2(12, 5));
  //    wall->Add<TextureComponent>('#');
  //    wall->Add<ObstacleComponent>();
  //    wall->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  //  }

  //  {
  //    auto player = engine.GetEntityManager()->CreateEntity();
  //    player->Add<TransformComponent>(Vec2(10, 1));
  //    player->Add<TextureComponent>('@');
  //    player->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  //    player->Add<PlayerControlComponent>(TK_LEFT, TK_RIGHT, TK_UP, TK_DOWN);
  //    player->Add<MovementComponent>(Vec2(1, 1));
  //  }
  //
  //  {
  //    auto wall = engine.GetEntityManager()->CreateEntity();
  //    wall->Add<TransformComponent>(Vec2(12, 5));
  //    wall->Add<TextureComponent>('#');
  //    wall->Add<ObstacleComponent>();
  //    wall->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  //  }
  //
  //  {
  //    auto wall = engine.GetEntityManager()->CreateEntity();
  //    wall->Add<TransformComponent>(Vec2(10, 5));
  //    wall->Add<TextureComponent>('#');
  //    wall->Add<ObstacleComponent>();
  //    wall->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  //  }
  //
  //
  //  {
  //    auto coin = engine.GetEntityManager()->CreateEntity();
  //    coin->Add<TransformComponent>(Vec2(14, 5));
  //    coin->Add<TextureComponent>('$');
  //    coin->Add<ObstacleComponent>();
  //    coin->Add<PriceComponent>();
  //    coin->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  //  }
  //
  //  {
  //    auto coin = engine.GetEntityManager()->CreateEntity();
  //    coin->Add<TransformComponent>(Vec2(14, 7));
  //    coin->Add<TextureComponent>('$');
  //    coin->Add<ObstacleComponent>();
  //    coin->Add<PriceComponent>();
  //    coin->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  //  }
  //
  //  {
  //    auto coin = engine.GetEntityManager()->CreateEntity();
  //    coin->Add<TransformComponent>(Vec2(14, 9));
  //    coin->Add<TextureComponent>('$');
  //    coin->Add<ObstacleComponent>();
  //    coin->Add<PriceComponent>();
  //    coin->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  //  }
  //
  //  {
  //    auto door = engine.GetEntityManager()->CreateEntity();
  //    door->Add<TransformComponent>(Vec2(79, 24));
  //    door->Add<TextureComponent>('>');
  //    door->Add<ObstacleComponent>();
  //    door->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  //  }
  //
  //  auto scoreboard_coins = engine.GetEntityManager()->CreateEntity();
  //  scoreboard_coins->Add<TransformComponent>(Vec2(73, 2));
  //  scoreboard_coins->Add<TextureComponent>('$');
  //  scoreboard_coins->Add<ScoreBoardComponent>();
  //  scoreboard_coins->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  //
}
void GameSceneLv1::OnRender() {
  engine.OnUpdate();
  engine.GetEntityManager()->Check();
}
void GameSceneLv1::OnExit() {
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}
GameSceneLv1::GameSceneLv1(Context* const ctx, const Controls& controls) : IScene(ctx), controls(controls) {}
