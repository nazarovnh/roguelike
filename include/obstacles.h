//
// Created by nariman on 20.02.20.
//

#ifndef NAZAROV_NARIMAN_GAME_OBSTACLES_H
#define NAZAROV_NARIMAN_GAME_OBSTACLES_H


class Obstacles {
    char sybmol = '#';
public:
    float x;
    float y;

    Obstacles(float x, float y) : x(x), y(y) {}

    void Update();

};


#endif //NAZAROV_NARIMAN_GAME_OBSTACLES_H
