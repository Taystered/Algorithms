#include<cstdio>
#include<vector>
#define N 20005
using namespace std;
int dfn[N],low[N],n,m,cnt,ans;
bool cut[N];
vector <int> e[N];
void dfs(int x,int dad)
{
	int child=0;
	dfn[x]=low[x]=++cnt;
	for (int y:e[x])
	{
		if (!dfn[y])
		{
			dfs(y,x),++child;
			low[x]=min(low[x],low[y]);
			if (dad && low[y]==dfn[x])
				ans+=!cut[x],cut[x]=1;
		}
		else low[x]=min(low[x],dfn[y]);
	}
	if (!dad && child>=2)
		ans+=!cut[x],cut[x]=1;
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1,u,v;i<=m;++i)
	{
		scanf("%d%d",&u,&v);
		e[u].emplace_back(v);
		e[v].emplace_back(u);
	}
	for (int i=1;i<=n;++i)
		if (!dfn[i]) dfs(i,0);
	printf("%d\n",ans);
	for (int i=1;i<=n;++i) 
		if (cut[i]) printf("%d ",i);
}
