#include "framework_dependent/fw.h"
#include "engine2d/resources.h"
#include "config.h"

appResources::appResources()
{
  mainTileset.loadFromFile( RES_MAIN_TILESET, 0, 0 );
  bGround = _LOAD_IMG( RES_BACKGROUND );
}
