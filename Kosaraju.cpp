#include<cstdio>
#include<cstring>
#define N 105
int n,m,top,t,ans,a[N][N],s[N],u[N],v[N];
bool vis[N];
void dfs1(int x)
{
	vis[x]=1;
	for (int i=1;i<=n;++i) if (a[x][i]==1 && !vis[i]) dfs1(i);
	s[++top]=x;
}
void dfs2(int x)
{
	vis[x]=1;
	for (int i=1;i<=n;++i) 
		if (a[x][i]==2 && !vis[i]) dfs2(i);
	++t;
}
int main()
{
//	freopen("");
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i) scanf("%d%d",&u[i],&v[i]);
	for (int i=1;i<=n;++i) if (!vis[i]) dfs1(i);
	memset(vis,0,sizeof(vis));
	for (;top--;) if (!vis[s[top]]) t=0,dfs2(s[top]),ans+=t*(t-1)/2;
	printf("%d",ans);
	return 0;
}
