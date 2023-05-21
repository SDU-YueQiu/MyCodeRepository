#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <list>
#include <algorithm>

struct ATTACK {
	int first, second;
};
// 0-sword, 1-bomb, 2-arrow
const ATTACK atk[3] = {
	{2, 10}, {4, 10}, {3, 10}
};

std::unordered_map<std::string, int> iniCity;
std::unordered_map<std::string, int> warriorStrength;
std::unordered_map<std::string, int> warriorHealth;

class Controller;
class Weapon;
class Warrior;
class Wolf;

using ShWp = std::shared_ptr<Weapon>;
using ShWr = std::shared_ptr<Warrior>;
enum ATTACK_STATE { RED_IS_ATTACKER, BLUE_IS_ATTACKER };
bool cmpRob(const ShWp& wp1, const ShWp& wp2);
bool cmpBattle(const ShWp& wp1, const ShWp& wp2);

// cities[i] = {red_wr, blue_wr} or {red_wr, null} or {null, blue_wr}
std::vector<std::pair<ShWr, ShWr>> cities;
std::vector<std::pair<std::string, std::string>> printCities;

class Warrior {
	friend class Controller;
	friend class Dragon;
	friend class Ninja;
	friend class Iceman;
	friend class Lion;
	friend class Wolf;
protected:
	std::string camp, name;
	int id, health, strength, remMeta, curCity;
	std::list<ShWp> weapons;
	std::unordered_map<std::string, int> wpCount;

public:
	int getHealth() const { return health; }
	int getStrength() const { return strength; }
	virtual std::string getName() const = 0;
	virtual std::string getCamp() const = 0;
	void setHealth(int health_) { health = health_; }

public:
	Warrior(
		const std::string& camp_,
		const std::string& name_,
		int id_, int health_, int strength_,
		int remMeta_, int curCity_
	) : camp(camp_), name(name_), id(id_), health(health_),
		strength(strength_), remMeta(remMeta_), curCity(curCity_) { }

	virtual void born(int hour, int minute) {
		printf("%03d:%02d %s %s %d born\n",
			hour, minute, camp.c_str(), name.c_str(), id);
	}

	void capture(ShWr& loser);
	int getMaxAttack();
	bool isWithoutBombAndArrow() const;
	void clearWeapon();

	/// <summary>
	/// return the marched city information, such as:
	/// "RED_WIN" is reputed "Red Headquarter is winner",
	/// "BLUE_WIN" is reputed "Blue Headquarter is winner",
	/// "KEEP_ON" is reputed "Please go on"
	/// </summary>
	virtual std::string march(int hour, int minute) {
		if (health <= 0) { return "KEEP_ON"; }
		char buf[256] = { '\0' };
		if ("red" == camp) {
			curCity = std::min(curCity + 1, iniCity["blue"]);
			if (curCity == iniCity["blue"]) {
				snprintf(buf, sizeof(buf) - 1, "%03d:%02d red %s %d reached blue headquarter with %d elements and force %d\n%03d:%02d blue headquarter was taken\n",
					hour, minute, name.c_str(), id, health, strength, hour, minute);
				printCities[curCity].first = std::string(buf);
				return "RED_WIN";
			}
			else {
				snprintf(buf, sizeof(buf) - 1, "%03d:%02d red %s %d marched to city %d with %d elements and force %d\n",
					hour, minute, name.c_str(), id, curCity, health, strength);
				printCities[curCity].first = std::string(buf);
			}
		}
		else {
			curCity = std::max(curCity - 1, iniCity["red"]);
			if (curCity == iniCity["red"]) {
				snprintf(buf, sizeof(buf) - 1, "%03d:%02d blue %s %d reached red headquarter with %d elements and force %d\n%03d:%02d red headquarter was taken\n",
					hour, minute, name.c_str(), id, health, strength, hour, minute);
				printCities[curCity].second = std::string(buf);
				return "BLUE_WIN";
			}
			else {
				snprintf(buf, sizeof(buf) - 1, "%03d:%02d blue %s %d marched to city %d with %d elements and force %d\n",
					hour, minute, name.c_str(), id, curCity, health, strength);
				printCities[curCity].second = std::string(buf);
			}
		}
		return "KEEP_ON";
	}

