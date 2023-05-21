#include "iostream"
#include "cstdio"

#ifndef _WARCRAFT_H
#define _WARCRAFT_H

#ifndef _WARRIOR_H
#define _WARRIOR_H

#include "algorithm"
#ifndef _POS_H
#define _POS_H


int InitHealth[5];
int InitATK[5];

enum _WARRIOR
{
    dragon,
    ninja,
    iceman,
    lion,
    wolf
};
const char WarriorName[5][10] = {
        "dragon",
        "ninja",
        "iceman",
        "lion",
        "wolf"};

enum _WEAPON
{
    sword,
    bomb,
    arrow
};
const char WeaponName[3][10] = {
        "sword",
        "bomb",
        "arrow"};
enum _CAMP
{
    RED,
    BLUE
};
const char CampName[2][5] = {
        "red",
        "blue"};


const _WARRIOR makelist[2][5] = {
        {iceman, lion, wolf, ninja, dragon},
        {lion, dragon, ninja, iceman, wolf}};
class Command;
class City;
class warrior;
class weapon;
class Lion;
class Wolf;

class City
{
private:
    int RedID;
    int BlueID;
    int id;

public:
    void clearRED() { RedID = -1; }
    void clearBLUE() { BlueID = -1; }
    void add(_CAMP camp, int tid)
    {
        if (camp == RED)
            RedID = tid;
        else
            BlueID = tid;
    }
    int getid() { return id; }
    int redid() { return RedID; }
    int blueid() { return BlueID; }
    City(int i) : id(i), RedID(-1), BlueID(-1) {}
};

class Command
{
private:
    _CAMP camp;
    int bioelement;
    int curid;
    bool isStop;

public:
    Command(){};
    Command(_CAMP cp, int bio) : camp(cp), bioelement(bio), curid(0) {}
    void report_bio();
    warrior *create();
    void init(_CAMP);
};


#endif
#include "vector"

class weapon
{
private:
    int ATKtoOther;
    int ATKtoSelf;
    int NumOfUse;
    int id;

public:
    weapon(_WEAPON);
    bool operator<(const weapon &b) const;
    const int getID() { return id; }
    const int getNum() { return NumOfUse; }
    const int getATK2o(const warrior &a);
    const int getATK2s(const warrior &a);
    void use() { --NumOfUse; }
};

class warrior
{
private:
    int id;
    std::vector<weapon> weapons;
    bool visble;
    _WARRIOR type;
    int ATK;
    int Health;
    _CAMP camp;
    int pos;
    int curweaponID;
    void useweapon(warrior &b);
    void beAtk(int);

public:
    warrior(_WARRIOR ttype, int curid, _CAMP tcamp);
    int getATK() const { return ATK; }
    virtual ~warrior(){};
    void march();
    void fight(warrior &b);
    const bool &vis() const { return visble; }
    _CAMP getcamp() { return camp; }
    const int getid() const { return id; }
    const int getpos() const { return pos; }
    void report_march();
    const _WARRIOR &gettype() const { return type; }
    weapon &firstweapon() { return weapons[0]; }
    const int weaponNum() const { return weapons.size(); }
    void report_weapon();
    void addWeapon(const weapon &w) { weapons.push_back(w); }
    void sortWeapon();
    weapon belooted();
    bool emptyWeapon();
    bool sumAtk();
    void died();
};

class Lion : public warrior
{
private:
    bool WillRun;
    int loyalty;

public:
    Lion(_WARRIOR ttype, int curid, _CAMP tcamp, int loy);
    bool isrun();
    void check();
};

class Wolf : public warrior
{
public:
    Wolf(_WARRIOR ttype, int curid, _CAMP tcamp) : warrior(ttype, curid, tcamp){};
    void loot(warrior *b);
};

#endif

void game();
void init();

#endif

#include "algorithm"
#include "cstdio"
#include "iostream"

