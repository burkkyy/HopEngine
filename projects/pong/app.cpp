#include "hop.hpp"

#include <iostream>

class Paddle{

public:
Paddle(hop::Game* game, int x, hop::Color color){
    this-> game = game;
    paddle_rectangle = game->create_rectangle(x,480,20,120,color);
    this-> y = 480;
    this->vy = 0;
}
void move_up(){

    if(y+120 < 1014){
        paddle_rectangle->move(0,10);
        this->y = this->y +10;
        if(vy<3){
            this->vy +=1;
        }
    }

}

void move_down(){

    if(y > 64){
        paddle_rectangle->move(0,-10);
        this->y = this->y -10;
        if(vy>-3){
            this->vy -=1;
        }
    }

}

private:
hop::Rectangle paddle_rectangle;
hop::Game* game;
int y;
int vy;

};
int main(){

    hop::Game game("My_Game_Name");
    game.set_fullscreen();
    game.run();
    game.monitor_key(KEY_ESCAPE);
    game.monitor_key(KEY_UP);
    game.monitor_key(KEY_DOWN);

    Paddle player_paddle(&game, 50, hop::BLUE);
    Paddle cpu_paddle(&game, 1850, hop::RED);

    
    hop::Rectangle bottom = game.create_rectangle(0,0,1920,60,hop::WHITE);
    hop::Rectangle top = game.create_rectangle(0,1020,1920,60,hop::WHITE);

    while(game.is_running()){
        game.update();
        if(game.key_pressed(KEY_ESCAPE)){
            game.stop();
        }    
        if(game.key_pressed(KEY_UP)||game.key_held(KEY_UP)){
            player_paddle.move_up();
        }
        if(game.key_pressed(KEY_DOWN)||game.key_held(KEY_DOWN)){
            player_paddle.move_down();
        }


    }

    return 0;
}
