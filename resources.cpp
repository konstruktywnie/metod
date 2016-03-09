#include "framework_dependent/fw.h"
#include "resources.h"
#include "config.h"

appResources::appResources()
{
  mainTileset.loadFromFile( RES_MAIN_TILESET, 0, 0 );
  
}


uint32 tileSet::loadFromFile( char* f, _SIZE tileWidth, _SIZE tileHeight ) {
  _SURFACE* image;
  image = _LOAD_IMG( f );
  if( !f || image == NULL ) {
    printf( "Error: Can not load image: %s\n", f );
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
	  _SURFACE* tile = _CREATE_RGB_SURFACE( tileWidth, tileHeight );
	  _SURFACE_BLIT( image, &s, tile, &d );
	  tiles.push_back( tile );
	}
  }

  _FREE_SURFACE( image );
  return tiles.size();
}

void tileSet::changeColor( _COLOR search, _COLOR changeTo, uint32 i ) {
  _PIXEL* pixels = (_PIXEL*)tiles[ i ]->pixels;
    for( _SIZE j = 0; j < tiles[ i ]->h; j++ ) {
	  for( _SIZE k = 0; k < tiles[ i ]->w; k++ ) {
	    if( pixels[ ( j * tiles[ i ]->w ) + k ] == search )
		  pixels[ ( j * tiles[ i ]->w ) + k ] = changeTo;
	  }
	}
}

void tileSet::changeColor( _COLOR search, _COLOR changeTo ) {
  uint32 ts = tiles.size();
  for( int i = 0; i < ts; i++ ) {
    changeColor( search, changeTo, i );
  }
}

void tileSet::changeColorAtAlpha( _COLOR changeTo ) {
  uint32 ts = tiles.size();
  for( int i = 0; i < ts; i++ ) {
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
  uint32 ts = tiles.size();
  for( int i = 0; i < ts; i++ ) {
    _PIXEL* pixels = (_PIXEL*)tiles[ i ]->pixels;
    for( _SIZE j = 0; j < tiles[ i ]->h; j++ ) {
	  for( _SIZE k = 0; k < tiles[ i ]->w; k++ ) {
	    if( (pixels[ j * tiles[ i ]->w + k ] & TRANSLUCENT_RGBA) != RGBA_MAX_CH ) {
		  pixels[ j * tiles[ i ]->w + k ] &= TRANSPARENT_RGBA;
		}
	  }
	}
  }
}


_SURFACE* optimizedSurface( char* f, _SIZE w, _SIZE h ) {
  _SURFACE* image = _LOAD_IMG( f );
  _SURFACE* destination;

  if( (w == image->w && h == image->h) || (w == 0 && h == 0) ) {
    destination = _LOAD_IMG( f );
  } else {
    destination = _EMPTY_PLANE( w, h, TRANSLUCENT_RGBA );
	_RECTANGLE s, d;
	s.x = d.x = 0;
	s.y = d.y = 0;
	s.w = d.w = w;
	s.h = d.h = h;

	if( image->w > w && image->h > h ) {
      _SURFACE_BLIT( image, &s, destination, &d );
	}
	if( image->w < w || image->h < h ) {
	s.w = image->w;
	s.h = image->h;

	_SIZE mw = w / image->w + 1;
	_SIZE mh = h / image->h + 1;
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

//  _SURFACE* optimized = _CONVERT_SURFACE( destination );
//  _FREE_SURFACE( destination );
  _FREE_SURFACE( image );
//  return optimized;
  return destination;
}
