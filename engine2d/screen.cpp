#include "../framework_dependent/fw.h"
#include "resources.h"
#include "screen.h"
#include "../config.h"
#include "../level.h"
#include "../game.h"

extern _SURFACE* MainScreen;
extern theGame Game;

theScreen::theScreen() {
  addWindow();
}
void theScreen::addWindow( uint8 nr ) {
  windows.resize( windows.size() + nr );
  while( nr > 0 ) 
    windows[ windows.size() - nr-- ] = new theWindow;
  
}
void theScreen::addWindow() {
  windows.resize( windows.size() + 1 );
  windows[ windows.size() - 1 ] = new theWindow;
}

theWindow::theWindow() {
  winWidth = planesWidth = theScreen::scrWidth;
  winHeight = planesHeight = theScreen::scrHeight;
  winPosX = winPosY = bgPosX = bgPosY = 0;
  
  planes.resize( 1 );
  regularPlanesNR = 1;
}
void theWindow::addPlane() {
  planes.resize( planes.size() + 1 );
  regularPlanesNR++;
}
void theWindow::addPlane( uint8 nr ) {
  planes.resize( planes.size() + nr );
  regularPlanesNR += nr;
}
void theWindow::addFilledPlane() {
  planes.resize( planes.size() + 1 );
  planes[ planes.size() - 1 ] = _CREATE_RGBA_SURFACE( planesWidth, planesHeight, 0 );
  regularPlanesNR++;
}

void theWindow::redrawAllPlanes() {
  _RECTANGLE s;
  s.w = winWidth;
  s.h = winHeight;
  s.x = bgPosX;
  s.y = bgPosY;
  _RECTANGLE d;
  d.w = winWidth;
  d.h = winHeight;
  d.x = winPosX;
  d.y = winPosY;
  for( uint8 i = 0; i < regularPlanesNR; i++ ) {
    _SURFACE_BLIT( planes[ i ], &s, MainScreen, &d );
  }
  _UPDATE_SURFACE( MainScreen, d.x, d.y, d.w, d.h );
}

void theWindow::placeRectangle( uint8 planeNr, uint32 x, uint32 y, uint32 w, uint32 h, _COLOR color )
{
  _SURFACE* rs = _CREATE_RGBA_SURFACE( w, h, color );
  _RECTANGLE offset;
  offset.x = x;
  offset.y = y;
  offset.w = 0;
  offset.h = 0;
  _SURFACE_SET_ALPHA( rs );
  _SURFACE_BLIT( rs, NULL, planes[ planeNr ], &offset );
  _FREE_SURFACE( rs );
}
void theWindow::placeRectangle( uint8 planeNr, uint32 x, uint32 y, uint32 w, uint32 h, _COLOR color, uint8 border, _COLOR bColor )
{
  placeRectangle( planeNr, x, y, w, h, color );
  _SURFACE* s = planes[ planeNr ];
  _PIXEL* pixels = (_PIXEL*)s->pixels;
  uint32 rc = 0;
  for( _SIZE i = y; i < y + h; i++ ) 
  {
    _SIZE sRow = i * s->w;
    uint32 cc = 0;
	for( _SIZE j = x; j < x + w; j++ ) 
	{
	  if( cc < border || rc < border ) pixels[ sRow + j ] = bColor;
	  if( (cc > w - border - 1) || (rc > h - border - 1) ) pixels[ sRow + j ] = bColor;
	  cc++;
	}
    rc++;
  }
}

void theWindow::makeBackground( uint8 planeNr, _SURFACE* image )
{
  _SURFACE* destination = _CREATE_RGBA_SURFACE( planesWidth, planesHeight, OPAQUE_RGBA );
  planes[ planeNr ] = destination;
  if( (planesWidth == image->w && planesHeight == image->h) || (planesWidth == 0 && planesHeight == 0) ) {
    _SURFACE_COPY( image, destination );
  } else 
  {
	_RECTANGLE s, d;
	s.x = d.x = 0;
	s.y = d.y = 0;
	s.w = d.w = planesWidth;
	s.h = d.h = planesHeight;

	if( image->w > planesWidth && image->h > planesHeight ) {
      _SURFACE_BLIT( image, &s, destination, &d );
	}
	if( image->w < planesWidth || image->h < planesHeight ) {
	s.w = image->w;
	s.h = image->h;

	_SIZE mw = planesWidth / image->w + 1;
	_SIZE mh = planesHeight / image->h + 1;
	for( _SIZE i = 0; i < mh; i++ ) {
	  for( _SIZE j = 0; j < mw; j++ ) {
	    _SURFACE_BLIT( image, &s, destination, &d );
		d.x += image->w;
	  }
	  d.y += image->h;
	  d.x = 0;
	}

	}
  }
  
}

uint32 theWindow::print( tileSet* font, uint8 planeNR, uint32 x, uint32 y, const char *fmt, ... )
{
  char buffer[ MAX_LINE ];
  va_list args;
  va_start( args, fmt );
  vsprintf( buffer, fmt, args );
  va_end( args );
  uint32 alphaF = 0;
  _RECTANGLE offset;
  offset.x = x;
  offset.y = y;
  for( uint32 i = 0; buffer[ i ] != 0; i++ ) 
  {
	if( buffer[ i ] == '\n' ) {
	  offset.y += font->tiles[ buffer[ i ] ]->h;
      offset.x = x;
      continue;
    }

	if( planeNR == 0 ) _SURFACE_SET_ALPHA( font->tiles[ buffer[ i ] ] );
	else _SURFACE_SET_ZALPHA( font->tiles[ buffer[ i ] ] );
    _SURFACE_BLIT( font->tiles[ buffer[ i ] ], NULL, planes[ planeNR ], &offset );
    offset.x += font->tiles[ buffer[ i ] ]->w;
  }
  return strlen( buffer );

}