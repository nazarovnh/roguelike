#include <game/components/collider_component.h>
#include <game/components/movement_component.h>
#include <game/components/obstacle_component.h>
#include <game/components/player_control_component.h>
#include <game/components/scoreboard_component.h>
#include <game/scenes/game_lv2_scene.h>
#include <game/systems/collision_system.h>
#include <game/systems/game_over_system.h>
#include <game/systems/level_up_system.h>
#include <game/systems/pick_up_coin_system.h>
#include <game/systems/steps_count_system.h>

#include "game/components/texture_component.h"
#include "game/components/transform_component.h"
#include "game/systems/movement_system.h"
#include "game/systems/obstacles_control_system.h"
#include "game/systems/rendering_system.h"
#include "lib/math/vec2.h"
void GameSceneLv2::OnCreate() {
  {
    auto player = engine.GetEntityManager()->CreateEntity();
    player->Add<TransformComponent>(Vec2(10, 1));
    player->Add<TextureComponent>('@');
    player->Add<ColliderComponent>(OnesVec2, ZeroVec2);
    player->Add<PlayerControlComponent>(TK_LEFT, TK_RIGHT, TK_UP, TK_DOWN);
    player->Add<MovementComponent>(Vec2(1, 1));
  }
  {
    auto sys = engine.GetSystemManager();
    sys->AddSystem<RenderingSystem>();
    sys->AddSystem<MovementSystem>(controls);
    sys->AddSystem<StepsCountSystem>(controls, ctx_);
    sys->AddSystem<ObstaclesControlSystem>(width_);
    sys->AddSystem<CollisionSystem>();
    sys->AddSystem<PickUpCoinSystem>(controls, ctx_);
    sys->AddSystem<LevelUpSystem>(ctx_);
    sys->AddSystem<GameOverSystem>(ctx_);
  }

  {
    auto scoreboard = engine.GetEntityManager()->CreateEntity();
    scoreboard->Add<TransformComponent>(Vec2(73, 2));
    scoreboard->Add<TextureComponent>('$');
    scoreboard->Add<ScoreBoardComponent>();
    scoreboard->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  }

  {
    auto door = engine.GetEntityManager()->CreateEntity();
    door->Add<TransformComponent>(Vec2(79, 24));
    door->Add<TextureComponent>('>');
    door->Add<ObstacleComponent>();
    door->Add<ColliderComponent>(OnesVec2, ZeroVec2);
  }
}

void GameSceneLv2::OnRender() {
  engine.OnUpdate();
  engine.GetEntityManager()->Check();
}
void GameSceneLv2::OnExit() {
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}
GameSceneLv2::GameSceneLv2(Context* const ctx, const Controls& controls) : IScene(ctx), controls(controls) {}
