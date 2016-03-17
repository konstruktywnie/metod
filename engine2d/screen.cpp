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
void theScreen::addWindow( _INDEX nr ) {
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
}
void theWindow::addPlane() {
  planes.resize( planes.size() + 1 );
}
void theWindow::addPlane( _INDEX nr ) {
  planes.resize( planes.size() + nr );
}
void theWindow::addFilledPlane() {
  planes.resize( planes.size() + 1 );
  planes[ planes.size() - 1 ] = _CREATE_RGBA_SURFACE( planesWidth, planesHeight, 0 );
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
  _SIZE allP = planes.size();
  for( _SIZE i = 0; i < allP; i++ ) {
    _SURFACE_BLIT( planes[ i ], &s, MainScreen, &d );
  }
  _UPDATE_SURFACE( MainScreen, d.x, d.y, d.w, d.h );
}

void theWindow::placeRectangle( _SURFACE* d, _POS x, _POS y, _SIZE w, _SIZE h, _COLOR color )
{
  _SURFACE* rs = _CREATE_RGBA_SURFACE( w, h, color );
  _RECTANGLE offset;
  offset.x = x;
  offset.y = y;
  offset.w = 0;
  offset.h = 0;
  _SURFACE_SET_ALPHA( rs );
  _SURFACE_BLIT( rs, NULL, d, &offset );
  _FREE_SURFACE( rs );
}
void theWindow::placeRectangle( _SURFACE* d, _POS x, _POS y, _SIZE w, _SIZE h, _COLOR color, _SIZE border, _COLOR bColor )
{
  placeRectangle( d, x, y, w, h, color );
  _PIXEL* pixels = (_PIXEL*)d->pixels;
  _SIZE rc = 0;
  for( _SIZE i = y; i < y + h; i++ ) 
  {
    _SIZE sRow = i * d->w;
    _SIZE cc = 0;
	for( _SIZE j = x; j < x + w; j++ ) 
	{
	  if( cc < border || rc < border ) pixels[ sRow + j ] = bColor;
	  if( (cc > w - border - 1) || (rc > h - border - 1) ) pixels[ sRow + j ] = bColor;
	  cc++;
	}
    rc++;
  }
}

void theWindow::makeBackground( _SURFACE* destination, _SURFACE* image )
{
  //_SURFACE* destination = _CREATE_RGBA_SURFACE( planesWidth, planesHeight, OPAQUE_RGBA );
  if( (planesWidth == image->w && planesHeight == image->h) || (planesWidth == 0 && planesHeight == 0) ) {
    _SURFACE_COPY( image, destination );
  } else 
  {
	_RECTANGLE s, d;
	s.x = d.x = 0;
	s.y = d.y = 0;
	s.w = d.w = destination->w;
	s.h = d.h = destination->h;

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

_SIZE theWindow::print( tileSet* font, _SURFACE* destination, _POS x, _POS y, const char *fmt, ... )
{
  char buffer[ MAX_LINE ];
  va_list args;
  va_start( args, fmt );
  vsprintf( buffer, fmt, args );
  va_end( args );
  _RECTANGLE offset;
  offset.x = x;
  offset.y = y;
  for( _INDEX i = 0; buffer[ i ] != 0; i++ ) 
  {
	if( buffer[ i ] == '\n' ) {
	  offset.y += font->tiles[ buffer[ i ] ]->h;
      offset.x = x;
      continue;
    }

//	if( planeNR == 0 ) _SURFACE_SET_ALPHA( font->tiles[ buffer[ i ] ] );
//	else _SURFACE_SET_ZALPHA( font->tiles[ buffer[ i ] ] );
	_SURFACE_BLIT( font->tiles[ buffer[ i ] ], NULL, destination, &offset );
    offset.x += font->tiles[ buffer[ i ] ]->w;
  }
  return strlen( buffer );

}

void theWindow::addPlaneMatrix( _SIZE secWidth, _SIZE secHeight )
{
  _SIZE cols = planesWidth / secWidth + (( planesWidth % secWidth > 0 )? 1 : 0);
  _SIZE rows = planesHeight / secHeight + (( planesHeight % secHeight > 0 )? 1 : 0);

  pMat.resize( pMat.size() + 1 );
  _SIZE mI = pMat.size() - 1;
  pMat[ mI ].resize( rows );
  for( _SIZE i = 0; i < rows; i++ )
    pMat[ mI ][ i ].resize( cols );
  sectorSizes.resize( sectorSizes.size() + 1 );	
  sectorSizes[ sectorSizes.size() - 1 ].w = secWidth;
  sectorSizes[ sectorSizes.size() - 1 ].h = secHeight;
}

void theWindow::makeBackgroundMatrix( _SURFACE* image, _SIZE sw, _SIZE sh ) 
{
  addPlaneMatrix( sw, sh );
  _SIZE mI = pMat.size() - 1;
  _POS posX = 0;
  _POS posY = 0;
  while( posY < planesHeight ) 
  {
    while( posX < planesWidth ) { 
	  putOnMatrix( mI, image, posX, posY );
	  posX += image->w;
    }
	posY += image->h;
	posX = 0;
  }
}
void theWindow::putOnMatrix( _INDEX index, _SURFACE* s, _POS posx, _POS posy )
{
  _SIZE rows = pMat[ index ].size();
  _SIZE cols = pMat[ index ][ 0 ].size();
  _SIZE secWidth = sectorSizes[ index ].w;
  _SIZE secHeight = sectorSizes[ index ].h;
  _SIZE surfCols = s->w / secWidth + (( s->w % secWidth > 0 )? 1 : 0);
  _SIZE surfRows = s->h / secHeight + (( s->h % secHeight > 0 )? 1 : 0);
  _SIZE col = posx / secWidth + (( posx % secWidth > 0 )? 1 : 0);
  _SIZE row = posy / secHeight + (( posy % secHeight > 0 )? 1 : 0);
  if( row > rows || col > cols ) return;
  if( row > 0 ) row--;
  if( col > 0 ) col--;

  visObj* vObj = new visObj;
  vObj->x = posx; 
  vObj->y = posy; 
  vObj->s = s; 
  for( _SIZE i = 0; i < surfRows && (row + i < rows); i++ )
  {
    for( _SIZE j = 0; j < surfCols && (col + j < cols); j++ )
	{
      _SIZE lastO = pMat[ index ][ row + i ][ col + j ].vo.size();
      pMat[ index ][ row + i ][ col + j ].vo.resize( lastO + 1 );
      pMat[ index ][ row + i ][ col + j ].vo[ lastO ] = vObj;
	}
	
  }
//fprintf( stderr, "[%i %i; %i %i; %i %i]\n\n", surfRows, surfCols, (int)row, (int)col, (int)rows, (int)cols );

}

void theWindow::prepareMatrixToDraw( _INDEX i, _POS x, _POS y, _SIZE w, _SIZE h ) 
{
}

void theWindow::redrawMatrix( _INDEX index, _POS x, _POS y, _SIZE w, _SIZE h )
{
  
}