#include "../framework_dependent/fw.h"
#include "screen.h"
#include "resources.h"
#include "../level.h"
#include "../game.h"

extern _SURFACE* MainScreen;
extern theGame Game;
theWindow::theWindow() {
  winWidth = planesWidth = Game.scrWidth;
  winHeight = planesHeight = Game.scrHeight;
  winPosX = winPosY = bgPosX = bgPosY = 0;
}

void theWindow::redrawAllPlanes() {
  _RECTANGLE s;
  s.w = winWidth;
  s.h = winHeight;
  s.x = bgPosX;
  s.y = bgPosY;
  _RECTANGLE d;
  d.w = winWidth;
  d.h = winHeight;
  d.x = winPosX;
  d.y = winPosY;
  for( uint8 i = 0; i < regularPlanesNR; i++ ) {
    _SURFACE_BLIT( planes[ i ], &s, MainScreen, &d );
  }
  _UPDATE_SURFACE( MainScreen, d.x, d.y, d.w, d.h );
}
