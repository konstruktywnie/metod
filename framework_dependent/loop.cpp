#include "fw.h"
#include "../events.h"
#include "../resources.h"
#include "../screen.h"
#include "../level.h"
#include "../game.h"
#include "../globals.h"

void _FRAMEWORK_LOOP()
{
  bool run = true;
  SDL_Event* event = new SDL_Event;
  while( run ) {
    if ( SDL_WaitEvent( event ) )
	  switch( event->type )
	  {
	    case SDL_USEREVENT:
		  if( event->user.code == EVENT_TILESET_ANIMATION ) {
		    PEvents[ EVENT_TILESET_ANIMATION ] = true;
		  }
		  attendProgEvents();
		break;
	  }
	  run = false;
  }

}