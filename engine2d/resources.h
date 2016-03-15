struct tileSet 
{
  vector<_SURFACE*> tiles;
  uint32 loadFromFile( char* f, _SIZE tileWidth, _SIZE tileHeight );
  void changeColor( _COLOR search, _COLOR changeTo, uint32 id );
  void changeColor( _COLOR search, _COLOR changeTo );
  void changeColorAtAlpha( _COLOR changeTo );
  void translucentToTransparent();
};
struct appResources 
{
  tileSet mainTileset, font;
  vector<_SURFACE*> bGround;
  appResources();
};