	virtual ~Warrior() { }
};

using CITY = std::vector<std::pair<ShWr, ShWr>>;
using CITY_INFO = std::vector<std::pair<std::string, std::string>>;
void setWarroirInCity(int cityIdx, ShWr& wr, CITY& city) {
	if ("red" == wr->getCamp()) { city[cityIdx].first = wr; }
	else if ("blue" == wr->getCamp()) { city[cityIdx].second = wr; }
}

void copyCityFrom(CITY& outCity, const CITY& inCity) {
	int citySize = (int)outCity.size();
	if (outCity.size() != inCity.size()) { return; }
	for (int i = 0; i < citySize; ++i) {
		outCity[i].first = inCity[i].first;
		outCity[i].second = inCity[i].second;
	}
}

void clearCitiesInfo(CITY_INFO& info) {
	int citySize = (int)info.size();
	for (int i = 0; i < citySize; ++i) {
		printCities[i].first = printCities[i].second = "NULL";
	}
}

void printCitiesInfo(CITY_INFO& info) {
	int citySize = (int)info.size();
	for (int i = 0; i < citySize; ++i) {
		if ("NULL" != printCities[i].first) { printf("%s", printCities[i].first.c_str()); }
		if ("NULL" != printCities[i].second) { printf("%s", printCities[i].second.c_str()); }
	}
	clearCitiesInfo(printCities);
}

class Weapon {
protected:
	bool canUsed;
public:
	Weapon(bool canUsed_ = true) : canUsed(canUsed_) { }

	/// <returns>return the current attack to attacked.</returns>
	int baseAttack(ShWr& attacker, ShWr& attacked, const ATTACK& atk) {
		int curAttack = attacker->getStrength() * atk.first / atk.second;
		int curHealth = attacked->getHealth() - curAttack;
		attacked->setHealth(curHealth);
		return curAttack;
	}

	virtual int attack(ShWr& attacker, ShWr& attacked) = 0;
	virtual std::shared_ptr<Weapon> createWeapon() = 0;
	virtual int getWeaponID() const = 0;
	virtual std::string getWeaponName() const = 0;

	bool getCanUsed() const { return canUsed; }
};

class Sword : public Weapon {
private:
	static int weaponID;
	static std::string weaponName;
public:
	int attack(ShWr& attacker, ShWr& attacked) {
		return baseAttack(attacker, attacked, atk[0]);
	}

	ShWp createWeapon() { return std::make_shared<Sword>(); }
	int getWeaponID() const { return weaponID; }
	std::string getWeaponName() const { return weaponName; }
};
std::string Sword::weaponName = "sword";
int Sword::weaponID = 0;

class Bomb : public Weapon {
private:
	int usableNums;
	static int weaponID;
	static std::string weaponName;

public:
	Bomb() : usableNums(1) { }

	int attack(ShWr& attacker, ShWr& attacked) {
		int attackToSelf = -1;
		if (usableNums > 0) {
			attackToSelf = baseAttack(attacker, attacked, atk[1]);
			usableNums--;
			if (usableNums <= 0) { canUsed = false; }
			if ("ninja" != attacker->getName()) {
				attackToSelf = attackToSelf * 5 / 10;
				int curUserHealth = attacker->getHealth();
				int userHealth = curUserHealth - attackToSelf;
				attacker->setHealth(userHealth);
			}
		}
		return attackToSelf;
	}

	ShWp createWeapon() { return std::make_shared<Bomb>(); }
	int getWeaponID() const { return weaponID; }
	std::string getWeaponName() const { return weaponName; }
};
std::string Bomb::weaponName = "bomb";
int Bomb::weaponID = 1;

class Arrow : public Weapon {
private:
	int usableNums;
	static int weaponID;
	static std::string weaponName;

public:
	Arrow() : usableNums(2) { }

	int attack(ShWr& attacker, ShWr& attacked) {
		int curAtk = -1;
		if (usableNums > 0) {
			usableNums--;
			if (usableNums <= 0) { canUsed = false; }
			curAtk = baseAttack(attacker, attacked, atk[2]);
		}
		return curAtk;
	}

