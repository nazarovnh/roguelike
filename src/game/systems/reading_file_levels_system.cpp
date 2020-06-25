#include "game/systems/reading_file_levels_system.h"

#include <game/components/obstacle_component.h>
#include <game/systems/creating_entity_system.h>

#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include "vector"
void ReadingFileLevelsSystem::OnUpdate() {
  std::ifstream LevelFile(path_file_.find(ctx_->scene_)->second);

  if (!LevelFile.is_open()) {
    std::cout << "cant open file" << std::endl;
    exit(-1);
  }

  SizeFile();
  if (ctx_->levels_.count(ctx_->level_number) == 0) {
    ctx_->levels_.insert(std::pair<int, std::vector<int>>(ctx_->level_number, m_data));
    ctx_->levels_.find(ctx_->level_number)->second.assign(ctx_->width_ * ctx_->height_, 0);
  }  //  for (int y = 0; y < ctx_->height_; y++) {
  //    for (int x = 0; x < ctx_->width_; x++) {
  //      creatingEntitySystem_->CreatingEntity(s[x], x, y);
  //    }
  //  }
  int y = 0;
  std::cout << "width " << ctx_->width_ << std::endl;
  // creatingEntitySystem_->CreatingEntity('$', ctx_->width_, ctx_->height_ + 1);
  while (std::getline(LevelFile, s)) {
    for (int x = 0; x < s.size(); x++) {
      if (ctx_->levels_.find(ctx_->level_number)->second[x + y * ctx_->width_] != 1) {
        creatingEntitySystem_->CreatingEntity(s[x], x, y);
      } else {
        creatingEntitySystem_->CreatingEntity(' ', x, y);
      }
    }
    y++;
  }

  creatingEntitySystem_->CreatePlayer(2, 2);
  LevelFile.close();
}

void ReadingFileLevelsSystem::OnPostUpdate() {
  GetSystemManagerPtr()->Delete<ReadingFileLevelsSystem>();
}
void ReadingFileLevelsSystem::SizeFile() {
  std::ifstream LevelFile(path_file_.find(ctx_->scene_)->second);

  int c = 0;
  if (!LevelFile.is_open()) {
    std::cout << "cant open file" << std::endl;
    exit(-1);
  }

  while (std::getline(LevelFile, s)) {
    c++;
  }
  ctx_->width_ = s.size() - 1;
  ctx_->height_ = c;
  LevelFile.close();
}
