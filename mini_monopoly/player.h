#include<string.h>
#ifndef PLAYER__
#define PLAYER__
class CPlayer
{
public:
    const int getid(){return id_;}
    const char *getname(){return name_;}
    const int getlocation(){return location_;}
    const int getmoney(){return money_;}
    const int getnumunits(){return num_units_;}
    const int getcnumunits(){return c_num_units_;}
    void setid(const int id){id_ = id;}
    void setname(const char name[]){strcpy(name_,name);}
    void setlocation(const int location){location_ = location;}
    void setmoney(const int money){money_ = money;}
    void setnumunits(const char type)
    {
        num_units_++;
        if(type == 'C') c_num_units_++;
    }
private:
    int  id_ = 0;
    char name_[20];
    int location_ = 0;
    int money_ = 30000;
    int num_units_ = 0;
    int c_num_units_ = 0;
};
class CWorldPlayer
{
public:
    const int getnumplayers(){return num_players_;}
    const int getturn(){return turn_;}
    CPlayer *getplayers(int i){return players_+i;}
    bool getstop(int i){return stop_[i];}
    void *setstop(const int i, bool stop){stop_[i] = stop;}
    void setnumplayers(const int i){num_players_ = i;}
    void setturn(const int i){turn_ = i;}
private:
    int num_players_ = 0;
    CPlayer players_[4];
    bool stop_[4] = {0};
    int turn_ = 0;
};
#endif
