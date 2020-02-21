//
// Created by nariman on 20.02.20.
//

#ifndef NAZAROV_NARIMAN_GAME_GROUND_H
#define NAZAROV_NARIMAN_GAME_GROUND_H


class Ground {
    char symbol_;
    int width_;
    int y_;
public:
    Ground(char symbol, int width, int y) : symbol_(symbol), width_(width), y_(y) {}

    void Update();
};


#endif //NAZAROV_NARIMAN_GAME_GROUND_H
