#define RES_MAIN_TILESET "data/graphics/mainTileset.png"
#define RES_BACKGROUND "data/graphics/water-texture.jpg"
#define RES_FONT1 "data/graphics/f16x20.png"
#define FONT1_W 16
#define FONT1_H 20
#define FONT_MENU_COLOR 0xf0f30aff
#define RES_MENU_BACKGROUND "data/graphics/bkg.jpg"
#define RES_LEVELS_LIST "data/levels/levels"
#define RES_ANIMATION_CRUMBLE "data/graphics/animations/crumble.png"
#define RES_ANIMATION_EXPLODE_EA "data/graphics/animations/Explode_EA.png"
#define RES_ANIMATION_EXPLODE_MSA "data/graphics/animations/Explode_MSA.png"
#define RES_ANIMATION_EXPLODE "data/graphics/animations/Explode.png"
#define RES_ANIMATION_SPLASH "data/graphics/animations/splash.png"

#define NUMBER_COLOR1 0xff0000ff //0xff9c00ff
#define NUMBER_COLOR2 0x000000ff

enum { BGR_MENU = 0, BGR_MENU_LIST, BGR_LEVEL, MAX_BGRS };

enum MainTiles             { T_FLOOR = 0, T_WALL, T_BOX, T_OBSTACLE, T_GEM1, T_GEM2, T_GEM3, T_GEM4, T_GEM5, T_GEM6, T_BALL1, T_BALL2, T_BALL3, T_BALL4, T_BALL5, T_BALL6, T_DOOR1, T_DOOR2, T_DOOR3, T_KEY1, T_KEY2, T_KEY3, T_PASS1, T_PASS2, T_PASS3, T_PASS4, T_PASS5, T_PASS6, T_PLATFORM_UP, T_PLATFORM_VERTICAL, T_PLATFORM_MULTIDIRECT, T_PLAYER_EA, T_PLAYER_MSA, T_EA, T_MSA, T_FUEL, T_DYNAMITE, T_REPAIR, T_TIME, T_ARROW_UP, T_HOLE, T_QUARTER1, T_QUARTER2, T_QUARTER3, T_BALL7, T_GEM_DARK, T_MAGNET, T_N0, T_N1, T_N2, T_N3, T_N4, T_N5, T_N6, T_N7, T_N8, T_N9, T_PLAYER_PU, T_PU, T_LASSO, T_PLATFORM, T_PLATFORM_M, T_DN0, T_DN1, T_DN2, T_DN3, T_DN4, T_DN5, T_DN6, T_DN7, T_DN8, T_DN9, T_MAGNET_LEFT, T_MAGNET_RIGHT, T_MAGNET_DOWN, T_QUARTER1_UP, T_QUARTER1_DOWN, T_QUARTER2_LEFT, T_QUARTER2_RIGHT, T_QUARTER3_LEFT, T_QUARTER3_RIGHT, T_QUARTER3_UP, T_QUARTER3_DOWN, T_QUARTER2_UP, T_QUARTER2_DOWN, T_QUARTER1_LEFT, T_QUARTER1_RIGHT, T_PLAYER_EA_DOWN, T_PLAYER_EA_LEFT, T_PLAYER_EA_RIGHT, T_PLAYER_MSA_DOWN, T_PLAYER_MSA_LEFT, T_PLAYER_MSA_RIGHT, T_PLAYER_PU_DOWN, T_PLAYER_PU_LEFT, T_PLAYER_PU_RIGHT, T_PASS1_H, T_PASS2_H, T_PASS3_H, T_PASS4_H, T_PASS5_H, T_PASS6_H, T_PLATFORM_DOWN, T_PLATFORM_LEFT, T_PLATFORM_RIGHT, T_PLATFORM_HORIZONTAL, T_ARROW_DOWN, T_ARROW_LEFT, T_ARROW_RIGHT, T_PASS1_LEFT, T_PASS2_LEFT, T_PASS3_LEFT, T_PASS4_LEFT, T_PASS5_LEFT, T_PASS6_LEFT, T_PASS1_RIGHT, T_PASS2_RIGHT, T_PASS3_RIGHT, T_PASS4_RIGHT, T_PASS5_RIGHT, T_PASS6_RIGHT, T_PASS1_UP, T_PASS2_UP, T_PASS3_UP, T_PASS4_UP, T_PASS5_UP, T_PASS6_UP, T_PASS1_DOWN, T_PASS2_DOWN, T_PASS3_DOWN, T_PASS4_DOWN, T_PASS5_DOWN, T_PASS6_DOWN, T_CRUMBLE, T_SPACE, T_PLAYER, T_MAX };
static const _CHAR* TRN[] = { ".,",         "##",   "b#",  "o#",       "g1",   "g2",   "g3",   "g4",   "g5",   "g6",   "b1",   "b2",     "b3",    "b4",    "b5",    "b6",    "d1",    "d2",    "d3",    "k1",   "k2",   "k3",   "|1",    "|2",    "|3",    "|4",    "|5",    "|6",    "^^",          "||",                "++",                   "PE",        "PM",        "EA",  "MS",  "FF",   "DD",       "RR",     "TT",   "AU",       "HH",   "Q1",       "Q2",       "Q3",       "b7",    "g7",       "^M",    "N0", "N1", "N2", "N3", "N4", "N5", "N6", "N7", "N8", "N9",  "PP",       "PU", "lasso", "[]",        "()",         "n0",  "n1",  "n2",   "n3", "n4",  "n5",  "n6",  "n7",  "n8",  "n9",   "<M",          ">M",           "vM",          "Q1u",         "Q1d",           "Q2l",           "Q2r",            "Q3l",           "Q3r",            "Q3u",         "Q3d",           "Q2u",         "Q2d",           "Q1l",           "Q1r",           "PEd",            "PEl",            "PEr",             "PMd",             "PMl",             "PMr",              "PPd",            "PPl",            "PPr",             "=1",      "=2",      "=3",      "=4",      "=5",      "=6",      "vv",            "<<",            ">>",             "==",                  "AD",         "AL",         "AR",          "<1",         "<2",         "<3",         "<4",         "<5",         "<6",         ">1",          ">2",          ">3",          ">4",          ">5",          ">6",          "^1",       "^2",       "^3",       "^4",       "^5",       "^6",       "v1",         "v2",         "v3",         "v4",         "v5",         "v6",         "c#",       "';",    "PL",     0 };

enum AnimationsIDs { ID_ANIMATION_CRUMBLE = 0, ID_ANIMATION_EXPLODE_EA, ID_ANIMATION_EXPLODE_MSA, ID_ANIMATION_EXPLODE, ID_ANIMATION_SPLASH };
