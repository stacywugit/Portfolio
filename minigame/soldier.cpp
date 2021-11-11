#include <allegro.h>
#include <stdio.h>
#include "soldier.h"
void Levelup(Player *p,Soldier *s)
{
    s->hp+=s->skill[s->level-1].uphp;
    s->attack+=s->skill[s->level-1].upatk;
    s->defend+=s->skill[s->level-1].updef;
    p->money+=s->skill[s->level-1].money;
    p->supply+=s->skill[s->level-1].supply;
    s->level+=1;
}
void Print(Player *p,Soldier *s)
{
    int end=0,chary=210;
    BITMAP *chara;
    chara=load_bitmap( "char.bmp", NULL );
    while(end!=1)
    {
        blit( s->Soldier, screen, 0, 0, 50, 100, s->Soldier->w,s->Soldier->h );
        textprintf_ex(screen, font, 450, 100, makecol(0, 0 ,0),
                      -1, "Level: %d",s->level);
        textprintf_ex(screen, font, 450, 110, makecol(0, 0 ,0),
                      -1, "Hp: %d",s->hp);
        textprintf_ex(screen, font, 450, 120, makecol(0, 0 ,0),
                      -1, "Attack: %d",s->attack);
        textprintf_ex(screen, font, 450, 130, makecol(0, 0 ,0),
                      -1, "Deffend: %d",s->defend);
        if(s->level==1)
        {
            textprintf_ex(screen, font, 450, 150, makecol(0, 0 ,0),
                          -1, "Next Level:");
            textprintf_ex(screen, font, 450, 160, makecol(0, 0 ,0),
                          -1, "%d",s->skill[0].money);
            textprintf_ex(screen, font, 450, 170, makecol(0, 0 ,0),
                          -1, "%d",s->skill[0].supply);
        }
        else if(s->level==2)
        {
            textprintf_ex(screen, font, 450, 150, makecol(0, 0 ,0),
                          -1, "Next Level:");
            textprintf_ex(screen, font, 450, 160, makecol(0, 0 ,0),
                          -1, "%d",s->skill[1].money);
            textprintf_ex(screen, font, 450, 170, makecol(0, 0 ,0),
                          -1, "%d",s->skill[1].supply);
        }
        blit( chara, screen, 0, 0, 450, chary, chara->w, chara->h );
        textprintf_ex(screen, font, 450, 200, makecol(0, 0 ,0),
                      -1, "Level up");
        textprintf_ex(screen, font, 450, 250, makecol(0, 0 ,0),
                      -1, "Exit");
        readkey();
        if(key[KEY_DOWN])
        {
            if(chary!=260)
            {
                chary+=50;
            }
        }
        else if(key[KEY_UP])
        {
            if(chary!=210)
            {
                chary-=50;
            }
        }
        else if(key[KEY_SPACE])
        {
            if(chary==210)
            {
                if(s->level<3&&(p->money>=(s->skill[s->level-1].money*-1))&&(p->supply>=(s->skill[s->level-1].supply*-1)))
                {
                    Levelup(p,s);
                }
            }
            else
            {
                end =1;
            }
        }
    }
    destroy_bitmap( chara );
}
