#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_events.h>
#include<vector>
//#include<math.h>
//#include<cstring>
//#include<stdio.h>
//#include<stdlib.h>

using namespace std;

typedef unsigned char uchar;
typedef SDL_Surface _SURFACE;
//typedef Uint32 _FLAG32;
//typedef Uint8 _FLAG8;
typedef Uint32 _PIXEL;
typedef Uint32 _COLOR;
typedef SDL_Rect _RECTANGLE;

inline void _SURFACE_SET_ALPHA( _SURFACE* s ) {
  SDL_SetAlpha( s, SDL_SRCALPHA, SDL_ALPHA_OPAQUE );
}
inline void _SURFACE_BLIT( _SURFACE* src, _RECTANGLE* srcRect, _SURFACE* dst, _RECTANGLE* dstRect )
{
  SDL_BlitSurface( src, srcRect, dst, dstRect );
}
inline void _FILL_RECT( _SURFACE* s, _RECTANGLE* clear, _COLOR color ) {
  SDL_FillRect( s, clear, color );
}

inline void _APPLY_SURFACE( Uint32 x, Uint32 y, _SURFACE* source, _SURFACE* destination ){
  _RECTANGLE offset;
  offset.x = x;
  offset.y = y;
  _SURFACE_SET_ALPHA( source );
  _SURFACE_BLIT( source, NULL, destination, &offset );
}

inline void _CLEAR_SURFACE( Uint32 x, Uint32 y, Uint32 w, Uint32 h, _SURFACE* s, _COLOR color ) {
  _RECTANGLE clear;
  clear.x = x;
  clear.y = y;
  clear.w = w;
  clear.h = h;
  _FILL_RECT( s, &clear, color );
}
