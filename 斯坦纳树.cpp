#include<queue>
#include<cstdio>
#include<cstring>
#define N 105
#define M 1005
#define inf 1010580540
#define min(x,y) (x<y?x:y)
using namespace std;
int to[M],dis[M],next[M],last[N],a[N],f[N][1<<10],n,m,k,t,ans=inf;
bool vis[N];
queue <int> q;
void add(int u,int v,int w)
{
	to[++t]=v,dis[t]=w,next[t]=last[u],last[u]=t;
}
int main()
{
	freopen("steiner.in","r",stdin);
	scanf("%d%d%d",&n,&m,&k);
	for (int i=1,u,v,w;i<=m;++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w),add(v,u,w);
	}
	memset(f,60,sizeof f);
	for (int i=1;i<=k;++i) 
	{
		scanf("%d",&a[i]);
		f[a[i]][1<<(i-1)]=0;
	}
	for (int S=0;S<(1<<k);++S)
	{
		for (int i=1;i<=n;++i)
			for (int T=S&(S-1);T;T=S&(T-1))
				f[i][S]=min(f[i][S],f[i][T]+f[i][S^T]);
		for (int i=1;i<=n;++i) if (f[i][S]<inf) q.push(i),vis[i]=1;
		for (int x;!q.empty();vis[x]=0)
		{
			x=q.front(),q.pop();
			for (int i=last[x],y;i;i=next[i])
				if (f[x][S]+dis[i]<f[y=to[i]][S])
				{
					f[y][S]=f[x][S]+dis[i];
					if (!vis[y]) q.push(y),vis[y]=1;
				}
		}
	}
	for (int i=1;i<=n;++i) ans=min(ans,f[i][(1<<k)-1]);
	printf("%d",ans);
} 
