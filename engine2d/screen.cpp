#include "../framework_dependent/fw.h"
#include "resources.h"
#include "screen.h"
#include "../config.h"
#include "../level.h"
#include "../game.h"

extern theGame Game;

theScreen::theScreen() {
  addWindow();
}
void theScreen::redraw()
{
  _SIZE ws = windows.size();
  for( _SIZE i = 0; i < ws; i++ )
  {
    windows[ i ]->redraw();
  }
}
void theScreen::addWindow( _INDEX nr ) {
  windows.resize( windows.size() + nr );
  for( _INDEX i = 0; i < nr; i++ ) 
    windows[ i ] = new theWindow;
  
}
void theScreen::addWindow() {
  windows.resize( windows.size() + 1 );
  windows[ windows.size() - 1 ] = new theWindow;
}

theWindow::theWindow() {
  winRec.w = planesWidth = theScreen::scrWidth;
  winRec.h = planesHeight = theScreen::scrHeight;
  winRec.x = winRec.y = bgPosX = bgPosY = 0;
  anchoredText = true;
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
  s.w = winRec.w;
  s.h = winRec.h;
  s.x = bgPosX;
  s.y = bgPosY;

  _SIZE allP = planes.size();
  for( _SIZE i = 0; i < allP; i++ ) {
	_APPLY_ON_DISPLAY( planes[ i ], &s, &winRec );
	
  }
  _UPDATE_DISPLAY( &winRec );
}

void theWindow::placeRectangle( _SURFACE* d, _POS x, _POS y, _SIZE w, _SIZE h, _COLOR color )
{
  _SURFACE* rs = _CREATE_RGBA_SURFACE( w, h, color );
  _RECTANGLE offset;
  offset.x = x;
  offset.y = y;
  offset.w = 0;
  offset.h = 0;
  //_SURFACE_SET_ALPHA( rs );
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
  if( anchoredText )
    _SURFACE_SET_ALPHA( font->tiles[ buffer[ i ] ] );
  else
    _SURFACE_SET_ZALPHA( font->tiles[ buffer[ i ] ] );
  _SURFACE_BLIT( font->tiles[ buffer[ i ] ], NULL, destination, &offset );
  offset.x += font->tiles[ buffer[ i ] ]->w;
  }
  return strlen( buffer );

}

void theWindow::addPlaneMatrix( _SIZE secWidth, _SIZE secHeight )
{
  sectorWidth = secWidth;
  sectorHeight = secHeight;
  addPlaneMatrix();
}
void theWindow::addPlaneMatrix() {
  _SIZE cols = planesWidth / sectorWidth + (( planesWidth % sectorWidth > 0 )? 1 : 0);
  _SIZE rows = planesHeight / sectorHeight + (( planesHeight % sectorHeight > 0 )? 1 : 0);

  pMat.resize( pMat.size() + 1 );
  _SIZE mI = pMat.size() - 1;
  pMat[ mI ].resize( rows );
  for( _SIZE i = 0; i < rows; i++ )
    pMat[ mI ][ i ].resize( cols );
  
  vObjs.resize( vObjs.size() + 1 );
  
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
  _SIZE col = posx / sectorWidth;
  _SIZE row = posy / sectorHeight;
  _SIZE colEnd = (posx + s->w) / sectorWidth;
  _SIZE rowEnd = (posy + s->h) / sectorHeight;
  if( colEnd > cols ) colEnd = cols;
  if( rowEnd > rows ) rowEnd = rows;
  
  visObj* vObj = new visObj;
  vObj->x = posx; 
  vObj->y = posy; 
  vObj->s = s; 
  _SIZE lastO;
  for( ; row < rowEnd; row++ )
  {
    for( _SIZE coli = col; coli < colEnd; coli++ )
	{
	  lastO = pMat[ index ][ row ][ coli ].vo.size();
      pMat[ index ][ row ][ coli ].vo.resize( lastO + 1 );
      pMat[ index ][ row ][ coli ].vo[ lastO ] = vObj;
	}
  }
}
void theWindow::print_vo_sizes( _INDEX index ) {
  for( _SIZE i = 0; i < pMat[ 0 ].size(); i++ ) {
    for( _SIZE j = 0; j < pMat[ 0 ][ 0 ].size(); j++ )
	  fprintf( stderr, "%i ", pMat[ 0 ][ i ][ j ].vo.size() );
    fprintf( stderr, "\n" );
  }
}
void theWindow::onMatrixCoordinates( _INDEX index, _POS x, _POS y, _SIZE w, _SIZE h, _SIZE& row, _SIZE& col, _SIZE& rowL, _SIZE& colL )
{
  _SIZE rows = pMat[ index ].size();
  _SIZE cols = pMat[ index ][ 0 ].size();
  col = x / sectorWidth;
  row = y / sectorHeight;
  colL = (x + w) / sectorWidth - col + 1;
  rowL = (y + h) / sectorHeight - row + 1;
  if( col + colL > cols ) colL = cols - col;
  if( row + rowL > rows ) rowL = rows - row;
}
/*
void theWindow::prepareMatrixToDraw( _INDEX index, _POS x, _POS y, _SIZE w, _SIZE h ) 
{
  _SIZE col, row, colL, rowL;
  onMatrixCoordinates( index, x, y, w, h, col, row, rowL, colL );
  for( _SIZE i = 0; i < rowL; i++ ) 
    for( _SIZE j = 0; j < colL; j++ )
	{
	  _SIZE vos = pMat[ index ][ row + i ][ col + j ].vo.size();
	  for( _SIZE k = 0; k < vos; k++ )
	    pMat[ index ][ row + i ][ col + j ].vo[ k ]->drawed = false;
	}
}*/
void theWindow::prepareMatrixToDraw( _INDEX index, _SIZE row, _SIZE col, _SIZE rowL, _SIZE colL ) 
{
  for( _SIZE i = 0; i < rowL; i++ ) 
    for( _SIZE j = 0; j < colL; j++ )
	{
	  _SIZE vos = pMat[ index ][ row + i ][ col + j ].vo.size();
	  for( _SIZE k = 0; k < vos; k++ )
	    pMat[ index ][ row + i ][ col + j ].vo[ k ]->drawed = false;
	}
}

