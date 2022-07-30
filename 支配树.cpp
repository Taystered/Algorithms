#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int dfn[N],rev[N],father[N],sdom[N],idom[N],Min[N],ans[N],n,m,t;
vector <int> Eu[N],Ev[N],E[N];
namespace DSU
{
	int f[N];
	int update(int x)
	{
		if (f[x]==x) return x;
		int y=update(f[x]);
		if (dfn[sdom[Min[x]]]>dfn[sdom[Min[f[x]]]])
			Min[x]=Min[f[x]];
		return f[x]=y;
	}
}
void dfs(int x,int dad)
{
	rev[dfn[x]=++t]=x,father[x]=dad;
	for (int y:Eu[x]) if (!dfn[y]) dfs(y,x);
}
int main()
{
	freopen("dominator.in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1,u,v;i<=m;++i)
	{
		scanf("%d%d",&u,&v);
		Eu[u].emplace_back(v);
		Ev[v].emplace_back(u);
	}
	dfs(1,0);
	for (int i=1;i<=t;++i) sdom[i]=Min[i]=DSU::f[i]=i;
	for (int i=t;i;--i)
	{
		int x=rev[i];
		for (int y:Ev[x]) if (dfn[y])
		{
			DSU::update(y);
			if (dfn[sdom[x]]>dfn[sdom[Min[y]]])
				sdom[x]=sdom[Min[y]];
		}
		DSU::f[x]=father[x];
		E[sdom[x]].emplace_back(x);
		for (int y:E[x=father[x]])
		{
			DSU::update(y);
			idom[y]=(x==sdom[Min[y]]?x:Min[y]);
		}
		E[x].clear();
	}
	for (int i=2,x;i<=t;++i)
		x=rev[i],(sdom[x]^idom[x]) && (idom[x]=idom[idom[x]],1);
	for (int i=t,x;i;--i)
		x=rev[i],ans[idom[x]]+=++ans[x];
	for (int i=1;i<=n;++i) printf("%d ",ans[i]);
	// t not_eq n ??
}
