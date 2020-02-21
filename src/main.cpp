#include <BearLibTerminal.h>
#include <vector>

#include "math-utils.h"
#include <controls.h>
#include <player.h>
#include <ground.h>
#include <obstaclesmanager.h>


int main()
{
    terminal_open();
    terminal_refresh();

    const int width = 80;
    const int ground_y = 15;
    const float gravity = 0.2;

    Controls controls{};
    Player player(controls, 2, ground_y-3, 4.5, gravity *3, ground_y, gravity);
    ObstaclesManager om(player, ground_y, width, 0.25);
    Ground ground{'^', width, ground_y};

    float speed_x = 0.25;

    bool gameover = false;

    // Ждем, пока пользователь не закроет окно
    while (true) {
        terminal_clear();

        controls.Update();

        om.Update();

        if (controls.IsExit()){
            break;
        }

        player.Update();

        ground.Update();

        terminal_refresh();
    }
    terminal_close();
}