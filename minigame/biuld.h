#include <allegro.h>
#include "soldier.h"
#ifndef BUILD__
#define BUILD__
enum buildkind {residence1,residence2,money1,money2,supply1,supply2,front1Barrack,front2Barrack,frontmidBarrack,mid1Barrack,mid2Barrack,midbackBarrack,back1Barrack,back2Barrack,frontbackBarrack,allBarrack,none};
struct Build
{
    buildkind kind=residence1;
    int t=0,money=0,supply=0,startt=0,sell=0;
    Soldier soldier;
    BITMAP *pic;
};
void Create(Build *b,buildkind kind);
#endif
