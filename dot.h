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

//myincludes
#include "basic.h"

//define the size of the dot on the screen
//IMPORTANT: this does not define the size of the image, but the size of
//the container which the program counts as belonging to the dot.
const int DOT_HEIGHT = 5;
const int DOT_WIDTH = 5;

class Dot{
 private:
  //its position
  int x,y;
  //its velocity
  //  int xvel,yvel;
  //the surface which is the basic object of the dot
  SDL_Surface* dot;
 public:
  //constructor
  Dot();
  //destructor
  //~Dot();
  float xvel,yvel;
  //handle the inputs the program gets and passes to the dot object
  void handle_input(SDL_Event);
  //update the position of the dot
  void move();
  //draw the dot onto the surface which is passed to the function
  void show(SDL_Surface*);
};

//initialize the class,set default values and load the image which shows the
//position of the dot
Dot::Dot(){
  x=0;
  y=0;
  xvel=0;
  yvel=0;
  dot = load_image("./dot.png");
}

//Dot::~Dot(){}

//handle input given be event
void Dot::handle_input(SDL_Event event){
  //check whether it is a keydown event, otherwise do nothing
  if(event.type == SDL_KEYDOWN){
    //if its a keydown, react to different inputs by adjusting velocity
    switch(event.key.keysym.sym){
    case SDLK_UP: yvel-=DOT_HEIGHT/2; break;
    case SDLK_DOWN: yvel+=DOT_HEIGHT/2; break;
    case SDLK_LEFT: xvel-=DOT_WIDTH/2; break;
    case SDLK_RIGHT: xvel+=DOT_WIDTH/2; break;
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
  x+=xvel;
  y+=yvel;
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
