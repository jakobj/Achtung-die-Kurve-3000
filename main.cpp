#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <iostream>

//myincludes

//###############testedit

//contains the dot class
#include "dot.h"
//contains basic function like drawing grapics and loading images
//contains information about the scren we want to set up
#include "basic.h"
//contains the timer class which is used to measure/fix the framerate
#include "timer.h"

int main(int argc,char* args[]){
  //the screen where everything else is drawn on
  SDL_Surface* screen;
  //eventcontainer used to handle inputs
  SDL_Event event;
  //if the user requested to quit the program
  bool quit=false;
  //initialize SDL, if it fails, quit
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
    return 1;
  }
  //set up the screen, parameter are defined in basic.h
  screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,
                            SDL_SWSURFACE);
  //set window caption
  SDL_WM_SetCaption("Move that dot!",NULL);
  //fill the screen white
  SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0xFF,
                                                    0xFF,0xFF));
  //create a dotclass member
  Dot myDot;
  //whether to cap the framerate
  bool cap = true;
  //these timers are used to measure/fix framerate
  Timer fps;
  Timer update;
  int frame;
  //start them both upon starting the program
  //the update timer isnt used at the moment
  //fps.start();
  update.start();
  //loop this until the user requests to quit the program
  while(quit == false){
    fps.start();
    //loop through captured events
    while(SDL_PollEvent(&event)){
      //let dotclass handle the events
      myDot.handle_input(event);
      //if the user wants to exit, set quit to true, such that the loop ends
      if(event.type == SDL_QUIT){
        quit = true;
      }
    }
    //move the dot to new positions depending on old postition and velocity
    myDot.move();
    //draw the whole screen white otherwise the dot image leaves a trail
    //since its old positions dont get deleted
    //(which is kind off what we want in the end!)
    SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0xFF,
                                                        0xFF,0xFF));

    //###########ignore this part for the moment###############
      /*      if(keystates[SDLK_UP]){
        apply_surface((SCREEN_WIDTH-upMessage->w)/2,
                      (SCREEN_HEIGHT/2-upMessage->h)/2,upMessage,screen);
      }
      if(keystates[SDLK_DOWN]){
        apply_surface((SCREEN_WIDTH-downMessage->w)/2,
                      (SCREEN_HEIGHT/2-downMessage->h)/2+SCREEN_HEIGHT/2,
                      downMessage,screen);
      }
      if(keystates[SDLK_LEFT]){
        apply_surface((SCREEN_WIDTH/2-leftMessage->w)/2,
                      (SCREEN_HEIGHT-leftMessage->h)/2,leftMessage,screen);
      }
      if(keystates[SDLK_RIGHT]){
        apply_surface((SCREEN_WIDTH/2-rightMessage->w)/2+SCREEN_WIDTH/2,
                      (SCREEN_HEIGHT-rightMessage->h)/2,rightMessage,screen);
                      }*/
    //#############unignore###################################

    //paint the dot at its new positions on the screen
    myDot.show(screen);
    //redraw the screen so that all changes get visible
    SDL_Flip(screen);
    //#######next line is not used at the moment
    //frame++;
    //this caps the framerate to FRAMES_PER_SECOND so that it runs at the same
    //speed on every computer
    if((cap=true) && (fps.get_ticks() < 1000 / FRAMES_PER_SECOND)){
      SDL_Delay((1000/FRAMES_PER_SECOND)-fps.get_ticks());
    }
  }
  //before quitting call SDL_Quit() to let the SDL library exit and clean up
  //properly
  SDL_Quit();
  //return without errorcode if the program made it until here
  return 0;
}
