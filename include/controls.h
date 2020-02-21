//
// Created by nariman on 20.02.20.
//

#ifndef NAZAROV_NARIMAN_GAME_CONTROLS_H
#define NAZAROV_NARIMAN_GAME_CONTROLS_H


class Controls {
    bool is_jump_ = false;
    bool is_exit_ = false;
    bool step_right_ = false;
    bool step_left_ = false;

public:
    bool IsJump() const;

    bool IsExit() const;

    bool StepRight() const;

    bool StepLeft() const;

    void Update();

};

#endif //NAZAROV_NARIMAN_GAME_CONTROLS_H
