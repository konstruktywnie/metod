
struct theGame {
  uint32 scrWidth, scrHeight;
  theScreen* screens;
  uint8 actualScr;
  theLevel* lvl;
  appResources* res;
  
  theGame();
};
