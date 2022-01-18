#ifndef MAPUNIT_H___
#define MAPUNIT_H___
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"player.h"
const int MAXNUM_PLAYER = 4;
const int MAX_LEVEL = 5;
class CMapUnit
{
public:
    int id_=-1, price_=0;
    char name_[21]="", type_=' ';
    int getHost() const
    {
        return host_;
    }
    virtual bool CanLevelUp() {return true;};
    virtual void setHost(const int Player_Id_)
    {
        host_ = Player_Id_;
    }
    virtual int ActuallyFine(int n)
    {
        return 0;
    };
    virtual void LevelUp() {};
    virtual void ToOriginalStatus()
    {
        host_=-1;
    }
    virtual void Display(CWorldPlayer cwp) const {};
protected:
    int host_=-1;
};

class CUpgradableUnit : public CMapUnit
{
public:
    int upgrade_price_[MAX_LEVEL]= {0}, travel_fine_=0;
    virtual bool CanLevelUp()
    {
        if(level_<MAX_LEVEL) return true;
        return false;
    }
    virtual void setHost(const int Player_Id_)
    {
        if(host_<0) host_ = Player_Id_;
        LevelUp();
    }
    virtual int ActuallyFine(int n)
    {
        return (level_)*travel_fine_;
    }
    virtual void Display(CWorldPlayer cwp) const
    {
        if( host_ < 0 ) printf("%10s    B$ %4d    ", name_, price_);
        else printf("%10s{%d} U$ %4d L%d ",
 name_, host_, travel_fine_, level_);
    }

protected:
    int level_=0;
    void LevelUp()
    {
        if( CanLevelUp() ) level_++;
    }
    virtual void ToOriginalStatus()
    {
        host_=-1, level_=0;
    }
};

class CCollectableUnit : public CMapUnit
{
public:
    int unit_fine_=0;
    virtual int ActuallyFine(int unit_num_)
    {
        return unit_fine_*unit_num_;
    }
    virtual void Display(CWorldPlayer cwp) const
    {
        if( host_ < 0 ) printf("%10s  B$ %4d    ", name_, price_);
        else printf("%10s {%d} x%d ", 
name_, host_, cwp.getplayers(host_)->getcnumunits());
    }
};
class CRandomsCostUnit : public CMapUnit
{
public:
    int travel_fine_=0;
    virtual int ActuallyFine(int n)
    {
        srand(time(0));
        int dice_ = rand()%6 + 1;
        return travel_fine_*dice_;
    }
    virtual void Display(CWorldPlayer cwp) const
    {
        if( host_ < 0 ) printf("%10s  B$ %4d    ", name_, price_);
        else printf("%10s {%d} ?     ", name_, host_);
    }
};

class CJailUnit: public CMapUnit
{
public:
    virtual void Display(CWorldPlayer cwp) const
    {
        printf("%10s\t\t", name_);
    }
};
#endif // MAPUNIT_H___
