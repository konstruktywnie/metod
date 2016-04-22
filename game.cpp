#include "framework_dependent/fw.h"
#include "config.h"
#include "config_resources.h"
#include "config_screen.h"
#include "engine2d/resources.h"
#include "engine2d/screen.h"
#include "level.h"
#include "game.h"

_SIZE theScreen::scrWidth = SCREEN_RESOLUTION_W;
_SIZE theScreen::scrHeight = SCREEN_RESOLUTION_H;

void theGame::buildMenu() 
{/*
  theWindow* menuW = screens[ SCREEN_MENU ].windows[ 0 ];
  menuW->addPlane();
  menuW->planes[ 0 ] = _CREATE_RGBA_SURFACE( theScreen::scrWidth, theScreen::scrHeight );
  menuW->makeBackground( menuW->planes[ 0 ], res->bGround[ BGR_MENU ] );
  menuW->placeRectangle( menuW->planes[ 0 ], MENU_POSX, MENU_POSY, MENU_WIDTH, MENU_HEIGHT, MENU_BG_COLOR, BORDER_MENU_WIDTH, BORDER_MENU_COLOR  );
  menuW->placeRectangle( menuW->planes[ 0 ], TITLE_POSX, TITLE_POSY, TITLE_WIDTH, TITLE_HEIGHT, TITLE_BG_COLOR, BORDER_MENU_WIDTH, BORDER_MENU_COLOR );
  menuW->print( &res->font, menuW->planes[ 0 ], TITLE_TEXT_POSX, TITLE_TEXT_POSY, TITLE_TEXT );
  menuW->print( &res->font, menuW->planes[ 0 ], MENU_TXT_POSX, MENU_TXT_POSY, MENU_CHOOSE_LEVEL_TXT );
  menuW->print( &res->font, menuW->planes[ 0 ], MENU_EXIT_POSX, MENU_EXIT_POSY, MENU_EXIT_TXT );
*/

  screens[ SCREEN_MENU ].addWindow( TITLE_POSX, TITLE_POSY, TITLE_WIDTH, TITLE_HEIGHT );
  screens[ SCREEN_MENU ].addWindow( MENU_POSX, MENU_POSY, MENU_WIDTH, MENU_HEIGHT );

  theWindow* menuW = screens[ SCREEN_MENU ].windows[ 0 ];
  theWindow* menuW1 = screens[ SCREEN_MENU ].windows[ 1 ];
  theWindow* menuW2 = screens[ SCREEN_MENU ].windows[ 2 ];

  menuW->addPlaneMatrix( res->bGround[ BGR_MENU ]->w, res->bGround[ BGR_MENU ]->h );
  menuW->makeBackgroundMatrix( 0, res->bGround[ BGR_MENU ] );
  menuW1->addPlaneMatrix();
  menuW2->addPlaneMatrix( res->bGround[ BGR_MENU_LIST ]->w, res->bGround[ BGR_MENU_LIST ]->h );
  menuW2->makeBackgroundMatrix( 0, res->bGround[ BGR_MENU_LIST ] );

  _SURFACE* mTitle = _CREATE_RGBA_SURFACE( TITLE_WIDTH, TITLE_HEIGHT, MENU_BG_COLOR );
  _SURFACE* txtChoose = _CREATE_RGBA_SURFACE( res->font.tiles[ 0 ]->w * strlen( MENU_CHOOSE_LEVEL_TXT ), res->font.tiles[ 0 ]->h, 0 );
  _SURFACE* txtExit = _CREATE_RGBA_SURFACE( res->font.tiles[ 0 ]->w * strlen( MENU_EXIT_TXT ), res->font.tiles[ 0 ]->h, 0 );
  
  menuW1->anchoredText = true;
  menuW1->print( &res->font, mTitle, TITLE_TEXT_POSX, TITLE_TEXT_POSY, TITLE_TEXT );
  menuW2->anchoredText = false;
  menuW2->print( &res->font, txtChoose, 0, 0, MENU_CHOOSE_LEVEL_TXT );
  menuW2->print( &res->font, txtExit, 0, 0, MENU_EXIT_TXT );

  menuW1->putOnMatrix( 0, mTitle, 0, 0 );
  menuW2->addPlaneMatrix();
  menuW2->putOnMatrix( 1, txtChoose, MENU_TXT_POSX, MENU_TXT_POSY );
  menuW2->putOnMatrix( 1, txtExit, MENU_EXIT_POSX, MENU_EXIT_POSY );

  /*
  menuW1->newVObj( 0, 0, mTitle, 0, 0 );
  menuW2->newVObj( 0, 0, txtChoose, MENU_TXT_POSX, MENU_TXT_POSY );
  menuW2->newVObj( 0, 1, txtExit, MENU_EXIT_POSX, MENU_EXIT_POSY );
*/


  menuW1->makeBorder( BORDER_MENU_WIDTH, BORDER_MENU_COLOR );
  menuW2->makeBorder( BORDER_MENU_WIDTH, BORDER_MENU_COLOR );

  
  //menuW->upperWindow = menuW2;
    /*
  menuW->bgPosX = 100;
  menuW->bgPosY = 40;
  menuW->winRec.w = 400;
  menuW->winRec.h = 400;
  menuW->winRec.x = 50;
  menuW->winRec.y = 130;
  */
  
  //_SURFACE* txtTitle = _CREATE_RGBA_SURFACE( MENU_WIDTH, MENU_HEIGHT, MENU_BG_COLOR );
  
}

theGame::theGame() {
  res = new appResources;
  screens = new theScreen [ MAX_ScreensNames ];
  
  buildMenu();  
}

void theGame::buildLevel( _CHAR* name )
{
  lvl = new theLevel;
  lvl->player = new thePlayer;
  lvl->buildMap( name );
  
    
}

extern theGame Game;
void initGame() {

 //fprintf( stderr, "\e[2J  \e[48;2;25;255;255m test \e[0m \e[3;1f \e[31m test2 \e[0m\n" );


 // Game.screens[ SCREEN_MENU ].windows[ 0 ]->redrawAllPlanes();
  //Game.screens[ SCREEN_MENU ].windows[ 0 ]->addPlaneMatrix( 50, 50 );
  //Game.screens[ SCREEN_MENU ].windows[ 0 ]->print_vo_sizes( 0 );
/*
  Game.screens[ SCREEN_MENU ].windows[ 0 ]->winRec.w = 300;
  Game.screens[ SCREEN_MENU ].windows[ 0 ]->winRec.h = 300;
  Game.screens[ SCREEN_MENU ].windows[ 0 ]->winRec.x = 0;
  Game.screens[ SCREEN_MENU ].windows[ 0 ]->winRec.y = 0;
  Game.screens[ SCREEN_MENU ].windows[ 0 ]->bgPosX = 58;
  Game.screens[ SCREEN_MENU ].windows[ 0 ]->bgPosY = 10;
  */
 
  //Game.screens[ SCREEN_MENU ].redraw();
  Game.buildLevel( "data\\levels\\tutorial 1" );
  
  Game.screens[ SCREEN_GAME ].windows[ WINDOW_LEVEL ]->addPlaneMatrix();
  Game.screens[ SCREEN_GAME ].windows[ WINDOW_LEVEL ]->putSeqOnMatrix( 3, &Game.res->tileSequences[ 0 ], 0, 0 );
  
  Game.screens[ SCREEN_GAME ].redraw();
  
}
