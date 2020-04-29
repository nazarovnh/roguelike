
#include <game/controls.h>
#include <lib/ecs/engine.h>
#include <lib/scenes/i_scene.h>

class GameSceneLv1 : public IScene {
  const int width_ = 80;
  const int ground_y_ = 15;
  const Engine engine{};
  const Controls& controls;

 public:
  GameSceneLv1(Context* const ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void Check();
  void OnExit() override;
};
