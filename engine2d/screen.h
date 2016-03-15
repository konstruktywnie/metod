
struct theWindow {
  vector<_SURFACE*> planes;
  uint32 winWidth, winHeight, planesWidth, planesHeight;
  uint32 winPosX, winPosY, bgPosX, bgPosY, marginX, marginY;
  uint8 regularPlanesNR;
  bool actualScroll, scrollH, scrollV;
  
  theWindow();
  void addPlane( uint8 nr );
  void addPlane();
  void addFilledPlane();
  void redrawAllPlanes();
  uint32 print( tileSet* font, uint8 planeNR, uint32 x, uint32 y, const char *fmt, ... );
  void makeBackground( uint8 planeNr, _SURFACE* s );
  void placeRectangle( uint8 planeNr, uint32 x, uint32 y, uint32 w, uint32 h, _COLOR color );
  void placeRectangle( uint8 planeNr, uint32 x, uint32 y, uint32 w, uint32 h, _COLOR color, uint8 bw, _COLOR bColor );
};

struct theScreen {
  static uint32 scrWidth, scrHeight;
  vector<theWindow*> windows;
  
  theScreen();
  void addWindow( uint8 nr );
  void addWindow();
};
