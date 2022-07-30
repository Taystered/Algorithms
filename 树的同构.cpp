#include<bits/stdc++.h>
#define N 55
#define seed 73
#define mod 1000000009
#define ll long long
using namespace std;
int size[N],cate[N],val[N],powseed[N],n,m;
vector <int> e[N],Root;
unordered_map <int,int> f[2];
int mul(int x,int y) {return 1ll*x*y%mod;}
int dfs(int x,int dad)
{
	int res=size[x]=1;
	for (int y:e[x]) if (y^dad)
	{
		res=mul(res,dfs(y,x));
		res=mul(res,powseed[size[y]]);
		res=mul(res,size[y]);
		size[x]+=size[y];
	}
	return res;
}
void getroot(int x,int dad)
{
	int Max=0; size[x]=1;
	for (int y:e[x]) if (y^dad)
	{
		getroot(y,x),size[x]+=size[y];
		Max=max(Max,size[y]);
	}
	if (max(n-size[x],Max)<=(n>>1)) Root.emplace_back(x);
}
int main()
{
	freopen("P5043_2.in","r",stdin);
	freopen("My.out","w",stdout);
	scanf("%d",&m);
	powseed[0]=1;
	for (int i=1;i<=50;++i) powseed[i]=mul(powseed[i-1],seed)%mod;
	for (int i=1;i<=m;++i)
	{
		scanf("%d",&n);
		for (int j=1,x;j<=n;++j)
			scanf("%d",&x),(x>0) && (
			e[x].emplace_back(j),
			e[j].emplace_back(x),1);
		Root.clear();
		getroot(1,0);
		cate[i]=Root.size()-1;
		if (cate[i]==0) val[i]=dfs(*Root.begin(),0);
		if (cate[i]==1) val[i]=min(dfs(*Root.begin(),0),dfs(*Root.rbegin(),0));
		for (int j=1;j<=n;++j) e[j].clear();
	}
	for (int i=m;i;--i) f[cate[i]][val[i]]=i;
	for (int i=1;i<=m;++i) printf("%d\n",f[cate[i]][val[i]]);
} 
