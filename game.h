
struct theGame {
  theScreen* screens;
  uint8 actualScr;
  theLevel* lvl;
  appResources* res;
  
  theGame();
  void buildMenu();

};