int CurHour = 0;
int M, N, K, T;
std::vector<City> citys;
static std::vector<warrior *> AllWarrior;
static std::vector<Lion *> AllLion;
Command CmdRed, CmdBlue;
bool isGameEnd = false;
int cnt = 0;
extern int InitHealth[5];
extern int InitATK[5];

bool cmp(warrior *a, warrior *b);
void delete_lion();
void sortwarrior();
void march();
void create();
void fight();
void wolf_loot();
void rpt_bio();
void rpt_weapon();
bool checktime(int minu);
void CMDwasTaken();

void init()
{
    citys.clear();
    for (auto x: AllWarrior)
        delete x;
    AllWarrior.clear();
    AllLion.clear();
    isGameEnd = false;
    std::cin >> M >> N >> K >> T;
    for (int i = 0; i < 5; ++i)
        std::cin >> InitHealth[i];
    for (int i = 0; i < 5; ++i)
        std::cin >> InitATK[i];
    CmdRed.init(RED);
    CmdBlue.init(BLUE);
    CurHour = 0;
    citys.push_back(City(0));
    for (int i = 1; i <= N; ++i)
        citys.push_back(City(i));
    citys.push_back(City(N + 1));
    printf("Case %d:\n", ++cnt);
}

void game()
{
    while (!isGameEnd)
    {
        if (checktime(0))
            break;
        create();
        if (checktime(5))
            break;
        delete_lion();
        if (checktime(10))
            break;
        march();
        if (isGameEnd)
        {
            CMDwasTaken();
            break;
        }
        if (checktime(35))
            break;
        wolf_loot();
        if (checktime(40))
            break;
        fight();
        if (checktime(50))
            break;
        rpt_bio();
        if (checktime(55))
            break;
        rpt_weapon();
        ++CurHour;
    }
}

void CMDwasTaken()
{
    if (citys[0].blueid() != -1)
        printf("%03d:10 red headquarter was taken\n", CurHour);
    if (citys[N + 1].redid() != -1)
        printf("%03d:10 blue headquarter was taken\n", CurHour);
}

bool cmp(warrior *a, warrior *b)
{
    if (b->vis() == 0)
        return true;
    if (a->vis() == 0)
        return false;
    if (a->getpos() != b->getpos())
        return a->getpos() < b->getpos();
    if (a->getcamp() == RED)
        return true;
    return false;
}

void delete_lion()
{
    for (auto x: AllLion)
        if (x->vis())
            if (x->isrun())
            {
                printf("%03d:05 %s lion %d ran away\n", CurHour, (x->getcamp() == RED ? "red" : "blue"), x->getid());
                x->died();
            }
}

inline void sortwarrior()
{
    std::sort(AllWarrior.begin(), AllWarrior.end(), cmp);
    while (AllWarrior.size() > 0 && !AllWarrior[AllWarrior.size() - 1]->vis())
        AllWarrior.pop_back();
}

void march()
{

    for (auto x: AllWarrior)
        if (x->vis())
            x->march();
    sortwarrior();
    for (auto x: AllWarrior)
        if (x->vis())
            x->report_march();
    for (auto x: AllLion)
        if (x->vis())
            x->check();
}

void create()
{
    warrior *nw = CmdRed.create();
    if (nw != nullptr)
    {
        AllWarrior.push_back(nw);
        if (AllWarrior[AllWarrior.size() - 1]->gettype() == lion)
            AllLion.push_back(dynamic_cast<Lion *>(AllWarrior[AllWarrior.size() - 1]));
    }
    nw = CmdBlue.create();
    if (nw != nullptr)
    {
        AllWarrior.push_back(nw);
        if (AllWarrior[AllWarrior.size() - 1]->gettype() == lion)
            AllLion.push_back(dynamic_cast<Lion *>(AllWarrior[AllWarrior.size() - 1]));
    }
    sortwarrior();
}

