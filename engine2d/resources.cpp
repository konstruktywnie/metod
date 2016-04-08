#include "../framework_dependent/fw.h"
#include "resources.h"
#include "../config.h"


_SIZE tileSet::loadFromFile( char* f, _SIZE tileWidth, _SIZE tileHeight ) {
  _SURFACE* image;
  image = _LOAD_IMG( f );
  if( !f || image == NULL ) {
    fprintf( stderr, "Error: Can not load image: %s\n", f );
    exit( 1 );
  }
  _SURFACE_SET_ZALPHA( image );
  //_SURFACE_SET_ALPHA( image );

  if( tileWidth == 0 && tileHeight == 0 ) {  //working out square tile size in case of elongated mosaic
    if( image->w >= image->h )
	  tileWidth = image->h;
	else tileWidth = image->w;
	tileHeight = tileWidth;
  }

  _SIZE tilesRows = image->h / tileHeight;
  _SIZE tilesCols = image->w / tileWidth;

  _RECTANGLE s;
  s.w = tileWidth;
  s.h = tileHeight;
  _RECTANGLE d;
  d.w = tileWidth;
  d.h = tileHeight;
  d.x = 0;
  d.y = 0;
  s.x = 0;
  s.y = 0;

  for( _SIZE i = 0; i < tilesRows; i++ ) {
    for( _SIZE j = 0; j < tilesCols; j++ ) {
	  s.x = j * tileWidth;
      s.y = i * tileHeight;
	  _SURFACE* tile = _CREATE_RGBA_SURFACE( tileWidth, tileHeight );
	  _SURFACE_BLIT( image, &s, tile, &d );
	  tiles.push_back( tile );
	}
  }

  _FREE_SURFACE( image );
  return tiles.size();
}

void tileSet::changeColor( _COLOR search, _COLOR changeTo, _INDEX i ) {
  _PIXEL* pixels = (_PIXEL*)tiles[ i ]->pixels;
    for( _SIZE j = 0; j < tiles[ i ]->h; j++ ) {
	  for( _SIZE k = 0; k < tiles[ i ]->w; k++ ) {
	    if( pixels[ ( j * tiles[ i ]->w ) + k ] == search )
		  pixels[ ( j * tiles[ i ]->w ) + k ] = changeTo;
	  }
	}
}

void tileSet::changeColor( _COLOR search, _COLOR changeTo ) {
  _INDEX ts = tiles.size();
  for( _INDEX i = 0; i < ts; i++ ) {
    changeColor( search, changeTo, i );
  }
}

void tileSet::changeColorAtAlpha( _COLOR changeTo ) {
  _INDEX ts = tiles.size();
  for( _INDEX i = 0; i < ts; i++ ) {
    _PIXEL* pixels = (_PIXEL*)tiles[ i ]->pixels;
    for( _SIZE j = 0; j < tiles[ i ]->h; j++ ) {
	  for( _SIZE k = 0; k < tiles[ i ]->w; k++ ) {
	    if( (pixels[ j * tiles[ i ]->w + k ] & RGBA_MAX_CH) != 0 )
		  pixels[ j * tiles[ i ]->w + k ] = changeTo;
	  }
	}
  }
}

void tileSet::translucentToTransparent() {
  _INDEX ts = tiles.size();
  for( _INDEX i = 0; i < ts; i++ ) {
    _PIXEL* pixels = (_PIXEL*)tiles[ i ]->pixels;
    for( _SIZE j = 0; j < tiles[ i ]->h; j++ ) {
	  for( _SIZE k = 0; k < tiles[ i ]->w; k++ ) {
	    if( (pixels[ j * tiles[ i ]->w + k ] & OPAQUE_RGBA) != RGBA_MAX_CH ) {
		  pixels[ j * tiles[ i ]->w + k ] &= TRANSPARENT_RGBA;
		}
	  }
	}
  }
}

