struct visObj {
  _POS x, y;
  _SURFACE* s;
  bool drawed;
};

struct tileSet 
{
  vector<_SURFACE*> tiles;
  
  _SIZE loadFromFile( _CHAR* f, _SIZE tileWidth, _SIZE tileHeight );
  void changeColor( _COLOR search, _COLOR changeTo, _INDEX id );
  void changeColor( _COLOR search, _COLOR changeTo );
  void changeColorAtAlpha( _COLOR changeTo );
  void translucentToTransparent();
  void copyTile( _INDEX i );
  void simpleRotation( _INT index, _INT degree );
};
struct sequence
{
  _INT begin, end, actualFrame;
};

struct theWindow;
struct tileSeq
{
  tileSet *ts;
  _INDEX id;
  _INDEX actualSeq;
  _INT nextFrame;
  vector<sequence*> seq;
  visObj* actualVO;
  _TIME interval;
  _TIMER_ID t_id;
  theWindow* win;
  bool looped;
  tileSeq();
  tileSeq( _CHAR* file );
  void prepare( tileSet* t );
  void start();
  void stop();
  void draw();
  
};
struct appResources 
{
  tileSet mainTileset, font;
  vector<tileSet> animations;
  vector<_SURFACE*> bGround;
  vector<tileSeq> tileSequences;
  appResources();
};

void apply_pixels( _POS x, _POS y, _SURFACE* source, _SURFACE* destination );
_SURFACE* apply_pixelsRev( _POS x, _POS y, _SURFACE* source, _SURFACE* destination );
bool jointField( _POS f1x, _POS f1y, _SIZE f1w, _SIZE f1h, _POS f2x, _POS f2y, _POS f2w, _POS f2h, _POS& jf1x, _POS& jf1y, _POS& jf2x, _POS& jf2y, _SIZE& jfw, _SIZE& jfh );
bool jointField( _POS f1x, _POS f1y, _SIZE f1w, _SIZE f1h, _POS f2x, _POS f2y, _POS f2w, _POS f2h, _POS& jf1x, _POS& jf1y, _SIZE& jfw, _SIZE& jfh );