void fight()
{
    for (auto x: citys)
    {
        if (x.redid() == -1 || x.blueid() == -1)
            continue;
        warrior *redw = nullptr, *bluew = nullptr;
        for (auto w: AllWarrior)
            if (w->vis())
            {
                if (w->getcamp() == RED && w->getid() == x.redid())
                    redw = w;
                else if (w->getcamp() == BLUE && w->getid() == x.blueid())
                    bluew = w;
            }
        if (redw == nullptr || bluew == nullptr)
            continue;
        if (x.getid() % 2 == 1)
            redw->fight(*bluew);
        else
            bluew->fight(*redw);
    }
}

void wolf_loot()
{
    for (auto x: AllWarrior)
        if (x->vis() && x->gettype() == wolf)
        {
            Wolf *pw = dynamic_cast<Wolf *>(x);
            warrior *po = nullptr;
            if (pw->getcamp() == BLUE)
            {
                if (citys[pw->getpos()].redid() == -1)
                    continue;
                for (auto y: AllWarrior)
                    if (y->vis() && y->getcamp() == RED && y->getid() == citys[pw->getpos()].redid())
                        po = y;
            } else
            {
                if (citys[pw->getpos()].blueid() == -1)
                    continue;
                for (auto y: AllWarrior)
                    if (y->vis() && y->getcamp() == BLUE && y->getid() == citys[pw->getpos()].blueid())
                        po = y;
            }
            if (po == nullptr)
                continue;
            pw->loot(po);
        }
}

inline void rpt_bio()
{
    CmdRed.report_bio();
    CmdBlue.report_bio();
}

inline void rpt_weapon()
{
    for (auto x: AllWarrior)
        if (x->vis())
            x->report_weapon();
}

inline bool checktime(int minu)
{
    int sum = CurHour * 60 + minu;
    if (sum < T)
        return false;
    isGameEnd = true;
    return true;
}

weapon::weapon(_WEAPON type)
{
    if (type == sword)
    {
        id = 0;
        ATKtoOther = 20;
        ATKtoSelf = 0;
        NumOfUse = -1;
    } else if (type == bomb)
    {
        id = 1;
        ATKtoOther = 40;
        ATKtoSelf = 20;
        NumOfUse = 1;
    } else if (type == arrow)
    {
        id = 2;
        ATKtoOther = 30;
        ATKtoSelf = 0;
        NumOfUse = 2;
    }
}

bool weapon::operator<(const weapon &b) const
{
    if (NumOfUse == 0)
        return false;
    if (b.NumOfUse == 0)
        return true;
    if (id != b.id)
        return id < b.id;
    return NumOfUse > b.NumOfUse;
}

warrior::warrior(_WARRIOR ttype, int curid, _CAMP tcamp) : type(ttype), id(curid), visble(true), camp(tcamp)
{
    pos = (camp == RED ? 0 : N + 1);
    ATK = InitATK[type];
    Health = InitHealth[type];
    if (type == dragon || type == lion)
        weapons.push_back(weapon(_WEAPON(id % 3)));
    if (type == ninja)
    {
        weapons.push_back(weapon(_WEAPON(id % 3)));
        weapons.push_back(weapon(_WEAPON((id + 1) % 3)));
    }
    if (type == iceman)
        weapons.push_back(weapon(_WEAPON(id % 3)));
}

void warrior::march()
{
    if (type == iceman)
        Health -= Health / 10;
    if (Health <= 0)
    {
        visble = false;
        return;
    }
    if (camp == RED)
    {
        if (citys[pos].redid() == id)
            citys[pos].clearRED();
        pos++;
        citys[pos].add(camp, id);
    } else
    {
        if (citys[pos].blueid() == id)
            citys[pos].clearBLUE();
        pos--;
        citys[pos].add(camp, id);
    }
}

void warrior::report_march()
{
    if ((camp == RED && pos == N + 1) || (camp == BLUE && pos == 0))
    {
        isGameEnd = true;
        printf("%03d:10 %s %s %d reached %s headquarter with %d elements and force %d\n",
               CurHour, CampName[camp], WarriorName[type], id, (camp == RED ? "blue" : "red"), Health, ATK);
    } else
        printf("%03d:10 %s %s %d marched to city %d with %d elements and force %d\n",
               CurHour, CampName[camp], WarriorName[type], id, pos, Health, ATK);
}

