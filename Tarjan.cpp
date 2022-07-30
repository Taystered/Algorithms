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
