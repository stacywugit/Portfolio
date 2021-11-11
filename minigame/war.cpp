#include "war.h"
#include "player.h"
#include <allegro.h>
#include "building.h"
#include "biuld.h"
int finweakeast(Soldier enemy[])
{
    int weak=-1;
    for(int i=0; i<3; i++)
    {
        if((weak==-1||enemy[weak].hp>enemy[i].hp)&&enemy[i].hp>0)
        {
            weak=i;
        }
    }
    return weak;
}
int startwar(Player p,war war,int num,BuildingS b)
{
    int round=1,win=-1,ch=0;
    BITMAP *ba;
    Soldier enemy[3],my[3];
    ba=load_bitmap("white2.bmp",NULL);
    if(num==1||num==3||num==7||num==9)
    {
        enemy[0].attack=12;
        enemy[0].defend=12;
        enemy[0].hp=134;
        enemy[1].attack=24;
        enemy[1].defend=13;
        enemy[1].hp=201;
        enemy[2].hp=0;
    }
    if(num==2)
    {
        enemy[0].attack=12;
        enemy[0].defend=12;
        enemy[0].hp=134;
        enemy[1].hp=0;
        enemy[2].hp=0;
    }
    if(num==4||num==5)
    {
        enemy[0].attack=12;
        enemy[0].defend=12;
        enemy[0].hp=134;
        enemy[1].attack=44;
        enemy[1].defend=13;
        enemy[1].hp=237;
        enemy[2].attack=20;
        enemy[2].defend=10;
        enemy[2].hp=134;
    }
    else if(num==6)
    {
        enemy[0].attack=12;
        enemy[0].defend=12;
        enemy[0].hp=134;
        enemy[1].attack=12;
        enemy[1].defend=12;
        enemy[1].hp=134;
        enemy[2].hp=0;
    }
    else if(num==8)
    {
        enemy[0].attack=24;
        enemy[0].defend=13;
        enemy[0].hp=201;
        enemy[1].attack=24;
        enemy[1].defend=13;
        enemy[1].hp=201;
        enemy[2].hp=0;
    }
    else if(num==10)
    {
        enemy[0].attack=12;
        enemy[0].defend=12;
        enemy[0].hp=134;
        enemy[1].attack=20;
        enemy[1].defend=10;
        enemy[1].hp=134;
        enemy[2].hp=0;
    }
    else if(num==11||num==12)
    {
        enemy[0].attack=12;
        enemy[0].defend=12;
        enemy[0].hp=134;
        enemy[1].attack=24;
        enemy[1].defend=12;
        enemy[1].hp=172;
        enemy[2].hp=0;
    }
    else if(num==13||num==14)
    {
        enemy[0].attack=12;
        enemy[0].defend=12;
        enemy[0].hp=134;
        enemy[1].attack=24;
        enemy[1].defend=12;
        enemy[1].hp=172;
        enemy[2].attack=20;
        enemy[2].defend=10;
        enemy[1].hp=134;
    }
    else if(num==15)
    {
        enemy[0].attack=12;
        enemy[0].defend=12;
        enemy[0].hp=134;
        enemy[1].attack=20;
        enemy[1].defend=10;
        enemy[1].hp=143;
        enemy[2].hp=0;
    }
    else if(num==16)
    {
        enemy[0].attack=12;
        enemy[0].defend=12;
        enemy[0].hp=134;
        enemy[1].attack=24;
        enemy[1].defend=13;
        enemy[1].hp=201;
        enemy[2].attack=20;
        enemy[2].defend=10;
        enemy[2].hp=143;
    }
    else if(num==17||num==20)
    {
        enemy[0].attack=12;
        enemy[0].defend=12;
        enemy[0].hp=134;
        enemy[1].attack=24;
        enemy[1].defend=12;
        enemy[1].hp=172;
        enemy[2].attack=20;
        enemy[2].defend=10;
        enemy[2].hp=143;
    }
    else if(num==18)
    {
        enemy[0].attack=24;
        enemy[0].defend=12;
        enemy[0].hp=172;
        enemy[1].attack=24;
        enemy[1].defend=12;
        enemy[1].hp=172;
        enemy[2].attack=20;
        enemy[2].defend=10;
        enemy[2].hp=143;
    }
    else if(num==19)
    {
        enemy[0].attack=12;
        enemy[0].defend=12;
        enemy[0].hp=134;
        enemy[1].attack=20;
        enemy[1].defend=10;
        enemy[1].hp=143;
        enemy[2].attack=20;
        enemy[2].defend=10;
        enemy[2].hp=143;
    }
    else if(num==21)
    {
        enemy[0].attack=12;
        enemy[0].defend=12;
        enemy[0].hp=134;
        enemy[1].attack=12;
        enemy[1].defend=12;
        enemy[1].hp=134;
        enemy[2].attack=24;
        enemy[2].defend=22;
        enemy[2].hp=356;
    }
    else if(num==22||num==24||num==25)
    {
        enemy[0].attack=12;
        enemy[0].defend=12;
        enemy[0].hp=134;
        enemy[1].attack=24;
        enemy[1].defend=13;
        enemy[1].hp=201;
        enemy[2].attack=24;
        enemy[2].defend=22;
        enemy[2].hp=356;
    }
    else if(num==23)
    {
        enemy[0].attack=24;
        enemy[0].defend=13;
        enemy[0].hp=201;
        enemy[1].attack=24;
        enemy[1].defend=13;
        enemy[1].hp=201;
        enemy[2].attack=24;
        enemy[2].defend=22;
        enemy[2].hp=356;
    }
    while(enemy[0].hp+enemy[1].hp+enemy[2].hp>=0&&round<=45)
    {
        blit( ba, screen, 0, 0, 130, 150, ba->w, ba->h);
        textprintf_ex(screen, font, 280, 150, makecol(0, 0 ,0),
                      -1, "ROUND %d",round);
        round+=1;
        for(int i=0; i<3; i++)
        {
            ListNode *cur = b.build;
            while(cur != 0)
            {
                if(war.warrior[i]==cur->data.kind)
                {
                    if(ch==0)
                    {
                        my[i]=cur->data.soldier;
                    }
                    if(enemy[i].hp>0)
                    {
                        int atk=cur->data.soldier.attack-enemy[i].defend;
                        if(atk>0)
                        {
                            enemy[i].hp-=atk;
                            if(i==0)
                            {
                                textprintf_ex(screen, font, 130, 160+10*i, makecol(0, 0 ,0),
                                              -1, "Your frontsoldier attack frontenemy %d hp",atk);
                            }
                            else if(i==1)
                            {
                                textprintf_ex(screen, font, 130, 160+10*i, makecol(0, 0 ,0),
                                              -1, "Your midsoldier attack midenemy %d hp",atk);
                            }
                            else
                            {
                                textprintf_ex(screen, font, 130, 160+10*i, makecol(0, 0 ,0),
                                              -1, "Your backsoldier attack backenemy %d hp",atk);
                            }
                        }
                    }
                    else
                    {
                        int find=finweakeast(enemy);
                        if(find!=-1)
                        {
                            int atk=cur->data.soldier.attack-enemy[find].defend;
                            if(atk>0)
                            {
                                enemy[find].hp-=atk;
                                if(i==0)
                                {
                                    if(find==1)
                                    {
                                        textprintf_ex(screen, font, 130, 160+10*i, makecol(0, 0 ,0),
                                                      -1, "Your frontsoldier attack midenemy %d hp",atk);
                                    }
                                    else
                                    {
                                        textprintf_ex(screen, font, 130, 160+10*i, makecol(0, 0 ,0),
                                                      -1, "Your frontsoldier attack backenemy %d hp",atk);
                                    }
                                }
                                else if(i==1)
                                {
                                    if(find==0)
                                    {
                                        textprintf_ex(screen, font, 130, 160+10*i, makecol(0, 0 ,0),
                                                      -1, "Your midsoldier attack frontenemy %d hp",atk);
                                    }
                                    else
                                    {
                                        textprintf_ex(screen, font, 130, 160+10*i, makecol(0, 0 ,0),
                                                      -1, "Your midsoldier attack backenemy %d hp",atk);
                                    }
                                }
                                else
                                {
                                    if(find==0)
                                    {
                                        textprintf_ex(screen, font, 130, 160+10*i, makecol(0, 0 ,0),
                                                      -1, "Your backsoldier attack frontenemy %d hp",atk);
                                    }
                                    else
                                    {
                                        textprintf_ex(screen, font, 130, 160+10*i, makecol(0, 0 ,0),
                                                      -1, "Your backsoldier attack midenemy %d hp",atk);
                                    }
                                }
                            }
                        }
                    }
                }
                cur = cur->next;
            }
        }
        ch+=1;
        for(int i=0; i<3; i++)
        {
            if(my[i].hp>0)
            {
                int atk=enemy[i].attack-my[i].defend;
                if(atk>0)
                {
                    my[i].hp-=atk;
                    if(i==0)
                    {
                        textprintf_ex(screen, font, 130, 160+10*(i+3), makecol(0, 0 ,0),
                                      -1, "Frontenemy attack your frontsoldier %d hp",atk);
                    }
                    else if(i==1)
                    {
                        textprintf_ex(screen, font, 130, 160+10*(i+3), makecol(0, 0 ,0),
                                      -1, "Midenemy attack your midsoldier %d hp",atk);
                    }
                    else
                    {
                        textprintf_ex(screen, font, 130, 160+10*(i+3), makecol(0, 0 ,0),
                                      -1, "Backenemy attack your backsoldier %d hp",atk);
                    }
                }
            }
            else
            {
                int find=finweakeast(my);
                if(find!=-1)
                {
                    int atk=enemy[i].attack-my[find].defend;
                    if(atk>0)
                    {
                        my[find].hp-=atk;
                        if(i==0)
                        {
                            if(find==1)
                            {
                                textprintf_ex(screen, font, 130, 160+10*(i+3), makecol(0, 0 ,0),
                                              -1, "Frontenemy attack your midsoldier %d hp",atk);
                            }
                            else
                            {
                                textprintf_ex(screen, font, 130, 160+10*(i+3), makecol(0, 0 ,0),
                                              -1, "Frontenemy attack your backsoldier %d hp",atk);
                            }
                        }
                        else if(i==1)
                        {
                            if(find==0)
                            {
                                textprintf_ex(screen, font, 130, 160+10*(i+3), makecol(0, 0 ,0),
                                              -1, "Midenemy attack your frontsoldier %d hp",atk);
                            }
                            else
                            {
                                textprintf_ex(screen, font, 130, 160+10*(i+3), makecol(0, 0 ,0),
                                              -1, "Midenemy attack your backsoldier %d hp",atk);
                            }
                        }
                        else
                        {
                            if(find==0)
                            {
                                textprintf_ex(screen, font, 130, 160+10*(i+3), makecol(0, 0 ,0),
                                              -1, "Backsoldier attack your frontsoldier %d hp",atk);
                            }
                            else
                            {
                                textprintf_ex(screen, font, 130, 160+10*(i+3), makecol(0, 0 ,0),
                                              -1, "Backsoldier attack your midsoldier %d hp",atk);
                            }
                        }
                    }
                }
            }
        }
        if(enemy[0].hp+enemy[1].hp+enemy[2].hp<=0)
        {
            textprintf_ex(screen, font, 280, 330, makecol(0, 0 ,0),
                          -1, "You win");
            readkey();
            destroy_bitmap( ba );
            return 1;
        }
        else if(my[0].hp+my[1].hp+my[2].hp<=0)
        {
            textprintf_ex(screen, font, 280, 330, makecol(0, 0 ,0),
                          -1, "You lose");
            readkey();
            destroy_bitmap( ba );
            return -1;
        }
        else if(round>45)
        {
            textprintf_ex(screen, font, 250, 330, makecol(0, 0 ,0),
                          -1, "Too many rounds.");
            readkey();
            destroy_bitmap( ba );
            return -1;
        }
        readkey();
    }
}
void printenemy(int num)
{
    BITMAP *e1,*e2,*e3;
    if(num ==1||num==3||num==7||num==9)
    {
        e1=load_bitmap("smallfront1.bmp",NULL);
        e2=load_bitmap("e1.bmp",NULL);
        e3=load_bitmap("none.bmp",NULL);
    }
    else if(num==2)
    {
        e1=load_bitmap("smallfront1.bmp",NULL);
        e2=load_bitmap("none.bmp",NULL);
        e3=load_bitmap("none.bmp",NULL);
    }
    else if(num == 4||num==5)
    {
        e1=load_bitmap("smallfront1.bmp",NULL);
        e2=load_bitmap("e2.bmp",NULL);
        e3=load_bitmap("smallback2.bmp",NULL);
    }
    else if(num==6)
    {
        e1=load_bitmap("smallfront1.bmp",NULL);
        e2=load_bitmap("smallfront1.bmp",NULL);
        e3=load_bitmap("none.bmp",NULL);
    }
    else if(num==8)
    {
        e1=load_bitmap("e1.bmp",NULL);
        e2=load_bitmap("e1.bmp",NULL);
    }
    else if(num==10)
    {
        e1=load_bitmap("smallfront1.bmp",NULL);
        e2=load_bitmap("smallback2.bmp",NULL);
        e3=load_bitmap("none.bmp",NULL);
    }
    else if(num==11||num==12)
    {
        e1=load_bitmap("smallfront1.bmp",NULL);
        e2=load_bitmap("smallmid1.bmp",NULL);
        e3=load_bitmap("none.bmp",NULL);
    }
    else if(num==13||num==14)
    {
        e1=load_bitmap("smallfront1.bmp",NULL);
        e2=load_bitmap("smallmid1.bmp",NULL);
        e3=load_bitmap("smallback2.bmp",NULL);
    }
    else if(num==15)
    {
        e1=load_bitmap("smallfront1.bmp",NULL);
        e2=load_bitmap("smallback1.bmp",NULL);
        e3=load_bitmap("none.bmp",NULL);
    }
    else if(num==16)
    {
        e1=load_bitmap("smallfront1.bmp",NULL);
        e2=load_bitmap("e1.bmp",NULL);
        e3=load_bitmap("smallback1.bmp",NULL);
    }
    else if(num==17||num==20)
    {
        e1=load_bitmap("smallfront1.bmp",NULL);
        e2=load_bitmap("smallmid1.bmp",NULL);
        e3=load_bitmap("smallback1.bmp",NULL);
    }
    else if(num==18)
    {
        e1=load_bitmap("smallmid1.bmp",NULL);
        e2=load_bitmap("smallmid1.bmp",NULL);
        e3=load_bitmap("smallback1.bmp",NULL);
    }
    else if(num==19)
    {
        e1=load_bitmap("smallfront1.bmp",NULL);
        e2=load_bitmap("smallback1.bmp",NULL);
        e3=load_bitmap("smallback1.bmp",NULL);
    }
    else if(num==21)
    {
        e1=load_bitmap("smallfront1.bmp",NULL);
        e2=load_bitmap("smallfront1.bmp",NULL);
        e3=load_bitmap("e3.bmp",NULL);
    }
    else if(num==22||num==24||num==25)
    {
        e1=load_bitmap("smallfront1.bmp",NULL);
        e2=load_bitmap("e1.bmp",NULL);
        e3=load_bitmap("e3.bmp",NULL);
    }
    else if(num==23)
    {
        e1=load_bitmap("e1.bmp",NULL);
        e2=load_bitmap("e1.bmp",NULL);
        e3=load_bitmap("e3.bmp",NULL);
    }
    blit( e1, screen, 0, 0, 350, 150, e1->w, e1->h);
    blit( e2, screen, 0, 0, 430, 150, e2->w, e2->h);
    blit( e3, screen, 0, 0, 510, 150, e3->w, e3->h);
}
buildkind change(int po,BuildingS b,BITMAP **s,war w)
{
    BITMAP *s1,*s2,*s3,*s4,*s5,*back,*chara;
    int end=0,charx=150,chary=260,c[5]= {0},p=0;
    back=load_bitmap("white.bmp",NULL);
    chara=load_bitmap("char.bmp",NULL);
    if(po==1)
    {
        if(find(front1Barrack,b)==1)
        {
            c[0]=1;
            s1=load_bitmap("smallfront1.bmp",NULL);
        }
        if(find(front2Barrack,b)==1)
        {
            c[1]=1;
            s2=load_bitmap("smallfront2.bmp",NULL);
        }
        if(find(frontmidBarrack,b)==1)
        {
            c[2]=1;
            s3=load_bitmap("smallfrontmid.bmp",NULL);
        }
        if(find(frontbackBarrack,b)==1)
        {
            c[3]=1;
            s4=load_bitmap("smallfrontback.bmp",NULL);
        }
        if(find(allBarrack,b)==1)
        {
            c[4]=1;
            s5=load_bitmap("smallall.bmp",NULL);
        }
    }
    else if(po==2)
    {
        if(find(mid1Barrack,b)==1)
        {
            c[0]=1;
            s1=load_bitmap("smallmid1.bmp",NULL);
        }
        if(find(mid2Barrack,b)==1)
        {
            c[1]=1;
            s2=load_bitmap("smallmid2.bmp",NULL);
        }
        if(find(frontmidBarrack,b)==1)
        {
            c[2]=1;
            s3=load_bitmap("smallfrontmid.bmp",NULL);
        }
        if(find(midbackBarrack,b)==1)
        {
            c[3]=1;
            s4=load_bitmap("smallmidback.bmp",NULL);
        }
        if(find(allBarrack,b)==1)
        {
            c[4]=1;
            s5=load_bitmap("smallall.bmp",NULL);
        }
    }
    else
    {
        if(find(back1Barrack,b)==1)
        {
            c[0]=1;
            s1=load_bitmap("smallback1.bmp",NULL);
        }
        if(find(back2Barrack,b)==1)
        {
            c[1]=1;
            s2=load_bitmap("smallback2.bmp",NULL);
        }
        if(find(frontbackBarrack,b)==1)
        {
            c[2]=1;
            s3=load_bitmap("smallfrontback.bmp",NULL);
        }
        if(find(midbackBarrack,b)==1)
        {
            c[3]=1;
            s4=load_bitmap("smallmidback.bmp",NULL);
        }
        if(find(allBarrack,b)==1)
        {
            c[4]=1;
            s5=load_bitmap("smallall.bmp",NULL);
        }
    }
    while(end!=1)
    {
        end=0;
        blit( back, screen, 0, 0, 150, 200, back->w, back->h);
        blit( chara, screen, 0, 0, charx, chary, chara->w, chara->h);
        if(c[0]==1)
        {
            blit( s1, screen, 0, 0, 150, 200, s1->w, s1->h);
        }
        if(c[1]==1)
        {
            blit( s2, screen, 0, 0, 210, 200, s2->w, s2->h);
        }
        if(c[2]==1)
        {
            blit( s3, screen, 0, 0, 270, 200, s3->w, s3->h);
        }
        if(c[3]==1)
        {
            blit( s4, screen, 0, 0, 330, 200, s4->w, s4->h);
        }
        if(c[4]==1)
        {
            blit( s5, screen, 0, 0, 390, 200, s5->w, s5->h);
        }
        readkey();
        if(key[KEY_RIGHT])
        {
            if(charx!=390)
            {
                p+=1;
                charx+=60;
            }
        }
        else if(key[KEY_LEFT])
        {
            if(charx!=150)
            {
                p-=1;
                charx-=60;
            }
        }
        else if(key[KEY_ESC])
        {
            return w.warrior[po-1];
        }
        else if(key[KEY_SPACE])
        {
            if(p==0&&c[0]==1)
            {
                *s=s1;
                if(po==1)
                {
                    return front1Barrack;
                }
                else if(po==2)
                {
                    return mid1Barrack;
                }
                else
                {
                    return back1Barrack;
                }
            }
            else if(p==1&&c[1]==1)
            {
                *s=s2;
                if(po==1)
                {
                    return front2Barrack;
                }
                else if(po==2)
                {
                    return mid2Barrack;
                }
                else
                {
                    return back2Barrack;
                }
            }
            else if(p==2&&c[2]==1)
            {
                if(po==1)
                {
                    if(w.warrior[0]!=frontmidBarrack&&w.warrior[1]!=frontmidBarrack)
                    {
                        *s=s3;
                        return frontmidBarrack;
                    }
                    return w.warrior[po-1];
                }
                else if(po==2)
                {
                    if(w.warrior[0]!=frontmidBarrack&&w.warrior[1]!=frontmidBarrack)
                    {
                        *s=s3;
                        return frontmidBarrack;
                    }
                    return w.warrior[po-1];
                }
                else
                {
                    if(w.warrior[0]!=frontbackBarrack&&w.warrior[2]!=frontbackBarrack)
                    {
                        *s=s3;
                        return frontbackBarrack;
                    }
                    return w.warrior[po-1];
                }
            }
            else if(p==3&&c[3]==1)
            {
                if(po==1)
                {
                    if(w.warrior[0]!=frontbackBarrack&&w.warrior[2]!=frontbackBarrack)
                    {
                        *s=s4;
                        return frontbackBarrack;
                    }
                    return w.warrior[po-1];
                }
                else if(po==2)
                {
                    if(w.warrior[1]!=midbackBarrack&&w.warrior[2]!=midbackBarrack)
                    {
                        *s=s4;
                        return midbackBarrack;
                    }
                    return w.warrior[po-1];
                }
                else
                {
                    if(w.warrior[1]!=midbackBarrack&&w.warrior[2]!=midbackBarrack)
                    {
                        *s=s4;
                        return midbackBarrack;
                    }
                    return w.warrior[po-1];
                }
            }
            else if(p==4&&c[4]==1)
            {
                if(w.warrior[0]!=allBarrack&&w.warrior[1]!=allBarrack&&w.warrior[2]!=allBarrack)
                {
                    *s=s5;
                    return allBarrack;
                }
                return w.warrior[po-1];
            }
        }
    }
}
int War(Player p,int warnum,BuildingS b)
{
    war war;
    war.warrior[0]=none,war.warrior[1]=none,war.warrior[2]=none;
    int end=0,charx=80,chary=250,win=0;
    BITMAP *warground,*mysoldier,*enemysoldier,*front,*mid,*back,*chara,*s1,*s2,*s3;
    warground=load_bitmap("war.bmp",NULL);
    mysoldier=load_bitmap("mysoldier.bmp",NULL);
    enemysoldier=load_bitmap("enemysoldier.bmp",NULL);
    front=load_bitmap("front.bmp",NULL);
    mid=load_bitmap("mid.bmp",NULL);
    back=load_bitmap("back.bmp",NULL);
    chara=load_bitmap("char.bmp",NULL);
    s2=load_bitmap("none.bmp",NULL);
    s3=s2;
    if(find(front1Barrack,b)==1)
    {
        war.warrior[0]=front1Barrack;
        s1=load_bitmap("smallfront1.bmp",NULL);
    }
    if(find(mid1Barrack,b)==1)
    {
        war.warrior[1]=mid1Barrack;
        s2=load_bitmap("smallmid1.bmp",NULL);
    }
    if(find(back1Barrack,b)==1)
    {
        war.warrior[2]=back1Barrack;
        s3=load_bitmap("smallback1.bmp",NULL);
    }
    do
    {
        end=0;
        blit( warground, screen, 0, 0, 0, 0, warground->w, warground->h);
        blit( mysoldier, screen, 0, 0, 120, 80, mysoldier->w, mysoldier->h);
        blit( enemysoldier, screen, 0, 0, 400, 80, enemysoldier->w, enemysoldier->h);
        blit( front, screen, 0, 0, 230, 120, front->w, front->h);
        blit( mid, screen, 0, 0, 150, 120, mid->w, mid->h);
        blit( back, screen, 0, 0, 70, 120, back->w, back->h);
        blit( chara, screen, 0, 0, charx, chary, chara->w, chara->h);
        textprintf_ex(screen, font, 290, 60, makecol(0, 0 ,0),
                      -1, "WAR %d",warnum);
        textprintf_ex(screen, font, 200, 380, makecol(0, 0 ,0),
                      -1, "PRESS ENTER TO START THE WAR",warnum);
        printenemy(warnum);
        for(int i=0; i<300; i++)
        {
            textprintf_ex(screen, font, 300, 70+i, makecol(0, 0 ,0),
                          -1, "|");
        }
        blit( front, screen, 0, 0, 350, 120, front->w, front->h);
        blit( mid, screen, 0, 0, 430, 120, mid->w, mid->h);
        blit( back, screen, 0, 0, 510, 120, back->w, back->h);
        blit( s1, screen, 0, 0, 230, 150, s1->w, s1->h);
        blit( s2, screen, 0, 0, 150, 150, s2->w, s2->h);
        blit( s3, screen, 0, 0, 70, 150, s3->w, s3->h);
        readkey();
        if(key[KEY_RIGHT])
        {
            if(charx!=240)
            {
                charx+=80;
            }
        }
        else if(key[KEY_LEFT])
        {
            if(charx!=80)
            {
                charx-=80;
            }
        }
        else if(key[KEY_ESC])
        {
            end=1;
        }
        else if(key[KEY_SPACE])
        {
            if(charx==80)
            {
                war.warrior[2]=change(3,b,&s3,war);
            }
            else if(charx==160)
            {
                war.warrior[1]=change(2,b,&s2,war);
            }
            else
            {
                war.warrior[0]=change(1,b,&s1,war);
            }
        }
        else if(key[KEY_ENTER])
        {
            end =1;
            win=startwar(p,war,warnum,b);
        }
    }
    while(end!=1);
    destroy_bitmap( warground );
    destroy_bitmap( mysoldier );
    destroy_bitmap( enemysoldier );
    destroy_bitmap( front );
    destroy_bitmap( mid );
    destroy_bitmap( back );
    destroy_bitmap( chara );
    destroy_bitmap( s1 );
    destroy_bitmap( s2 );
    destroy_bitmap( s3 );
    return win;
}
