#include "hop.hpp"
#include <time.h>
#include <stdlib.h>  
#include <iostream>


class Paddle{

public:
Paddle(hop::Game* game, int x, hop::Color color){
    this-> game = game;
    paddle_rectangle = game->create_rectangle(x,550,20,120,color);
    this-> y = 550;
    this->vy = 0;
}
void move_up( int magnitude){

    if(y+120 < 1014){
        paddle_rectangle->move(0,magnitude);
        y = y + magnitude;
        if(vy<5){
            this->vy +=1;
        }
    }

}

void move_down( int magnitude){

    if(y > 214){
        paddle_rectangle->move(0,-magnitude);
        this->y = this->y -magnitude;
        if(vy>-5){
            this->vy -=1;
        }
    }

}
int y;
int vy;
private:
hop::Rectangle paddle_rectangle;
hop::Game* game;


};

class Ball{
    public:
    Ball(hop::Game* game) {
        this->game = game;
        reset();
    }
    void reset (){
        circle = game->create_circle(950,600,20, hop::GREEN);
        this->vx = -10;
        this->vy = rand()%16 -8;
        this->x = 950;
        this->y = 600;
    }
    void update(){
        circle->move(vx,vy);
        x+= vx;
        y+=vy;
    }
    int x;
    int vx;
    int y;
    int vy;
    int radius = 10;
    int velo;

    private:
    hop::Game* game;
    hop::Circle circle;
    int speed = 10;

};

void collision(Ball& ball, Paddle& player_paddle, Paddle& cpu_paddle, hop::Sound boing){

    if((ball.x < 80) &&(ball.x>60)&&(ball.y>=player_paddle.y-20)&&((ball.y+30)<=(player_paddle.y + 150))){
        int new_y_vel = ((ball.y-player_paddle.y)/10) - 5; 
        ball.vy = new_y_vel;
        ball.vx = ball.vx * -1;
        if(boing!=NULL){
            boing->play();
        }
    }

    else if((ball.x > 1820) &&(ball.x<1840)&&(ball.y>=cpu_paddle.y)&&((ball.y+20)<=(cpu_paddle.y + 120))){
        int new_y_vel = ((ball.y-cpu_paddle.y)/10) - 5; 
        ball.vy = new_y_vel;
        ball.vx = ball.vx * -1;
        if(boing!=NULL){
            boing->play();
        }
    }
}

bool collision(Ball& ball){

    if((ball.y<220)&&(ball.y>200)){
        return true;
    }

    if((ball.y<1010)&&(ball.y>990)){
        return true;
    }

    return false;
}


int main(){
   
    srand (time(NULL));
    hop::Game game("My_Game_Name");
    game.set_fullscreen();
    game.run();
    game.monitor_key(KEY_ESCAPE);
    game.monitor_key(KEY_UP);
    game.monitor_key(KEY_DOWN);
    Paddle player_paddle(&game, 50, hop::BLUE);
    Paddle cpu_paddle(&game, 1850, hop::RED);
    hop::Rectangle bottom = game.create_rectangle(0,150,1920,60,hop::WHITE);
    hop::Rectangle top = game.create_rectangle(0,1020,1920,60,hop::WHITE);
    hop::Rectangle p1l3 = game.create_rectangle(40, 25, 20,100, hop::BLUE);
    hop::Rectangle p1l2 = game.create_rectangle(80, 25, 20,100, hop::BLUE);
    hop::Rectangle p1l1 = game.create_rectangle(120, 25, 20,100, hop::BLUE);
    hop::Rectangle cl3 = game.create_rectangle(1780, 25, 20,100, hop::RED);
    hop::Rectangle cl2 = game.create_rectangle(1820, 25, 20,100, hop::RED);
    hop::Rectangle cl1 = game.create_rectangle(1860, 25, 20,100, hop::RED);
    int player_lives = 3;
    int cpu_lives = 3;
    Ball ball(&game);
    hop::TextBox title(660,25,5,hop::GREEN,"PONG!");
    hop::Sound background_music = game.create_sound("pong_background.mp3", true);
    hop::Sound boing = game.create_sound("boing.wav", false);
    if(background_music!=NULL){
        background_music->play();
    }


    while(game.is_running()){
        game.update();
        if(game.key_pressed(KEY_ESCAPE)){
            game.stop();
        }    
        if(game.key_pressed(KEY_UP)||game.key_held(KEY_UP)){
            player_paddle.move_up(15);
        }
        if(game.key_pressed(KEY_DOWN)||game.key_held(KEY_DOWN)){
            player_paddle.move_down(15);
        }

        ball.update();

            if(ball.vx>0){
                if((cpu_paddle.y+60)<(ball.y+10-40)){
                    cpu_paddle.move_up(4);
                }
                else if((cpu_paddle.y+60)>(ball.y+10+40)){
                    cpu_paddle.move_down(4);
                }
        }    

        collision(ball,player_paddle, cpu_paddle, boing);
        
        if(collision(ball)){
            ball.vy = -1* ball.vy;
        }
        if(ball.x<-200){
            player_lives -=1;
            if(player_lives == 2){
                p1l1->move(0,-1000);
                ball.reset();
            }
            else if(player_lives == 1){
                p1l2->move(0,-1000);
                ball.reset();

            }
            else if(player_lives == 0){
                p1l3->move(0,-1000);
                hop::TextBox title(540,600,4,hop::RED,"GAME OVER!");
            }
        }
      if(ball.x>2100){
            cpu_lives -=1;
            if(cpu_lives == 2){
                cl1->move(0,-1000);
                ball.reset();
            }
            else if(cpu_lives == 1){
                cl2->move(0,-1000);
                ball.reset();

            }
            else if(cpu_lives == 0){
                cl3->move(0,-1000);
                hop::TextBox title(560,600,4,hop::RED,"You WIN!");
            }
        }
    }

    return 0;
}
