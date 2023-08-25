#include<stdio.h>
int read(){
	int res=0,zf=1;char ch;
	while((ch=getchar())<48||ch>57)if(ch=='-')zf=!zf;res=(ch^48);
	while((ch=getchar())>=48&&ch<=57)res=(res<<3)+(res<<1)+(ch^48);
	return zf?res:(-res);
}
long long readll(){
	long long res=0;int zf=1;char ch;
	while((ch=getchar())<48||ch>57)if(ch=='-')zf=!zf;res=(ch^48);
	while((ch=getchar())>=48&&ch<=57)res=(res<<3ll)+(res<<1ll)+(ch^48);
	return zf?res:(-res);
}
/*
Player玩家 
Active主动 
Passive被动 
Skill技能 
dot(damage over time)持续伤害  
*/ 
long long maxa,maxb,maxc;
struct Player{
	long long a,b,c;
}player[5001];
struct Active_skill{
	int knd,p,q,r;//knd(k-nd)第k种技能 
}acs[5001]; 
struct Passive_skill{
	int knd,g;
}pas[5001];
int acsid[5001][5001],pasid[5001][5001];
int lasta[5001][5001],cnta[5001],headp[5001];//主动技能剩余量，主动技能数量，被动技能头指针（被动技能用循环链表表示
int n,m,q,d,e;
long long dot[5001],fdot[5001][5001];
long long teamdec[5001],teamadd[5001],teamdec2[5001],teamdec3[5001];//队友伤害减少，对手伤害增加，受到队友伤害减少,受到非队友伤害减少 
int team[5001];
int main(){
	int i,j,h,k,nowid,id,x,y,s,flag,nowturn,FLAG;long long P,P2;
	n=read();m=read();q=read();
	maxa=readll();maxb=readll();maxc=readll();d=read();e=read();
	for(i=0;i<n;i++){
		player[i].a=maxa;
		player[i].b=maxb;
		player[i].c=maxc;
		team[i]=1;
	}
	for(i=1;i<=m;i++){
		acs[i].knd=read();
		acs[i].p=read();
		acs[i].q=read();
		if(acs[i].knd==2||acs[i].knd==4)
			acs[i].r=read();//只有2,4有r
	}
	for(i=1;i<=q;i++){
		pas[i].knd=read();
		pas[i].g=read();
	}
	k=read();
	nowid=0,nowturn=1;
	FLAG=1;
	for(h=1;FLAG&&h<=k;h++)
		switch(read()){
		case 1:
			id=read();s=read();
			if(id>m){puts("No");break;}
			cnta[nowid]++;
			acsid[nowid][cnta[nowid]]=id;
			lasta[nowid][cnta[nowid]]=s;
			puts("Yes");
			break;
		case 2:
			id=read();x=read();y=read();s=read()-1;
			if(cnta[nowid]<id||lasta[nowid][id]<=0||x>player[nowid].a||y>player[nowid].b||s>=n)puts("No");//技能不能发动 
			else{
				P=1ll*acs[acsid[nowid][id]].p*x+1ll*acs[acsid[nowid][id]].q*y;
				flag=1;
				switch(acs[acsid[nowid][id]].knd){
					case 1:
						if(team[nowid]==team[s]){
							P2=P-teamdec[nowid]-teamdec2[s]; 
						}else{
							P2=P+teamadd[nowid]-teamdec3[s];
						}
						if(P2<0)P2=0;
						if(player[s].c>0)player[s].c-=P2;else flag=0;
						break;
					case 2:
						if(player[s].c<0)flag=0;
						dot[s]+=P;
						if(nowturn+acs[acsid[nowid][id]].r+1<=k)//防止越界 
							fdot[s][nowturn+acs[acsid[nowid][id]].r+1]-=P;
						break;
					case 3:
						flag=0;
						for(i=0;i<n;i++)
							if(i!=nowid&&i!=s&&player[i].c>0){
								if(team[nowid]==team[i]){
									P2=P-teamdec[nowid]-teamdec2[i]; 
								}else{
									P2=P+teamadd[nowid]-teamdec3[i];
								}
								if(P2<0)P2=0;
								player[i].c-=P2;
								flag=1;
							}
						break;
					case 4:
						flag=0;
						for(i=0;i<n;i++)
							if(i!=nowid&&i!=s&&player[i].c>0){
								flag=1;
								dot[i]+=P;
								if(nowturn+acs[acsid[nowid][id]].r+1<=k)
									fdot[i][nowturn+acs[acsid[nowid][id]].r+1]-=P;
							}
						break;
					case 5:
						P=(1ll*acs[acsid[nowid][id]].p*y+1ll*acs[acsid[nowid][id]].q*x)/(1ll*x*y);
						if(player[nowid].c<maxc){
							player[nowid].c+=P;
							if(player[nowid].c>maxc)player[nowid].c=maxc;
						}else flag=0;
						break;
				}
				if(flag){
					player[nowid].a-=x;player[nowid].b-=y;
					lasta[nowid][id]--;
					puts("Yes");
				}else puts("No");
			}
			break;
		case 3:
			flag=0;
			if(player[nowid].a<maxa||player[nowid].b<maxb||player[nowid].c<maxc)puts("Yes");
			else puts("No");
			player[nowid].a+=readll();
			player[nowid].b+=readll();
			player[nowid].c+=readll();
			if(player[nowid].a>maxa)player[nowid].a=maxa;
			if(player[nowid].b>maxb)player[nowid].b=maxb;
			if(player[nowid].c>maxc)player[nowid].c=maxc;
			break;
		case 4:
			id=read();
			if(id>q){puts("No");break;} 
			headp[nowid]=(headp[nowid]+1)%d;
			switch(pas[pasid[nowid][headp[nowid]]].knd){
				case 0:break;
				case 1:
					teamdec[nowid]-=pas[pasid[nowid][headp[nowid]]].g;
					break;
				case 2:
					teamadd[nowid]-=pas[pasid[nowid][headp[nowid]]].g;	
					break;
				case 3:
					teamdec2[nowid]-=pas[pasid[nowid][headp[nowid]]].g;
					break;
				case 4:
					teamdec3[nowid]-=pas[pasid[nowid][headp[nowid]]].g;
					break;
			}
			pasid[nowid][headp[nowid]]=id;
			switch(pas[pasid[nowid][headp[nowid]]].knd){
				case 0:break;
				case 1:
					teamdec[nowid]+=pas[pasid[nowid][headp[nowid]]].g;
					break;
				case 2:
					teamadd[nowid]+=pas[pasid[nowid][headp[nowid]]].g;	
					break;
				case 3:
					teamdec2[nowid]+=pas[pasid[nowid][headp[nowid]]].g;
					break;
				case 4:
					teamdec3[nowid]+=pas[pasid[nowid][headp[nowid]]].g;
					break;
			}
			puts("Yes");
			break;
		case 5:
			id=read();
			if(team[nowid]==id)puts("No");
			else puts("Yes");
			team[nowid]=id;
			break;
		case 6:
			id=read();
			if(team[nowid]==id){puts("No");break;}
			puts("Yes");
			s=team[nowid];
			for(i=0;i<n;i++)if(player[i].c>0&&team[i]==s)team[i]=id;
			break;
		case 7:
			id=-1;
			do{
				nowid=(nowid+1)%n;
				if(nowid==0){
					int FFF=0;
					for(i=0;i<n;i++)if(player[i].c>0)FFF=1;
					if(!FFF){
						FLAG=0;
						puts("Yes");	
						for(h++;h<=k;h++)puts("No");	
						break;
					}
				}
				if(nowid==0){
					nowturn++;
					for(i=0;i<n;i++)
						if(player[i].c>0){
							dot[i]+=fdot[i][nowturn];
							player[i].c-=dot[i];
						}
				}
				if(player[nowid].c>0){puts("Yes");break;} 
			}while(player[nowid].c<=0);
			break;
		default:
			puts("ERROR");while(1);
	}
	for(i=0;i<n;i++)if(player[i].c<0)puts("0 0 0");
	else printf("%lld %lld %lld\n",player[i].a,player[i].b,player[i].c);
	return 0;
}
