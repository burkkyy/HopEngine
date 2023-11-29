#include "hop.hpp"

#include <iostream>

void monitor_keys(hop::Game* game){
    
    game->monitor_key(KEY_RIGHT);
    game->monitor_key(KEY_LEFT);
    game->monitor_key(KEY_UP);
    game->monitor_key(KEY_DOWN);
    game->monitor_key(KEY_ESCAPE);

}

void parse_input(hop::Game* game, std::vector<int> keys_pressed, std::vector<GameObject> head){

    for(int k: keys_pressed){
        if(k==KEY_ESCAPE){
            game->stop();
        }
        if(k==KEY_RIGHT){
            for(auto o:head){
                o->move(50,0);
            }
        }
        if(k==KEY_LEFT){
            for(auto o:head){
                o->move(-50,0);
            }
        }
        if(k==KEY_UP){
            for(auto o:head){
                o->move(0,50);
            }
        }
        if(k==KEY_DOWN){
            for(auto o:head){
                o->move(0,-50);
            }
        }
    }
}

int main(){

    hop::Game game("My_Game_Name");
    game.set_window_size(game.get_resolution_height(),game.get_resolution_height());
    game.run();
    
    std::vector<GameObject> head;
    head.push_back(game.create_circle(280,240,20,hop::RED));
    head.push_back(game.create_rectangle(260,320,20,20,hop::GREEN));
    head.push_back(game.create_rectangle(320,320,20,20,hop::GREEN));
    head.push_back(game.create_circle(200,200,100,hop::BLUE));
    monitor_keys(&game);

    while(game.is_running()){
        game.update();
        std::vector<int> keys_pressed = game.get_pressed_keys();
        parse_input(&game, keys_pressed,head);
    }

    return 0;
}
