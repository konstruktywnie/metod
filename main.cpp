void _FRAMEWORK_INIT();
void _FRAMEWORK_LOOP();
void _FRAMEWORK_END();
void initGame();

int main( int argc, char** argv ) {
  _FRAMEWORK_INIT();
  initGame();
  _FRAMEWORK_LOOP();
  _FRAMEWORK_END();
  return 0;
}
