//####################################################################
//# dot.h
//# This file contains the dot class. This class is the thin that you
//# can move arround on the screen. it contains functions to handle
//# events, paint the dot on the screen and update its postion.
//####################################################################

#ifndef DOT_H
#define DOT_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>
#include <stdlib.h>
//#include <time.h>
#include <string>


#define sqr(x) ((x)*(x))
#define sin_d(x) (sin((x)*M_PI/180))
#define cos_d(x) (cos((x)*M_PI/180))
#define tan_d(x) (tan((x)*M_PI/180))
#define asin_d(x) (asin(x)*180/M_PI)
#define acos_d(x) (acos(x)*180/M_PI)
#define atan_d(x) (atan(x)*180/M_PI)

//myincludes
#include "basic.h"

//define the size of the dot on the screen
//IMPORTANT: this does not define the size of the image, but the size of
//the container which the program counts as belonging to the dot.
const int DOT_HEIGHT = 1;
const int DOT_WIDTH = 1;

class Dot{														
  public:
  //its position
  float x,y;
  //its velocity
    float xvel,yvel;
  // angle of velocity vector
  int phi;
  // radius of velocity vector
  int r;
  // its status (alive=1 equals dead)
  int alive;
  // array contaning the path of the dot
  int path_array[5000][2];
  //the surface which is the basic object of the dot
  SDL_Surface* dot;
  //rectangle defines area of the dot
  SDL_Rect rect;
  //clip is used to define color of the dot by loading the specific area of the
  //dotimage file
  SDL_Rect clip;
  //constructor
  Dot();
  //destructor
  //~Dot();
  //handle the inputs the program gets and passes to the dot object
  //void handle_input(SDL_Event);
  //update the position of the dot
  void move();
  //draw the dot onto the surface which is passed to the function
  void show(SDL_Surface*);
  //stores the actual position
  void store_path(int);
  // check if actual position collides with old ones
  void check_collision(int*,int*,int);
  //set the color of the dot by loading the appropiate image
  void setcolor(std::string);
};

//initialize the object,set random start values and load the image which shows the
//position of the dot
Dot::Dot(){
 x=rand()%640;
  y=200;
  alive=0;
  xvel=9;
  yvel=0;
  phi=0;
  dot = load_image("./dots.png");
  rect.h=DOT_HEIGHT;
  rect.w=DOT_WIDTH;
  clip.x=0;
  clip.w=5;
  clip.h=5;
 }

void Dot::store_path(int i){
  path_array[i][0]=floor(x);
  path_array[i][1]=floor(y);
}

void Dot::check_collision(int *path1,int *path2,int i){						
    
    int fx=floor(x);
    int fy=floor(y);
    int k=0;
    for(k=0;k<i;k++){
      if(fx==*(path1+k) && fy==*(path1+k+1)){alive=1;}
    }
    k=0;
    for(k=0;k<i;k++){
      if(fx==*(path2+k) && fy==*(path2+k+1)){alive=1;}
    }
}

//Dot::~Dot(){}

//handle input given be event
/*void Dot::handle_input(SDL_Event event){
  //check whether it is a keydown event, otherwise do nothing
  if(event.type == SDL_KEYDOWN){
    //if its a keydown, react to different inputs by adjusting velocity
    switch(event.key.keysym.sym){
    case SDLK_LEFT: phi -= 20; break;
    case SDLK_RIGHT: phi += 20; break;
    }
  }
  }*/

//update the position of the dot according to the current velocity
void Dot::move(){
  if(alive==0){
    r=1;
    x+=r*cos_d(phi);
    y+=r*sin_d(phi);
  }
}

//paint the dot onto the screen with the given offsets
void Dot::show(SDL_Surface* screen){
  rect.x = x;
  rect.y = y;
  //fill the rect just to mark its position on the screen
  SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,0x00,
                                      0xFF,0x00));
  //substract 2 from x,y so that these coordinates point
  //to the midpoint of the image
  apply_surface(x-2,y-2,dot,screen,&clip);
}

void Dot::setcolor(std::string color){
  if(color == "green"){
    clip.y=0;
  }
  if(color == "red"){
    clip.y=5;
  }
  if(color == "blue"){
    clip.y=10;
  }
  if(color == "yellow"){
    clip.y=15;
  }
}

#endif
