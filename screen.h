
enum ScreensNames { SCREEN_GAME = 0, SCREEN_MENU, SCREEN_INTRO, MAX_ScreensNames };

struct theWindow {
  vector<_SURFACE*> planes;
  uint32 winWidth, winHeight, planesWidth, planesHeight;
  uint32 winPosX, winPosY, bgPosX, bgPosY, marginX, marginY;
  uint8 regularPlanesNR;
  bool actualScroll, scrollH, scrollV;
  
  void redrawAllPlanes();
  theWindow();
};

struct theScreen {
  vector<theWindow*> windows;
};
