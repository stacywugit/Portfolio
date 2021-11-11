#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "player.h"
#include "building.h"
#include "war.h"
#include <time.h>
void savegame(Player player,BuildingS building)
{
    int startc=120,end=0,cx=250;
    BITMAP *kingdom,*chara,*file1,*file2,*file3;
    BITMAP *cover=load_bitmap("cover.bmp",NULL);
    kingdom = load_bitmap( "kingdomknights.bmp", NULL );
    chara=load_bitmap( "char.bmp", NULL );
    file1=load_bitmap( "file1.bmp", NULL );
    file2=load_bitmap( "file2.bmp", NULL );
    file3=load_bitmap( "file3.bmp", NULL );
    Player player1,player2,player3;
    FILE *fp1=fopen("file1.sav","rb");
    FILE *fp2=fopen("file2.sav","rb");
    FILE *fp3=fopen("file3.sav","rb");
    while(end!=1)
    {
        end=0;
        blit( kingdom, screen, 0, 0, 0, 0, kingdom->w, kingdom->h );
        blit( file1, screen, 0, 0, 150, 90, file1->w, file1->h );
        blit( file2, screen, 0, 0, 150, 200, file2->w, file2->h );
        blit( file3, screen, 0, 0, 150, 310, file3->w, file3->h );
        blit( chara, screen, 0, 0, 400, startc, chara->w, chara->h );
        if(fp1)
        {
            fread(&player1, sizeof(Player), 1, fp1);
            textprintf_ex(screen, font, 150, 110, makecol(0, 0, 0),
                          -1, "Level:%d Money:%d Supplies:%d",player1.level,player1.money,player1.supply);
            textprintf_ex(screen, font, 150, 120, makecol(0, 0, 0),
                          -1, "Attack:%d Deffend:%d",player1.attack,player1.defend);
            textprintf_ex(screen, font, 150, 130, makecol(0, 0, 0),
                          -1, "hp:%d exp:%d war:%d",player1.hp,player1.exp,player1.war);
        }
        if(fp2)
        {
            fread(&player2, sizeof(Player), 1, fp2);
            textprintf_ex(screen, font, 150, 220, makecol(0, 0, 0),
                          -1, "Level:%d Money:%d Supplies:%d",player2.level,player2.money,player2.supply);
            textprintf_ex(screen, font, 150, 230, makecol(0, 0, 0),
                          -1, "Attack:%d Deffend:%d",player2.attack,player2.defend);
            textprintf_ex(screen, font, 150, 240, makecol(0, 0, 0),
                          -1, "hp:%d exp:%d war:%d",player2.hp,player2.exp,player2.war);
        }
        if(fp3)
        {
            fread(&player3, sizeof(Player), 1, fp3);
            textprintf_ex(screen, font, 150, 330, makecol(0, 0, 0),
                          -1, "Level:%d Money:%d Supplies:%d",player3.level,player3.money,player3.supply);
            textprintf_ex(screen, font, 150, 340, makecol(0, 0, 0),
                          -1, "Attack:%d Deffend:%d",player3.attack,player3.defend);
            textprintf_ex(screen, font, 150, 350, makecol(0, 0, 0),
                          -1, "hp:%d exp:%d war:%d",player3.hp,player3.exp,player3.war);
        }
        readkey();
        if(key[KEY_DOWN])
        {
            if(startc!=340)
            {
                startc+=110;
            }
        }
        else if(key[KEY_UP])
        {
            if(startc!=120)
            {
                startc-=110;
            }
        }
        else if(key[KEY_SPACE])
        {
            if(startc==120)
            {
                if(fp1)
                {
                    fclose(fp1);
                    while(end!=1)
                    {
                        end=0;
                        blit( cover, screen, 0, 0, 200, 200, cover->w, cover->h );
                        blit( chara, screen, 0, 0, cx, 300, chara->w, chara->h );
                        readkey();
                        if(key[KEY_LEFT])
                        {
                            if(cx!=250)
                            {
                                cx-=120;
                            }
                        }
                        else if(key[KEY_RIGHT])
                        {
                            if(cx!=370)
                            {
                                cx+=120;
                            }
                        }
                        else if(key[KEY_SPACE])
                        {
                            if(cx==250)
                            {
                                fwrite(&player, sizeof(Player), 1, fp1);
                                ListNode *cur = building.build;
                                while (cur != 0)
                                {
                                    fwrite(&cur->data, sizeof(Build), 1, fp1);
                                    cur = cur->next;
                                }
                                fclose(fp1);
                                end=1;
                            }
                            else
                            {
                                end=1;
                            }
                            destroy_bitmap( cover );
                        }
                    }
                }
                else
                {
                    FILE *fp1=fopen("file1.sav","wb");
                    fwrite(&player, sizeof(Player), 1, fp1);
                    ListNode *cur = building.build;
                    while (cur != 0)
                    {
                        fwrite(&cur->data, sizeof(Build), 1, fp1);
                        cur = cur->next;
                    }
                    fclose(fp1);
                    end=1;
                }
            }
            else if(startc==230)
            {
                if(fp2)
                {
                    fclose(fp2);
                    while(end!=1)
                    {
                        end=0;
                        blit( cover, screen, 0, 0, 200, 200, cover->w, cover->h );
                        blit( chara, screen, 0, 0, cx, 300, chara->w, chara->h );
                        readkey();
                        if(key[KEY_LEFT])
                        {
                            if(cx!=250)
                            {
                                cx-=120;
                            }
                        }
                        else if(key[KEY_RIGHT])
                        {
                            if(cx!=370)
                            {
                                cx+=120;
                            }
                        }
                        else if(key[KEY_SPACE])
                        {
                            if(cx==250)
                            {
                                fwrite(&player, sizeof(Player), 1, fp2);
                                ListNode *cur = building.build;
                                while (cur != 0)
                                {
                                    fwrite(&cur->data, sizeof(Build), 1, fp2);
                                    cur = cur->next;
                                }
                                fclose(fp2);
                                end=1;
                            }
                            else
                            {
                                end=1;
                            }
                            destroy_bitmap( cover );
                        }
                    }
                }
                else
                {
                    FILE *fp2=fopen("file2.sav","wb");
                    fwrite(&player, sizeof(Player), 1, fp2);
                    ListNode *cur = building.build;
                    while (cur != 0)
                    {
                        fwrite(&cur->data, sizeof(Build), 1, fp2);
                        cur = cur->next;
                    }
                    fclose(fp2);
                    end=1;
                }
            }
            else
            {
                if(fp3)
                {
                    fclose(fp3);
                    while(end!=1)
                    {
                        end=0;
                        blit( cover, screen, 0, 0, 200, 200, cover->w, cover->h );
                        blit( chara, screen, 0, 0, cx, 300, chara->w, chara->h );
                        readkey();
                        if(key[KEY_LEFT])
                        {
                            if(cx!=250)
                            {
                                cx-=120;
                            }
                        }
                        else if(key[KEY_RIGHT])
                        {
                            if(cx!=370)
                            {
                                cx+=120;
                            }
                        }
                        else if(key[KEY_SPACE])
                        {
                            if(cx==250)
                            {
                                fwrite(&player, sizeof(Player), 1, fp3);
                                ListNode *cur = building.build;
                                while (cur != 0)
                                {
                                    fwrite(&cur->data, sizeof(Build), 1, fp3);
                                    cur = cur->next;
                                }
                                fclose(fp3);
                                end=1;
                            }
                            else
                            {
                                end=1;
                            }
                            destroy_bitmap( cover );
                        }
                    }
                }
                else
                {
                    FILE *fp3=fopen("file3.sav","wb");
                    fwrite(&player, sizeof(Player), 1, fp3);
                    ListNode *cur = building.build;
                    while (cur != 0)
                    {
                        fwrite(&cur->data, sizeof(Build), 1, fp3);
                        cur = cur->next;
                    }
                    fclose(fp3);
                    end=1;
                }
            }
        }
    }
    destroy_bitmap( kingdom );
    destroy_bitmap( chara );
    destroy_bitmap( file1 );
    destroy_bitmap( file2 );
    destroy_bitmap( file3 );
}
void game()
{
    clock_t start, finish;
    start = clock();
    Player player;
    BuildingS building;
    Create(&building);
    int end=0,chary=110,charx=50,prex,prey,p=0,cx=250;
    BITMAP *ground,*supply1,*chara,*battle;
    BITMAP *save=load_bitmap("save.bmp",NULL);
    ground=load_bitmap( "ground.bmp", NULL );
    battle=load_bitmap("battle.bmp",NULL);
    chara=load_bitmap( "char.bmp", NULL );
    blit( ground, screen, 0, 0, 0, 0, ground->w, ground->h );
    textprintf_ex(screen, font, 10, 10, makecol(0, 0, 0),
                  -1, "Level: %d   Money: %d   Supplies: %d   Attack: %d   Deffend: %d",player.level,player.money,player.supply,player.attack,player.defend);
    supply1=load_bitmap("supply1.bmp",NULL);
    while(end!=1)
    {
        end=0;
        blit( ground, screen, 0, 0, 0, 0, ground->w, ground->h );
        blit( chara, screen, 0, 0, charx, chary, chara->w, chara->h );
        textprintf_ex(screen, font, 10, 10, makecol(255, 255, 0),
                      -1, "Level: %d   Money: %d   Supplies: %d   Attack: %d   Deffend: %d",player.level,player.money,player.supply,player.attack,player.defend);
        blit( battle, screen, 0, 0, 540, 350, battle->w, battle->h );
        Print(building);
        readkey();
        if(key[KEY_DOWN])
        {
            if(chary!=410)
            {
                chary+=100;
                p+=6;
            }
        }
        else if(key[KEY_UP])
        {
            if(chary!=110)
            {
                chary-=100;
                p-=6;
            }
        }
        else if(key[KEY_LEFT])
        {
            if(charx!=50)
            {
                charx-=100;
                p-=1;
            }
        }
        else if(key[KEY_RIGHT])
        {
            if(charx!=550)
            {
                charx+=100;
                p+=1;
            }
        }
        else if(key[KEY_ESC])
        {
            //while(end!=1)
            //{
               // end=0;
               //blit( save, screen, 0, 0, 200, 200, save->w, save->h );
               // blit( chara, screen, 0, 0, cx, 300, chara->w, chara->h );
               // readkey();
               // if(key[KEY_LEFT])
               // {
               //     if(cx!=250)
               //     {
               //         cx-=120;
               //     }
               // }
               // else if(key[KEY_RIGHT])
               // {
               //     if(cx!=370)
               //     {
               //         cx+=120;
               //     }
               // }
               // else if(key[KEY_SPACE])
               // {
               //     if(cx==250)
               //     {
               //         savegame(player,building);
               //         end=1;
               //     }
               //     else
               //     {
               //         end=1;
               //     }
               //     destroy_bitmap( save );
               // }
           // }
        }
        else if(key[KEY_SPACE])
        {
            prex=charx;
            prey=chary;
            if(p==23&&player.war<25&&player.money-250*player.war>0&&player.supply-125*player.war>0)
            {
                int win=War(player,player.war,building);
                if(win==1)
                {
                    player.money+=500*player.war;
                    player.supply+=250*player.war;
                    player.exp+=50;
                    player.war+=1;
                }
                else if(win==-1)
                {
                    player.money-=250*player.war;
                    player.supply-=125*player.war;
                }
            }
            else if(p!=23)
            {
                buildchoose(&player,&building,p,(finish-start)/1000);
            }
            chary=prey;
            charx=prex;
        }
        if(player.exp>=50)
        {
            player.level+=1;
            player.attack=player.level*10;
            player.defend=player.level*10;
            player.hp=90+player.level*10;
            player.exp=0;
        }
        finish = clock();
    }
    destroy_bitmap( ground );
    destroy_bitmap( chara );
    destroy_bitmap( battle );
}
void loadgame()
{
    int startc=100,end=0,ch1=0,ch2=0,ch3=0;
    BITMAP *kingdom,*chara,*file1,*file2,*file3;
    kingdom = load_bitmap( "kingdomknights.bmp", NULL );
    chara=load_bitmap( "char.bmp", NULL );
    file1=load_bitmap( "file1.bmp", NULL );
    file2=load_bitmap( "file2.bmp", NULL );
    file3=load_bitmap( "file3.bmp", NULL );
    Player player1,player2,player3;
    BuildingS building1,building2,building3;
    FILE *fp1=fopen("file1.sav","rb");
    FILE *fp2=fopen("file2.sav","rb");
    FILE *fp3=fopen("file3.sav","rb");
    while(end!=1)
    {
        end=0;
        blit( kingdom, screen, 0, 0, 0, 0, kingdom->w, kingdom->h );
        blit( file1, screen, 0, 0, 150, 90, file1->w, file1->h );
        blit( file2, screen, 0, 0, 150, 200, file2->w, file2->h );
        blit( file3, screen, 0, 0, 150, 310, file3->w, file3->h );
        blit( chara, screen, 0, 0, 400, startc, chara->w, chara->h );
        if(fp1)
        {
            fread(&player1, sizeof(Player), 1, fp1);
            while(!feof(fp1))
            {
                Build build;
                fread(&build, sizeof(Build), 1, fp1);
                addbuild(&building1,build.kind);
            }
            textprintf_ex(screen, font, 150, 110, makecol(0, 0, 0),
                          -1, "Level:%d Money:%d Supplies:%d",player1.level,player1.money,player1.supply);
            textprintf_ex(screen, font, 150, 120, makecol(0, 0, 0),
                          -1, "Attack:%d Deffend:%d",player1.attack,player1.defend);
            textprintf_ex(screen, font, 150, 130, makecol(0, 0, 0),
                          -1, "hp:%d exp:%d war:%d",player1.hp,player1.exp,player1.war);
            fclose(fp1);
            ch1=1;
        }
        if(fp2)
        {
            fread(&player2, sizeof(Player), 1, fp2);
            while(!feof(fp2))
            {
                Build build;
                fread(&build, sizeof(Build), 1, fp2);
                addbuild(&building2,build.kind);
            }
            textprintf_ex(screen, font, 150, 220, makecol(0, 0, 0),
                          -1, "Level:%d Money:%d Supplies:%d",player2.level,player2.money,player2.supply);
            textprintf_ex(screen, font, 150, 230, makecol(0, 0, 0),
                          -1, "Attack:%d Deffend:%d",player2.attack,player2.defend);
            textprintf_ex(screen, font, 150, 240, makecol(0, 0, 0),
                          -1, "hp:%d exp:%d war:%d",player2.hp,player2.exp,player2.war);
            fclose(fp2);
            ch2=1;
        }
        if(fp3)
        {
            fread(&player3, sizeof(Player), 1, fp3);
            while(!feof(fp3))
            {
                Build build;
                fread(&build, sizeof(Build), 1, fp3);
                addbuild(&building3,build.kind);
            }
            textprintf_ex(screen, font, 150, 330, makecol(0, 0, 0),
                          -1, "Level:%d Money:%d Supplies:%d",player3.level,player3.money,player3.supply);
            textprintf_ex(screen, font, 150, 340, makecol(0, 0, 0),
                          -1, "Attack:%d Deffend:%d",player3.attack,player3.defend);
            textprintf_ex(screen, font, 150, 350, makecol(0, 0, 0),
                          -1, "hp:%d exp:%d war:%d",player3.hp,player3.exp,player3.war);
            fclose(fp3);
            ch3=1;
        }
        readkey();
        if(key[KEY_DOWN])
        {
            if(startc!=320)
            {
                startc+=110;
            }
        }
        else if(key[KEY_UP])
        {
            if(startc!=100)
            {
                startc-=110;
            }
        }
        else if(key[KEY_ESC])
        {
            end=1;
        }
        else if(key[KEY_SPACE])
        {
            if(startc==100&&ch1==1)
            {
                //game(1,player1,building1);
                end=1;
            }
            else if(startc==210&&ch2==1)
            {
                //game(1,player2,building2);
                end=1;
            }
            else if(startc==320&&ch3==1)
            {
               // game(1,player3,building3);
                end=1;
            }
        }
    }
    destroy_bitmap( kingdom );
    destroy_bitmap( chara );
    destroy_bitmap( file1 );
    destroy_bitmap( file2 );
    destroy_bitmap( file3 );
}
