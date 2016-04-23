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
typedef Uint8 _FLAG8;
typedef uint32 _PIXEL;
typedef uint32 _COLOR;
typedef uint32 _SIZE;
typedef uint32 _POS;
typedef uint32 _INDEX;
typedef uint32 _TIME;
typedef char _CHAR;
typedef int _INT;
typedef unsigned int _UINT;
typedef SDL_Rect _RECTANGLE;
typedef SDL_NewTimerCallback _TIMER_CALLBACK;
typedef SDL_TimerID _TIMER_ID;
typedef SDL_Event _EVENT;
#define MAX_LINE 255

extern _SURFACE* MainScreen;

_SURFACE* _CREATE_RGBA_SURFACE( _SIZE tileWidth, _SIZE tileHeight );
_SURFACE* _CREATE_RGBA_SURFACE( _SIZE tileWidth, _SIZE tileHeight, _COLOR c );
//_SURFACE* _CONVERT_SURFACE( _SURFACE* destination );
_CHAR* _LOAD_FILE( _CHAR* file );
inline void _APPLY_ON_DISPLAY( _SURFACE* source, _RECTANGLE* s, _RECTANGLE* d )
{
  //SDL_SetAlpha( source, SDL_SRCALPHA, SDL_ALPHA_OPAQUE );
  SDL_BlitSurface( source, s, MainScreen, d );

}
inline void _UPDATE_DISPLAY( _RECTANGLE* r )
{
  SDL_UpdateRect( MainScreen, r->x, r->y, r->w, r->h );
}

inline _SURFACE* _LOAD_IMG( _CHAR* f ) {
  return IMG_Load( f );
}
/*inline _PIXEL_FORMAT* _GET_PIXEL_FORMAT( _SURFACE* s ) {
  return s->format;
}*/
inline void _UPDATE_SURFACE( _SURFACE* s, _POS x, _POS y, _SIZE w, _SIZE h ) {
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
inline void _APPLY_SURFACE( _POS x, _POS y, _SURFACE* source, _SURFACE* destination ){
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

inline void _PUSH_EVENT( void* data, _INT event_code ) {
  SDL_Event event;
  event.type = SDL_USEREVENT;
  event.user.code = event_code;
  event.user.data1 = data;
  event.user.data2 = 0;
  SDL_PushEvent( &event );
}

inline _TIMER_ID _ADD_TIMER( _TIME interval, _TIMER_CALLBACK callback, void* param )
{
  //_TIMER_ID t = SDL_AddTimer( interval, callback, param );
  //if( !t ) fprintf( stderr, "Error: Can not start timer\n" );
  return SDL_AddTimer( interval, callback, param );
}
inline void _REMOVE_TIMER( _TIMER_ID id )
{
  if( !SDL_RemoveTimer( id ) ) {
    fprintf( stderr, "Error: Can not remove timer\n" );
  }
}
