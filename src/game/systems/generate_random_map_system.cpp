#include "game/systems/generate_random_map_system.h"

#include <BearLibTerminal.h>

#include <iostream>
#include <queue>
#include <utility>
#include <vector>

void GenerateRandomMapSystem::OnUpdate() {
  srand(time(NULL));
  Point Start;
  Start.x = 0;
  Start.y = 0;
  Start.cost = 1;
  Point Finish;
  Finish.x = 68;
  Finish.y = 20;
  Finish.cost = 1;
  int count_r = 1 + random() % 3;
  std::cout << "level nubmer is " << ctx_->level_number << std::endl;
  std::cout << "ctx_->scene_ " << ctx_->scene_ << std::endl;
  std::cout << "ctx_->prev_scene_ " << ctx_->prev_scene_ << std::endl;
  if (ctx_->levels_.count(ctx_->level_number) == 0) {
    std::cout << "not found" << std::endl;
    generate(count_r);
    //  зануляем карту индексом 0
    ctx_->levels_.insert(std::pair<int, std::vector<int>>(ctx_->level_number, m_data));
    ctx_->levels_.find(ctx_->level_number)->second.assign(m_width * m_height, 0);
    //  // пространство комнат заполняем индексом 1
    for (const Room& room : m_rooms) {
      for (int x = 0; x < room.w; ++x)
        for (int y = 0; y < room.h; ++y) {
          ctx_->levels_.find(ctx_->level_number)->second[(room.x + x) + (room.y + y) * m_width] = 1;
        }
    }
    generatePassage(Start, Finish);
    generateWalls();
    generatePlayer();
    generateCoins();
    generateDoor();
  } else {
    std::cout << "found" << std::endl;
    int a = 0;
    for (int x = 0; x < m_width; x++) {
      for (int y = 0; y < m_height; y++) {
        if (ctx_->levels_.find(ctx_->level_number)->second[x + y * m_width] == 2) {
          creatingEntitySystem_->CreatingEntity('#', x, y);
        } else if (ctx_->levels_.find(ctx_->level_number)->second[x + y * m_width] == 3) {
          creatingEntitySystem_->CreatingEntity('$', x, y);
        } else if (ctx_->levels_.find(ctx_->level_number)->second[x + y * m_width] == 4) {
          creatingEntitySystem_->CreatingEntity('>', x, y);
          std::cout << "next door add" << std::endl;
          if (ctx_->scene_ < ctx_->prev_scene_ && ctx_->prev_scene_ != "result_scene") {
            creatingEntitySystem_->CreatingEntity('@', x - 1, y);
            std::cout << "player add" << std::endl;
          }
        } else if (ctx_->levels_.find(ctx_->level_number)->second[x + y * m_width] == 5) {
          creatingEntitySystem_->CreatingEntity('<', x, y);
          if (ctx_->prev_scene_ == "result_scene") {
            // std::cout << "player add" << std::endl;
            creatingEntitySystem_->CreatingEntity('@', x, y + 1);
          }
        }
      }
    }
  }
}

void GenerateRandomMapSystem::generate(int roomsCount) {
  srand(time(NULL));
  m_rooms.clear();
  // std::cout << roomsCount << " roomsCount" << std::endl;
  // второй цикл предотвращает залипание, в случае если на карту уже не помещается ни одной комнаты
  for (int i = 0; i < roomsCount; ++i)
    for (int j = 0; j < 100; ++j) {
      // ширина и высота комнаты в пределах [3,6]
      const int w = 3 + random() % 6, h = 3 + random() % 6;
      // избегаем "прилипания" комнаты к краю карты
      const Room room = {static_cast<int>(3 + random() % (m_width - w - 6)),
                         static_cast<int>(3 + random() % (m_height - h - 6)), w, h};

      // найдем первую комнату, из уже существующих, которая пересекается с новой
      auto intersect =
          std::find_if(std::begin(m_rooms), std::end(m_rooms), [&room](const Room& r) { return room.intersect(r); });

      // если новая комната не имеет пересечений - добавляем ее
      if (intersect == std::end(m_rooms)) {
        m_rooms.push_back(room);
        break;
      }
    }
}
void GenerateRandomMapSystem::generatePassage(

    const GenerateRandomMapSystem::Point& start,
    const GenerateRandomMapSystem::Point& finish) {  // для хранения направления на "родительскую" клетку
  std::vector<int> parents(m_width * m_height, -1);
  srand(time(NULL));
  // приоритетная очередь доступных клеток, отсортирована по "стоимости"
  std::priority_queue<Point> active;
  active.push(start);

  // направления возможных перемещений
  static const int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  while (!active.empty()) {
    // берем самую "дешевую" клетку из списка доступных
    const Point point = active.top();
    active.pop();

    if (point == finish) break;

    // продолжаем поиск в доступных направлениях
    for (int i = 0; i < 4; ++i) {
      Point p = {point.x - directions[i][0], point.y - directions[i][1], 0};
      if (p.x < 0 || p.y < 0 || p.x >= m_width || p.y >= m_height) continue;

      // если мы еще не посещали заданную клетку
      if (parents[p.x + p.y * m_width] < 0) {
        // вычисляем "стоимость" указанной клетки
        p.cost = 1;
        active.push(p);

        parents[p.x + p.y * m_width] = i;
      }
    }
  }

  // путь найден - теперь прокладываем его на карте, начиная с конца
  Point point = finish;
  while (!(point == start)) {
    ctx_->levels_.find(ctx_->level_number)->second[point.x + point.y * m_width] = 1;

    const int* directon = directions[parents[point.x + point.y * m_width]];
    point.x += directon[0];  // TODO(Nariman) E:
    point.y += directon[1];
  }
}
void GenerateRandomMapSystem::generateWalls() {
  // смещения для соседних клеток
  static const int offsets[8][2] = {
      {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0},
  };

  // игнорируем край карты, чтобы не проверять граничные условия
  for (int x = 1; x < m_width - 1; ++x) {
    for (int y = 1; y < m_height - 1; ++y) {
      if (ctx_->levels_.find(ctx_->level_number)->second[x + y * m_width] == 0)
        for (int i = 0; i < 8; ++i) {
          // если по соседству есть хоть одна клетка комнаты или коридора - размещаем стену (индекс 2)
          if (ctx_->levels_.find(ctx_->level_number)->second[(x + offsets[i][0]) + (y + offsets[i][1]) * m_width] ==
              1) {
            ctx_->levels_.find(ctx_->level_number)->second[x + y * m_width] = 2;
            creatingEntitySystem_->CreatingEntity('#', x, y);
            if (x > max_x_) {
              max_x_ = x;
              max_y_ = y;
            }
            if (x < min_x_ && y < min_y_) {
              min_x_ = x;
              min_y_ = y;
            }
            break;
          }
        }
    }
  }
  while (ctx_->levels_.find(ctx_->level_number)->second[max_x_ + (max_y_ + 2) * m_width] == 2) {
    max_y_ += 1;
  }
}

