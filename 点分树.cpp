#include<bits/stdc++.h>
#define N 100005
#define min(x,y) (x<y?x:y)
using namespace std;
int f[N][17],dep[N],size[N],father[N],a[N],n,m,R;
bool erased[N];
vector <int> e[N];
struct BIT
{
	vector <int> f;
	int lowbit(int x) {return x&-x;}
	void modify(int x,int v)
	{
		for (++x;x<f.size();x+=lowbit(x)) f[x]+=v;
	}
	int query(int x,int res=0)
	{
		x=min(x+1,f.size()-1);
		for (;x;x-=lowbit(x)) res+=f[x];
		return res;
	}
} F[N],G[N];
void dfs(int x,int dad)
{
	f[x][0]=dad,dep[x]=dep[dad]+1;
	for (int i=1;i<=16;++i) f[x][i]=f[f[x][i-1]][i-1];
	for (int y:e[x]) if (y^dad) dfs(y,x); 
}
int LCA(int x,int y)
{
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=16;~i;--i) if (dep[f[x][i]]>=dep[y]) x=f[x][i];
	for (int i=16;~i;--i) if (f[x][i]^f[y][i]) x=f[x][i],y=f[y][i];
	return x^y?f[x][0]:x;
}
int dis(int x,int y) {return dep[x]+dep[y]-2*dep[LCA(x,y)];}
void dfs(int x,int dad,int n)
{
	bool flag=size[x]=1;
	for (int y:e[x]) if (y^dad && !erased[y])
		dfs(y,x,n),size[x]+=size[y],flag&=(size[y]<=n/2);
	if (flag&(n-size[x]<=n/2)) R=x;
}
void solve(int x,int dad,int n)
{
	dfs(x,0,n);
	int nowR=R;
	father[nowR]=dad,erased[nowR]=1;
	F[nowR].f.resize(n+2),G[nowR].f.resize(n+2);// >> for 1 bit 
	for (int y:e[nowR]) if (!erased[y])
		solve(y,nowR,size[y]<size[nowR]?size[y]:n-size[nowR]);
}
void modify(int x,int v)
{
	for (int y=x;y;y=father[y]) F[y].modify(dis(x,y),v);
	for (int y=x;father[y];y=father[y])	G[y].modify(dis(x,father[y]),v);
}
int main()
{
//	freopen("tree.in","r",stdin);
	freopen("P6329_1.in","r",stdin);
	freopen("My.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",&a[i]);
	for (int i=1,u,v;i<n;++i)
	{
		scanf("%d%d",&u,&v);
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	dfs(1,0),solve(1,0,n);
	for (int i=1;i<=n;++i) modify(i,a[i]);
	for (int op,x,y,ans=0;m--;)
	{
		scanf("%d%d%d",&op,&x,&y);
		x^=ans,y^=ans;
		if (op==0)
		{
			ans=F[x].query(y);
			for (int u=x;father[u];u=father[u])
			{
				int now=dis(father[u],x);
				if (now<=y) ans+=F[father[u]].query(y-now)-G[u].query(y-now);
			}
			printf("%d\n",ans);
		}
		if (op==1) modify(x,y-a[x]),a[x]=y;
	}
	return 0-0; // :>
}
