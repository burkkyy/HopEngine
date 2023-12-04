#include "hop.hpp"

#include <iostream>

void monitor_keys(hop::Game* game){
    
    game->monitor_key(KEY_RIGHT);
    game->monitor_key(KEY_LEFT);
    game->monitor_key(KEY_UP);
    game->monitor_key(KEY_DOWN);
    game->monitor_key(KEY_ESCAPE);

}

void parse_input(hop::Game* game, std::vector<int> keys_pressed, hop::Image* group){

    for(int k: keys_pressed){
        if(k==KEY_ESCAPE){
            game->stop();
        }
        if(k==KEY_RIGHT){
            group->move(90,0);
        }
        if(k==KEY_LEFT){
            group->move(-90,00);
        }
        if(k==KEY_UP){
            group->move(0,100);
        }
        if(k==KEY_DOWN){
            group->move(0,-100);
        }
    }
}

int main(){

    hop::Game game("My_Game_Name");
    game.set_fullscreen();
    game.run();
    hop::Color pink={{1.0}, {0.4}, {0.7}};

    hop::TextBox a(0,600,6,hop::GREEN,"1234,56789?a?b!");
    hop::TextBox b(0,400,1,hop::GREEN,"It was the best of times,it was the blurst of times. Was it though?");

    hop::Image Hank2(30,975,90,100);
    Hank2.create_rectangle(64,75,6,15,pink); //ear detail
    Hank2.create_rectangle(75,55,5,10,hop::BLACK); //bunny eye
    Hank2.create_rectangle(86,45,4,5,pink); //bunny nose
    Hank2.create_rectangle(50,35,40,40,hop::WHITE); //bunny head
    Hank2.create_rectangle(10,5,70,50,hop::WHITE); // bunny body
    Hank2.create_rectangle(60,75,10,25,hop::WHITE); //bunny ear
    Hank2.create_circle (0,15,10,hop::WHITE); //bunny tail
    Hank2.create_rectangle(20,0,10,10,hop::WHITE); //bunny back feet
    Hank2.create_rectangle(60,0,10,10,hop::WHITE); //bunny front feet
    hop::Image Hank(30,975,90,100);
    Hank.create_rectangle(64,75,6,15,pink); //ear detail
    Hank.create_rectangle(75,55,5,10,hop::BLACK); //bunny eye
    Hank.create_rectangle(86,45,4,5,pink); //bunny nose
    Hank.create_rectangle(50,35,40,40,hop::WHITE); //bunny head
    Hank.create_rectangle(10,5,70,50,hop::WHITE); // bunny body
    Hank.create_rectangle(60,75,10,25,hop::WHITE); //bunny ear
    Hank.create_circle (0,15,10,hop::WHITE); //bunny tail
    Hank.create_rectangle(20,0,10,10,hop::WHITE); //bunny back feet
    Hank.create_rectangle(60,0,10,10,hop::WHITE); //bunny front feet
    Hank.flip();
    monitor_keys(&game);
    while(game.is_running()){
        game.update();
        
        std::vector<int> keys_pressed = game.get_pressed_keys();

        parse_input(&game, keys_pressed, &Hank);
    }

    return 0;
}
