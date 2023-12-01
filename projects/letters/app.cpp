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
            group->move(-100,00);
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
    
    hop::ObjectGroup A(200,800,32,40);
    A.create_rectangle(0,0,8,32,hop::WHITE);
    A.create_rectangle(24,0,8,32,hop::WHITE);
    A.create_rectangle(8,32,16,8,hop::WHITE);
    A.create_rectangle(8,16,16,8,hop::WHITE);
        
    hop::ObjectGroup AA(240,800,32,40);
    AA.create_rectangle(0,0,8,32,hop::RED);
    AA.create_rectangle(24,0,8,32,hop::RED);
    AA.create_rectangle(8,32,16,8,hop::RED);
    AA.create_rectangle(8,16,16,8,hop::RED);
    
    hop::ObjectGroup AAA(280,800,32,40);
    AAA.create_rectangle(0,0,8,32,hop::BLUE);
    AAA.create_rectangle(24,0,8,32,hop::BLUE);
    AAA.create_rectangle(8,32,16,8,hop::BLUE);
    AAA.create_rectangle(8,16,16,8,hop::BLUE);
    
    hop::ObjectGroup B(320,800,32,40);
    B.create_rectangle(0,0,8,40,hop::WHITE);
    B.create_rectangle(8,0,16,8,hop::WHITE);
    B.create_rectangle(8,16,16,8,hop::WHITE);
    B.create_rectangle(8,32,16,8,hop::WHITE);
    B.create_rectangle(24,8,8,8,hop::WHITE);
    B.create_rectangle(24,24,8,8,hop::WHITE);
    B.create_rectangle(24,4,4,16,hop::WHITE);
    B.create_rectangle(24,20,4,16,hop::WHITE);

    hop::ObjectGroup BB(360,800,32,40);
    BB.create_rectangle(0,0,8,40,hop::RED);
    BB.create_rectangle(8,0,16,8,hop::RED);
    BB.create_rectangle(8,16,16,8,hop::RED);
    BB.create_rectangle(8,32,16,8,hop::RED);
    BB.create_rectangle(24,8,8,8,hop::RED);
    BB.create_rectangle(24,24,8,8,hop::RED);
    BB.create_rectangle(24,4,4,16,hop::RED);
    BB.create_rectangle(24,20,4,16,hop::RED);

    hop::ObjectGroup BBB(400,800,32,40);
    BBB.create_rectangle(0,0,8,40,hop::BLUE);
    BBB.create_rectangle(8,0,16,8,hop::BLUE);
    BBB.create_rectangle(8,16,16,8,hop::BLUE);
    BBB.create_rectangle(8,32,16,8,hop::BLUE);
    BBB.create_rectangle(24,8,8,8,hop::BLUE);
    BBB.create_rectangle(24,24,8,8,hop::BLUE);
    BBB.create_rectangle(24,4,4,16,hop::BLUE);
    BBB.create_rectangle(24,20,4,16,hop::BLUE);


    monitor_keys(&game);
    float changing_color = 0.0;
    while(game.is_running()){
        game.update();
        
        std::vector<int> keys_pressed = game.get_pressed_keys();

        parse_input(&game, keys_pressed, &A);
    }

    return 0;
}
