#include "hop.hpp"
#include <iostream>


void monitor_keys(hop::Game* game){
    
    game->monitor_key(KEY_RIGHT);
    game->monitor_key(KEY_LEFT);
    game->monitor_key(KEY_UP);
    game->monitor_key(KEY_DOWN);
    game->monitor_key(KEY_ESCAPE);

}
/*class Square{
public:
	Square(int x, int y){ //says game is uninitialized in function
		hop::Game* game;
		int w = 50;
		int h = 70;
		hop::Color color = hop::RED;
		game->create_rectangle(x, y, w, h, color);
	}	
};*/
void parse_input(hop::Game* game, std::vector<int> keys_pressed, std::vector<hop::GameObject> hank){

    for(int k: keys_pressed){
        if(k==KEY_ESCAPE){
            game->stop();
        }
        if(k==KEY_RIGHT){
            for(auto o:hank){
                o->move(50,0);
            }
        }
        if(k==KEY_LEFT){
            for(auto o:hank){
                o->move(-50,0);
            }
        }
        if(k==KEY_UP){
            for(auto o:hank){
                o->move(0,50);
            }
        }
        if(k==KEY_DOWN){
            for(auto o:hank){
                o->move(0,-50);
            }
        }
    }
}

int main(){

    hop::Game game("Bunny_Game");
    hop::Color pink={{1.0}, {0.4}, {0.7}};
    game.set_window_size(game.get_resolution_height(),game.get_resolution_height());
    game.run();
    
    // Custom colours
    hop::Color orange={{0.9}, {0.5}, {0.0}};
    hop::Color light_pink={{1}, {0.76}, {0.9}};
    hop::Color brown={{0.7}, {0.4}, {0.1}};
    
    // CARROT
    std::vector<hop::GameObject> carrot;
    carrot.push_back(game.create_triangle(920,1020,850,960,940,980,orange)); //carrot body
    carrot.push_back(game.create_triangle(930,1000,945,1020,950,990,hop::GREEN)); //carrot body

    
    // stairs   
    std::vector<hop::GameObject> stairs;
    stairs.push_back(game.create_rectangle(0,0,150,975,brown)); // hank spawn
    stairs.push_back(game.create_rectangle(150,0,70,950,brown));
    stairs.push_back(game.create_rectangle(220,0,100,930,brown));
    stairs.push_back(game.create_rectangle(320,0,80,910,brown));
    stairs.push_back(game.create_rectangle(400,0,200,890,brown));//done
    stairs.push_back(game.create_rectangle(600,0,200,870,brown));
    stairs.push_back(game.create_rectangle(1000,0,100,870,brown));//done

    // hank
    std::vector<hop::GameObject> hank;
    hank.push_back(game.create_rectangle(84,1050,6,15,pink)); //ear detail
    hank.push_back(game.create_rectangle(95,1030,5,10,hop::BLACK)); //bunny eye
    hank.push_back(game.create_rectangle(106,1020,4,5,pink)); //bunny nose
    hank.push_back(game.create_rectangle(70,1010,40,40,hop::WHITE)); //bunny head
    hank.push_back(game.create_rectangle(30,980,70,50,hop::WHITE)); //bunny body
    hank.push_back(game.create_rectangle(80,1050,10,25,hop::WHITE)); //bunny ear
    hank.push_back(game.create_circle(20,990,10,hop::WHITE)); //bunny tail
    hank.push_back(game.create_rectangle(40,975,10,10,hop::WHITE)); //bunny back feet
    hank.push_back(game.create_rectangle(80,975,10,10,hop::WHITE)); //bunny front feet

   // Square newSquare(100, 1100);
    monitor_keys(&game);

    while(game.is_running()){
        game.update();
        std::vector<int> keys_pressed = game.get_pressed_keys();
        parse_input(&game, keys_pressed,hank);
    }

    return 0;
}
