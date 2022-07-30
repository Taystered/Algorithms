#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define M 205
#define N 40005
using namespace std;
int dep[N],f[N][16],val[N],key[N],id[N],d[N],u[N],cnt[N],QwQ[M][M],n,m,t,B,quq;
bitset <N> F[1<<15],Now;
vector <int> e[N];
void read(int &x)
{
	char ch=getchar(); x=0;
	for (;ch<'0' || '9'<ch;ch=getchar());
	for (;'0'<=ch && ch<='9';x=(x<<1)+(x<<3)+(ch^48),ch=getchar());
}
void discrete(int *a,int n)
{
	pair <int,int> p[N];
	for (int i=1;i<=n;++i) p[i]=make_pair(a[i],i);
	sort(p+1,p+n+1);
	for (int i=1;i<=n;++i) a[p[i].second]=a[p[i-1].second]+(p[i].first!=p[i-1].first);
}
void build(int x)
{
	dep[x]=dep[f[x][0]]+1;
	for (int i=1;i<16;++i) f[x][i]=f[f[x][i-1]][i-1];
	for (int y:e[x]) if (y^f[x][0])
		f[y][0]=x,build(y),d[x]=max(d[x],d[y]+1);
	if (dep[x]%B==0 && d[x]>=B) id[key[x]=++t]=x;
}
void dfs(int x,int S,int last)
{
	u[x]=last;
	if (++cnt[val[x]]==1) Now[val[x]]=1;
	if (key[x]) F[QwQ[key[S]][key[x]]=++quq]=Now;
	for (int y:e[x]) if (y^f[x][0]) dfs(y,S,key[y]?y:last);
	if (!--cnt[val[x]]) Now[val[x]]=0;
}
int LCA(int x,int y)
{
	if (dep[x]<dep[y]) x^=y^=x^=y;
	for (int i=15;~i;--i) if (dep[f[x][i]]>=dep[y]) x=f[x][i];
	for (int i=15;~i;--i) if (f[x][i]^f[y][i]) x=f[x][i],y=f[y][i];
	return x^y?f[x][0]:x;
}
int jump(int x,int lim)
{
	for (int i=15;~i;--i) if (dep[f[x][i]]>=lim) x=f[x][i];
	return x;
}
int main()
{
	freopen("P6177_9.in","r",stdin);
	freopen("Olivia.out","w",stdout);
	read(n),read(m); B=sqrt(n);
	for (int i=1;i<=n;++i) read(val[i]);
	discrete(val,n);
	for (int i=1,u,v;i<n;++i)
		read(u),read(v),
		e[u].emplace_back(v),
		e[v].emplace_back(u);
	build(1);
	for (int i=1;i<=t;++i) dfs(id[i],id[i],id[i]);
	for (int x,y,r,ux,uy,lastans=0;m--;Now.reset())
	{
		read(x),read(y),x^=lastans,r=LCA(x,y);
		for (int T=u[x];x^r && x^T;x=f[x][0]) Now[val[x]]=1;
		for (int T=u[y];y^r && y^T;y=f[y][0]) Now[val[y]]=1;
		ux=jump(x,dep[r]+(B<<1));
		uy=jump(y,dep[r]+(B<<1));
		ux=dep[r]<=dep[u[ux]]?u[ux]:r;
		uy=dep[r]<=dep[u[uy]]?u[uy]:r;
		Now|=F[QwQ[key[ux]][key[x]]],Now|=F[QwQ[key[uy]][key[y]]];
		if (ux^r) for (ux=f[ux][0];ux^r;ux=f[ux][0]) Now[val[ux]]=1;
		if (uy^r) for (uy=f[uy][0];uy^r;uy=f[uy][0]) Now[val[uy]]=1;
		Now[val[r]]=1;
		printf("%d\n",lastans=(signed)Now.count());
	}
	return 0-0;
}
