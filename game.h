
struct theGame {
  theScreen* screens;
  _INDEX actualScr;
  theLevel* lvl;
  appResources* res;
  
  theGame();
  void buildMenu();
  void buildLevel( _CHAR* name );
  
};
