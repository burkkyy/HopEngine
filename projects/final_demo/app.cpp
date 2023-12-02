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

bool collision(hop::GameObject obj1, hop::GameObject obj2){
    bool x_overlap = false;
    bool y_overlap = false;

    int o1_minx = obj1->x;
    int o1_maxx = obj1->x + obj1->width;
    int o1_miny = obj1->y;
    int o1_maxy = obj1->y + obj1->height; 
    int o2_minx = obj2->x;
    int o2_maxx = obj2->x + obj2->width;
    int o2_miny = obj2->y;
    int o2_maxy = obj2->y + obj2->height; 

    if((o1_minx<= o2_minx)&&(o1_maxx >= o2_minx)){
        x_overlap = true;
    }

    if((o2_minx<= o1_minx)&&(o2_maxx >= o1_minx)){
        x_overlap = true;
    }
    if((o1_miny<= o2_miny)&&(o1_maxy >= o2_miny)){
        y_overlap = true;
    }

    if((o2_miny<= o1_miny)&&(o2_maxy >= o1_miny)){
        y_overlap = true;
    }

    return x_overlap && y_overlap;

    return false;
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
    hop::Triangle carrot_body = game.create_triangle(920,1020,850,960,940,980,orange);
    carrot.push_back(carrot_body);
    
    hop::Triangle carrot_top = game.create_triangle(930,1000,945,1020,950,990,hop::GREEN);

    carrot.push_back(carrot_top);
    
    // stairs   
    std::vector<hop::GameObject> stairs;
    stairs.push_back(game.create_rectangle(0,0,200,750,brown)); // hank spawn
    stairs.push_back(game.create_rectangle(200,650,200,100,brown));
    stairs.push_back(game.create_rectangle(400,650,200,150,brown));
    stairs.push_back(game.create_rectangle(600,750,170,50,brown));
    stairs.push_back(game.create_rectangle(200,0,1200,200,brown));
    stairs.push_back(game.create_rectangle(1000,0,200,800,brown));
    stairs.push_back(game.create_rectangle(770,200,300,175,hop::WHITE)); //bunny hideout
    stairs.push_back(game.create_rectangle(770,375,150,200,brown));

    // hank
    std::vector<hop::GameObject> hank;
    hank.push_back(game.create_rectangle(84,1050,6,15,pink)); //ear detail
    hank.push_back(game.create_rectangle(95,1030,5,10,hop::BLACK)); //bunny eye
    hank.push_back(game.create_rectangle(106,1020,4,5,pink)); //bunny nose
    hank.push_back(game.create_rectangle(70,1010,40,40,hop::WHITE)); //bunny head
    hop::Rectangle bunny_bod = game.create_rectangle(30,980,70,50,hop::WHITE);
    hank.push_back(bunny_bod);
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
        if(collision(bunny_bod,carrot_body)){
            carrot_body->move(1000,0);
            carrot_top->move(1000,0);
        }
    }

    return 0;
}