bool theWindow::visibleInWindow( _POS fx, _POS fy, _SIZE fw, _SIZE fh, _POS& vis_fx, _POS& vis_fy, _SIZE& vis_fw, _SIZE& vis_fh )
{
//  if( fw > winRec.w ) fw = winRec.w;
//  if( fh > winRec.h ) fh = winRec.h;
  
  _POS end_fx = fx + fw;
  _POS end_fy = fy + fh;
  _POS end_winx = bgPosX + winRec.w;
  _POS end_winy = bgPosY + winRec.h;
  
  vis_fx = fx;
  vis_fy = fy;
  vis_fw = fw;
  vis_fh = fh;
  
  if( end_fx > bgPosX && fx < end_winx && end_fy > bgPosY  && fy < end_winy )
  {
    if( end_fx > bgPosX && fx < bgPosX )
	{
	  vis_fx = bgPosX;
	  vis_fw = fw - (bgPosX - fx);
	}
	if( end_fx > bgPosX + winRec.w && fx < end_winx ) {
	  vis_fx = fx;
	  vis_fw = fw - (end_fx - end_winx);
	}
	if( fx < bgPosX && end_fx > end_winx )
	{
	  vis_fx = bgPosX;
	  vis_fw = end_winx - bgPosX;
	}
	
    if( end_fy > bgPosY && fy < bgPosY ) {
	  vis_fy = bgPosY;
	  vis_fh = fh - (bgPosY - fy);
	}
	if( end_fy > end_winy && fy < end_winy ) {
	  vis_fy = fy;
	  vis_fh = fh - (end_fy - end_winy);
	}
	if( fy < bgPosY && end_fy > end_winy )
	{
	  vis_fy = bgPosY;
	  vis_fh = end_winy - bgPosY;
	}
	
	return true;
  }
  return false;
}
bool theWindow::visibleField( _POS fx, _POS fy, _SIZE fw, _SIZE fh, _POS sx, _POS sy, _POS sw, _POS sh, _POS& vis_sx, _POS& vis_sy, _SIZE& vis_sw, _SIZE& vis_sh )
{
  _POS end_fx = fx + fw;
  _POS end_fy = fy + fh;
  _POS end_sx = sx + sw;
  _POS end_sy = sy + sh;
  vis_sx = 0;
  vis_sy = 0;
  vis_sw = sw;
  vis_sh = sh;
  
  if( end_sx > fx && sx < end_fx && end_sy > fy && sy < end_fy )
  {
    	
	if( end_sx > fx && sx < fx )
	{
	  vis_sx = fx - sx;
	  vis_sw = sw - vis_sx;
	}
	if( end_sx > end_fx && sx < end_fx ) {
	  vis_sx = 0;
	  vis_sw = sw - (end_sx - end_fx);
	}
	if( end_sx > end_fx && sx < fx ) {
	  vis_sx = fx - sx;
	  vis_sw = fw;
	}
	
	if( end_sy > fy && sy < fy )
	{
	  vis_sy = fy - sy;
	  vis_sh = sh - vis_sy;
	}
	if( end_sy > end_fy && sy < end_fy ) {
	  vis_sy = 0;
	  vis_sh = sh - (end_sy - end_fy);
	}
	if( end_sy > end_fy && sy < fy ) {
	  vis_sy = fy - sy;
	  vis_sh = fh;
	}
    
	return true;
  }
  return false;
}
void theWindow::redraw() {
  redrawField( bgPosX, bgPosY, winRec.w, winRec.h );
}
void theWindow::redrawField( _POS x, _POS y, _SIZE w, _SIZE h )
{
  _SIZE matS = pMat.size();
  _POS visFX, visFY;
  _SIZE visFW, visFH;
  _RECTANGLE r;
    
  if( visibleInWindow( x, y, w, h, visFX, visFY, visFW, visFH ) )
  {
    _SIZE col, row, colL, rowL;
    onMatrixCoordinates( 0, x, y, w, h, col, row, rowL, colL );
    for( _SIZE i = 0; i < matS; i++ ) 
	{
	  prepareMatrixToDraw( i, row, col, rowL, colL );
	  redrawMatrix( i, row, col, rowL, colL, visFX, visFY, visFW, visFH );
	  redrawVObjs( i, visFX, visFY, visFW, visFH );
	}
    r.x = winRec.x + visFX - bgPosX;
    r.y = winRec.y + visFY - bgPosY;
    r.w = visFW;
    r.h = visFH;
    _UPDATE_DISPLAY( &r );
  }
  
}

