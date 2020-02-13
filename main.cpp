#include <BearLibTerminal.h>
#include <vector>
#include <cmath>

int to_pos(float x){
    return static_cast<int>(std::round(x));
}


class Controls {
    bool is_jump_ = false;
    bool is_exit_ = false;

public:
    bool IsJump() const { return is_jump_; }
    bool IsExit() const { return is_exit_; }
    void Update() {
        is_jump_ = false; // Мы же уже объявили  ?

        while (terminal_has_input()) {
            auto key = terminal_read();
            if (key == TK_SPACE) {
                is_jump_ = true;
            }
            if (key == TK_CLOSE) {
                is_exit_ = true;
            }
        }
    }
};


class Player{
    float speed_y = 0;
    char symbol = '@';

    const Controls &controls;
    int x_;
    float y_;
    float max_jump_height_;
    float max_speed_y_;
    int ground_y_;
    float gravity_;

    bool IsFlying() const {
        return  y_ < ground_y_;
    }

    void Render() {
        terminal_put(x_,y_, symbol);
    }

    void Move() {
        if(controls.IsJump() && !IsFlying()){
            speed_y = max_speed_y_;
        }
        if( y_ >= ground_y_){
            y_ = ground_y_;
        }
        if(y_ <= ground_y_ - max_jump_height_){
            speed_y = 0;
        }

        y_ -= speed_y;
        y_ += gravity_;
    }

public:
    Player(const Controls &controls, int x, float y, float max_jump_height , float max_speed_y, int ground_y, float gravity)
            : controls(controls) ,x_(x), y_(y), max_jump_height_(max_jump_height), max_speed_y_(max_speed_y), ground_y_(ground_y), gravity_(gravity) {} // Горячие клавиши


    void Update() {
        Move();
        Render();
    }

    int GetX() const { return  to_pos(x_); }
    int GetY() const { return  to_pos(y_); }
};

class Obstacles {
    char sybmol = '#';
public:
    float x;
    float y;

    Obstacles(float x, float y) : x(x), y(y) {}

    void Update() {
        terminal_put(to_pos(x), to_pos(y), sybmol);
    }
};

class ObstaclesManager {
    const Player& player_;
    float  ground_y = 0;
    int world_width;
    float speed_x;
    std::vector<Obstacles> obstacles{{35, ground_y}, {55, ground_y}, {70, ground_y}};
public:

    ObstaclesManager(const Player& player, float ground_y, int world_width, float speed_x)
    : player_(player), ground_y(ground_y), world_width(world_width), speed_x(speed_x) {}
    void Update(){
        // Почему указатель ?
        for (auto& o: obstacles) {
            o.x -= speed_x;
            if (o.x <= 0){
                o.x = world_width;
            }

            if(player_.GetX() == to_pos(o.x) && player_.GetY() == to_pos(ground_y)){
                terminal_print(1, 1, "BUM");
                //game_over = true;
            }

            o.Update();
        }
    }
};

class Ground {
    char symbol_;
    int width_;
    int y_;
public:
    Ground(char symbol, int width, int y) : symbol_(symbol), width_(width), y_(y) {}

    void Update(){
        for (int i = 0; i < width_; i++){
            terminal_put(i, y_+1, '^');
        }
    }
};



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

    bool game_over = false;

    // Ждем, пока пользователь не закроет окно
    while (true) {
        terminal_clear();

        controls.Update();

        if (controls.IsExit()){
            break;
        }

        om.Update();

//        if(game_over){
//            terminal_print(1,1, "Game over!");
//            terminal_refresh();
//            continue;
//        }

        player.Update();

        ground.Update();

        terminal_refresh();
    }

    terminal_close();
}