	ShWp createWeapon() { return std::make_shared<Arrow>(); }
	int getWeaponID() const { return weaponID; }
	std::string getWeaponName() const { return weaponName; }
	int getUsableNums() const { return usableNums; }
};
std::string Arrow::weaponName = "arrow";
int Arrow::weaponID = 2;

const std::vector<ShWp> WEAPONPOOL = {
	std::make_shared<Sword>(), std::make_shared<Bomb>(), std::make_shared<Arrow>()
};

bool cmpRob(const ShWp& wp1, const ShWp& wp2) {
	int wid1 = wp1->getWeaponID();
	int wid2 = wp2->getWeaponID();
	if ("arrow" == wp1->getWeaponName() && "arrow" == wp2->getWeaponName()) {
		int usable1 = std::dynamic_pointer_cast<Arrow>(wp1)->getUsableNums();
		int usable2 = std::dynamic_pointer_cast<Arrow>(wp2)->getUsableNums();
		if (usable1 != usable2) { return usable1 < usable2; }
	}
	return wid1 > wid2;
}

bool cmpBattle(const ShWp& wp1, const ShWp& wp2) {
	int wid1 = wp1->getWeaponID();
	int wid2 = wp2->getWeaponID();
	if ("arrow" == wp1->getWeaponName() && "arrow" == wp2->getWeaponName()) {
		int usable1 = std::dynamic_pointer_cast<Arrow>(wp1)->getUsableNums();
		int usable2 = std::dynamic_pointer_cast<Arrow>(wp2)->getUsableNums();
		if (usable1 != usable2) { return usable1 < usable2; }
	}
	return wid1 < wid2;
}

int Warrior::getMaxAttack() {
	int res = 0;
	for (const auto& wp : weapons) {
		if (!wp->getCanUsed()) { continue; }
		int curAtk = 0, wpId = 0;
		if ("sword" == wp->getWeaponName()) { wpId = 0; }
		else if ("bomb" == wp->getWeaponName()) { wpId = 1; }
		else if ("arrow" == wp->getWeaponName()) { wpId = 2; }
		curAtk = strength * atk[wpId].first / atk[wpId].second;
		res = std::max(res, curAtk);
	}
	return res;
}

bool Warrior::isWithoutBombAndArrow() const {
	bool res = true;
	for (const auto& wp : weapons) {
		if (!wp->getCanUsed()) { continue; }
		std::string curWpName = wp->getWeaponName();
		if ("bomb" == curWpName || "arrow" == curWpName) { return false; }
	}
	return true;
}

void Warrior::clearWeapon() {
	std::list<ShWp>::iterator itr = weapons.begin();
	std::vector<std::list<ShWp>::iterator> willErase;
	for (; weapons.end() != itr; ++itr) {
		if (!(*itr)->getCanUsed()) {
			willErase.push_back(itr);
			--wpCount[(*itr)->getWeaponName()];
		}
	}
	for (auto& itr : willErase) { weapons.erase(itr); }
}

void Warrior::capture(ShWr& loser) {
	loser->clearWeapon();
	loser->weapons.sort(cmpRob);
	int curWpSize = (int)weapons.size();
	while (curWpSize <= 10 && !loser->weapons.empty()) {
		ShWp& wp = loser->weapons.back();
		if (!wp->getCanUsed()) { continue; }
		weapons.push_back(wp);
		++wpCount[wp->getWeaponName()];
		--loser->wpCount[wp->getWeaponName()];
		loser->weapons.pop_back();
		curWpSize++;
	}
}

class Dragon : public Warrior {
private:
	static std::string name;

public:
	Dragon(
		const std::string& camp_,
		int id_, int health_, int strength_, int remMeta_, int curCity_
	) : Warrior(camp_, name, id_, health_, strength_, remMeta_, curCity_) {
		weapons.push_back(WEAPONPOOL[id_ % 3]->createWeapon());
		++wpCount[WEAPONPOOL[id_ % 3]->getWeaponName()];
	}

