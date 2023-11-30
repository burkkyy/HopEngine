#include "hop.hpp"

#include <iostream>

int main(){

    hop::Game game("My_Game_Name");
    game.set_fullscreen();
    game.run();

    game.monitor_key(KEY_UP);
    game.monitor_key(KEY_DOWN);
    game.monitor_key(KEY_LEFT);
    game.monitor_key(KEY_RIGHT);
    game.monitor_key(KEY_ESCAPE);

    Rectangle my_rectangle = game.create_rectangle(20,20,100,150,hop::RED);

    while(game.is_running()){
        game.update();

        if(game.key_pressed(KEY_ESCAPE)){
            game.stop();
        }
        if(game.key_pressed(KEY_UP)){
            my_rectangle->move(0,50);
        }
        if(game.key_pressed(KEY_DOWN)){
            my_rectangle->move(0,-50);
        }
        if(game.key_pressed(KEY_LEFT)){
            my_rectangle->move(-50,0);
        }
        if(game.key_pressed(KEY_RIGHT)){
            my_rectangle->move(50,0);
        }
    }

    return 0;
}