bool GenerateRandomMapSystem::Room::intersect(const GenerateRandomMapSystem::Room& r) const {
  return !(r.x >= (x + w) || x >= (r.x + r.w) || r.y >= (y + h) || y >= (r.y + r.h));
}

void GenerateRandomMapSystem::OnPostUpdate() {
  GetSystemManagerPtr()->Delete<GenerateRandomMapSystem>();
}
void GenerateRandomMapSystem::generateCoins() {
  srand(time(NULL));
  int countCoins = 1 + random() % 3;
  // std::cout << "countCoins " << countCoins << std::endl;
  for (int i = 0; i < countCoins; i++) {
    int x = 0 + random() % 70;
    int y = 0 + random() % 26;
    for (int j = x; j < m_width - 1; j++) {
      for (int k = y; k < m_height - 1; k++) {
        if (ctx_->levels_.find(ctx_->level_number)->second[j + k * m_width] == 1) {
          ctx_->levels_.find(ctx_->level_number)->second[j + k * m_width] = 3;
          creatingEntitySystem_->CreatingEntity('$', j, k);
          k = m_height;
          j = m_width;
        }
      }
    }
  }
}
void GenerateRandomMapSystem::generateDoor() {
  if (ctx_->levels_.find(ctx_->level_number)->second[(max_x_ + 1) + (max_y_) *m_width] == 1) {
    ctx_->levels_.find(ctx_->level_number)->second[(max_x_ + 1) + (max_y_) *m_width] = 4;
    creatingEntitySystem_->CreatingEntity('>', max_x_ + 1, max_y_);
  } else if (ctx_->levels_.find(ctx_->level_number)->second[(max_x_ - 1) + (max_y_) *m_width] == 1) {
    ctx_->levels_.find(ctx_->level_number)->second[(max_x_ - 1) + (max_y_) *m_width] = 4;
    creatingEntitySystem_->CreatingEntity('>', max_x_ - 1, max_y_);
  }
  if (ctx_->scene_ == "game_lv1") {
    ctx_->levels_.find(ctx_->level_number)->second[(min_x_ + 1) + (min_y_) *m_width] = 2;
    creatingEntitySystem_->CreatingEntity('#', min_x_ + 1, min_y_);
  } else {
    ctx_->levels_.find(ctx_->level_number)->second[(min_x_ + 1) + (min_y_) *m_width] = 5;
    creatingEntitySystem_->CreatingEntity('<', min_x_ + 1, min_y_);
  }
}
void GenerateRandomMapSystem::generatePlayer() {
  //  if ((m_data[(max_x_ - 2) + (max_y_) *m_width] == 1) && (ctx_->scene_ < ctx_->prev_scene_)) {
  //    creatingEntitySystem_->CreatingEntity('@', max_x_ - 2, max_y_);
  //  } else
  if (ctx_->levels_.find(ctx_->level_number)->second[(min_x_ + 1) + (min_y_ + 1) * m_width] == 1 &&
      (ctx_->scene_ != ctx_->prev_scene_)) {
    creatingEntitySystem_->CreatingEntity('@', min_x_ + 1, min_y_ + 1);
  }
}

// while (m_data[x + ((y + 2) * m_width)] != 1) {
//            int x = 0 + random() % 75;
//            int y = 0 + random() % 28;
//          }
