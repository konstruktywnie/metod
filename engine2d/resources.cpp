#include "../framework_dependent/fw.h"
#include "../config_events.h"
#include "resources.h"
#include "screen.h"
#include "../config.h"

_TIME tileSeqCallback( _TIME interval, void* param )
{
  _PUSH_EVENT( param, EVENT_TILESET_ANIMATION );
  return interval;
}

void tileSeq::start()
{
  t_id = _ADD_TIMER( interval, tileSeqCallback, (void*) this );
    
}
void tileSeq::stop()
{
  _REMOVE_TIMER( t_id );
}

void tileSeq::draw()
{
  win->redrawField( actualVO->x, actualVO->y, actualVO->s->w, actualVO->s->h );
  seq[ actualSeq ]->actualFrame += nextFrame;
  if( seq[ actualSeq ]->actualFrame > seq[ actualSeq ]->end )
  {
    if( looped )
      seq[ actualSeq ]->actualFrame = seq[ actualSeq ]->begin;
	else { stop(); return; }
  }
  if( seq[ actualSeq ]->actualFrame < seq[ actualSeq ]->begin )
  {
    if( looped )
      seq[ actualSeq ]->actualFrame = seq[ actualSeq ]->end;
	else { stop(); return; }
  }
  actualVO->s = ts->tiles[ seq[ actualSeq ]->actualFrame ];
  
  //fprintf( stderr, " (seq[ actualSeq ]->actualFrame)%i (seq[ actualSeq ]->begin)%i (seq[ actualSeq ]->end)%i\n", seq[ actualSeq ]->actualFrame, seq[ actualSeq ]->begin, seq[ actualSeq ]->end );
  
  
  	
}

tileSeq::tileSeq()
{
  actualSeq = 0;
  nextFrame = 1;
  interval = DEFAULT_INTERVAL;
  looped = false;
}
tileSeq::tileSeq( _CHAR* file )
{
  tileSet t;
  t.loadFromFile( file, 0, 0 );
  prepare( &t );
}
void tileSeq::prepare( tileSet* t )
{
  ts = t;
  if( !seq.empty() )
    seq.clear();
  sequence* s = new sequence;
  s->begin = s->actualFrame = 0;
  s->end = ts->tiles.size() - 1;
  seq.resize( 1 );
  seq[ 0 ] = s;
}

_SIZE tileSet::loadFromFile( _CHAR* f, _SIZE tileWidth, _SIZE tileHeight ) {
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

void tileSet::copyTile( _INDEX index ) {
  SDL_Surface *ns = _CREATE_RGBA_SURFACE( tiles[ index ]->w, tiles[ index ]->h );
  //SDL_SetAlpha( tiles[ index ], 0, SDL_ALPHA_OPAQUE ); //SDL_SRCALPHA
  _SURFACE_SET_ZALPHA( tiles[ index ] );
  _SURFACE_BLIT( tiles[ index ], NULL, ns, NULL );

  tiles.push_back( ns );
}

void apply_pixels( _POS x, _POS y, _SURFACE* source, _SURFACE* destination )
{
  _PIXEL* pixels1 = (_PIXEL*)source->pixels;
  _PIXEL* pixels2 = (_PIXEL*)destination->pixels;

  for( _SIZE i = 0; i < source->h; i++ ) {
    _SIZE dRow = (i + y) * destination->w;
	_SIZE sRow = i * source->w;
    for( _SIZE j = 0; j < source->w; j++ ) {
	  if( (pixels1[ sRow + j ] & 0xff) != 0 )
	    pixels2[ dRow + j + x ] = pixels1[ sRow + j ];
	}
  }
}
SDL_Surface* apply_pixelsRev( _POS x, _POS y, _SURFACE* source, _SURFACE* destination )
{
    _SURFACE* ns = _CREATE_RGBA_SURFACE( source->w,  source->h );
	apply_pixels( 0, 0, source, ns );
    apply_pixels( 0, 0, destination, ns );
    _FREE_SURFACE( destination );
	return ns;
}

void tileSet::simpleRotation( _INT index, _INT degree ) {
  if( index < 0 ) index = tiles.size() + index;
  _SURFACE* r;
  _PIXEL* pixels1 = (_PIXEL*)tiles[ index ]->pixels;
  _PIXEL* pixels2;

  if( degree == 180 ) {
    r = _CREATE_RGBA_SURFACE( tiles[ index ]->w, tiles[ index ]->h );
	pixels2 = (_PIXEL*)r->pixels;
    for( _SIZE j = 0; j < tiles[ index ]->h; j++ ) {
	  _SIZE sRow = j * tiles[ index ]->w;
	  _SIZE dRow = (tiles[ index ]->h - 1 - j) * tiles[ index ]->w;
	  for( _SIZE k = 0; k < tiles[ index ]->w; k++ ) {
	    pixels2[ dRow + tiles[ index ]->w - 1 - k ] = pixels1[ sRow + k ];
	  }
	}
  }
  if( degree == 90 ) {
    r = _CREATE_RGBA_SURFACE( tiles[ index ]->h, tiles[ index ]->w );
	pixels2 = (_PIXEL*)r->pixels;
    for( _SIZE j = 0; j < tiles[ index ]->h; j++ ) {
	  _SIZE sRow = j * tiles[ index ]->w;
	  for( _SIZE k = 0; k < tiles[ index ]->w; k++ ) {
	    pixels2[ k * r->w + (r->w - 1 - j) ] = pixels1[ sRow + k ];
	  }
	}
  }
  if( degree == -90 || degree == 270 ) {
    r = _CREATE_RGBA_SURFACE( tiles[ index ]->h, tiles[ index ]->w );
	pixels2 = (_PIXEL*)r->pixels;
    for( _SIZE j = 0; j < tiles[ index ]->h; j++ ) {
	  _SIZE sRow = j * tiles[ index ]->w;
	  for( _SIZE k = 0; k < tiles[ index ]->w; k++ ) {
	    pixels2[ (r->h - 1 - k) * r->w + j ] = pixels1[ sRow + k ];
	  }
	}
  }

  _FREE_SURFACE( tiles[ index ] );
  tiles[ index ] = r;

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
