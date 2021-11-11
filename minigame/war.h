#include <allegro.h>
#include "player.h"
#include "soldier.h"
#include "building.h"
#ifndef WAR__
#define WAR__
struct war
{
    buildkind warrior[3];
    int round=0;
};
int War(Player p,int warnum,BuildingS b);
buildkind change(int po,BuildingS b,BITMAP *s,war w);
int startwar(Player p,war war,int num,BuildingS b);
int Attack(Player p,buildkind mine[],Soldier enemy[],BuildingS b);
int finweakeast(Soldier enemy[]);
#endif
