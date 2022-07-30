//#pragma GCC optimize(3) 
#include<bits/stdc++.h>
#define next Next
using namespace std;
const int N=3005,logN=10,INF=INT_MAX;
int to[N],vol[N],next[N],last[N],dis[N],gap[N],col[N],cur[N],dep[N],f[N][logN+1],g[N][logN+1],n,m,q,t=1,S,T;
vector <pair<int,int>> e[N];
void add(int u,int v,int w) {to[++t]=v,vol[t]=w,next[t]=last[u],last[u]=t;}
int dfs(int x,int flow=INF)
{
	if (x==T) return flow;
	int have=0;
	for (int i=cur[x];i;i=next[i])
		if (vol[cur[x]=i] && dis[to[i]]+1==dis[x])
		{
			int now=dfs(to[i],min(vol[i],flow-have));
			vol[i]-=now,vol[i^1]+=now,have+=now;
			if (flow==have) return have;
		}
	cur[x]=last[x];
	if (!--gap[dis[x]]) dis[S]=N;
	++gap[++dis[x]];
	return have;
}
int Mincut(int x,int y)
{
	int res=0;
	memset(gap,0,sizeof gap);
	memset(dis,0,sizeof dis);
	memset(col,0,sizeof col);
	for (int i=2;i<=t;++++i) vol[i]=vol[i^1]=(vol[i]+vol[i^1])/2;
	for (S=x,T=y;dis[S]<N;) res+=dfs(S);
	return res;
}
void paint(int x)
{
	col[x]=1;
	for (int i=last[x];i;i=next[i])
		if (vol[i] && !col[to[i]]) paint(to[i]);
}
void solve(vector <int> a)
{
	if (a.size()<=1) return;
	int res=Mincut(*a.begin(),*a.rbegin());
	e[S].emplace_back(T,res);
	e[T].emplace_back(S,res);
	paint(S);
	col[T]=0;
	vector <int> L,R;
	for (int x:a) (col[x]?L:R).emplace_back(x);
	solve(L),solve(R);
}
void build(int x,int dad)
{
	dep[x]=dep[dad]+1;
	for (int i=1;i<=logN;++i)
		f[x][i]=f[f[x][i-1]][i-1],
		g[x][i]=min(g[x][i-1],g[f[x][i-1]][i-1]);
	for (auto y:e[x]) if (y.first^dad)
		f[y.first][0]=x,g[y.first][0]=y.second,build(y.first,x);
}
int LCA(int x,int y)
{
	int res=INF;
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=logN;~i;--i) if (dep[f[x][i]]>=dep[y]) res=min(res,g[x][i]),x=f[x][i];
	for (int i=logN;~i;--i) if (f[x][i]^f[y][i]) res=min({res,g[x][i],g[y][i]}),x=f[x][i],y=f[y][i];
	return x^y?min({res,g[x][0],g[y][0]}):res; 
}
int main()
{
	freopen("input.in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1,u,v,w;i<=m;++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w),add(v,u,w);
	}
	vector <int> start;
	start.resize(n);
	iota(start.begin(),start.end(),1);
	solve(start);
	build(1,0);
	scanf("%d",&q);
	for (int u,v;q--;)
		scanf("%d%d",&u,&v),printf("%d\n",LCA(u,v));
}
