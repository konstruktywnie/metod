#include "framework_dependent/fw.h"
#include "config.h"
#include "resources.h"
#include "screen.h"
#include "level.h"
#include "game.h"

theGame::theGame() {
  scrWidth = SCREEN_RESOLUTION_W;
  scrHeight = SCREEN_RESOLUTION_H;
  res = new appResources;
  screens = new theScreen [ MAX_ScreensNames ];
  screens[ SCREEN_MENU ].windows.resize( 1 );
  screens[ SCREEN_MENU ].windows[ 0 ] = new theWindow;
  screens[ SCREEN_MENU ].windows[ 0 ]->planes.resize( 1 );
  //screens[ SCREEN_MENU ].windows[ 0 ]->planes[ 0 ] = _LOAD_IMG( RES_BACKGROUND );
  screens[ SCREEN_MENU ].windows[ 0 ]->regularPlanesNR = 1;
  screens[ SCREEN_MENU ].windows[ 0 ]->planes[ 0 ] = optimizedSurface( RES_BACKGROUND, scrWidth, scrHeight );
  
}


extern theGame Game;
void initGame() {
  Game.screens[ SCREEN_MENU ].windows[ 0 ]->redrawAllPlanes();
}
