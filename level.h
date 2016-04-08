struct mapUnit
{
  _INDEX f_id;
  _INDEX of_id;
  _FLAG8 flags;
};

struct inventory {
  char key1, key2, key3;
  int ea, msa, pu;
  int time, fuel;
};
struct thePlayer {
  inventory items;
  _UINT hitPoints;
};

struct theLevel {
  _CHAR* chs;
  _CHAR introFile[ MAX_LINE ];
  thePlayer* player;
  _SIZE rows, cols;
  vector< vector<mapUnit> > map;
  _UINT EA_damage_mod, MSA_damage_mod;
  bool water;
  
  void parseCfgLine();
  void buildMap( _CHAR* file );
  theLevel();
};
