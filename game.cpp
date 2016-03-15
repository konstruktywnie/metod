#include "framework_dependent/fw.h"
#include "config.h"
#include "config_resources.h"
#include "config_screen.h"
#include "engine2d/resources.h"
#include "engine2d/screen.h"
#include "level.h"
#include "game.h"

uint32 theScreen::scrWidth = SCREEN_RESOLUTION_W;
uint32 theScreen::scrHeight = SCREEN_RESOLUTION_H;

void theGame::buildMenu() 
{
  screens[ SCREEN_MENU ].windows[ 0 ]->makeBackground( 0, res->bGround[ BGR_MENU ] );
  screens[ SCREEN_MENU ].windows[ 0 ]->placeRectangle( 0, MENU_POSX, MENU_POSY, MENU_WIDTH, MENU_HEIGHT, MENU_BG_COLOR, BORDER_MENU_WIDTH, BORDER_MENU_COLOR  );
  screens[ SCREEN_MENU ].windows[ 0 ]->placeRectangle( 0, TITLE_POSX, TITLE_POSY, TITLE_WIDTH, TITLE_HEIGHT, TITLE_BG_COLOR, BORDER_MENU_WIDTH, BORDER_MENU_COLOR );
  screens[ SCREEN_MENU ].windows[ 0 ]->print( &res->font, 0, TITLE_TEXT_POSX, TITLE_TEXT_POSY, TITLE_TEXT );
  screens[ SCREEN_MENU ].windows[ 0 ]->print( &res->font, 0, MENU_TXT_POSX, MENU_TXT_POSY, MENU_CHOOSE_LEVEL_TXT );
  screens[ SCREEN_MENU ].windows[ 0 ]->print( &res->font, 0, MENU_EXIT_POSX, MENU_EXIT_POSY, MENU_EXIT_TXT );
}

theGame::theGame() {
  res = new appResources;
  screens = new theScreen [ MAX_ScreensNames ];
  buildMenu();  
}


extern theGame Game;
void initGame() {
  //Game.screens[ SCREEN_MENU ].windows[ 0 ]->print( &Game.res->font, 0, 0, 0, "test\n@#$@!!&$" );
  Game.screens[ SCREEN_MENU ].windows[ 0 ]->redrawAllPlanes();

}
