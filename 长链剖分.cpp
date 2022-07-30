#include<cstdio>
#include<vector>
#define N 500005
#define ui unsigned int
#define ll long long
using namespace std;
int f[N][20],dep[N],son[N],log[N],len[N],top[N],n,q,rt;
ui s;
ll Ans;
vector <int> e[N],up[N],down[N];
ui get(ui x)
{
	x^=x<<13,x^=x>>17,x^=x<<5;
	return s=x; 
}
void dfs(int x)
{
	dep[x]=dep[f[x][0]]+1;
	for (int i=1;i<20;++i) f[x][i]=f[f[x][i-1]][i-1]; 
	for (int y:e[x]) dfs(y),son[x]=len[son[x]]>len[y]?son[x]:y;
	len[x]=len[son[x]]+1;
}
void dfs(int x,int S)
{
	top[x]=S;
	if (x==S)
	{
		for (int i=0,y=x;y && i<=len[x];++i)
			up[x].emplace_back(y),y=f[y][0];
		for (int i=0,y=x;y && i<=len[x];++i)
			down[x].emplace_back(y),y=son[y];
	}
	if (son[x]) dfs(son[x],S);
	for (int y:e[x]) if (y^son[x]) dfs(y,y);
}
int query(int x,int k)
{
	if (!k) return x;
	x=f[x][log[k]],k-=(1<<log[k])+(dep[x]-dep[top[x]]),x=top[x];
	return k>0?up[x][k]:down[x][-k];
}
int main()
{
	freopen("P5903_1.in","r",stdin);
	scanf("%d%d%u",&n,&q,&s);
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&f[i][0]);
		e[f[i][0]].emplace_back(i);
		log[i]=log[i>>1]+(i>1);
	}
	rt=e[0][0],dfs(rt),dfs(rt,rt);
	for (int i=1,x,k,ans=0;i<=q;++i)
	{
		x=(get(s)^ans)%n+1;
		k=(get(s)^ans)%dep[x];
		ans=query(x,k);
		Ans^=1ll*i*ans;
	}
	printf("%lld",Ans);
}
