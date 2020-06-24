#include "game/scenes/game_lv3_scene.h"

#include <game/scenes/game_lv2_scene.h>
#include <game/systems/collision_system.h>
#include <game/systems/game_over_system.h>
#include <game/systems/generate_random_map_system.h>
#include <game/systems/level_up_system.h>
#include <game/systems/pick_up_coin_system.h>
#include <game/systems/reading_file_levels_system.h>
#include <game/systems/steps_count_system.h>

#include "game/systems/movement_system.h"
#include "game/systems/obstacles_control_system.h"
#include "game/systems/rendering_system.h"
void GameSceneLv3::OnCreate() {
  auto sys = engine.GetSystemManager();
  sys->AddSystem<CreatingEntitySystem>(ctx_, engine.GetEntityManager());
  sys->AddSystem<RenderingSystem>();
  sys->AddSystem<MovementSystem>(controls);
  sys->AddSystem<StepsCountSystem>(controls, ctx_);
  sys->AddSystem<ObstaclesControlSystem>(width_);
  sys->AddSystem<CollisionSystem>();
  sys->AddSystem<PickUpCoinSystem>(controls, ctx_);
  sys->AddSystem<LevelUpSystem>(ctx_);
  sys->AddSystem<GameOverSystem>(ctx_);
  // sys->AddSystem<ReadingFileLevelsSystem>(ctx_, engine.GetSystemManager()->Get<CreatingEntitySystem>());
  sys->AddSystem<GenerateRandomMapSystem>(ctx_, engine.GetSystemManager()->Get<CreatingEntitySystem>(), 72, 24);
}

void GameSceneLv3::OnRender() {
  engine.OnUpdate();
  engine.GetEntityManager()->Check();
}
void GameSceneLv3::OnExit() {
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}
GameSceneLv3::GameSceneLv3(Context* const ctx, const Controls& controls) : IScene(ctx), controls(controls) {}
