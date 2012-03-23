#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <SDL/SDL.h>

class player{
 private:
  int points;
  SDLKey keyright;
  SDLKey keyleft;
  SDLKey keyfire;
  //Snake plsnake;
  //vector<Powerup> plpowerup;
 public:
  player();
  ~player();
  void change_points(int);
  int get_points();
  void handleinput(SDL_Event);
  //void addpowerup(Powerup);
};

#endif
