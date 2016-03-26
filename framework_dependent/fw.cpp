#include "fw.h"
#include "..\config.h"

extern _SURFACE* MainScreen;

_SURFACE* _CREATE_RGBA_SURFACE( _SIZE tileWidth, _SIZE tileHeight ) {
  return SDL_CreateRGBSurface( SURFACE_TYPE, tileWidth, tileHeight, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );
}
_SURFACE* _CREATE_RGBA_SURFACE( _SIZE tileWidth, _SIZE tileHeight, _COLOR c ) {
  _SURFACE* s = _CREATE_RGBA_SURFACE( tileWidth, tileHeight );
  _FILL_RECT( s, NULL, c );
  //_SURFACE_SET_ALPHA( s );
  return s;
}
