#include "framework_dependent/fw.h"
#include "engine2d/resources.h"
#include "config.h"
#include "config_resources.h"

appResources::appResources()
{
  mainTileset.loadFromFile( RES_MAIN_TILESET, 0, 0 );
  bGround.resize( MAX_BGRS );
  bGround[ BGR_MENU ] = _LOAD_IMG( RES_MENU_BACKGROUND );
  bGround[ BGR_LEVEL ] = _LOAD_IMG( RES_BACKGROUND );
  font.loadFromFile( RES_FONT1, FONT1_COLS, FONT1_ROWS );
  font.changeColor( COLOR_BLANK, FONT_MENU_COLOR );
  font.translucentToTransparent();
}