Lion::Lion(_WARRIOR ttype, int curid, _CAMP tcamp, int loy) : warrior(ttype, curid, tcamp), loyalty(loy), WillRun(false) {}


weapon warrior::belooted()
{
    weapon looted = weapons[0];
    weapons.erase(weapons.begin());
    return looted;
}

void Wolf::loot(warrior *b)
{
    if (b->gettype() == wolf || b->emptyWeapon())
        return;
    b->sortWeapon();
    int Fid = b->firstweapon().getID();
    int lootnum = 0;
    while (weaponNum() < 10 && !b->emptyWeapon() && b->firstweapon().getID() == Fid)
    {
        ++lootnum;
        addWeapon(b->belooted());
    }
    sortWeapon();
    printf("%03d:35 %s wolf %d took %d %s from %s %s %d in city %d\n",
           CurHour, CampName[getcamp()], getid(), lootnum, WeaponName[Fid], CampName[b->getcamp()], WarriorName[b->gettype()], b->getid(), getpos());
}

bool warrior::emptyWeapon()
{
    bool ret = true;
    for (auto x: weapons)
        if (x.getNum() != 0)
            ret = false;
    return ret;
}

void warrior::sortWeapon()
{
    curweaponID = 0;
    std::sort(weapons.begin(), weapons.end());
    while (weapons.size() > 0 && weapons[weapons.size() - 1].getNum() == 0)
        weapons.pop_back();
}

inline const int weapon::getATK2s(const warrior &a)
{
    if (a.gettype() == ninja)
        return 0;
    return ATKtoSelf * a.getATK() / 100;
}
inline const int weapon::getATK2o(const warrior &a) { return ATKtoOther * a.getATK() / 100; }
bool warrior::sumAtk()
{
    int sum2o = 0;
    int sum2s = 0;
    for (auto x: weapons)
    {
        if (x.getNum() != 0)
        {
            sum2o += x.getATK2o(*this);
            sum2s += x.getATK2s(*this);
        }
    }
    return sum2o || sum2s;
}

enum ending
{
    con,
    die,
    zeroWeapon,
    zeroATK,
    alldie
};

inline ending isend(warrior &a, warrior &b)
{
    ending flag = con;
    if (a.vis() ^ b.vis())
    {
        flag = die;
        return flag;
    }
    if (!a.vis() && !b.vis())
    {
        flag = alldie;
        return flag;
    }
    if (a.emptyWeapon() && b.emptyWeapon())
    {
        flag = zeroWeapon;
        return flag;
    }
    if (!a.sumAtk() && !b.sumAtk())
    {
        flag = zeroATK;
        return flag;
    }
    return flag;
}

void warrior::beAtk(int num)
{
    Health -= num;
    if (Health <= 0)
        visble = false;
}

void warrior::useweapon(warrior &b)
{
    if (emptyWeapon())
        return;
    while (curweaponID < weapons.size() && weapons[curweaponID].getNum() == 0)
        ++curweaponID;
    if (curweaponID == weapons.size())
    {
        curweaponID = 0;
        while (curweaponID < weapons.size() && weapons[curweaponID].getNum() == 0)
            ++curweaponID;
        if (curweaponID == weapons.size())
            return;
    }
    this->beAtk(weapons[curweaponID].getATK2s(*this));
    b.beAtk(weapons[curweaponID].getATK2o(*this));
    weapons[curweaponID].use();
    ++curweaponID;
}


