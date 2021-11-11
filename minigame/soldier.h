#include <allegro.h>
#include "player.h"
#ifndef SOLDIER__
#define SOLDIER__
struct Skill
{
    int round=0,money=0,supply=0,uphp=0,upatk=0,updef=0,atk=0,upatkinwar=0;
};
struct Soldier
{
    int level=1,hp=0,attack=0,defend=0;
    BITMAP *Soldier;
    Skill skill[3];
};
void Print(Player *p,Soldier *s);
void Levelup(Player *p,Soldier *s);
#endif
