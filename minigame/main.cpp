#include <allegro.h>
#include <stdio.h>
#include "game.h"
#include "player.h"
int main( void )
{
    BITMAP *kingdom,*start,*chara;
    Player player;
    BuildingS b;
    int startc=100,end=0;
    allegro_init();
    install_keyboard();
    set_color_depth( 32 );
    set_gfx_mode( GFX_SAFE, 600, 520, 0, 0 );
    kingdom = load_bitmap( "kingdomknights.bmp", NULL );
    start=load_bitmap( "start.bmp", NULL );
    chara=load_bitmap( "char.bmp", NULL );
    blit( kingdom, screen, 0, 0, 0, 0, kingdom->w, kingdom->h );
    blit( start, screen, 0, 0, 200, 100, start->w,start->h );
    while(end!=1)
    {
        end=0;
        blit( kingdom, screen, 0, 0, 0, 0, kingdom->w, kingdom->h );
        blit( start, screen, 0, 0, 200, 100, start->w,start->h );
        blit( chara, screen, 0, 0, 320, startc, chara->w, chara->h );
        readkey();
        if(key[KEY_DOWN])
        {
            if(startc!=160)
            {
                startc+=30;
            }
        }
        else if(key[KEY_UP])
        {
            if(startc!=100)
            {
                startc-=30;
            }
        }
        else if(key[KEY_SPACE])
        {
            if(startc==100)
            {
                game();
            }
            else if(startc==130)
            {
                //loadgame();
            }
            else
            {
                end=1;
            }
        }
    }
    destroy_bitmap( kingdom );
    destroy_bitmap( start );
    destroy_bitmap( chara );
    return 0;
}
END_OF_MAIN()
