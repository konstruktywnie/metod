#include "framework_dependent/fw.h"
#include "config.h"
#include "config_resources.h"
#include "config_screen.h"
#include "engine2d/resources.h"
#include "engine2d/screen.h"
#include "level.h"
#include "game.h"

extern theGame Game;

theLevel::theLevel()
{
  
}

void theLevel::parseCfgLine()
{
  sscanf( chs, "%d %d %d %d %d %d %d %d %s\n", &player->items.time, &player->items.fuel, &player->hitPoints, &player->items.ea, &player->items.msa, &player->items.pu, &EA_damage_mod, &MSA_damage_mod, introFile );

}

bool getTileID( const _CHAR** TRN, _CHAR* tileChars, _INDEX &id ) {
	for( _INDEX k = 0; TRN[ k ] != 0; k++ ) {
	  if( tileChars[ 0 ] == TRN[ k ][ 0 ] && tileChars[ 1 ] == TRN[ k ][ 1 ] ) {
		id = k;
		return true;
      }
    }
  return false;
}


void theLevel::buildMap( _CHAR* file )
{
  chs = _LOAD_FILE( file );
  parseCfgLine();
  _INDEX i = 0;
  while( chs[ i ] != '\n' && chs[ i ] != '\r' ) i++;
  while( chs[ i ] == '\n' || chs[ i ] == '\r' ) i++;
  _SIZE firstLineSize;
  for( _SIZE line = 0; chs[ i ] != 0; line++ ) {
    map.resize( 1 + line );
    _SIZE lCount = 0;
    while( chs[ i + lCount ] != 0 && chs[ i + lCount ] != '\n' && chs[ i + lCount ] != '\r' ) {
	  lCount++;
	}
	if( line == 0 ) firstLineSize = lCount;
	else if( lCount != firstLineSize ) {
	  fprintf( stderr, "Error: Wrong size of line %d in %s", line + 1, file );
      exit( EXIT_FAILURE );
	}
	if( lCount % 2 ) {
	  fprintf( stderr, "Error: Wrong length of data line: %d for %s", line + 1, file );
      exit( EXIT_FAILURE );
	}
	
	for( _SIZE j = 0; j < lCount; j += 2 ) {
	  _CHAR tileChars[ 5 ] = { 0 };
	  strncpy( tileChars, chs + i + j, 2 );
	  _INDEX tID;
	  bool found = getTileID( TRN, tileChars, tID );
	  if( found ) {
        mapUnit mU;
		mU.f_id = tID;
		map[ line ].push_back( mU );
		if( tID == T_SPACE )
	      water = true;
		
	  }
	  else {
	    fprintf( stderr, "Error: Unknown tile representation at %d (\"%s\") in %s line: %d", i + j, tileChars, file, line + 1 );
        exit( EXIT_FAILURE );
  	  }
	}
	i += lCount;
	while( chs[ i ] != 0 && (chs[ i ] == '\n' || chs[ i ] == '\r') ) i++;
    if( chs[ i ]  == '.' && (chs[ i + 1 ]  == '\n' || chs[ i + 1 ]  == '\r') )
	  break;
  }
  
  rows = map.size();
  cols = map[ 0 ].size();
  theWindow* win = Game.screens[ SCREEN_GAME ].windows[ WINDOW_LEVEL ];
  win->sectorWidth = Game.res->mainTileset.tiles[ 0 ]->w;
  win->sectorHeight = Game.res->mainTileset.tiles[ 0 ]->h;
  win->planesWidth = win->sectorWidth * cols;
  win->planesHeight = win->sectorHeight * rows;
  win->winRec.w = win->planesWidth;
  win->winRec.h = win->planesHeight;
  
  if( water ) {
    win->addPlaneMatrix();
    win->makeBackgroundMatrix( 0,  Game.res->bGround[ BGR_LEVEL ] );
  }
  win->addPlaneMatrix();
  for( _SIZE r = 0; r < rows; r++ )
  {
    for( _SIZE c = 0; c < cols; c++ )
	{
	  if( map[ r ][ c ].f_id < Game.res->mainTileset.tiles.size() && map[ r ][ c ].f_id != T_SPACE )
	    win->putOnMatrix( 1, Game.res->mainTileset.tiles[ map[ r ][ c ].f_id ], c * win->sectorWidth, r * win->sectorHeight );
	}
  }
  
  delete[] chs;
}