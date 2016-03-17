struct tileSet 
{
  vector<_SURFACE*> tiles;
  _SIZE loadFromFile( char* f, _SIZE tileWidth, _SIZE tileHeight );
  void changeColor( _COLOR search, _COLOR changeTo, _INDEX id );
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

