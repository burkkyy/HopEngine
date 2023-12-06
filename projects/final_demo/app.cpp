#include "hop.hpp"
#include <iostream>


void monitor_keys(hop::Game* game){
    
    game->monitor_key(KEY_RIGHT);
    game->monitor_key(KEY_LEFT);
    game->monitor_key(KEY_UP);
    game->monitor_key(KEY_DOWN);
    game->monitor_key(KEY_ESCAPE);
    game->monitor_key(KEY_SPACE);
    game->monitor_key(KEY_LEFT_SHIFT);


}

bool collision(hop::Image* hank, hop::Image* thing);
bool bunny_grounded(hop::Image *hank, hop::Image* terrain); 
bool collision(hop::Image* hank, hop::GameObject thing);

int main(){
    bool hank_right = true;
    hop::Game game("Bunny_Game");
    hop::Color pink={{1.0}, {0.4}, {0.7}};
    game.set_window_size(game.get_resolution_height(),game.get_resolution_height());
    game.run();
    hop::TextBox Title(100,900,1,hop::WHITE,"Find tom hes dying fdown there");
    // Custom colours
    hop::Color orange={{0.9}, {0.5}, {0.0}};
    hop::Color light_pink={{1}, {0.76}, {0.9}};
    hop::Color brown={{0.7}, {0.4}, {0.1}};
    hop::Color grey={{0.4}, {0.5}, {0.5}};
    hop::Color real_brown={{0.5}, {0.3}, {0.0}};
    
    // CARROT
    hop::Image carrot1(850,960,100,60);
    carrot1.create_triangle(70,60,0,0,90,20,orange);
    carrot1.create_triangle(80,40,95,60,100,30,hop::GREEN);
    // CARROT 2
    hop::Image carrot2(250,510,100,100);
    carrot2.create_triangle(70,60,0,0,90,20,orange);
    carrot2.create_triangle(80,40,95,60,100,30,hop::GREEN);
    
 
    // stairs
    hop::Image stairs(0,0,1400,975);
    stairs.create_rectangle(0,0,200,750,brown); // hank spawn
    stairs.create_rectangle(200,650,200,100,brown);
    stairs.create_rectangle(400,650,200,150,brown);
    stairs.create_rectangle(600,750,170,50,brown);
    stairs.create_rectangle(-1000,0,2200,200,brown);
    stairs.create_rectangle(1000,0,200,800,brown);
    stairs.create_rectangle(770,375,150,200,brown);
    stairs.create_rectangle(920, 375, 100, 300, brown);
    stairs.create_rectangle(650, 375, 150, 100, brown);
    stairs.create_rectangle(200, 375, 200, 100, brown);
	

    hop::Image hideout(770,200,300,175);
    hideout.create_rectangle(0,0,300,175,brown);//bunny hideout

    std::vector<hop::GameObject> house;
    house.push_back(game.create_rectangle(0, 750, 150, 100, hop::BLUE)); //house base
    house.push_back(game.create_triangle(0, 850, 75, 900, 150, 850, hop::WHITE)); //house roof


    // heart
    hop::Image heart(820, 300, 50, 50);
    heart.create_rectangle(10, 15, 25, 10, light_pink);
    heart.create_rectangle(15, 10, 15, 5, light_pink);
    heart.create_rectangle(20, 5, 5, 5, light_pink);
    heart.create_rectangle(13, 25, 7, 5, light_pink);
    heart.create_rectangle(25, 25, 7, 5, light_pink);

    // hank
    hop::Image hank(30,750,90,100);
    hank.create_rectangle(64,75,6,15,pink); //ear detail
    hank.create_rectangle(75,55,5,10,hop::BLACK); //bunny eye
    hank.create_rectangle(86,45,4,5,pink); //bunny nose
    hank.create_rectangle(50,35,40,40,hop::WHITE); //bunny head
    hank.create_rectangle(10,5,70,50,hop::WHITE); // bunny body
    hank.create_rectangle(60,75,10,25,hop::WHITE); //bunny ear
    hank.create_circle (0,15,10,hop::WHITE); //bunny tail
    hank.create_rectangle(20,0,10,10,hop::WHITE); //bunny back feet
    hank.create_rectangle(60,0,10,10,hop::WHITE); //bunny front feeti

    hop::Image tom(770,200,150,100);
    tom.create_rectangle(64,75,6,15,pink); //ear detail
    tom.create_rectangle(75,55,5,10,hop::BLACK); //bunny eye
    tom.create_rectangle(86,45,4,5,pink); //bunny nose
    tom.create_rectangle(50,35,40,40,grey); //bunny head
    tom.create_rectangle(10,5,70,50,grey); // bunny body
    tom.create_rectangle(60,75,10,25,grey); //bunny ear
    tom.create_circle (0,15,10,grey); //bunny tail
    tom.create_rectangle(20,0,10,10,grey); //bunny back feet
    tom.create_rectangle(60,0,10,10,grey); //bunny front feet
 

    std::vector<hop::GameObject> background;
    background.push_back(game.create_rectangle(0, 0, 2000, 2000, hop::BLACK));

    monitor_keys(&game);
    float falling_duration = 1.0;
    while(game.is_running()){
        game.update();
        if(game.key_pressed(KEY_ESCAPE)){
            game.stop();
        }

        if(game.key_pressed(KEY_SPACE)&&(bunny_grounded(&hank,&stairs))){
            if(hank_right){
                hank.move(200,100);   
            }
            else{
                hank.move(-200,100);
            }
          }
        
        if(game.key_pressed(KEY_RIGHT)||game.key_held(KEY_RIGHT)){
            hank.move(10,0);
            if(!hank_right){
                hank.flip();
                hank_right = true;
            }
    }
        if(game.key_pressed(KEY_LEFT)||game.key_held(KEY_LEFT)){
            hank.move(-10,0);
            if(hank_right){
                hank.flip();
                hank_right = false;
            }
        }
        if(collision(&hank,&carrot1)){
            carrot1.move(1000,0);
        }
	    if(collision(&hank, &carrot2)){
		    carrot2.move(1000,0);
	    }
        if(collision(&hank,&hideout)){
            hideout.move(1000,0);
	        tom.flip();
        }
        if(!bunny_grounded(&hank,&stairs)){
            falling_duration += 0.5;
            int fall_distance = falling_duration * -1;
            hank.move(0,fall_distance);
        }
        else{
            falling_duration = 0.0;
        }
    }

    return 0;
}

