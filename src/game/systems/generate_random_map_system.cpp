#include "game/systems/generate_random_map_system.h"

#include <BearLibTerminal.h>

#include <iostream>
#include <queue>
#include <vector>

void GenerateRandomMapSystem::OnUpdate() {
  unsigned int a = 50;
  unsigned int* b = &a;
  std::cout << "rand_r " << rand_r(&a) % 49 << std::endl;
  Point Start;
  Start.x = 0;
  Start.y = 0;
  Start.cost = 1;
  Point Finish;
  Finish.x = rand_r(&a) % 27;
  Finish.y = rand_r(&a) % 27;
  Finish.cost = 1;

  generate(5);
  //  зануляем карту индексом 0
  m_data.assign(m_width * m_height, 0);
  //  // пространство комнат заполняем индексом 1
  for (const Room& room : m_rooms) {
    for (int x = 0; x < room.w; ++x)
      for (int y = 0; y < room.h; ++y) {
        m_data[(room.x + x) + (room.y + y) * m_width] = 1;
      }
  }

  generatePassage(Start, Finish);
  generateWalls();
}

void GenerateRandomMapSystem::generate(int roomsCount) {
  m_rooms.clear();

  // второй цикл предотвращает залипание, в случае если на карту уже не помещается ни одной комнаты
  for (int i = 0; i < roomsCount; ++i)
    for (int j = 0; j < 1000; ++j) {
      unsigned int a = 50;
      unsigned int* b = &a;

      // ширина и высота комнаты в пределах [10,40]
      const int w = 10 + rand_r(&a) % 31, h = 10 + rand_r(&a) % 31;
      // избегаем "прилипания" комнаты к краю карты
      const Room room = {3 + rand_r(&a) % (m_width - w - 6), 3 + rand_r(&a) % (m_height - h - 6), w, h};

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
    m_data[point.x + point.y * m_width] = 1;

    const int* directon = directions[parents[point.x + point.y * m_width]];
    point.x += directon[0];
    point.y += directon[1];
  }
}
void GenerateRandomMapSystem::generateWalls() {
  // смещения для соседних клеток
  static const int offsets[8][2] = {
      {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0},
  };

  // игнорируем край карты, чтобы не проверять граничные условия
  for (int x = 1; x < m_width - 1; ++x)
    for (int y = 1; y < m_height - 1; ++y) {
      if (m_data[x + y * m_width] == 0)
        for (int i = 0; i < 8; ++i) {
          // если по соседству есть хоть одна клетка комнаты или коридора - размещаем стену (индекс 2)
          if (m_data[(x + offsets[i][0]) + (y + offsets[i][1]) * m_width] == 1) {
            m_data[x + y * m_width] = 2;
            creatingEntitySystem_->CreatingEntity('#', x, y);
            // terminal_put(ToPos(x), ToPos(y), '#');
            break;
          }
        }
    }
}

bool GenerateRandomMapSystem::Room::intersect(const GenerateRandomMapSystem::Room& r) const {
  return !(r.x >= (x + w) || x >= (r.x + r.w) || r.y >= (y + h) || y >= (r.y + r.h));
}

void GenerateRandomMapSystem::OnPostUpdate() {
  GetSystemManagerPtr()->Delete<GenerateRandomMapSystem>();
}
