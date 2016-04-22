#include "fw.h"
#include "..\config.h"
//#include "..\config_resources.h"

extern _SURFACE* MainScreen;

_SURFACE* _CREATE_RGBA_SURFACE( _SIZE tileWidth, _SIZE tileHeight ) {
  return SDL_CreateRGBSurface( SURFACE_TYPE, tileWidth, tileHeight, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );
}
_SURFACE* _CREATE_RGBA_SURFACE( _SIZE tileWidth, _SIZE tileHeight, _COLOR c ) {
  _SURFACE* s = _CREATE_RGBA_SURFACE( tileWidth, tileHeight );
  _FILL_RECT( s, NULL, c );
  
  return s;
}

_CHAR* _LOAD_FILE( _CHAR* file ) {
  FILE *f;
  _SIZE fSize = 0;
  f = fopen( file, "rb" );
  if( f == NULL ) {
    fprintf( stderr, "Error: Can not read file %s", file );
    exit( EXIT_FAILURE );
  }
  fseek( f , 0L , SEEK_END);
  fSize = ftell( f );
  rewind( f );

  _CHAR* buf = new _CHAR [fSize + 1];
  buf[ fSize ] = 0;
  if( fread( buf , fSize, 1 , f ) != 1 ) {
    fprintf( stderr, "Error: Can not read file %s", file );
    exit( EXIT_FAILURE );
  }
  fclose( f );
  return buf;
}