	std::string getName() const { return name; }
	std::string getCamp() const { return camp; }

	void hail(int hour, int minute, int cityId) {
		printf("%03d:%02d %s dragon %d yelled in city %d\n",
			hour, minute, camp.c_str(), id, cityId);
	}
};
std::string Dragon::name = "dragon";

class Ninja : public Warrior {
private:
	static std::string name;

public:
	Ninja(
		const std::string& camp_,
		int id_, int health_, int strength_, int remMeta_, int curCity_
	) : Warrior(camp_, name, id_, health_, strength_, remMeta_, curCity_) {
		weapons.push_back(WEAPONPOOL[id_ % 3]->createWeapon());
		++wpCount[WEAPONPOOL[id_ % 3]->getWeaponName()];
		weapons.push_back(WEAPONPOOL[(id_ + 1) % 3]->createWeapon());
		++wpCount[WEAPONPOOL[(id_ + 1) % 3]->getWeaponName()];
	}

	std::string getName() const { return name; }
	std::string getCamp() const { return camp; }
};
std::string Ninja::name = "ninja";

class Iceman : public Warrior {
private:
	static std::string name;

public:
	Iceman(
		const std::string& camp_,
		int id_, int health_, int strength_, int remMeta_, int curCity_
	) : Warrior(camp_, name, id_, health_, strength_, remMeta_, curCity_) {
		weapons.push_back(WEAPONPOOL[id_ % 3]->createWeapon());
		++wpCount[WEAPONPOOL[id_ % 3]->getWeaponName()];
	}

	std::string getName() const { return name; }
	std::string getCamp() const { return camp; }

	std::string march(int hour, int minute) {
		int decHealth = health / 10;
		health -= decHealth;
		return Warrior::march(hour, minute);
	}
};
std::string Iceman::name = "iceman";

class Lion : public Warrior {
private:
	int loyalty;
	static std::string name;

public:
	Lion(
		const std::string& camp_,
		int id_, int health_, int strength_, int remMeta_, int curCity_
	) : Warrior(camp_, name, id_, health_, strength_, remMeta_, curCity_), loyalty(remMeta_) {
		weapons.push_back(WEAPONPOOL[id_ % 3]->createWeapon());
		++wpCount[WEAPONPOOL[id_ % 3]->getWeaponName()];
	}

	void born(int hour, int minute) {
		Warrior::born(hour, minute);
		printf("Its loyalty is %d\n", loyalty);
	}

	void runAway(int hour, int minute) {
		printf("%03d:%02d %s lion %d ran away\n",
			hour, minute, camp.c_str(), id);
	}

	std::string getName() const { return name; }
	std::string getCamp() const { return camp; }
	int getLoyalty() const { return loyalty; }
	int getCity() const { return curCity; }

	std::string march(int hour, int minute, int K) {
		loyalty -= K;
		return Warrior::march(hour, minute);
	}
};
std::string Lion::name = "lion";

class Wolf : public Warrior {
private:
	static std::string name;

public:
	Wolf(
		const std::string& camp_,
		int id_, int health_, int strength_, int remMeta_, int curCity_
	) : Warrior(camp_, name, id_, health_, strength_, remMeta_, curCity_) { }

	void grab(ShWr& enemy, int hour, int minute, int cityId) {
		if (enemy->weapons.empty()) { return; }
		enemy->weapons.sort(cmpRob);
		if ("wolf" != enemy->getName()) {
			int curWpSize = (int)weapons.size(), wpIdx = 0;
			int* robCntPtr = nullptr;
			std::string robWp = "NULL";
			// sword-0, bomb-1, arrow-2
			if (enemy->wpCount["sword"] > 0) {
				robCntPtr = &enemy->wpCount["sword"], robWp = "sword";
			}
			else if (enemy->wpCount["bomb"] > 0) {
				robCntPtr = &enemy->wpCount["bomb"], robWp = "bomb";
			}
			else if (enemy->wpCount["arrow"] > 0) {
				robCntPtr = &enemy->wpCount["arrow"], robWp = "arrow";
			}
			if (!robCntPtr) { return; }
			int canBeRob = std::min(*robCntPtr, 10 - curWpSize);
			if (canBeRob > 0 && curWpSize <= 10) {
				printf("%03d:%02d %s %s %d took %d %s from %s %s %d in city %d\n",
					hour, minute, camp.c_str(), name.c_str(), id, canBeRob, robWp.c_str(),
					enemy->camp.c_str(), enemy->name.c_str(), enemy->id, cityId);
				while (canBeRob > 0 && curWpSize <= 10) {
					if (enemy->weapons.empty()) {
						break;
					}
					ShWp& curWp = enemy->weapons.back();
					++wpCount[curWp->getWeaponName()];
					weapons.push_back(curWp);
					enemy->weapons.pop_back();
					++curWpSize, --canBeRob;
					--* robCntPtr;
				}
			}
		}
	}

