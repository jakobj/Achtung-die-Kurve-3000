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
#include <time.h>


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
const int DOT_HEIGHT = 15;
const int DOT_WIDTH = 15;

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
  //constructor
  Dot();
  //destructor
  //~Dot();
  //handle the inputs the program gets and passes to the dot object
  void handle_input(SDL_Event);
  //update the position of the dot
  void move();
  //draw the dot onto the surface which is passed to the function
  void show(SDL_Surface*);
  
  //stores the actual position
  void store_path(int);
  // check if actual position collides with old ones
  void check_collision(int*,int*,int);
  
  
};

//initialize the object,set random start values and load the image which shows the
//position of the dot

Dot::Dot(){
 x=rand()%640;
  y=200;
  alive=0;
  xvel=5;
  yvel=0;
  phi=0;
  dot = load_image("./dot.png");
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
    if(fx==*(path1+k) && fy==*(path1+k+1)){alive=1;}};
    k=0;
    for(k=0;k<i;k++){
    if(fx==*(path2+k) && fy==*(path2+k+1)){alive=1;}};
  
}



//Dot::~Dot(){}

//handle input given be event
void Dot::handle_input(SDL_Event event){
  //check whether it is a keydown event, otherwise do nothing
  if(event.type == SDL_KEYDOWN){
    //if its a keydown, react to different inputs by adjusting velocity
    switch(event.key.keysym.sym){
    case SDLK_LEFT: phi -= 20; break;
    case SDLK_RIGHT: phi += 20; break;
    }
}
  //###################ignore this part##############
  /*else if (event.type == SDL_KEYUP){
    switch(event.key.keysym.sym){
    case SDLK_UP: yvel+=DOT_HEIGHT/2; break;
    case SDLK_DOWN: yvel-=DOT_HEIGHT/2; break;
    case SDLK_LEFT: xvel+=DOT_WIDTH/2; break;
    case SDLK_RIGHT: xvel-=DOT_WIDTH/2; break;
    }
    }*/
  //###############unignore##########################
}

//update the position of the dot according to the current velocity
void Dot::move(){
  if(alive==0){
    r=1;
    x+=r*cos_d(phi);
    y+=r*sin_d(phi);
  }
  //###############ignore this part##################
  /*if((x<0) || (x+DOT_WIDTH > SCREEN_WIDTH)){
    xvel=-xvel;
  }
  if((y<0) || (y-DOT_HEIGHT > SCREEN_HEIGHT)){
    yvel=-yvel;
  }*/
  //################unignore#########################
}

//paint the dot onto the screen with the given offsets
void Dot::show(SDL_Surface* screen){
  apply_surface(x,y,dot,screen,NULL);
}
#endif
