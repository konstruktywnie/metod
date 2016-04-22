struct mapUnit
{
  _INDEX f_id;
  _INDEX of_id;
  _FLAG8 flags;
  mapUnit();
};

struct inventory {
  _UINT key1, key2, key3;
  _UINT ea, msa, pu;
  _UINT time, fuel;
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