	std::string getName() const { return name; }
	std::string getCamp() const { return camp; }
};
std::string Wolf::name = "wolf";

using ShWr = std::shared_ptr<Warrior>;
class Headquarter {
	friend class Controller;
private:
	std::string name;
	std::vector<std::string> order;
	std::list<ShWr> warroirs;
	int healthMeta, curID;
	bool canBornWr;
	size_t curIdx;

public:
	Headquarter(
		const std::string& name_,
		const std::vector<std::string>& order_, int healthMeta_
	) : name(name_), order(order_), healthMeta(healthMeta_),
		curID(1), canBornWr(true), curIdx(0) { }

	void born(int hour, int minute) {
		if (!canBornWr) {
			return;
		}
		std::string curWr = order[curIdx];
		int curHealth = warriorHealth[curWr];
		if (healthMeta < curHealth) {
			canBornWr = false;
			return;
		}
		int curStrength = warriorStrength[curWr];
		int curCity = iniCity[name];
		healthMeta -= curHealth;
		curIdx = (curIdx + 1) % order.size();
		if ("dragon" == curWr) {
			warroirs.push_back(std::make_shared<Dragon>(name, curID,
				curHealth, curStrength, healthMeta, curCity));
		}
		else if ("ninja" == curWr) {
			warroirs.push_back(std::make_shared<Ninja>(name, curID,
				curHealth, curStrength, healthMeta, curCity));
		}
		else if ("iceman" == curWr) {
			warroirs.push_back(std::make_shared<Iceman>(name, curID,
				curHealth, curStrength, healthMeta, curCity));
		}
		else if ("lion" == curWr) {
			warroirs.push_back(std::make_shared<Lion>(name, curID,
				curHealth, curStrength, healthMeta, curCity));
		}
		else if ("wolf" == curWr) {
			warroirs.push_back(std::make_shared<Wolf>(name, curID,
				curHealth, curStrength, healthMeta, curCity));
		}
		warroirs.back()->born(hour, minute);
		setWarroirInCity(curCity, warroirs.back(), cities);
		curID++;
	}
};

class Controller {
public:
	static void runAway(Headquarter& red, Headquarter& blue, int hour, int minute) {
		int citySize = (int)cities.size();
		for (int i = 0; i < citySize; ++i) {
			ShWr& redWr = cities[i].first;
			ShWr& blueWr = cities[i].second;
			if (redWr && "lion" == redWr->name) {
				int targetCity = iniCity["blue"];
				std::shared_ptr<Lion> tempRedLionPtr =
					std::dynamic_pointer_cast<Lion>(redWr);
				int curLoyalty = tempRedLionPtr->getLoyalty();
				int curCity = tempRedLionPtr->getCity();
				if (curLoyalty <= 0 && curCity != targetCity) {
					tempRedLionPtr->runAway(hour, minute);
					red.warroirs.remove(redWr);
					cities[redWr->curCity].first = nullptr;
				}
			}
			if (blueWr && "lion" == blueWr->name) {
				int targetCity = iniCity["red"];
				std::shared_ptr<Lion> tempBlueLionPtr =
					std::dynamic_pointer_cast<Lion>(blueWr);
				int curLoyalty = tempBlueLionPtr->getLoyalty();
				int curCity = tempBlueLionPtr->getCity();
				if (curLoyalty <= 0 && curCity != targetCity) {
					tempBlueLionPtr->runAway(hour, minute);
					red.warroirs.remove(redWr);
					cities[blueWr->curCity].second = nullptr;
				}
			}
		}
	}

