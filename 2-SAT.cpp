#include<cstdio>
#include<vector>
#define N 1000005
#define min(x,y) (x<y?x:y)
int to[N<<1],next[N<<1],last[N<<1],stk[N<<1],dfn[N<<1],low[N<<1],col[N<<1],n,m,t,top,cnt,time;
bool vis[N<<1];
void add(int u,int v) {to[++t]=v,next[t]=last[u],last[u]=t;}
void tarjan(int x)
{
	stk[++top]=x,vis[x]=1,dfn[x]=low[x]=++time;
	for (int i=last[x];i;i=next[i])
	{
		int y=to[i];
		if (!dfn[y]) tarjan(y),low[x]=min(low[x],low[y]);
		else if (vis[y]) low[x]=min(low[x],dfn[y]);
	}
	if (dfn[x]==low[x])
	{
		++cnt;
		do
		{
			col[stk[top]]=cnt;
			vis[stk[top]]=0;
		} while (stk[top--]^x);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int x,y,sx,sy;m--;)
	{
		scanf("%d%d%d%d",&x,&sx,&y,&sy);
		add(x+(1-sx)*n,y+sy*n);
		add(y+(1-sy)*n,x+sx*n);
	}
	for (int i=1;i<=(n<<1);++i) if (!dfn[i]) tarjan(i);
	for (int i=1;i<=n;++i) if (col[i]==col[i+n]) return puts("IMPOSSIBLE"),0;
	puts("POSSIBLE");
	for (int i=1;i<=n;++i) putchar(col[i]>col[i+n]?'1':'0'),putchar(' ');
}
