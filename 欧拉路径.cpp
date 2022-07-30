#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,m,t,S,cntS,cntT,cur[N],indeg[N],outdeg[N],ans[N<<1];
vector <int> e[N];
void dfs(int x)
{
	for (int i=cur[x];i<e[x].size();i=cur[x])
		cur[x]=i+1,dfs(e[x][i]);
	ans[++t]=x;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1,u,v;i<=m;++i)
	{
		scanf("%d%d",&u,&v);
		e[u].emplace_back(v);
		++indeg[v],++outdeg[u];
	}
	for (int i=1;i<=n;++i) sort(begin(e[i]),end(e[i]));
	for (int i=n;i;--i)
	{
		if (indeg[i]-outdeg[i]>1) return puts("No"),0;
		if (outdeg[i]-indeg[i]>1) return puts("No"),0;
		if (outdeg[i]-indeg[i]==1) ++cntS,S=i;
		if (indeg[i]-outdeg[i]==1) ++cntT;
	}
	if (cntS && (cntS^cntT || (cntS+cntT)^2)) return puts("No"),0;
	dfs(S?S:1);
	for (int i=t;i;--i) printf("%d ",ans[i]); 
}