bool jointField( _POS f1x, _POS f1y, _SIZE f1w, _SIZE f1h, _POS f2x, _POS f2y, _POS f2w, _POS f2h, _POS& jf1x, _POS& jf1y, _POS& jf2x, _POS& jf2y, _SIZE& jfw, _SIZE& jfh )
{
  _POS f1x_end = f1x + f1w;
  _POS f1y_end = f1y + f1h;
  _POS f2x_end = f2x + f2w;
  _POS f2y_end = f2y + f2h;
  
  if( f1x_end >= f2x && f1x <= f2x_end && f1y_end >= f2y && f1y <= f2y_end )
  {
  
    if( f1x >= f2x && f1x_end <= f2x_end )
	{
	  jf1x = 0;
	  jfw = f1w;
	  jf2x = f1x - f2x;
	  
	  
	} else
    if( f1x_end >= f2x && f1x_end <= f2x_end && f1x < f2x )
	{
	  jf1x = f2x - f1x;
	  jfw = f1x_end - f2x + 1;
	  jf2x = 0;
	  
	  
	} else
	if( f1x_end > f2x_end && f1x <= f2x_end && f1x >= f2x )
	{
	  jf2x = f1x - f2x;
	  jfw = f2x_end - f1x + 1;
	  jf1x = 0;
	  
	  
	} else
	if( f1x < f2x && f1x_end > f2x_end )
	{
	  jf2x = 0;
	  jfw = f2w;
	  jf1x = f2x - f1x;
	  
	  
	}
	
	if( f1y >= f2y && f1y_end <= f2y_end )
	{
	  jf1y = 0;
	  jfh = f1h;
	  jf2y = f1y - f2y;
	  
	  
	} else
    if( f1y_end >= f2y && f1y_end <= f2y_end && f1y < f2y )
	{
	  jf1y = f2y - f1y;
	  jfh = f1y_end - f2y + 1;
	  jf2y = 0;
	  
	  
	} else
	if( f1y_end > f2y_end && f1y <= f2y_end && f1y >= f2y )
	{
	  jf2y = f1y - f2y;
	  jfh = f2y_end - f1y + 1;
	  jf1y = 0;
	  
	  
	} else
	if( f1y < f2y && f1y_end > f2y_end )
	{
	  jf2y = 0;
	  jfh = f2h;
	  jf1y = f2y - f1y;
	  
	  
	}

  
    return true;
  }
  
  return false;
}
bool jointField( _POS f1x, _POS f1y, _SIZE f1w, _SIZE f1h, _POS f2x, _POS f2y, _POS f2w, _POS f2h, _POS& jf1x, _POS& jf1y, _SIZE& jfw, _SIZE& jfh )
{
  _POS f1x_end = f1x + f1w;
  _POS f1y_end = f1y + f1h;
  _POS f2x_end = f2x + f2w;
  _POS f2y_end = f2y + f2h;
  
  if( f1x_end >= f2x && f1x <= f2x_end && f1y_end >= f2y && f1y <= f2y_end )
  {
  
    if( f1x >= f2x && f1x_end <= f2x_end )
	{
	  jf1x = 0;
	  jfw = f1w;
	} else
    if( f1x_end >= f2x && f1x_end <= f2x_end && f1x < f2x )
	{
	  jf1x = f2x - f1x;
	  jfw = f1x_end - f2x + 1;
	} else
	if( f1x_end > f2x_end && f1x <= f2x_end && f1x >= f2x )
	{
	  jfw = f2x_end - f1x + 1;
	  jf1x = 0;
	} else
	if( f1x < f2x && f1x_end > f2x_end )
	{
	  jfw = f2w;
	  jf1x = f2x - f1x;
	}
	
	if( f1y >= f2y && f1y_end <= f2y_end )
	{
	  jf1y = 0;
	  jfh = f1h;
	} else
    if( f1y_end >= f2y && f1y_end <= f2y_end && f1y < f2y )
	{
	  jf1y = f2y - f1y;
	  jfh = f1y_end - f2y + 1;
	} else
	if( f1y_end > f2y_end && f1y <= f2y_end && f1y >= f2y )
	{
	  jfh = f2y_end - f1y + 1;
	  jf1y = 0;
	} else
	if( f1y < f2y && f1y_end > f2y_end )
	{
	  jfh = f2h;
	  jf1y = f2y - f1y;
	}
    return true;
  }
  return false;
}
