bool KEvents[ MAX_KeysNames ] = { false };
bool PEvents[ MAX_ProgEventNames ] = { false };
bool GEvents[ MAX_GameEventNames ] = { false };

void (*KeyEventsTab[ 2 ])() = { attendKeyEventsMenu, attendKeyEvents };

_SURFACE* MainScreen;
theGame Game;
