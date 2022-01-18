#include "CMapUnit.h"
#ifndef CWORLDMAP_H___
#define CWORLDMAP_H___
const int MAXNUM_UNIT = 20;
class CWorldMap
{
public:
    ~CWorldMap()
    {
        for(int i = 0; i < total_units; i ++)
        {
            delete units_[i];
        }
    };
    void CreateMap();
    const int gettotalunits()
    {
        return total_units;
    }
    CMapUnit *getunits(int i)
    {
        return units_[i];
    }
    void settotalunits(int i)
    {
        total_units = i;
    }
    //add b L.Tarng START
    bool IsUpgradable(const int Unit_Id_);
    bool IsJail(const int Unit_Id_);
    void RecoverNoHost(int Player_Id_);
    //add by L.Tarng END

    bool nohost(const int i)
    {
        if(units_[i]->getHost() >=0) return false;
        else return true;
    }
    const int buyhouseprice(int i)
    {
        return units_[i]->price_;
    }
    void ToOriginal(const int player)
    {
        for(int i = 0; i < total_units; i++)
        {
            if(units_[i]->getHost()==player) units_[i]->ToOriginalStatus();
        }
    }
    
    int HaveCUnit(const int playerid)
    {
        int num = 0;
        for(int i = 0 ; i < total_units; i++)
        {
            if(units_[i]->getHost() == playerid && units_[i]->type_=='C')
            {
                num++;
            }
        }
        return num;
    }
    int HaveUnit(const int playerid)
    {
        int num = 0;
        for(int i = 0 ; i < total_units; i++)
        {
            if(units_[i]->getHost() == playerid)
            {
                num++;
            }
        }
        return num;
    }
private:
    int total_units=0;
    CMapUnit *units_[MAXNUM_UNIT]= {};
};
#endif // CWORLDMAP_H___
