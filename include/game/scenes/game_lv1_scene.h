
#include <game/controls.h>
#include <game/systems/reading_file_levels_system.h>
#include <lib/ecs/engine.h>
#include <lib/scenes/i_scene.h>

#include "vector"
class GameSceneLv1 : public IScene {
  const int width_ = 80;
  const int ground_y_ = 15;
  const Controls& controls;
  const Engine engine{};

 public:
  GameSceneLv1(Context* const ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};
