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
