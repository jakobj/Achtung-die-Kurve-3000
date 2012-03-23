#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <SDL/SDL.h>

#include "basic.h"

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
  //Snake plsnake;
  //vector<Powerup> plpowerup;
 public:
  Player();
  ~Player();
  void change_points(int);
  int get_points();
  void handleinput(SDL_Event);
  void setup(SDL_Surface*,SDL_Event);
  bool is_set();
  //void addpowerup(Powerup);
};

Player::Player(){
  points = 0;
  keyright_set = false;
  keyleft_set = false;
  keyfire_set = false;
}

Player::~Player(){}

void Player::setup(SDL_Surface* screen,SDL_Event event){
  printf("setting up first player!\n");
  std::string buff;
  buff.clear();
  SDL_EnableUNICODE(SDL_ENABLE);
  if(keyleft_set == false){
    print_message("Select \'Left\' key",screen,340,240,{0,255,0},60);
    if(event.key.keysym.sym != SDLK_1 && event.key.keysym.sym != SDLK_2){
      keyleft = event.key.keysym.sym;
      keyleft_set = true;
      buff=(char)event.key.keysym.unicode;
      keyleft_c=buff[0];
    }
  }
  else if(keyright_set == false){
    print_message("Select \'Right\' key",screen,340,240,{0,255,0},60);
    if(event.key.keysym.sym != SDLK_1 && event.key.keysym.sym != SDLK_2){
      keyright = event.key.keysym.sym;
      keyright_set = true;
      buff=(char)event.key.keysym.unicode;
      keyright_c=buff[0];
    }
  }
  else if(keyfire_set == false){
    print_message("Select \'Fire\' key",screen,340,240,{0,255,0},60);
    if(event.key.keysym.sym != SDLK_1 && event.key.keysym.sym != SDLK_2){
      keyfire = event.key.keysym.sym;
      keyfire_set = true;
      buff=(char)event.key.keysym.unicode;
      keyfire_c=buff[0];
    }
  }
}

bool Player::is_set(){
  if(keyright_set && keyleft_set && keyfire_set){
    return true;
  }
  else{
    return false;
  }
}

#endif
