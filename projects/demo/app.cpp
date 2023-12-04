#include "hop.hpp"

#include <iostream>

void monitor_keys(hop::Game* game){
    
    game->monitor_key(KEY_RIGHT);
    game->monitor_key(KEY_LEFT);
    game->monitor_key(KEY_UP);
    game->monitor_key(KEY_DOWN);
    game->monitor_key(KEY_ESCAPE);

}

void parse_input(hop::Game* game, std::vector<int> keys_pressed, hop::ObjectGroup* group){

    for(int k: keys_pressed){
        if(k==KEY_ESCAPE){
            game->stop();
        }
        if(k==KEY_RIGHT){
            group->move(100,0);
        }
        if(k==KEY_LEFT){

        }
        if(k==KEY_UP){

        }
        if(k==KEY_DOWN){

        }
    }
}

int main(){

    hop::Game game("My_Game_Name");
    game.set_fullscreen();
    game.run();
    
    hop::ObjectGroup my_group(200,200,16,20);

    my_group.create_rectangle(0,0,4,16,hop::WHITE);
    my_group.create_rectangle(12,0,4,16,hop::WHITE);
    my_group.create_rectangle(4,16,8,4,hop::WHITE);
    my_group.create_rectangle(4,8,8,4,hop::WHITE);


    monitor_keys(&game);
    float changing_color = 0.0;
    while(game.is_running()){
        game.update();
        
        std::vector<int> keys_pressed = game.get_pressed_keys();

        parse_input(&game, keys_pressed, &my_group);
    }

    return 0;
}