void warrior::fight(warrior &b)
{
    sortWeapon();
    b.sortWeapon();
    int time = 1;
    while (isend(*this, b) == con)
    {
        if (time % 2)
            useweapon(b);
        else
            b.useweapon(*this);
        ++time;
    }
    ending end = isend(*this, b);
    if (end == die)
    {
        warrior &winner = (this->vis() ? *this : b);
        warrior &died = (this->vis() ? b : *this);
        printf("%03d:40 %s %s %d killed %s %s %d in city %d remaining %d elements\n",
               CurHour, CampName[winner.getcamp()], WarriorName[winner.gettype()], winner.getid(),
               CampName[died.getcamp()], WarriorName[died.gettype()], died.getid(),
               pos, winner.Health);
        if (winner.type == dragon)
            printf("%03d:40 %s dragon %d yelled in city %d\n",
                   CurHour, CampName[winner.camp], winner.id, pos);
        died.sortWeapon();
        while (winner.weapons.size() <= 10 && !died.emptyWeapon())
            winner.addWeapon(died.belooted());
    } else if (end == alldie)
    {
        warrior &redw = (this->camp == RED ? *this : b);
        warrior &bluew = (this->camp == BLUE ? *this : b);
        printf("%03d:40 both red %s %d and blue %s %d died in city %d\n",
               CurHour, WarriorName[redw.type], redw.id, WarriorName[bluew.type], bluew.id, pos);
    } else
    {
        warrior &redw = (this->camp == RED ? *this : b);
        warrior &bluew = (this->camp == BLUE ? *this : b);
        printf("%03d:40 both red %s %d and blue %s %d were alive in city %d\n",
               CurHour, WarriorName[redw.type], redw.id, WarriorName[bluew.type], bluew.id, pos);
        if (type == dragon && b.type == dragon)
        {
            if (camp == RED)
            {
                printf("%03d:40 %s dragon %d yelled in city %d\n",
                       CurHour, CampName[camp], id, pos);
                printf("%03d:40 %s dragon %d yelled in city %d\n",
                       CurHour, CampName[b.camp], b.id, pos);
            } else
            {
                printf("%03d:40 %s dragon %d yelled in city %d\n",
                       CurHour, CampName[b.camp], b.id, pos);
                printf("%03d:40 %s dragon %d yelled in city %d\n",
                       CurHour, CampName[camp], id, pos);
            }
        } else
        {
            if (type == dragon)
                printf("%03d:40 %s dragon %d yelled in city %d\n",
                       CurHour, CampName[camp], id, pos);
            if (b.type == dragon)
                printf("%03d:40 %s dragon %d yelled in city %d\n",
                       CurHour, CampName[b.camp], b.id, pos);
        }
    }
}

void warrior::report_weapon()
{
    int sum[3] = {0};
    sortWeapon();
    for (auto x: weapons)
        sum[x.getID()]++;
    printf("%03d:55 %s %s %d has %d sword %d bomb %d arrow and %d elements\n",
           CurHour, CampName[camp], WarriorName[type], id, sum[sword], sum[bomb], sum[arrow], Health);
}

void Lion::check()
{
    loyalty -= K;
    if (loyalty <= 0)
        WillRun = true;
}

bool Lion::isrun()
{
    return WillRun;
}

void warrior::died()
{
    visble = false;
    if (camp == RED)
        citys[pos].clearRED();
    else
        citys[pos].clearBLUE();
}

#include "cstdio"

void Command::report_bio()
{
    printf("%03d:50 %d elements in %s headquarter\n", CurHour, bioelement, (camp == RED ? "red" : "blue"));
}

warrior *Command::create()
{
    if (isStop)
        return nullptr;
    curid++;
    _WARRIOR wartype = makelist[camp][CurHour % 5];
    if (bioelement - InitHealth[wartype] < 0)
    {
        isStop = true;
        return nullptr;
    }
    bioelement -= InitHealth[wartype];
    warrior *pt;
    if (wartype == lion)
        pt = new Lion(wartype, curid, camp, bioelement);
    else if (wartype == wolf)
        pt = new Wolf(wartype, curid, camp);
    else
        pt = new warrior(wartype, curid, camp);
    printf("%03d:00 %s %s %d born\n", CurHour, CampName[camp], WarriorName[pt->gettype()], curid);
    if (wartype == lion)
        printf("Its loyalty is %d\n", bioelement);
    return pt;
}

void Command::init(_CAMP c)
{
    camp = c;
    bioelement = M;
    curid = 0;
    isStop = false;
}

int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        init();
        game();
    }
    return 0;
}