void theWindow::redrawMatrix( _INDEX index, _SIZE row, _SIZE col, _SIZE rowL, _SIZE colL, _POS visFX, _POS visFY, _SIZE visFW, _SIZE visFH )
{
  _POS visX, visY;
  _SIZE visW, visH;
  _RECTANGLE s, d;
  
  for( _SIZE i = 0; i < rowL; i++ ) 
  {
    for( _SIZE j = 0; j < colL; j++ )
	{
	  _SIZE vos = pMat[ index ][ i ][ j ].vo.size();
	  for( _SIZE k = 0; k < vos; k++ )
	  {
	    visObj* vObj = pMat[ index ][ i ][ j ].vo[ k ];
		
		if( !vObj->drawed && visibleField( visFX, visFY, visFW, visFH, vObj->x, vObj->y, vObj->s->w, vObj->s->h, visX, visY, visW, visH ) )
		{
		  s.x = visX;
		  s.y = visY;
		  s.w = visW;
		  s.h = visH;
		  d.x = winRec.x + vObj->x + visX - bgPosX;
		  d.y = winRec.y + vObj->y + visY - bgPosY;
		  d.w = visW;
		  d.h = visH;
		  _APPLY_ON_DISPLAY( vObj->s, &s, &d );
		  vObj->drawed = true;
		}
		
	  }
	}
  }
  
}
void theWindow::newVObj( _INDEX p, _INDEX i, _SURFACE* s, _POS x, _POS y )
{
  if( vObjs[ p ].empty() )
    vObjs[ p ].resize( 1 );
  if( i > (vObjs[ p ].size() - 1) )
    vObjs[ p ].resize( i + 1 );
  vObjs[ p ][ i ] = new visObj;
  vObjs[ p ][ i ]->s = s;
  vObjs[ p ][ i ]->x = x;
  vObjs[ p ][ i ]->y = y;
}
void theWindow::redrawVObjs( _INDEX index, _POS visFX, _POS visFY, _SIZE visFW, _SIZE visFH )
{
  _POS visX, visY;
  _SIZE visW, visH;
  _SIZE voS = vObjs[ index ].size();
  _RECTANGLE s, d;
  for(_SIZE i = 0; i < voS; i++ )
  {
    if( visibleField( visFX, visFY, visFW, visFH, vObjs[ index ][ i ]->x, vObjs[ index ][ i ]->y, vObjs[ index ][ i ]->s->w, vObjs[ index ][ i ]->s->h, visX, visY, visW, visH ) )
	{
	  s.x = visX;
	  s.y = visY;
	  s.w = visW;
	  s.h = visH;
	  d.x = winRec.x + vObjs[ index ][ i ]->x + visX - bgPosX;
	  d.y = winRec.y + vObjs[ index ][ i ]->y + visY - bgPosY;
	  d.w = visW;
	  d.h = visH;
	  _APPLY_ON_DISPLAY( vObjs[ index ][ i ]->s, &s, &d );
	  //vObjs[ index ][ i ]->drawed = true;
	}
  }
}
  