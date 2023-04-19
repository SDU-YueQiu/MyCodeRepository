#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define INF 0x7fffffffffffffffll
//using namespace std;
int nowturn=1,nowid=1;
int cntk;
long long maxa,maxb,maxc;
int d,e;
int n,m,q;
class Active_skill{
public:	
	int knd,p,q,r;
	int id;
	inline void init(){
		std::cin>>knd>>p>>q;
		if(knd==2||knd==4)std::cin>>r;
	}
	inline long long calatt(const int&x,const int&y)const{//calculate attack
		return 1ll*p*x+1ll*q*y;
	}
	inline long long calrec(const int&x,const int&y)const{//calculate recover
		return (1ll*p*y+1ll*x*q)/(1ll*p*q);
	}
	inline int calR()const{
		int R=nowturn+1;
		if(r+R>cntk)return cntk+10;
		return r+R;
	}
}acs[5010]; 
struct Passive_skill{
public:
	int knd,g;
	inline void init(){
		std::cin>>knd>>g;
	}
}pas[5010];
class Player{
private:
	long long a,b,c;
	int team;
	int cntacs,acsid[5010],lst[5010];//主动技能数量，技能编号，剩余次数 
	int headpas,pasid[5010];//主动技能头指针，技能编号(循环队列) 
	long long attackdec,attackinc,teamdec,notteamdec;
	long long dot,fdot[5010];
public:
	Player(){
		a=b=c=cntacs=headpas=0;
		attackdec=attackinc=teamdec=notteamdec=0;
		memset(acsid,0,sizeof(acsid));
		memset(pasid,0,sizeof(pasid));
		memset(fdot,0,sizeof(fdot));
		dot=0;
		return ;
	}
	~Player(){}
	inline bool isalive()const{return c>0;}
	inline void init(){
		a=maxa;b=maxb;c=maxc;
		team=1;
	}
	inline void output(){
		if(!isalive())std::cout<<"0 0 0"<<std::endl; 
		else std::cout<<a<<' '<<b<<' '<<c<<std::endl;
	}
	inline bool getattack(long long P){
		if(!isalive())return 0;
		if(P<0)P=0;
		c-=P;
		return 1;
	}
	inline bool getdot(const long long&P,const int&R){
		if(!isalive())return 0;
		dot+=P;
		fdot[R]-=P;
		return 1;
	}
	bool recover(const long long&P){
		if(!isalive())return 0;
		if(c==maxc)return 0;
		c+=P;
		if(c>maxc)c=maxc;
		return 1;
	}
	inline bool recoverall(const long long&A,const long long&B,const long long&C){
		if(!isalive())return 0;
		if(a==maxa&&b==maxb&&c==maxc)return 0;
		a+=A;
		if(a>maxa)a=maxa;
		b+=B;
		if(b>maxb)b=maxb;
		c+=C;
		if(c>maxc)c=maxc;
		return 1;
	}	
	inline bool getacs(const int&id,const int&s){
		if(id>m)return 0;
		cntacs++;
		acsid[cntacs]=id;
		lst[cntacs]=s;
		return 1;
	}
	inline void losepas(){
		if(pasid[headpas]==0)return;
		const Passive_skill&k=pas[pasid[headpas]];
		switch(k.knd){
			case 1:
				attackdec-=k.g;
				break;
			case 2:
				attackinc-=k.g;
				break;
			case 3:
				teamdec-=k.g;
				break;
			case 4:
				notteamdec-=k.g;
				break;
			default:
				printf("error");
		}
		return;
	}
	inline void addpas(const int&id){
		pasid[headpas]=id;
		const Passive_skill&k=pas[pasid[headpas]];
		switch(k.knd){
			case 1:
				attackdec+=k.g;
				break;
			case 2:
				attackinc+=k.g;
				break;
			case 3:
				teamdec+=k.g;
				break;
			case 4:
				notteamdec+=k.g;
				break;
			default:
				printf("error");
		}
		return;
	}
	inline bool getpas(const int&id){
		if(id>q)return 0;
		headpas=(headpas+1)%d;
		losepas();
		addpas(id);
		return 1;
	}
	inline bool getdotturn(int turn){
		if(isalive()){
			dot+=fdot[turn];
			c-=dot;
			return true;
		}
		return false;
	}
	inline bool jointeam(const int&);
	inline bool jointeam_withteammates(const int&);
	inline bool attack(const int&,long long)const; 
	inline bool groupatt(const int&,const long long&)const;
	inline bool dotattack(const int&,const long long&,const int&)const;
	inline bool groupdot(const int&,const long long&,const int&)const;
	inline bool useacs(const int&,const int&,const int&,const int&);	
}player[5010];
inline bool Player::attack(const int&to,long long P)const{
	long long P2;
	if(team==player[to].team)P2=P-attackdec-player[to].teamdec;
	else P2=P+attackinc-player[to].notteamdec;
	return player[to].getattack(P2);
}
inline bool Player::groupatt(const int&s,const long long&P)const{
	bool flag=0;
	for(int i=1;i<=n;i++)if(i!=nowid&&i!=s){
		flag=(attack(i,P)||flag);
	}
	return flag;
}
inline bool Player::dotattack(const int&to,const long long&P,const int&R)const{
	return player[to].getdot(P,R);
}
inline bool Player::groupdot(const int&s,const long long&P,const int&R)const{
	bool flag=0;
	for(int i=1;i<=n;i++)if(i!=nowid&&i!=s){
		flag=(dotattack(i,P,R)||flag);
	}
	return flag;
} 
inline bool Player::useacs(const int&id,const int&x,const int&y,const int&s){
	if(id>cntacs)return 0;
	const Active_skill&k=acs[acsid[id]];
	if(a<x||b<y)return 0;
	if(lst[id]<=0)return 0;
	if(s>n)return 0; 
	switch(k.knd){
		case 1:
			if(attack(s,k.calatt(x,y))){
				a-=x;b-=y;	
				lst[id]--;
				return 1;
			}else return 0;
		case 2:
			if(dotattack(s,k.calatt(x,y),k.calR())){
				a-=x;b-=y;
				lst[id]--;	
				return 1;
			}else return 0;
		case 3:
			if(groupatt(s,k.calatt(x,y))){
				a-=x;b-=y;	
				lst[id]--;	
				return 1;
			}else return 0;	
		case 4:
			if(groupdot(s,k.calatt(x,y),k.calR())){
				a-=x;b-=y;	
				lst[id]--;	
				return 1;
			}else return 0;
		case 5:
			if(recover(k.calrec(x,y))){
				a-=x;b-=y;	
				lst[id]--;	
				return 1;
			}else return 0;
		default:
			printf("Error!");
	}
	printf("Error");
}
inline bool Player::jointeam(const int&s){
	if(team==s)return 0;
	team=s;
	return 1;
}
inline bool Player::jointeam_withteammates(const int&s){
	int nows=team;
	if(team==s)return 0;
	for(int i=1;i<=n;i++)if(player[i].team==nows)player[i].jointeam(s);
	return 1;
}
inline bool haveanalive(){
	for(int i=1;i<=n;i++)if(player[i].isalive())return 1;
	return 0;
}
int main(){
	std::cin>>n>>m>>q>>maxa>>maxb>>maxc>>d>>e;
	for(int i=1;i<=m;i++)acs[i].id=i;
	for(int i=1;i<=m;i++)acs[i].init();
	for(int i=1;i<=q;i++)pas[i].init();
	for(int i=1;i<=n;i++)player[i].init();
	std::cin>>cntk;
	for(int H=1;H<=cntk;H++)if(haveanalive()){
		int P,id,X,Y,S;
		std::cin>>P;
		bool flag=0;
		switch(P){
			case 1:
				std::cin>>id>>X;
				flag=player[nowid].getacs(id,X);
				break;
			case 2:
				std::cin>>id>>X>>Y>>S;
				flag=player[nowid].useacs(id,X,Y,S);
				break;
			case 3:
				std::cin>>X>>Y>>S;
				flag=player[nowid].recoverall(X,Y,S);
				break;
			case 4:
				std::cin>>id;
				flag=player[nowid].getpas(id);
				break;
			case 5:
				std::cin>>id;
				flag=player[nowid].jointeam(id);
				break;
			case 6:
				std::cin>>id;
				flag=player[nowid].jointeam_withteammates(id);
				break;
			case 7:
				flag=0;
				while(!flag||!player[nowid].isalive()){
					nowid++;flag=1;
					if(nowid>n){
						nowturn++;
						for(int i=1;i<=n;i++)player[i].getdotturn(nowturn);
						nowid=1;
						if(!haveanalive())break;
					}
				}
				break;
			default:
				printf("error!");
		}
		if(flag)std::cout<<"Yes"<<std::endl;
		else std::cout<<"No"<<std::endl;
	}else std::cout<<"No"<<std::endl;
	for(int i=1;i<=n;i++)player[i].output();
	return 0;
}