	static std::string wrMarch(ShWr& wr, int hour, int minute, int K, CITY& tempCity) {
		std::string retInfo = "KEEP_ON";
		if ("lion" == wr->name) {
			std::shared_ptr<Lion> tempLionPtr =
				std::dynamic_pointer_cast<Lion>(wr);
			retInfo = tempLionPtr->march(hour, minute, K);
		}
		else {
			retInfo = wr->march(hour, minute);
		}
		setWarroirInCity(wr->curCity, wr, tempCity);
		return retInfo;
	}

	static std::string march(Headquarter& red, Headquarter& blue, int hour, int minute, int K) {
		std::string retInfo = "KEEP_ON";
		int citySize = (int)cities.size();
		std::vector<std::pair<ShWr, ShWr>> tempCities;
		tempCities.resize(citySize, { nullptr, nullptr });
		for (int i = 0; i < citySize; ++i) {
			ShWr& redWr = cities[i].first;
			ShWr& blueWr = cities[i].second;
			if (redWr) {
				std::string curInfo = wrMarch(redWr, hour, minute, K, tempCities);
				if ("KEEP_ON" == retInfo && "KEEP_ON" != curInfo) { retInfo = curInfo; }
				if (redWr->health <= 0) { tempCities[redWr->curCity].first = nullptr; }
			}
			if (blueWr) {
				std::string curInfo = wrMarch(blueWr, hour, minute, K, tempCities);
				if ("KEEP_ON" == retInfo && "KEEP_ON" != curInfo) { retInfo = curInfo; }
				if (blueWr->health <= 0) { tempCities[blueWr->curCity].second = nullptr; }
			}
		}
		if ("KEEP_ON" != retInfo) { return retInfo; }
		copyCityFrom(cities, tempCities);
		clearWarroir(red);
		clearWarroir(blue);
		return retInfo;
	}

	static void grab(int hour, int minute) {
		int citySize = (int)cities.size(); // citySize >= 2
		for (int i = 1; i < citySize - 1; ++i) {
			if (!cities[i].first || !cities[i].second) { continue; }
			if ("wolf" == cities[i].first->name) {
				std::shared_ptr<Wolf> tempWolfPtr =
					std::dynamic_pointer_cast<Wolf>(cities[i].first);
				tempWolfPtr->grab(cities[i].second, hour, minute, i);
			}
			else if ("wolf" == cities[i].second->name) {
				std::shared_ptr<Wolf> tempWolfPtr =
					std::dynamic_pointer_cast<Wolf>(cities[i].second);
				tempWolfPtr->grab(cities[i].first, hour, minute, i);
			}
		}
	}

	static void clearWarroir(Headquarter& hq) {
		std::list<ShWr>::iterator itr = hq.warroirs.begin();
		std::vector<std::list<ShWr>::iterator> willErase;
		for (; itr != hq.warroirs.end(); ++itr) {
			if ((*itr)->health <= 0) {
				int itrCity = (*itr)->curCity;
				if ("red" == (*itr)->camp) { cities[itrCity].first = nullptr; }
				else { cities[itrCity].second = nullptr; }
				willErase.push_back(itr);
			}
		}
		for (auto& itr : willErase) { hq.warroirs.erase(itr); }
	}

	static void printBattle(int hour, int minute, int cityIdx, ShWr& loser, ShWr& winner) {
		printf("%03d:%02d %s %s %d killed %s %s %d in city %d remaining %d elements\n",
			hour, minute, winner->camp.c_str(), winner->name.c_str(),
			winner->id, loser->camp.c_str(), loser->name.c_str(), loser->id,
			cityIdx, winner->health);
		winner->capture(loser);
		if ("red" == loser->camp) { cities[cityIdx].first = nullptr; }
		else if ("blue" == loser->camp) { cities[cityIdx].second = nullptr; }
	}

