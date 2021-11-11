#include "biuld.h"
#include "player.h"
#ifndef BUILDINGS__
#define BUILDINGS__
struct ListNode{
    Build data;
    ListNode *next;
};
struct BuildingS
{
    int num_building=0;
    ListNode *build=0;
};
void buildchoose(Player *pl,BuildingS *building,int p,int t);
void buyhouse(Player *pl,BuildingS *b);
void Create(BuildingS *b);
void Print(const BuildingS b);
void addbuild(BuildingS *b,buildkind kind);
void deletebuild(Player *pl,BuildingS *b,int p);
int find(buildkind po,BuildingS b);
#endif

