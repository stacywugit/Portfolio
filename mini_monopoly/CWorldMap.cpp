#include "CWorldMap.h"
#include "CMapUnit.h"
#include <stdio.h>
void CWorldMap::CreateMap()
{
    FILE* mapfile;
    mapfile = fopen("map.txt", "r");
    char unittype;
    if(mapfile)
    {
        while(!feof(mapfile))
        {
            fscanf(mapfile, "%c", &unittype);
            if(unittype == 'R')
            {
                total_units += 1;
                CRandomsCostUnit *R = new CRandomsCostUnit;
                R->id_ = total_units - 1;
                fscanf(mapfile, "%s", R->name_);
                fscanf(mapfile, "%d", &R->price_);
                fscanf(mapfile, "%d", &R->travel_fine_); 
                R->type_ = 'R';
                units_[total_units-1] = R;
            }
            else if(unittype == 'U')
            {
                total_units += 1;
                CUpgradableUnit *U = new CUpgradableUnit;
                U->id_ = total_units - 1;
                fscanf(mapfile, "%s", U->name_);
                fscanf(mapfile, "%d", &U->price_);
                fscanf(mapfile, "%d", &U->travel_fine_);
                for(int i = 0; i < 5; i++)
                {
                    fscanf(mapfile, "%d", &U->upgrade_price_[i]);
                }
                U->type_ = 'U';
                units_[total_units-1] = U;
            }
            else if(unittype == 'C')
            {
                total_units += 1;
                CCollectableUnit *C = new CCollectableUnit;
                C->id_ = total_units - 1;
                fscanf(mapfile, "%s", C->name_);
                fscanf(mapfile, "%d", &C->price_);
                fscanf(mapfile, "%d", &C->unit_fine_);
                C->type_ = 'C';
                units_[total_units-1] = C;
            }
            else if(unittype == 'J')
            {
                total_units += 1;
                CJailUnit *J = new CJailUnit;
                J->id_ = total_units - 1;
                fscanf(mapfile, "%s", J->name_);
                units_[total_units-1] = J;
                J->type_ = 'J';
            }
        }
        fclose(mapfile);
    }
}

//add by L.Tarng START
bool CWorldMap::IsUpgradable(const int Unit_Id_)
{
    if(units_[Unit_Id_]->type_ == 'U') return true;
    else return false;
}
bool CWorldMap::IsJail(const int Unit_Id_)
{
    if(units_[Unit_Id_]->type_ == 'J') return true;
    else return false;
}
void CWorldMap::RecoverNoHost(const int Player_Id_)
{
    for(int i=0; i<total_units; i++)
    {
        if(units_[i]->getHost() == Player_Id_) units_[i]->ToOriginalStatus();
    }
}
//add by L.Tarng END
