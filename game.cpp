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
{
  theWindow* menuW = screens[ SCREEN_MENU ].windows[ 0 ];
  menuW->addPlane();
  menuW->planes[ 0 ] = _CREATE_RGBA_SURFACE( theScreen::scrWidth, theScreen::scrHeight );
  menuW->makeBackground( menuW->planes[ 0 ], res->bGround[ BGR_MENU ] );
  menuW->placeRectangle( menuW->planes[ 0 ], MENU_POSX, MENU_POSY, MENU_WIDTH, MENU_HEIGHT, MENU_BG_COLOR, BORDER_MENU_WIDTH, BORDER_MENU_COLOR  );
  menuW->placeRectangle( menuW->planes[ 0 ], TITLE_POSX, TITLE_POSY, TITLE_WIDTH, TITLE_HEIGHT, TITLE_BG_COLOR, BORDER_MENU_WIDTH, BORDER_MENU_COLOR );
  menuW->print( &res->font, menuW->planes[ 0 ], TITLE_TEXT_POSX, TITLE_TEXT_POSY, TITLE_TEXT );
  menuW->print( &res->font, menuW->planes[ 0 ], MENU_TXT_POSX, MENU_TXT_POSY, MENU_CHOOSE_LEVEL_TXT );
  menuW->print( &res->font, menuW->planes[ 0 ], MENU_EXIT_POSX, MENU_EXIT_POSY, MENU_EXIT_TXT );
}

theGame::theGame() {
  res = new appResources;
  screens = new theScreen [ MAX_ScreensNames ];
  buildMenu();  
}


extern theGame Game;
void initGame() {

 //fprintf( stderr, "\e[2J  \e[48;2;25;255;255m test \e[0m \e[3;1f \e[31m test2 \e[0m\n" );


  Game.screens[ SCREEN_MENU ].windows[ 0 ]->redrawAllPlanes();
  //Game.screens[ SCREEN_MENU ].windows[ 0 ]->addPlaneMatrix( 50, 50 );
  Game.screens[ SCREEN_MENU ].windows[ 0 ]->makeBackgroundMatrix( Game.res->bGround[ BGR_MENU ], Game.res->bGround[ BGR_MENU ]->w, Game.res->bGround[ BGR_MENU ]->h );
  //Game.screens[ SCREEN_MENU ].windows[ 0 ]->print_vo_sizes( 0 );
    
}
