
enum ProgEventNames { EVENT_TILESET_ANIMATION = 0, EVENT_MOVE_OBJ, EVENT_TILESET_COLLIDED, EVENT_TILESET_COLLIDED_FULL, EVENT_WINDOW_SCROLL, EVENT_TILESET_ANIMATION_ENDED_LOOP, EVENT_TILESET_ENDED_MOVCOUNTER, MAX_ProgEventNames };
enum GameEventNames { EVENT_GAME_FULL_HOLE = 0, EVENT_UPDATE_INFO, MAX_GameEventNames };
enum KeysNames { K_UP = 0, K_LEFT, K_RIGHT, K_DOWN, K_LCTRL, K_LALT, K_SPACE, MAX_KeysNames };

void attendProgEvents( _EVENT* event );
void attendKeyEvents();
void attendKeyEventsMenu();
void attendGameEvents();
