#include<bits/stdc++.h>
#define N 505
#define M 300005
#define mod 998244353
#define next Next
#define F(x) for (int i=last[x],y;i;i=next[i]) if (!del[y=to[i]] && y^dad)
using namespace std;
int a[M],d[M],ans[N],to[M<<1],next[M<<1],last[M],cnt[M],cntV[M],cntE[M<<1],size[M],Max[M],Pow[M],n,m,R,t=1,Ans;
bool del[M];
void link(int u,int v) {to[++t]=v,next[t]=last[u],last[u]=t;}
int GetR(int x,int dad,int n)
{
	int res=0;
	size[x]=1,Max[x]=0;
	F(x)
	{
		res+=GetR(y,x,n)*(!res);
		size[x]+=size[y];
		Max[x]=max(Max[x],size[y]);
	}
	if (max(Max[x],n-size[x])<=n/2) res+=x*(!res);
	return res;
}
void push(int x,int dad,int dep,int n)
{
	//++cnt[min(n,d[y]-dep)];
	F(x) push(y,x,dep+1,n);
}
void calc(int x,int dad,int dep,int E,int sig)
{
	cntV[x]+=cnt[dep]*sig;
	cntE[E]=cntE[E^1]+=cnt[dep]*sig;
	F(x) calc(y,x,dep+1,i,sig);
}
void sum(int n) {for (int i=n;i;--i) cnt[i-1]+=cnt[i];}
void solve(int x,int dad,int n)
{
	int G=GetR(x,dad,n);
	F(G) 
	{
		size[y]=size[y]>size[G]?n-size[G]:size[y];
		push(y,G,1,size[y]),sum(size[y]),calc(y,G,1,i,-1); // start from depth 1
		cntE[i]=cntE[i^1]+=cnt[0];
		fill(cnt,cnt+size[y]+2,0);
	}
	push(G,dad,0,n),sum(n),calc(G,dad,0,0,1),fill(cnt,cnt+n+1,0);
	del[G]=1;
	F(G) solve(y,G,size[y]);
}
int main()
{
}
