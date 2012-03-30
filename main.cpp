#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>


//contains the dot class
#include "dot.h"
//contains basic function like drawing grapics and loading images
//contains information about the scren we want to set up
#include "basic.h"
//contains the timer class which is used to measure/fix the framerate
#include "timer.h"
//contains the startscreen with keyselection
//#include "startscreen.h"
//contains the player class
#include "player.h"

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
  //initialize TTF
  if(TTF_Init() == -1){
    return 1;
  }
  //set up the screen, parameter are defined in basic.h
  screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,
                            SDL_SWSURFACE);
  //set window caption
  SDL_WM_SetCaption("Achtung die Kurve 3000",NULL);
  //fill the screen white
  SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0xFF,
                                                    0xFF,0xFF));
  //game is not started
  bool game = false;
  //load font
  TTF_Font* font = NULL;
  font = TTF_OpenFont("./adkfont.ttf",20);
  if(font == NULL){
    printf("Error:main.cpp:could not load font.\n");
    return 1;
  }
  //startscreen basic setup
  SDL_Surface* background = NULL;
  background = load_image("./background.png");
  if(background == NULL){
    printf("Error:main.cpp:could not load background image.\n");
  }

  //this vector holds all players (in the future ;) )
  //  std::vector<Player> player;
  Player player1("red");
  player1.id=1;
  Player player2("green");
  player2.id=2;
  //rect that defines the playing field
  SDL_Rect field;
  field.x=0;
  field.y=0;
  field.h=SCREEN_HEIGHT;
  field.w=SCREEN_HEIGHT;
  //seperates field from the other part
  SDL_Rect sep;
  sep.x=field.w;
  sep.y=0;
  sep.w=8;
  sep.h=SCREEN_HEIGHT;
  //display of statistics and stuff
  SDL_Rect stat;
  stat.x=field.w+sep.w;
  stat.y=0;
  stat.w=SCREEN_WIDTH-field.w-sep.w;
  stat.h=SCREEN_HEIGHT;
  //to pause the game press space
  bool pause = false;
  //whether to cap the framerate
  bool cap = true;
  //these timers are used to measure/fix framerate
  Timer fps;
  Timer update;
  int frame;
  //start them both upon starting the program
  //the update timer isnt used at the moment
  //used with collision detection
  int i;
  //update.start();

  //loop this until the user requests to quit the program
  while(quit == false){
    if(game == true){
      fps.start();
      //loop through captured events
      while(SDL_PollEvent(&event)){
        //if the user wants to exit, set quit to true, such that the loop ends
        if(event.type == SDL_QUIT){
          quit = true;
        }
        if(event.type == SDL_KEYDOWN){
          if(event.key.keysym.sym == SDLK_ESCAPE){
            game = false;
          }
          if(event.key.keysym.sym == SDLK_SPACE){
            if(pause == false){
              print_message("PAUSED",screen,150,240,100);
              pause = true;
            }
            else{
              pause = false;
            }
          }
          if(event.key.keysym.sym == SDLK_u){
            player1.changepoints(1);
          }
          if(event.key.keysym.sym == SDLK_o){
            player2.changepoints(1);
          }
        }
      }
      if(pause == false){
        if(player1.is_set() == true){
          player1.handleinput();
        }
        if(player2.is_set() == true){
          player2.handleinput();
        }
        //store path for collision detection
        player1.dot.store_path(i);
        player2.dot.store_path(i);
        //move the dot to new positions depending on old postition and velocity
        player1.dot.move();
        player2.dot.move();
        //check whether a collision happened
        //player1.dot.check_collision(&player1.dot.path_array[0][0],
        //                     &player2.dot.path_array[0][0],i);
        //draw the whole screen white otherwise the dot image leaves a trail
        //since its old positions dont get deleted
        //(which is kind off what we want in the end!)
        SDL_FillRect(screen,&field,SDL_MapRGB(screen->format,0xFF,
                                              0xFF,0xFF));
        SDL_FillRect(screen,&sep,SDL_MapRGB(screen->format,0x00,
                                            0x00,0x00));
        //        SDL_FillRect(screen,&stat,SDL_MapRGB(screen->format,0xFF,0xFF,0x00));
        //display points of players
        player1.displaypoints(screen,stat.x+stat.w);
        player2.displaypoints(screen,stat.x+stat.w);
        //paint the dot at its new positions on the screen
        player1.dot.show(screen);
        player2.dot.show(screen);
        //#######next line is not used at the moment
        //frame++;
      }
    }
    else if (game == false){
      while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
          quit = true;
        }
        apply_surface(0,0,background,screen);
        print_message("Achtung die Kurve 3000",screen,30,30,60);
        print_message("Select player and keys",screen,50,100,40);
        print_message("Press 1 or 2 to select player, SPACE to start",
                      screen,55,170,30);
        if(event.type == SDL_KEYDOWN){
          if(event.key.keysym.sym == SDLK_1){
            player1.setup(screen);
          }
          if(event.key.keysym.sym == SDLK_2){
            player2.setup(screen);
          }
          if(event.key.keysym.sym == SDLK_SPACE){
            game = true;
            SDL_FillRect(screen,&field,SDL_MapRGB(screen->format,0xFF,
                                                  0xFF,0xFF));
            SDL_FillRect(screen,&sep,SDL_MapRGB(screen->format,0x00,
                                                0x00,0x00));
            SDL_FillRect(screen,&stat,SDL_MapRGB(screen->format,0xFF,0xFF,0x00));
          }
        }
        //display settings for the players
        player1.displaysettings(screen);
        player2.displaysettings(screen);
      }
    }
    SDL_Flip(screen);
    //this caps the framerate to FRAMES_PER_SECOND so that it runs at the same
    //speed on every computer
    if((cap=true) && (fps.get_ticks() < 1000 / FRAMES_PER_SECOND)){
      SDL_Delay((1000/FRAMES_PER_SECOND)-fps.get_ticks());
    }
    
    //count cycles
    i++;
  }
  //before quitting call SDL_Quit() to let the SDL library exit and clean up
  //properly
  SDL_Quit();
  //return without errorcode if the program made it until here
  return 0;
}
