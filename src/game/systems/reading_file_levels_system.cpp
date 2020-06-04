#include "game/systems/reading_file_levels_system.h"

#include <game/components/obstacle_component.h>
#include <game/systems/creating_entity_system.h>

#include <fstream>
#include <iostream>
#include <string>

#include "vector"

void ReadingFileLevelsSystem::OnUpdate() {
  std::ifstream LevelFile("levels/level_1");

  int c = 1;
  if (!LevelFile.is_open()) {
    std::cout << "cant open file" << std::endl;
    exit(-1);
  }
  while (std::getline(LevelFile, s)) {
    c++;
    //  std::vector<char> row;
    for (int i = 0; i < s.size(); i++) {
      //      row.push_back(s[i]);
      creatingEntitySystem_->CreatingEntity(s[i], 0, 0);
      //  creatingEntitySystem_->CreatingEntity(s[i], i, i);
    }
    // levelfile.push_back(row);
  }
  LevelFile.close();
}

void ReadingFileLevelsSystem::ReadFile() {}
std::vector<std::vector<char>> ReadingFileLevelsSystem::GetLevel() {
  //  return levelfile;
}
