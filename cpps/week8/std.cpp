#include<iostream>
#include<string>
#include<cstring>
using namespace std;
bool edges[30][30];int in[30],out[30];
bool B[30];
void dfs(int u)
{
	B[u]=0;
	for(int i=0;i<=25;++i)
	{
		if(B[i]&&edges[u][i]) dfs(i);
	}
	return;
}
bool solve()
{
	int n;
	cin>>n;
	string s[100000+10];
	for(int i=1;i<=n;++i)
	{
		cin>>s[i];
		int c0=s[i][0]-'a',c1=s[i][s[i].size()-1]-'a';
		B[c0]=B[c1]=1;
		edges[c0][c1]=edges[c1][c0]=1;
		++in[c1];
		++out[c0];
	}
	int j;
	for(int i=0;i<=25;++i) if(B[i])
	{
		j=i;
		break;
	}
	dfs(j);
	for(int i=0;i<=25;++i) if(B[i]) return 0;
	int cntin=0,cntout=0;
	for(int i=0;i<=25;++i)
	{
		if(in[i]-out[i]==1) ++cntout;
		else if(out[i]-in[i]==1) ++cntin;
		else if(abs(in[i]-out[i])>1) return 0;
	}
	if((cntin==1&&cntout==1)||(cntin==0&&cntout==0)) return 1;
	return 0;
}
int main()
{
	int n;
	cin>>n;
	while(n--)
	{
		memset(edges,0,sizeof(edges));
		memset(B,0,sizeof(B));
		memset(in,0,sizeof(in));
		memset(out,0,sizeof(out));
		if(solve()) cout<<"Ordering is possible.\n";
		else cout<<"The door cannot be opened.\n";
	}
	return 0;
}