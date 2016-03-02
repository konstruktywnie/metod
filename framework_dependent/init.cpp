#include "fw.h"
#include "../config.h"

extern _SURFACE* MainScreen;

void _FRAMEWORK_INIT() {
  SDL_putenv( "SDL_VIDEO_CENTERED=center" );
  SDL_Init( SDL_INIT_VIDEO );
  MainScreen = SDL_SetVideoMode( SCREEN_RESOLUTION_W, SCREEN_RESOLUTION_H, 32, SURFACE_TYPE );  
  SDL_WM_SetCaption( TITLE_TEXT, NULL );
  SDL_ShowCursor( SDL_DISABLE );

  for ( int i = 0; i < SDL_NUMEVENTS; i++ )
    if ( i != SDL_USEREVENT && i != SDL_KEYDOWN && i != SDL_QUIT )
      SDL_EventState( i, SDL_IGNORE );
}
