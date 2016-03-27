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

  _SIZE fw = res->font.tiles[ 0 ]->w;
  _SIZE fh = res->font.tiles[ 0 ]->h;
  
  screens[ SCREEN_MENU ].addWindow( MENU_POSX, MENU_POSY, MENU_WIDTH, MENU_HEIGHT );
  theWindow* menuW2 = screens[ SCREEN_MENU ].windows[ 1 ];
  menuW2->background = res->bGround[ BGR_MENU_LIST ];
  //menuW2->placeRectangle( menuW2->background, 0, 0, menuW2->background->w, menuW2->background->h, 0, BORDER_MENU_WIDTH, BORDER_MENU_COLOR );
  menuW2->makeBackgroundMatrix( res->bGround[ BGR_MENU_LIST ]->w, res->bGround[ BGR_MENU_LIST ]->h );
  menuW2->makeBorder( BORDER_MENU_WIDTH, BORDER_MENU_COLOR );
  
  theWindow* menuW = screens[ SCREEN_MENU ].windows[ 0 ];
  menuW->background = res->bGround[ BGR_MENU ];
  menuW->makeBackgroundMatrix( res->bGround[ BGR_MENU ]->w, res->bGround[ BGR_MENU ]->h );
  _SURFACE* mTitle = _CREATE_RGBA_SURFACE( TITLE_WIDTH, TITLE_HEIGHT, TITLE_BG_COLOR );
  //_SURFACE* mMain = _CREATE_RGBA_SURFACE( MENU_WIDTH, MENU_HEIGHT, MENU_BG_COLOR );
  _SURFACE* txtChoose = _CREATE_RGBA_SURFACE( fw * strlen( MENU_CHOOSE_LEVEL_TXT ), fh, 0 );
  _SURFACE* txtExit = _CREATE_RGBA_SURFACE( fw * strlen( MENU_EXIT_TXT ), fh, 0 );
  menuW->placeRectangle( mTitle, 0, 0, mTitle->w, mTitle->h, 0, BORDER_MENU_WIDTH, BORDER_MENU_COLOR );
  //menuW->placeRectangle( mMain, 0, 0, mMain->w, mMain->h, 0, BORDER_MENU_WIDTH, BORDER_MENU_COLOR );
  
  menuW->anchoredText = true;
  menuW->print( &res->font, mTitle, 35, 15, TITLE_TEXT );
  menuW2->anchoredText = false;
  menuW2->print( &res->font, txtChoose, 0, 0, MENU_CHOOSE_LEVEL_TXT );
  menuW2->print( &res->font, txtExit, 0, 0, MENU_EXIT_TXT );

  menuW->newVObj( 0, 0, mTitle, TITLE_TEXT_POSX, TITLE_TEXT_POSY );
  //menuW2->newVObj( 0, 1, mMain, MENU_POSX, MENU_POSY );
  menuW2->newVObj( 0, 0, txtChoose, MENU_TXT_POSX, MENU_TXT_POSY );
  menuW2->newVObj( 0, 1, txtExit, MENU_EXIT_POSX, MENU_EXIT_POSY );
  
/*    
  menuW->bgPosX = 20;
  menuW->bgPosY = 20;
  menuW->winRec.w = 300;
  menuW->winRec.h = 300;
  menuW->winRec.x = 100;
  menuW->winRec.y = 100;
  */
  
  //_SURFACE* txtTitle = _CREATE_RGBA_SURFACE( MENU_WIDTH, MENU_HEIGHT, MENU_BG_COLOR );
  
}

theGame::theGame() {
  res = new appResources;
  screens = new theScreen [ MAX_ScreensNames ];
  
  buildMenu();  
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
 // _SURFACE* m = _CREATE_RGBA_SURFACE( MENU_WIDTH, MENU_HEIGHT, MENU_BG_COLOR );
 // Game.screens[ SCREEN_MENU ].windows[ 0 ]->putOnMatrix( 0, m, MENU_POSX, MENU_POSY );
  Game.screens[ SCREEN_MENU ].redraw();
 
 //Game.screens[ SCREEN_MENU ].windows[ 0 ]->redrawField( 0, 0, Game.screens[ SCREEN_MENU ].windows[ 0 ]->winRec.w, Game.screens[ SCREEN_MENU ].windows[ 0 ]->winRec.h );
}
