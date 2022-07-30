#include<cmath>
#include<cstdio>
#include<algorithm>
#define N 50005
#define M 100005
#define next Next
using namespace std;
int to[N<<1],next[N<<1],last[N],c[N],dep[N],f[N][20],q[N<<1],S[N],T[N],B[N<<1],tot[N],
	u[M],v[M],a[M],b[M],rt[M],p[M],Ans[M],n,m,t,cnt,ans,len;
bool vis[M],op[M];
bool cmp(int x,int y) {return B[u[x]]^B[u[y]]?B[u[x]]<B[u[y]]:v[x]<v[y];}
void add(int u,int v) {to[++t]=v,next[t]=last[u],last[u]=t;}
void swap(int &x,int &y) {x^=y^=x^=y;}
void dfs(int x,int dad)
{
	q[S[x]=++cnt]=x;
	f[x][0]=dad,dep[x]=dep[dad]+1;
	for (int i=1;i<20;++i) f[x][i]=f[f[x][i-1]][i-1];
	for (int i=last[x];i;i=next[i])
		if (to[i]^dad) dfs(to[i],x);
	q[T[x]=++cnt]=x;
}
int LCA(int x,int y)
{
	if (dep[x]<dep[y]) x^=y^=x^=y;
	for (int i=19;~i;--i) if (dep[f[x][i]]>=dep[y]) x=f[x][i];
	if (x==y) return x;
	for (int i=19;~i;--i) if (f[x][i]^f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
void change(int x)
{
	(vis[x]^=1)?(++tot[c[x]]==1) && (++ans,1):
				(!--tot[c[x]]) && (--ans,1);
}
int main()
{
	freopen("apple4.in","r",stdin);
	freopen("apple.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",&c[i]);
	for (int i=1,x,y;i<=n;++i) scanf("%d%d",&x,&y),add(x,y),add(y,x);
	dfs(0,0),len=(int)sqrt(cnt);
	for (int i=1;i<=m;++i) 
	{
		scanf("%d%d%d%d",&u[p[i]=i],&v[i],&a[i],&b[i]);
		(S[u[i]]>S[v[i]]) && (swap(u[i],v[i]),1);
		rt[i]=LCA(u[i],v[i]),op[i]=rt[i]^u[i];
		u[i]=(op[i]?T[u[i]]:S[u[i]]),v[i]=S[v[i]];
	}
	for (int i=1;i<=cnt;++i) B[i]=i/len+1;
	sort(p+1,p+m+1,cmp);
	for (int i=1,l=2,r=1;i<=m;++i)
	{
		while (l<u[p[i]]) change(q[l++]);
		while (l>u[p[i]]) change(q[--l]);
		while (r<v[p[i]]) change(q[++r]);
		while (r>v[p[i]]) change(q[r--]);
		(op[p[i]]) && (change(rt[p[i]]),1);
		Ans[p[i]]=ans-(tot[a[p[i]]] && tot[b[p[i]]] && a[p[i]]^b[p[i]]);
		(op[p[i]]) && (change(rt[p[i]]),1);
	}
	for (int i=1;i<=m;++i) printf("%d\n",Ans[i]);
	return 0;
} 
