//####################################################################
//# basic.h
//# This file will contain all functions which dont really belong to
//# any particular part of the program and are used in many different
//# places. most of the are only introduced to make the rest of the
//# code shorter and more readable.
//# In addition the basic setup for the screen is defined.
//####################################################################

#ifndef BASIC_H
#define BASIC_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string>

//set constants for the screen
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32; //(Bit Per Pixel)
const int FRAMES_PER_SECOND = 60;

//this function loads the image which is passed via filename in an optimized
//version for the screen.
//it is using IMG_Load from the SDL_image library to load
//images different from .bmp (SDL usually only has a function SDL_LoadBMP
//the function returns a pointer to the optimized image
SDL_Surface *load_image(std::string filename){
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;
  //first load the image in the regular way
  loadedImage = IMG_Load(filename.c_str());
  //if this was successfull
  if(loadedImage != NULL){
    //call the optimization and set optimized image to the result
    optimizedImage=SDL_DisplayFormat(loadedImage);
    //colorkey is the color which is ignored in the final image
    //e.g. if we have a black dot on a white background we would have
    //0xFF,0xFF,0xFF in SDL_MapRGB
    Uint32 colorkey = SDL_MapRGB(optimizedImage->format,0,0xFF,0xFF);
    //now we set the colorkey for the image
    SDL_SetColorKey(optimizedImage,SDL_SRCCOLORKEY,colorkey);
    //finally we have to free the old image since it is not used anymore
    //(if we dont do this it stays in the memory until the computer gets
    //restarded)
    SDL_FreeSurface(loadedImage);
  }
  return optimizedImage;
}

//paints source surface onto dest surface with a given offset
//optionally we can pass a clipping area, but we prbly wont use that
void apply_surface(int x,int y,SDL_Surface *source,SDL_Surface *dest,
                   SDL_Rect *clip = NULL){
  //create an offset container to store the x,y values in
  SDL_Rect offset;
  offset.x=x;
  offset.y=y;
  //paint the source onto dest with this offset
  SDL_BlitSurface(source,clip,dest,&offset);
}

void print_message(std::string msg,SDL_Surface* screen,int x,int y,int size=20){
  TTF_Font* font=TTF_OpenFont("./adkfont.ttf",size);
  SDL_Surface* message = NULL;
  SDL_Color textcolor={0,0,0};
  message = TTF_RenderText_Solid(font,msg.c_str(),textcolor);
  apply_surface(x,y,message,screen);
}
#endif