	static void procBattle(std::list<ShWp>::iterator& wpItr, ShWr& attacker, ShWr& attacked) {
		if (wpItr == attacker->weapons.end()) { return; }
		int cnt = 0;
		while (!(*wpItr)->getCanUsed()) {
			if (cnt == (int)attacker->weapons.size()) { return; }
			++wpItr;
			++cnt;
			if (wpItr == attacker->weapons.end()) {
				wpItr = attacker->weapons.begin();
			}
		}
		ShWp& curWp = *wpItr;
		std::string wpName = curWp->getWeaponName();
		int res = curWp->attack(attacker, attacked);
		++wpItr;
		if (wpItr == attacker->weapons.end()) {
			wpItr = attacker->weapons.begin();
		}
	}

	static bool procPrintBattle(int hour, int minute, int cityIdx, ShWr& wr1, ShWr& wr2) {
		if (wr1->health > 0 && wr2->health > 0) { return true; }
		else if (wr1->health > 0 && wr2->health <= 0) {
			printBattle(hour, minute, cityIdx, wr2, wr1);
		}
		else if (wr1->health <= 0 && wr2->health > 0) {
			printBattle(hour, minute, cityIdx, wr1, wr2);
		}
		else if (wr1->health <= 0 && wr2->health <= 0) {
			ShWr redWr = nullptr, blueWr = nullptr;
			if ("red" == wr1->camp) { redWr = wr1, blueWr = wr2; }
			else { redWr = wr2, blueWr = wr1; }
			printf("%03d:%02d both red %s %d and blue %s %d died in city %d\n",
				hour, minute, redWr->name.c_str(), redWr->id,
				blueWr->name.c_str(), blueWr->id, cityIdx);
			cities[cityIdx].first = cities[cityIdx].second = nullptr;
		}
		return false;
	}

	static void battleRound(int hour, int minute, int cityIdx, ShWr& attacker, ShWr& attacked, bool& isAllAlive) {
		isAllAlive = true;
		std::list<ShWp>::iterator attackerItr = attacker->weapons.begin();
		std::list<ShWp>::iterator attackedItr = attacked->weapons.begin();
		while (attacker->health > 0 && attacked->health > 0) {
			procBattle(attackerItr, attacker, attacked);
			if (!procPrintBattle(hour, minute, cityIdx, attacker, attacked)) {
				isAllAlive = false; break;
			}
			procBattle(attackedItr, attacked, attacker);
			if (!procPrintBattle(hour, minute, cityIdx, attacked, attacker)) {
				isAllAlive = false; break;
			}
			if (attacker->isWithoutBombAndArrow() && attacked->isWithoutBombAndArrow() &&
				!attacker->getMaxAttack() && !attacked->getMaxAttack()) {
				break;
			}
		}
		if (attacker) { attacker->clearWeapon(); }
		if (attacked) { attacked->clearWeapon(); }
	}

	static void battle(int hour, int minute, Headquarter& red, Headquarter& blue) {
		int citySize = (int)cities.size();
		for (int cityIdx = 1; cityIdx < citySize - 1; ++cityIdx) {
			auto& redWr = cities[cityIdx].first;
			auto& blueWr = cities[cityIdx].second;
			if (!redWr || !blueWr) { continue; }
			redWr->weapons.sort(cmpBattle), blueWr->weapons.sort(cmpBattle);
			if (redWr->health > 0 && blueWr->health > 0) {
				bool isAllAlive = true;
				if (cityIdx & 1) {
					battleRound(hour, minute, cityIdx, redWr, blueWr, isAllAlive);
				}
				else {
					battleRound(hour, minute, cityIdx, blueWr, redWr, isAllAlive);
				}
				if (isAllAlive) {
					printf("%03d:%02d both red %s %d and blue %s %d were alive in city %d\n",
						hour, minute, redWr->name.c_str(), redWr->id,
						blueWr->name.c_str(), blueWr->id, cityIdx);
				}
			}
			if (redWr && redWr->health > 0 && "dragon" == redWr->name) {
				yell(hour, minute, cityIdx, "red", redWr);
			}
			if (blueWr && blueWr->health > 0 && "dragon" == blueWr->name) {
				yell(hour, minute, cityIdx, "blue", blueWr);
			}
		}
		clearWarroir(red);
		clearWarroir(blue);
	}

