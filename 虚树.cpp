#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define N 250005
#define ll long long
#define next Next
#define min(x,y) (x<y?x:y)
using namespace std;
int dfn[N],f[N][20],to[N<<1],val[N<<1],next[N<<1],last[N],dep[N],h[N],s[N],n,m,k,t,cnt,top;
ll Min[N];
bool key[N];
vector <int> e[N];
bool cmp(int x,int y) {return dfn[x]<dfn[y];}
void add(int u,int v,int w){to[++t]=v,val[t]=w,next[t]=last[u],last[u]=t;}
void build(int x,int dad)
{
	for (int i=1;i<20;++i) f[x][i]=f[f[x][i-1]][i-1];
	dfn[x]=++cnt,dep[x]=dep[dad]+1;
	for (int i=last[x],y;i;i=next[i]) if ((y=to[i])^dad) 
		f[y][0]=x,Min[y]=min(Min[x],val[i]),build(y,x);
}
int LCA(int x,int y)
{
	if (dep[x]<dep[y]) x^=y^=x^=y;
	for (int i=19;~i;--i) if (dep[f[x][i]]>=dep[y]) x=f[x][i];
	for (int i=19;~i;--i) if (f[x][i]^f[y][i]) x=f[x][i],y=f[y][i];
	return x^y?f[x][0]:x;
}
ll dp(int x)
{
	ll sum=0;
	if (e[x].empty()) return Min[x];
	for (int y:e[x]) sum+=dp(y);
	e[x].clear();
	return min(sum,Min[x]);
}
void insert(int x)
{
	int r=LCA(x,s[top]);
	if (top==1) return void(s[++top]=x); //this is pro-based too
	if (s[top]==r) goto skip;
	for (;top>1 && dfn[s[top-1]]>=dfn[r];--top) e[s[top-1]].push_back(s[top]);
	if (r^s[top]) e[r].push_back(s[top]),s[top]=r;
	s[++top]=x; //usually we're supposed to link when skipped, but this pro, needless
	skip:return;
}
int main()
{
	scanf("%d",&n);
	for (int i=1,u,v,w;i<n;++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w),add(v,u,w);
	}
	Min[1]=1ll<<60,build(1,0);
	for (scanf("%d",&m);m--;)
	{
		scanf("%d",&k);
		for (int i=s[top=1]=1;i<=k;++i) scanf("%d",&h[i]);
		sort(h+1,h+k+1,cmp);
		for (int i=1;i<=k;++i) insert(h[i]);
		for (;top>1;--top) e[s[top-1]].push_back(s[top]); 
		printf("%lld\n",dp(1));
	}
	return 0;
}
