#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <SDL/SDL.h>
#include <iostream>

#include "basic.h"
#include "dot.h"

class Player{
 private:
  int points;
  SDLKey keyright;
  SDLKey keyleft;
  SDLKey keyfire;
  bool keyright_set;
  bool keyleft_set;
  bool keyfire_set;
  char keyleft_c;
  char keyright_c;
  char keyfire_c;
  bool settingup;
  //Snake plsnake;
  //vector<Powerup> plpowerup;
 public:
  Player();
  ~Player();
  int id;
  Dot dot;
  void change_points(int);
  int get_points();
  void handleinput(SDL_Event);
  void setup(SDL_Surface*);
  bool is_set();
  SDLKey getkey(std::string);
  void displaysettings(SDL_Surface*);
  void handleinput();
  //void addpowerup(Powerup);
};

Player::Player(){
  points = 0;
  keyright_set = false;
  keyleft_set = false;
  keyfire_set = false;
}

Player::~Player(){}

void Player::setup(SDL_Surface* screen){
  //enable unicode support, we need it to get the characters from
  //the pressed keys
  SDL_EnableUNICODE(SDL_ENABLE);
  //store the events
  SDL_Event event;
  //this rect is used to paint over the previos instructions
  SDL_Rect rect;
  rect.x=320;
  rect.y=220;
  rect.h=100;
  rect.w=470;
  //disable mouse motion and keyup events since otherwise the count to SDL_WaitEvent
  SDL_EventState(SDL_MOUSEMOTION,SDL_DISABLE);
  SDL_EventState(SDL_KEYUP,SDL_DISABLE);
  //show what to do
  print_message("Select \'Left\' key",screen,340,240,60);
  //update screen and wait for userinput
  SDL_Flip(screen);
  SDL_WaitEvent(&event);
  //ignore settings which are blocked by player selection
  if(event.key.keysym.sym != SDLK_1 && event.key.keysym.sym != SDLK_2){
    //if valid event, store it
    keyleft = event.key.keysym.sym;
    keyleft_set = true;
    keyleft_c=(char)event.key.keysym.unicode;
  }
  //paint over old message
  SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,0xFF,0xFF,0xFF));
  //set new message
  print_message("Select \'Right\' key",screen,340,240,60);
  //flip and wait
  SDL_Flip(screen);
  SDL_WaitEvent(&event);
  //same as above
  if(event.key.keysym.sym != SDLK_1 && event.key.keysym.sym != SDLK_2){
    keyright = event.key.keysym.sym;
    keyright_set = true;
    keyright_c=(char)event.key.keysym.unicode;
  }
  SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,0xFF,0xFF,0xFF));
  print_message("Select \'Fire\' key",screen,340,240,60);
  SDL_Flip(screen);
  SDL_WaitEvent(&event);
  if(event.key.keysym.sym != SDLK_1 && event.key.keysym.sym != SDLK_2){
    keyfire = event.key.keysym.sym;
    keyfire_set = true;
    keyfire_c=(char)event.key.keysym.unicode;
  }
  //after were done with everything, enable events again
  SDL_EventState(SDL_MOUSEMOTION,SDL_ENABLE);
  SDL_EventState(SDL_KEYUP,SDL_ENABLE);
  //disable unicode use again since we dont need it anymore
  SDL_EnableUNICODE(SDL_DISABLE);
}

//returns true if all keys are properly set up
bool Player::is_set(){
  if(keyright_set && keyleft_set && keyfire_set){
    return true;
  }
  else{
    return false;
  }
}

//return the key assigned to the requested action
SDLKey Player::getkey(std::string dir){
  if(dir == "left"){
    return keyleft;
  }
  if(dir == "right"){
    return keyright;
  }
  if(dir == "fire"){
    return keyfire;
  }
}

//print the settings for the player onto the screen
void Player::displaysettings(SDL_Surface* screen){
  //buff is used to to store values in before writing to screen
  //(conversion issue)
  std::string buff;
  buff.clear();
  //first we want to print the player id,
  //so we need to convert to char
  buff+=(char)((int)'0'+id);
  print_message(buff,screen,40,210+id*40);
  //then print alle the other keys (if they are set)
  if(keyleft_set == true){
    buff.clear();
    buff+=keyleft_c;
    print_message(buff,screen,80,210+id*40);
  }
  if(keyright_set == true){
    buff.clear();
    buff+=keyright_c;
    print_message(buff,screen,110,210+id*40);
  }
  if(keyfire_set == true){
    buff.clear();
    buff+=keyfire_c;
    print_message(buff,screen,140,210+id*40);
  }
}

//handle input
void Player::handleinput(){
  Uint8 *keystates = SDL_GetKeyState(NULL);
  if(keystates[keyleft]){
    dot.phi-=2;
  }
  if(keystates[keyright]){
    dot.phi+=2;
  }
}
#endif
