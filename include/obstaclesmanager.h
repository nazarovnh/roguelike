//
// Created by nariman on 21.02.20.
//

#ifndef NAZAROV_NARIMAN_GAME_OBSTACLESMANAGER_H
#define NAZAROV_NARIMAN_GAME_OBSTACLESMANAGER_H

#include "player.h"
#include "obstacles.h"
#include <vector>


class ObstaclesManager {
    const Player& player_;
    float  ground_y = 0;
    int world_width;
    float speed_x;
    std::vector<Obstacles> obstacles{{35, ground_y}, {55, ground_y}, {70, ground_y}};

public:

    ObstaclesManager(const Player& player, float ground_y, int world_width, float speed_x)
            : player_(player), ground_y(ground_y), world_width(world_width), speed_x(speed_x) {}

    void Gameover();

    void Update();

};


#endif //NAZAROV_NARIMAN_GAME_OBSTACLESMANAGER_H
