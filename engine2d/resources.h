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

bool jointField( _POS f1x, _POS f1y, _SIZE f1w, _SIZE f1h, _POS f2x, _POS f2y, _POS f2w, _POS f2h, _POS& jf1x, _POS& jf1y, _POS& jf2x, _POS& jf2y, _SIZE& jfw, _SIZE& jfh );
bool jointField( _POS f1x, _POS f1y, _SIZE f1w, _SIZE f1h, _POS f2x, _POS f2y, _POS f2w, _POS f2h, _POS& jf1x, _POS& jf1y, _SIZE& jfw, _SIZE& jfh );