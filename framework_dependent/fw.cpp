#include "fw.h"
#include "..\config.h"

_SURFACE* _CREATE_RGBA_SURFACE( _SIZE tileWidth, _SIZE tileHeight ) {
  return SDL_CreateRGBSurface( SURFACE_TYPE, tileWidth, tileHeight, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );
}

/*
extern _SURFACE* MainScreen;
_SURFACE* _CONVERT_SURFACE( _SURFACE* destination ) { 
  return SDL_ConvertSurface( destination, MainScreen->format, 0 );
}*/
