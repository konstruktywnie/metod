#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_events.h>
#include <vector>
#include <cstdarg>
//#include<math.h>
//#include<cstring>
//#include<stdio.h>
//#include<stdlib.h>

using namespace std;

/* default SDL surface struct: 
  w (surface width)
  h (surface height)
  pixels (pointer to _PIXEL)
  format (pixel format)
*/
typedef SDL_Surface _SURFACE;
typedef SDL_PixelFormat _PIXEL_FORMAT;
typedef Uint32 uint32;
typedef Uint8 uint8;
//typedef Uint32 _FLAG32;
//typedef Uint8 _FLAG8;
typedef Uint32 _PIXEL;
typedef Uint32 _COLOR;
typedef Uint32 _SIZE;
typedef SDL_Rect _RECTANGLE;

_SURFACE* _CREATE_RGBA_SURFACE( _SIZE tileWidth, _SIZE tileHeight );
_SURFACE* _CREATE_RGBA_SURFACE( _SIZE tileWidth, _SIZE tileHeight, _COLOR c );
//_SURFACE* _CONVERT_SURFACE( _SURFACE* destination );
inline _SURFACE* _LOAD_IMG( char* f ) {
  return IMG_Load( f );
}
/*inline _PIXEL_FORMAT* _GET_PIXEL_FORMAT( _SURFACE* s ) {
  return s->format;
}*/
inline void _UPDATE_SURFACE( _SURFACE* s, uint32 x, uint32 y, uint32 w, uint32 h ) {
  SDL_UpdateRect( s, x, y, w, h );
}
inline void _SURFACE_SET_ALPHA( _SURFACE* s ) {
  SDL_SetAlpha( s, SDL_SRCALPHA, SDL_ALPHA_OPAQUE );
}
inline void _SURFACE_SET_ZALPHA( _SURFACE* s ) {
  SDL_SetAlpha( s, 0, SDL_ALPHA_OPAQUE );
}
inline void _SURFACE_BLIT( _SURFACE* src, _RECTANGLE* srcRect, _SURFACE* dst, _RECTANGLE* dstRect )
{
  SDL_BlitSurface( src, srcRect, dst, dstRect );
}
inline void _SURFACE_COPY( _SURFACE* src, _SURFACE* dst ) {
  _SURFACE_BLIT( src, NULL, dst, NULL );
}
inline void _APPLY_SURFACE( uint32 x, uint32 y, _SURFACE* source, _SURFACE* destination ){
  _RECTANGLE offset;
  offset.x = x;
  offset.y = y;
  _SURFACE_SET_ALPHA( source );
  _SURFACE_BLIT( source, NULL, destination, &offset );
}
inline void _FREE_SURFACE( _SURFACE* s ) {
  SDL_FreeSurface( s );
}
inline void _FILL_RECT( _SURFACE* s, _RECTANGLE* clear, _COLOR color ) {
  SDL_FillRect( s, clear, color );
}
inline void _CLEAR_SURFACE( uint32 x, uint32 y, uint32 w, uint32 h, _SURFACE* s, _COLOR color ) {
  _RECTANGLE clear;
  clear.x = x;
  clear.y = y;
  clear.w = w;
  clear.h = h;
  _FILL_RECT( s, &clear, color );
}
