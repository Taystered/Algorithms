#include<queue>
#include<cstdio>
#include<cstring>
#define N 410
#define M 30010
#define next Next
#define min(x,y) (x<y?x:y)
using namespace std;
int to[M],vol[M],pri[M],next[M],last[N],flow[N],cost[N],lastV[N],lastE[N],n,m,t=1,maxf,minc,S=1,T;
bool vis[N];
queue <int> q;
void add(int u,int v,int w,int c) {to[++t]=v,vol[t]=w,pri[t]=c,next[t]=last[u],last[u]=t;}
void link(int u,int v,int w,int c) {add(u,v,w,c),add(v,u,0,-c);}
bool SPFA()
{
	memset(vis,0,sizeof vis);
	memset(cost,63,sizeof cost);
	memset(flow,63,sizeof flow);
	q.push(S),vis[S]=1,cost[S]=lastV[T]=0;
	for (;!q.empty();)
	{
		int x=q.front(); q.pop();
		for (int i=last[x];i;i=next[i])
		{
			int y=to[i];
			if (vol[i]>0 && cost[y]>cost[x]+pri[i])
			{
				cost[y]=cost[x]+pri[i];
				flow[y]=min(flow[x],vol[i]);
				lastV[y]=x,lastE[y]=i;
				if (!vis[y]) q.push(y),vis[y]=1;
			}
		}
		vis[x]=0;
	}
	return lastV[T];
}
int main()
{
	freopen("cost.in","r",stdin);
	scanf("%d%d",&n,&m); T=n;
	for (int i=1,u,v,w,c;i<=m;++i)
		scanf("%d%d%d%d",&u,&v,&w,&c),link(u,v,w,c);
	for (;SPFA();)
	{
		maxf+=flow[T],minc+=flow[T]*cost[T];
		for (int x=T;x!=S;x=lastV[x]) 
			vol[lastE[x]]-=flow[T],vol[lastE[x]^1]+=flow[T];
	}
	printf("%d %d",maxf,minc);
	return 0;
}
