//####################################################################
//# timer.h
//# this file contains the timer class which is manly used for fixing
//# the framerate (and therefore the speed of the program).
//# the timer has basic features like start,stop,pause and functions
//# to display its time(ticks) and status
//#
//# TODO: -add functions to return its status
//####################################################################

#ifndef TIMER_H
#define TIMER_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "basic.h"

class Timer{
 private:
  //stores the time when it was started
  int startticks;
  //stores the time when it was stopped
  int pausedticks;
  //paused?started? (status)
  bool paused;
  bool started;
 public:
  //constructor
  Timer();
  //destructor
  ~Timer();
  //start the timer
  void start();
  //stop the timer
  void stop();
  //pause the timer
  void pause();
  //let it continue
  void unpause();
  //returns the ticks since it was started
  int get_ticks();
  //returns the status
  bool is_started();
  bool is_paused();
};

//initialize the timer with default values
Timer::Timer(){
  startticks=0;
  pausedticks=0;
  paused = false;
  started = false;
}

//destroy the timer
Timer::~Timer(){}

void Timer::start(){
  //use the SDL_GetTicks function to measure time
  startticks=SDL_GetTicks();
  started=true;
  paused=false;
}

void Timer::stop(){
  started=false;
  paused=false;
}  

//returns the current ticks (ticks=milliseconds(?))
int Timer::get_ticks(){
  //check if its running
  if(started == true){
    //if paused return the ticks it had when it was paused
    if(paused == true) return pausedticks;
    //otherwise return the time its running by substracting the time when it
    //was started from the current time
    else return SDL_GetTicks()-startticks;
  }
  //if its stopped just return 0
  return 0;
}

void Timer::pause(){
  //check whether is makes sence to pause
  if(started == true && paused == false){
    //if so, update status and store the time it ran until now in pausedticks
    paused=true;
    pausedticks=SDL_GetTicks()-startticks;
  }
}

void Timer::unpause(){
  //check whether it makes sence to unpause
  if(started == true && paused == true){
    //if so update status and substract from current time the time at 
    //which it was paused, after that reset pausedticks
    paused=false;
    startticks=SDL_GetTicks()-pausedticks;
    pausedticks=0;
  }
}
#endif
