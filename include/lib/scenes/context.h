#pragma once
#include <map>
#include <string>
#include <vector>

/**
 * В контексте хранится информация о сцене, которую нужно сейчас отрисоватывать.
 * Контекст должен создаться где-то во вне и передаться по указателю во все сцены,
 * чтобы они могли
 * им манипулировать и в SceneManager,
 * чтобы он мог читать из него информацию о сценах.
 *
 * Кстати, можно использовать контекст для хранения некоторой информации при переходе между сценами.
 * Но рекомендуется придумать механизм, чтобы не пришлось постоянно править класс контектса.
 * Как минимум используйте map<string, iobject*>
 */
class Context {
 public:
  std::string scene_ = "";
  std::string prev_scene_ = "";
  std::map<int, std::vector<int>> levels_;
  int level_number = 0;
  int score_steps = 0;
  int score_coins = 0;
  int width_ = 0;
  int height_ = 0;
};
