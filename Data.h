#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>
#include <unistd.h>
#include <string.h>


/* Size of the window */
#define SCREEN_WIDTH  600
#define SCREEN_HEIGTH 600

/* Sprite */
#define SPRITE_SIZE 32
#define DIR_UP      0
#define DIR_RIGHT   1
#define DIR_DOWN    2
#define DIR_LEFT    3

#define SPRITE_STEP 5

/* Structures */

struct Sprite_t{
  int col;
  int lig;
  int size;
  int current;
  int anim_flip;
  SDL_Rect position;
  SDL_Rect image;
  SDL_Surface *sprite_picture;
};

typedef struct Sprite_t sprite_t

