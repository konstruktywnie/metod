
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
  _SIZE planesWidth, planesHeight, sectorWidth, sectorHeight;
  _POS bgPosX, bgPosY;
  _RECTANGLE winRec;
  _SURFACE* background;
  bool anchoredText, border;
  
  theWindow();
  void addPlane( _INDEX nr );
  void addPlane();
  void addFilledPlane();
  void redrawAllPlanes();
  void makeBackground( _SURFACE* d, _SURFACE* s );
  void placeRectangle( _SURFACE* d, _POS x, _POS y, _SIZE w, _SIZE h, _COLOR color );
  void placeRectangle( _SURFACE* d, _POS x, _POS y, _SIZE w, _SIZE h, _COLOR color, _SIZE bw, _COLOR bColor );
  _SIZE print( tileSet* font, _SURFACE* d, _POS x, _POS y, const char *fmt, ... );

  void addPlaneMatrix( _SIZE sectorWidth, _SIZE sectorHeight );
  void addPlaneMatrix();
  void makeBackgroundMatrix( _SIZE sw, _SIZE sh );
  void makeBorder( _SIZE bw, _COLOR bc );
  void redrawMatrix( _INDEX index, _SIZE row, _SIZE col, _SIZE rowL, _SIZE colL, _POS visFX, _POS visFY, _SIZE visFW, _SIZE visFH );
  void redrawVObjs( _INDEX index, _POS visFX, _POS visFY, _SIZE visFW, _SIZE visFH );
  void putOnMatrix( _INDEX i, _SURFACE* s, _POS posx, _POS posy );
  void print_vo_sizes( _INDEX index );
  void onMatrixCoordinates( _INDEX index, _POS x, _POS y, _SIZE w, _SIZE h, _SIZE& row, _SIZE& col, _SIZE& rowL, _SIZE& colL );
//  void prepareMatrixToDraw( _INDEX i, _POS x, _POS y, _SIZE w, _SIZE h );
  void prepareMatrixToDraw( _INDEX i, _SIZE row, _SIZE col, _SIZE rowL, _SIZE colL );
  bool visibleInWindow( _POS fx, _POS fy, _SIZE fw, _SIZE fh, _POS& vis_fx, _POS& vis_fy, _SIZE& vis_fw, _SIZE& vis_fh );
  bool visibleField( _POS fx, _POS fy, _SIZE fw, _SIZE fh, _POS sx, _POS sy, _POS sw, _POS sh, _POS& vis_sx, _POS& vis_sy, _SIZE& vis_sw, _SIZE& vis_sh );
  void redrawField( _POS x, _POS y, _SIZE w, _SIZE h );
  void redraw();
  void newVObj( _INDEX p, _INDEX i, _SURFACE* s, _POS x, _POS y );
  // void checkMatrixOpacity( _SIZE index );
};

struct theScreen {
  static _SIZE scrWidth, scrHeight;
  vector<theWindow*> windows;
  
  theScreen();
  void addWindow( _POS x, _POS y, _SIZE w, _SIZE h );
  void addWindow();
  void redraw();
};
