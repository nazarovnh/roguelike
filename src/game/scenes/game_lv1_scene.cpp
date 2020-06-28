#include "game/scenes/game_lv1_scene.h"

#include <game/systems/collision_system.h>
#include <game/systems/creating_entity_system.h>
#include <game/systems/game_over_system.h>
#include <game/systems/generate_random_map_system.h>
#include <game/systems/level_up_system.h>
#include <game/systems/pick_up_coin_system.h>
#include <game/systems/reading_file_levels_system.h>
#include <game/systems/steps_count_system.h>

#include "game/systems/movement_system.h"
#include "game/systems/obstacles_control_system.h"
#include "game/systems/rendering_system.h"

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
  sys->AddSystem<CreatingEntitySystem>(ctx_, engine.GetEntityManager());
  sys->AddSystem<RenderingSystem>();
  sys->AddSystem<MovementSystem>(controls);
  sys->AddSystem<StepsCountSystem>(controls, ctx_);
  sys->AddSystem<ObstaclesControlSystem>();
  sys->AddSystem<CollisionSystem>();
  sys->AddSystem<PickUpCoinSystem>(controls, ctx_);
  sys->AddSystem<LevelUpSystem>(ctx_);
  sys->AddSystem<GameOverSystem>(ctx_);
  //  sys->AddSystem<ReadingFileLevelsSystem>(ctx_, engine.GetSystemManager()->Get<CreatingEntitySystem>());
  sys->AddSystem<GenerateRandomMapSystem>(ctx_, engine.GetSystemManager()->Get<CreatingEntitySystem>(), 72, 24);
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
