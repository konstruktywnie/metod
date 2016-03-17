
struct visObj {
  _POS x, y;
  _SURFACE* s;
  bool drawed;
};

struct mSector {
  vector<visObj*> vo;
  bool opaque;
};
struct secSize { _SIZE w, h; };

typedef vector< vector<mSector> > sectorsMatrix;

struct theWindow {
  vector<_SURFACE*> planes;
  vector<sectorsMatrix> pMat;
  vector< vector<visObj*> > vObjs;
  vector<secSize> sectorSizes;
  _SIZE winWidth, winHeight, planesWidth, planesHeight;
  _POS winPosX, winPosY, bgPosX, bgPosY, marginX, marginY;
  
  theWindow();
  void addPlane( _INDEX nr );
  void addPlane();
  void addFilledPlane();
  void redrawAllPlanes();
  _SIZE print( tileSet* font, _SURFACE* d, _POS x, _POS y, const char *fmt, ... );
  void makeBackground( _SURFACE* d, _SURFACE* s );
  void placeRectangle( _SURFACE* d, _POS x, _POS y, _SIZE w, _SIZE h, _COLOR color );
  void placeRectangle( _SURFACE* d, _POS x, _POS y, _SIZE w, _SIZE h, _COLOR color, _SIZE bw, _COLOR bColor );
  
  void addPlaneMatrix( _SIZE sectorWidth, _SIZE sectorHeight );
  void makeBackgroundMatrix( _SURFACE* image, _SIZE sw, _SIZE sh );
  void redrawMatrix( _INDEX i, _POS x, _POS y, _SIZE w, _SIZE h );
 // void redrawMatrixesvObjs();
  void putOnMatrix( _INDEX i, _SURFACE* s, _POS posx, _POS posy );
  void prepareMatrixToDraw( _INDEX i, _POS x, _POS y, _SIZE w, _SIZE h );
 // void checkMatrixOpacity( _SIZE index );
};

struct theScreen {
  static _SIZE scrWidth, scrHeight;
  vector<theWindow*> windows;
  
  theScreen();
  void addWindow( _INDEX nr );
  void addWindow();
};
