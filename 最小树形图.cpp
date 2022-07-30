#include<bits/stdc++.h>
#define N 1000005
#define INF 1010580540
using namespace std;
int n,m,r,ans,u[N],v[N],w[N],id[N],in[N],pre[N];
bool vis[N];
int main()
{
	scanf("%d%d%d",&n,&m,&r);
	for (int i=1;i<=m;++i) scanf("%d%d%d",&u[i],&v[i],&w[i]);
	for (int cnt;;)
	{
		memset(in,60,sizeof in);
		memset(id,cnt=0,sizeof id);
		for (int i=1;i<=m;++i)
			if (u[i]^v[i] && w[i]<in[v[i]])
				in[v[i]]=w[i],pre[v[i]]=u[i];
		for (int i=1;i<=n;++i) if (i^r && in[i]==INF) return puts("-1"),0;
		for (int i=1,x;i<=n;++i) if (i^r)
		{
			ans+=in[i];
			for (x=i;!vis[x];x=pre[x]) vis[x]=1;
			if (x^r && x==i && !id[x])
				for (x=i,++cnt;!id[x];x=pre[x]) id[x]=cnt;
			for (x=i;vis[x];x=pre[x]) vis[x]=0;
		}
		if (!cnt) break;
		for (int i=1;i<=n;++i) if (!id[i]) id[i]=++cnt;
		for (int i=1;i<=m;++i)
		{
			if (id[u[i]]^id[v[i]]) w[i]-=in[v[i]];
			u[i]=id[u[i]],v[i]=id[v[i]];
		}
		r=id[r],n=cnt;
	}
	printf("%d",ans);
}
