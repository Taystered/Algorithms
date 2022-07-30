#include<cstdio>
#include<cstring>
#define min(x,y) (x<y?x:y)
const int N=210,M=40010,inf=2147483647;
int n,m,tot=1,sum=0,s,t,S,T;
int flow[N],gap[N],dis[N],cur[N],to[M],next[M],vol[M],last[N];
void link(int u,int v,int w) {to[++tot]=v,vol[tot]=w,next[tot]=last[u],cur[u]=last[u]=tot;}
void add(int u,int v,int w) {link(u,v,w),link(v,u,0);}
void add(int u,int v,int low,int up)
{
    flow[u]+=low,flow[v]-=low;
    add(u,v,up-low);
}
int dfs(int u, int v, int flow)
{
    if (u==v) return flow;
    int have=0;
    for (int i=cur[u];i;i=next[i])
        if (vol[i] && dis[u]==dis[to[i]]+1)
		{
			cur[u]=i;
            int now=dfs(to[i],v,min(vol[i],flow-have));
            vol[i]-=now,vol[i^1]+=now,have+=now;
            if (have==flow) return have;
        }
    cur[u]=last[u];
    if (!--gap[dis[u]]) dis[v]=n;
    ++gap[++dis[u]];
    return have;
}
int main()
{
	freopen("5.in","r",stdin);
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i=1,x,y,low,up;i<=m;++i)
        scanf("%d%d%d%d",&x,&y,&low,&up),add(x,y,low,up);
    S=++n,T=++n;
    for (int i=1;i<=n-2;++i)
        flow[i]>0?add(i,T,flow[i]):add(S,i,-flow[i]);
    add(t,s,0,inf),gap[0]=n;
    while (dis[T]<n) sum+=dfs(S,T,inf);
    for (int i=last[S];i;i=next[i]) if (vol[i]) 
	{
        puts("please go home to sleep");
        return 0;
    }
    for (int i=1;i<=n;++i)
	{
        dis[i]=0;
        cur[i]=last[i];
	}
    memset(gap,0,sizeof gap);
    gap[sum=0]=n;
    while (dis[t]<n) sum+=dfs(s,t,inf);
    printf("%d",sum);
    return 0;
}
