#include "game/systems/reading_file_levels_system.h"

#include <game/components/obstacle_component.h>
#include <game/systems/creating_entity_system.h>

#include <fstream>
#include <iostream>
#include <string>

#include "vector"

void ReadingFileLevelsSystem::OnUpdate() {
  std::ifstream LevelFile(path_file_.find(ctx_->scene_)->second);

  int c = 0;
  if (!LevelFile.is_open()) {
    std::cout << "cant open file" << std::endl;
    exit(-1);
  }
  while (std::getline(LevelFile, s)) {
    c++;
    for (int i = 0; i < s.size(); i++) {
      creatingEntitySystem_->CreatingEntity(s[i], i, c);
    }
  }
  LevelFile.close();
}

void ReadingFileLevelsSystem::OnPostUpdate() {
  GetSystemManagerPtr()->Delete<ReadingFileLevelsSystem>();
}