bool collision(hop::Image* hank, hop::Image* thing){
    bool x_overlap = false;
    bool y_overlap = false;

    int o1_minx = hank->get_x();
    int o1_maxx = hank->get_x() + hank->get_width();
    int o1_miny = hank->get_y();
    int o1_maxy = hank->get_y() + hank->get_height(); 
    int o2_minx = thing->get_x();
    int o2_maxx = thing->get_x() + thing->get_width();
    int o2_miny = thing->get_y();
    int o2_maxy = thing->get_y() + thing->get_height(); 

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

bool bunny_grounded(hop::Image *hank, hop::Image* terrain){

    int bun_minx = hank->get_x();
    int bun_maxx = hank->get_x() + hank->get_width();

    for(auto obj: terrain->game_objects){
        bool x_overlap = false;
        int obj_minx = obj->x;
        int obj_maxx = obj->x + obj->width;
        int obj_top = obj->y+obj->height;
        if((bun_minx<= obj_minx)&&(bun_maxx >= obj_minx)){
            x_overlap = true;
        }
        if((obj_minx<= bun_minx)&&(obj_maxx >= bun_minx)){
            x_overlap = true;
        }

        if((x_overlap)&&(hank->get_y() > (obj_top-10))&&(hank->get_y()< (obj_top+10))){
            return true;
        }
    }
    return false;
}