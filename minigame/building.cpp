#include "building.h"
#include "biuld.h"
#include <allegro.h>
#include <stdio.h>
int find(buildkind po,BuildingS b)
{
    ListNode *cur = b.build;
    while (cur != 0)
    {
        if(cur->data.kind==po)
        {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}
void addbuild(BuildingS *b,buildkind kind)
{
    ListNode *newb = (ListNode *)malloc(sizeof(ListNode));
    if(newb)
    {
        Create(&(newb->data),kind);
        newb->next=0;
        ListNode *prev = 0, *cur = b->build;
        while (cur != 0)
        {
            prev = cur;
            cur = cur->next;
        }
        if (prev == 0)
        {
            newb->next = b->build;
            b->build = newb;
        }
        else
        {
            prev->next = newb;
            newb->next = cur;
        }
        b->num_building+=1;
    }
}
void Create(BuildingS *b)
{
    addbuild(b,residence1);
    addbuild(b,supply1);
    addbuild(b,front1Barrack);
}
void deletebuild(Player *pl,BuildingS *b,int p)
{
    int i=0;
    ListNode *prev = 0, *cur = b->build;
    while (cur != 0 && p!=i)
    {
        prev = cur;
        cur = cur->next;
        i++;
    }
    pl->money+=cur->data.sell;
    if (prev == 0)
    {
        b->build = cur->next;
        destroy_bitmap( cur->data.pic );
        free(cur);
    }
    else if (cur != 0)
    {
        prev->next = cur->next;
        destroy_bitmap( cur->data.pic );
        free(cur);
    }
    b->num_building -=1;
}
void Print(const BuildingS b)
{
    int i=0;
    ListNode *cur = b.build;
    while (cur != 0)
    {
        blit( cur->data.pic, screen, 0, 0, 20+(i%6)*100, 30+(i/6)*100, cur->data.pic->w, cur->data.pic->h );
        cur = cur->next;
        i++;
    }
}
void buyhouse(Player *pl,BuildingS *b)
{
    int end=0,charx=110,chary=280;
    BITMAP *store1,*chara,*store2;
    store1=load_bitmap("store1.bmp",NULL);
    store2=load_bitmap("store2.bmp",NULL);
    chara=load_bitmap( "char.bmp", NULL );
    while(end!=1)
    {
        end=0;
        blit( store1, screen, 0, 0, 70, 50, store1->w, store1->h );
        blit( chara, screen, 0, 0, charx, chary, chara->w, chara->h );
        readkey();
        if(key[KEY_DOWN])
        {
            if(chary!=480)
            {
                chary+=200;
            }
        }
        else if(key[KEY_UP])
        {
            if(chary!=280)
            {
                chary-=200;
            }
        }
        else if(key[KEY_LEFT])
        {
            if(charx!=110)
            {
                charx-=90;
            }
        }
        else if(key[KEY_RIGHT])
        {
            if(charx!=380)
            {
                charx+=90;
            }
        }
        else if(key[KEY_SPACE])
        {
            if(chary==480&&charx==380)//exit
            {
                end=1;
            }
            else if(chary==280&&charx==110)//residence1
            {
                if(pl->money>=400)
                {
                    pl->money-=400;
                    addbuild(b,residence1);
                    end=1;
                }
            }
            else if(chary==280&&charx==200)//residence2
            {
                if(pl->money>=1500)
                {
                    pl->money-=1500;
                    addbuild(b,residence2);
                    end=1;
                }
            }
            else if(chary==280&&charx==290)//money1
            {
                if(pl->money>=700)
                {
                    pl->money-=700;
                    addbuild(b,money1);
                    end=1;
                }
            }
            else if(chary==280&&charx==380)//money2
            {
                if(pl->money>=2300)
                {
                    pl->money-=2300;
                    addbuild(b,money2);
                    end=1;
                }
            }
            else if(chary==480&&charx==110)//supply1
            {
                if(pl->money>=400)
                {
                    pl->money-=400;
                    addbuild(b,supply1);
                    end=1;
                }
            }
            else if(chary==480&&charx==200)//supply2
            {
                if(pl->money>=1400)
                {
                    pl->money-=1400;
                    addbuild(b,supply2);
                    end=1;
                }
            }
            else if(chary==480&&charx==290)//store2
            {
                charx=100,chary=280;
                while(end!=1)
                {
                    blit( store2, screen, 0, 0, 60, 50, store2->w, store2->h );
                    blit( chara, screen, 0, 0, charx, chary, chara->w, chara->h );
                    readkey();
                    if(key[KEY_DOWN])
                    {
                        if(chary!=480)
                        {
                            chary+=200;
                        }
                    }
                    else if(key[KEY_UP])
                    {
                        if(chary!=280)
                        {
                            chary-=200;
                        }
                    }
                    else if(key[KEY_LEFT])
                    {
                        if(charx!=100)
                        {
                            charx-=90;
                        }
                    }
                    else if(key[KEY_RIGHT])
                    {
                        if(charx!=460)
                        {
                            charx+=90;
                        }
                    }
                    else if(key[KEY_SPACE])
                    {
                        if(chary==480&&charx==460)//exit
                        {
                            end=1;
                        }
                        else if(chary==280&&charx==100)//front2Barrack
                        {
                            if(pl->money>=11000&&pl->supply>=2000&&find(front2Barrack,*b)==0)
                            {
                                pl->money-=400;
                                pl->supply-=2000;
                                addbuild(b,front2Barrack);
                                end=1;
                            }
                        }
                        else if(chary==280&&charx==190)//frontmidBarrack
                        {
                            if(pl->money>=50000&&pl->supply>=9000&&find(frontmidBarrack,*b)==0)
                            {
                                pl->money-=50000;
                                pl->supply-=9000;
                                addbuild(b,frontmidBarrack);
                                end=1;
                            }
                        }
                        else if(chary==280&&charx==280)//mid1Barrack
                        {
                            if(pl->money>=2300&&pl->supply>=400&&find(mid1Barrack,*b)==0)
                            {
                                pl->money-=2300;
                                pl->supply-=400;
                                addbuild(b,mid1Barrack);
                                end=1;
                            }
                        }
                        else if(chary==280&&charx==370)//mid2Barrack
                        {
                            if(pl->money>=20000&&pl->supply>=5000&&find(mid2Barrack,*b)==0)
                            {
                                pl->money-=20000;
                                pl->supply-=5000;
                                addbuild(b,mid2Barrack);
                                end=1;
                            }
                        }

                        else if(chary==280&&charx==460)//midbackBarrack
                        {
                            if(pl->money>=80000&&pl->supply>=10000&&find(midbackBarrack,*b)==0)
                            {
                                pl->money-=80000;
                                pl->supply-=10000;
                                addbuild(b,midbackBarrack);
                                end=1;
                            }
                        }
                        else if(chary==480&&charx==100)//back1Barrack
                        {
                            if(pl->money>=900&&find(back1Barrack,*b)==0)
                            {
                                pl->money-=900;
                                addbuild(b,back1Barrack);
                                end=1;
                            }
                        }
                        else if(chary==480&&charx==190)//back2Barrack
                        {
                            if(pl->money>=8000&&pl->supply>=1300&&find(back2Barrack,*b)==0)
                            {
                                pl->money-=8000;
                                pl->supply-=1300;
                                addbuild(b,back2Barrack);
                                end=1;
                            }
                        }
                        else if(chary==480&&charx==280)//frontbackBarrack
                        {
                            if(pl->money>=100000&&pl->supply>=30000&&find(frontbackBarrack,*b)==0)
                            {
                                pl->money-=100000;
                                pl->supply-=30000;
                                addbuild(b,frontbackBarrack);
                                end=1;
                            }
                        }
                        else if(chary==480&&charx==370)//allBarrack
                        {
                            if(pl->money>=150000&&pl->supply>=50000&&find(allBarrack,*b)==0)
                            {
                                pl->money-=150000;
                                pl->supply-=50000;
                                addbuild(b,allBarrack);
                                end=1;
                            }
                        }
                    }
                }
            }
        }
    }
    destroy_bitmap( store1 );
    destroy_bitmap( store2 );
    destroy_bitmap( chara );
}

void buildchoose(Player *pl,BuildingS *building,int p,int t)
{
    int end=0,charx=200,chary=270;
    BITMAP *buildch,*chara;
    buildch=load_bitmap("buildchoose.bmp",NULL);
    chara=load_bitmap( "char.bmp", NULL );
    while(end!=1)
    {
        end=0;
        blit( buildch, screen, 0, 0, 190, 240, buildch->w, buildch->h );
        blit( chara, screen, 0, 0, charx, chary, chara->w, chara->h );
        readkey();
        if(key[KEY_LEFT])
        {
            if(charx!=200)
            {
                charx-=50;
            }
        }
        else if(key[KEY_RIGHT])
        {
            if(charx!=400)
            {
                charx+=50;
            }
        }
        else if(key[KEY_SPACE])
        {
            if(charx==200)//build
            {
                if(building->num_building<=22)
                {
                    buyhouse(pl,building);
                    end=1;
                }
            }
            else if(charx==250)//produce
            {
                int i=0;
                ListNode *prev = 0, *cur = building->build;
                while (cur != 0)
                {
                    if(i==p)
                    {
                        if(cur->data.kind<supply1&&cur->data.kind>residence2&&pl->supply>cur->data.supply&&cur->data.startt==0)
                        {
                            cur->data.startt=t;
                            pl->supply+=cur->data.supply;
                        }
                        else if(cur->data.kind<front1Barrack&&cur->data.kind>money2&&pl->money>cur->data.money&&cur->data.startt==0)
                        {
                            cur->data.startt=t;
                            pl->money+=cur->data.money;
                        }
                        else if(cur->data.kind>supply2)
                        {
                            Print(pl,&cur->data.soldier);
                        }
                        break;
                    }
                    prev = cur;
                    cur = cur->next;
                    i++;
                }
                end =1;
            }
            else if(charx==300)//get
            {
                int i=0;
                ListNode *prev = 0, *cur = building->build;
                while (cur != 0)
                {
                    if(i==p)
                    {
                        if((t-cur->data.startt)>cur->data.t&&p<building->num_building)
                        {
                            if(cur->data.kind<money1)
                            {
                                cur->data.startt=t;
                                pl->money+=cur->data.money;
                                pl->supply+=cur->data.supply;
                            }
                            else if(cur->data.kind<supply1&&cur->data.kind>residence2&&cur->data.startt!=0)
                            {
                                cur->data.startt=0;
                                pl->money+=cur->data.money;
                            }
                            else if(cur->data.kind<front1Barrack&&cur->data.kind>money2&&cur->data.startt!=0)
                            {
                                cur->data.startt=0;
                                pl->supply+=cur->data.supply;
                            }
                            pl->exp+=1;
                        }
                        break;
                    }
                    prev = cur;
                    cur = cur->next;
                    i++;
                }
                break;
            }
            else if(charx==350)//sell
            {
                int i=0;
                ListNode *prev = 0, *cur = building->build;
                while (cur != 0)
                {
                    if(i==p)
                    {
                        if(p<building->num_building&&cur->data.kind<front1Barrack)
                        {
                            deletebuild(pl,building,p);
                            break;
                        }
                    }
                    prev = cur;
                    cur = cur->next;
                    i++;
                }
                break;
            }
            else//exit
            {
                end=1;
            }
        }
    }
    destroy_bitmap( buildch );
    destroy_bitmap( chara );
}
