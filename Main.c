#include "Data.h"

/*controls*/
void Handle_event(SDL_Event event, int* quit, int* anim_flip, sprite_t* player)
{
  switch (event.type)
    {
    case SDL_QUIT:
      *quit = 1;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym)
	{
	case SDLK_ESCAPE:
	case SDLK_q:
	  *quit = 1;
	  break;
	case SDLK_LEFT:
	  *player->current = DIR_LEFT;
	  *player->anim_flip = 1 - *player->anim_flip;
	  player->position.x -= SPRITE_STEP;
	  break;
	case SDLK_RIGHT:
	  *player->current = DIR_RIGHT;
	  *player->anim_flip = 1 - *player->anim_flip;
	  player->psition.x += SPRITE_STEP;
	  break;
	case SDLK_UP:
	  *player->current = DIR_UP;
	  *player->anim_flip;
	  player->position.y -= SPRITE_STEP;
	  break;
	case SDLK_DOWN:
	  *player->current = DIR_DOWN;
	  *player->anim_flip;
	  player->position.y += SPRITE_STEP;
	  break;
	default:
	  break;
	}
      break;
    }
}



int main()
{

}