	static void reportHealthOfHQ(const Headquarter& hq, int hour, int minute) {
		printf("%03d:%02d %d elements in %s headquarter\n",
			hour, minute, hq.healthMeta, hq.name.c_str());
	}

	static void reportWpOfWr(int hour, int minute) {
		int citySize = (int)cities.size();
		for (int i = 0; i < citySize; ++i) {
			ShWr& redWr = cities[i].first;
			ShWr& blueWr = cities[i].second;
			if (redWr) {
				redWr->clearWeapon();
				printf("%03d:%02d red %s %d has %d sword %d bomb %d arrow and %d elements\n",
					hour, minute, redWr->name.c_str(), redWr->id, redWr->wpCount["sword"],
					redWr->wpCount["bomb"], redWr->wpCount["arrow"], redWr->health);
			}
			if (blueWr) {
				blueWr->clearWeapon();
				printf("%03d:%02d blue %s %d has %d sword %d bomb %d arrow and %d elements\n",
					hour, minute, blueWr->name.c_str(), blueWr->id, blueWr->wpCount["sword"],
					blueWr->wpCount["bomb"], blueWr->wpCount["arrow"], blueWr->health);
			}
		}
	}

	static void yell(int hour, int minute, int cityIdx,
		const std::string& hq, const ShWr& wr) {
		printf("%03d:%02d %s dragon %d yelled in city %d\n",
			hour, minute, hq.c_str(), wr->id, cityIdx);
	}
};

int main() {
	int caseNums;
	scanf("%d", &caseNums);
	for (int cs = 1; cs <= caseNums; ++cs) {
		int M, N, K, T;
		int dragonS, ninjaS, icemanS, lionS, wolfS;
		int dragonH, ninjaH, icemanH, lionH, wolfH;
		scanf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &M, &N, &K, &T,
			&dragonH, &ninjaH, &icemanH, &lionH, &wolfH,
			&dragonS, &ninjaS, &icemanS, &lionS, &wolfS);
		iniCity["red"] = 0;
		iniCity["blue"] = N + 1;
		cities.resize(N + 2, { nullptr, nullptr });
		printCities.resize(N + 2, { "NULL", "NULL" });
		warriorStrength = {
			{"dragon", dragonS}, {"ninja", ninjaS},
			{"iceman", icemanS}, {"lion", lionS}, {"wolf", wolfS}
		};
		warriorHealth = {
			{"dragon", dragonH}, {"ninja", ninjaH},
			{"iceman", icemanH}, {"lion", lionH}, {"wolf", wolfH}
		};
		Headquarter red(
			"red", { "iceman", "lion", "wolf", "ninja", "dragon" }, M);
		Headquarter blue(
			"blue", { "lion", "dragon", "ninja", "iceman","wolf" }, M);
		printf("Case %d:\n", cs);
		for (int curTime = 0; curTime <= T; ++curTime) {
			int hour = curTime / 60, minute = curTime % 60;
			if (0 == minute) {
				red.born(hour, minute);
				blue.born(hour, minute);
			}
			else if (5 == minute) {
				Controller::runAway(red, blue, hour, minute);
			}
			else if (10 == minute) {
				std::string retInfo = Controller::march(red, blue, hour, minute, K);
				printCitiesInfo(printCities);
				if ("KEEP_ON" != retInfo) { break; }
			}
			else if (35 == minute) {
				Controller::grab(hour, minute);
			}
			else if (40 == minute) {
				Controller::battle(hour, minute, red, blue);
			}
			else if (50 == minute) {
				Controller::reportHealthOfHQ(red, hour, minute);
				Controller::reportHealthOfHQ(blue, hour, minute);
			}
			else if (55 == minute) {
				Controller::reportWpOfWr(hour, minute);
			}
		}
		cities.clear();
		printCities.clear();
	}
	return 0;
}
