#include "framework_dependent/fw.h"
#include "engine2d/resources.h"
#include "config.h"
#include "config_resources.h"

void prepareMainTiles( appResources* res )
{
  res->mainTileset.tiles[ T_HOLE ] = apply_pixelsRev( 0, 0, res->mainTileset.tiles[ T_FLOOR ], res->mainTileset.tiles[ T_HOLE ] );

  res->mainTileset.copyTile( T_N0 );
  res->mainTileset.copyTile( T_N1 );
  res->mainTileset.copyTile( T_N2 );
  res->mainTileset.copyTile( T_N3 );
  res->mainTileset.copyTile( T_N4 );
  res->mainTileset.copyTile( T_N5 );
  res->mainTileset.copyTile( T_N6 );
  res->mainTileset.copyTile( T_N7 );
  res->mainTileset.copyTile( T_N8 );
  res->mainTileset.copyTile( T_N9 );

  for( Uint32 i = T_N0; i <= T_N9; i++ ) {
    res->mainTileset.changeColor( 0xffffffff, NUMBER_COLOR1, i );
    res->mainTileset.tiles[ i ] = apply_pixelsRev( 0, 0, res->mainTileset.tiles[ T_BOX ], res->mainTileset.tiles[ i ] );

  }
  for( Uint32 i = T_DN0; i <= T_DN9; i++ ) {
    res->mainTileset.changeColor( 0xffffffff, NUMBER_COLOR2, i );
    res->mainTileset.tiles[ i ] = apply_pixelsRev( 0, 0, res->mainTileset.tiles[ T_BOX ], res->mainTileset.tiles[ i ] );
  }

  res->mainTileset.copyTile( T_MAGNET );
  res->mainTileset.simpleRotation( -1, -90 );
  res->mainTileset.copyTile( T_MAGNET );
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_MAGNET );
  res->mainTileset.simpleRotation( -1, 180 );

  res->mainTileset.copyTile( T_QUARTER1 );       //red up
  res->mainTileset.copyTile( T_QUARTER1 );       //red down
  res->mainTileset.simpleRotation( -1, 180 );
  res->mainTileset.copyTile( T_QUARTER2 );       //yellow left
  res->mainTileset.simpleRotation( -1, -90 );
  res->mainTileset.copyTile( T_QUARTER2 );       //yellow right
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_QUARTER3 );       //blue left
  res->mainTileset.simpleRotation( -1, -90 );
  res->mainTileset.copyTile( T_QUARTER3 );       //blue right
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_QUARTER3 );       //blue up
  res->mainTileset.copyTile( T_QUARTER3 );       //blue down
  res->mainTileset.simpleRotation( -1, 180 );
  res->mainTileset.copyTile( T_QUARTER2 );       //yellow up
  res->mainTileset.copyTile( T_QUARTER2 );       //yellow down
  res->mainTileset.simpleRotation( -1, 180 );
  res->mainTileset.copyTile( T_QUARTER1 );       //red left
  res->mainTileset.simpleRotation( -1, -90 );
  res->mainTileset.copyTile( T_QUARTER1 );       //red right
  res->mainTileset.simpleRotation( -1, 90 );

  res->mainTileset.copyTile( T_PLAYER_EA );
  res->mainTileset.simpleRotation( -1, 180 );
  res->mainTileset.copyTile( T_PLAYER_EA );
  res->mainTileset.simpleRotation( -1, -90 );
  res->mainTileset.copyTile( T_PLAYER_EA );
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_PLAYER_MSA );
  res->mainTileset.simpleRotation( -1, 180 );
  res->mainTileset.copyTile( T_PLAYER_MSA );
  res->mainTileset.simpleRotation( -1, -90 );
  res->mainTileset.copyTile( T_PLAYER_MSA );
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_PLAYER_PU );
  res->mainTileset.simpleRotation( -1, 180 );
  res->mainTileset.copyTile( T_PLAYER_PU );
  res->mainTileset.simpleRotation( -1, -90 );
  res->mainTileset.copyTile( T_PLAYER_PU );
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_PASS1 );
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_PASS2 );
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_PASS3 );
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_PASS4 );
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_PASS5 );
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_PASS6 );
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_PLATFORM_UP );
  res->mainTileset.simpleRotation( -1, 180 );
  res->mainTileset.copyTile( T_PLATFORM_UP );
  res->mainTileset.simpleRotation( -1, -90 );
  res->mainTileset.copyTile( T_PLATFORM_UP );
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_PLATFORM_VERTICAL );
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_ARROW_UP );
  res->mainTileset.simpleRotation( -1, 180 );
  res->mainTileset.copyTile( T_ARROW_UP );
  res->mainTileset.simpleRotation( -1, -90 );
  res->mainTileset.copyTile( T_ARROW_UP );
  res->mainTileset.simpleRotation( -1, 90 );
  res->mainTileset.copyTile( T_PASS1_H );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_LEFT ], res->mainTileset.tiles[ T_PASS1_LEFT ] );
  res->mainTileset.copyTile( T_PASS2_H );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_LEFT ], res->mainTileset.tiles[ T_PASS2_LEFT ] );
  res->mainTileset.copyTile( T_PASS3_H );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_LEFT ], res->mainTileset.tiles[ T_PASS3_LEFT ] );
  res->mainTileset.copyTile( T_PASS4_H );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_LEFT ], res->mainTileset.tiles[ T_PASS4_LEFT ] );
  res->mainTileset.copyTile( T_PASS5_H );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_LEFT ], res->mainTileset.tiles[ T_PASS5_LEFT ] );
  res->mainTileset.copyTile( T_PASS6_H );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_LEFT ], res->mainTileset.tiles[ T_PASS6_LEFT ] );

  res->mainTileset.copyTile( T_PASS1_H );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_RIGHT ], res->mainTileset.tiles[ T_PASS1_RIGHT ] );
  res->mainTileset.copyTile( T_PASS2_H );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_RIGHT ], res->mainTileset.tiles[ T_PASS2_RIGHT ] );
  res->mainTileset.copyTile( T_PASS3_H );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_RIGHT ], res->mainTileset.tiles[ T_PASS3_RIGHT ] );
  res->mainTileset.copyTile( T_PASS4_H );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_RIGHT ], res->mainTileset.tiles[ T_PASS4_RIGHT ] );
  res->mainTileset.copyTile( T_PASS5_H );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_RIGHT ], res->mainTileset.tiles[ T_PASS5_RIGHT ] );
  res->mainTileset.copyTile( T_PASS6_H );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_RIGHT ], res->mainTileset.tiles[ T_PASS6_RIGHT ] );

  res->mainTileset.copyTile( T_PASS1 );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_UP ], res->mainTileset.tiles[ T_PASS1_UP ] );
  res->mainTileset.copyTile( T_PASS2 );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_UP ], res->mainTileset.tiles[ T_PASS2_UP ] );
  res->mainTileset.copyTile( T_PASS3 );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_UP ], res->mainTileset.tiles[ T_PASS3_UP ] );
  res->mainTileset.copyTile( T_PASS4 );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_UP ], res->mainTileset.tiles[ T_PASS4_UP ] );
  res->mainTileset.copyTile( T_PASS5 );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_UP ], res->mainTileset.tiles[ T_PASS5_UP ] );
  res->mainTileset.copyTile( T_PASS6 );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_UP ], res->mainTileset.tiles[ T_PASS6_UP ] );

  res->mainTileset.copyTile( T_PASS1 );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_DOWN ], res->mainTileset.tiles[ T_PASS1_DOWN ] );
  res->mainTileset.copyTile( T_PASS2 );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_DOWN ], res->mainTileset.tiles[ T_PASS2_DOWN ] );
  res->mainTileset.copyTile( T_PASS3 );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_DOWN ], res->mainTileset.tiles[ T_PASS3_DOWN ] );
  res->mainTileset.copyTile( T_PASS4 );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_DOWN ], res->mainTileset.tiles[ T_PASS4_DOWN ] );
  res->mainTileset.copyTile( T_PASS5 );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_DOWN ], res->mainTileset.tiles[ T_PASS5_DOWN ] );
  res->mainTileset.copyTile( T_PASS6 );
  _APPLY_SURFACE( 0, 0, res->mainTileset.tiles[ T_ARROW_DOWN ], res->mainTileset.tiles[ T_PASS6_DOWN ] );

  res->animations.resize( 5 );
  res->animations[ ID_ANIMATION_CRUMBLE ].loadFromFile( RES_ANIMATION_CRUMBLE, 0, 0 );
  res->animations[ ID_ANIMATION_EXPLODE_EA ].loadFromFile( RES_ANIMATION_EXPLODE_EA, 0, 0 );
  res->animations[ ID_ANIMATION_EXPLODE_MSA ].loadFromFile( RES_ANIMATION_EXPLODE_MSA, 0, 0 );
  res->animations[ ID_ANIMATION_EXPLODE ].loadFromFile( RES_ANIMATION_EXPLODE, 40, 40 );
  res->animations[ ID_ANIMATION_SPLASH ].loadFromFile( RES_ANIMATION_SPLASH, 0, 0 );
  res->mainTileset.tiles.push_back( res->animations[ ID_ANIMATION_CRUMBLE ].tiles[ 0 ] );
  res->mainTileset.tiles.push_back( res->animations[ ID_ANIMATION_EXPLODE_MSA ].tiles[ 0 ] );
  res->mainTileset.tiles.push_back( res->animations[ ID_ANIMATION_EXPLODE_EA ].tiles[ 0 ] );

}

void prepareSequences( appResources* res )
{
  res->tileSequences.resize( 1 );
  res->tileSequences[ 0 ].prepare( &res->animations[ ID_ANIMATION_EXPLODE ] );
  
}

appResources::appResources()
{
  mainTileset.loadFromFile( RES_MAIN_TILESET, 0, 0 );
  bGround.resize( MAX_BGRS );
  bGround[ BGR_MENU ] = _LOAD_IMG( RES_MENU_BACKGROUND );
  bGround[ BGR_MENU_LIST ] = _CREATE_RGBA_SURFACE( 64, 64, MENU_BG_COLOR );
  bGround[ BGR_LEVEL ] = _LOAD_IMG( RES_BACKGROUND );
  font.loadFromFile( RES_FONT1, FONT1_W, FONT1_H );
  font.changeColor( COLOR_BLANK, FONT_MENU_COLOR );
  font.translucentToTransparent();
  
  prepareMainTiles( this );
  prepareSequences( this );
}

