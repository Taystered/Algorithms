#include<bits/stdc++.h>
#define N 1005
#define next Next
void add(int u,int v,int w) {to[++t]=v,vol[t]=w,next[t]=last[u],last[u]=t;}
void link(int u,int v,int w) {add(u,v,w),add(v,u,0);}
int dfs(int x,int flow)
{
	if (x==T) return flow;
	int have=0;
	for (int i=cur[x];i;i=next[i])
		if (vol[cur[x]=i] && dis[x]==dis[to[i]]+1)
		{
			int now=dfs(to[i],min(vol[i],flow-have));
			vol[i]-=now,vol[i^1]+=now,have+=now;
			if (have==flow) return have;	
		}
	cur[x]=last[x];
	if (!--gap[dis[x]]) dis[S]=T;
	++gap[++dis[x]];
	return have;
}
int main()
{
	
} 
