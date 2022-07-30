#include<cstdio>
#include<cstring>
#define N 5000005
int len[N],son[N][26],fail[N],cnt[N],last,tot,sz,ans;
char s[N];
void newnode(int x)
{
	ans=ans>x?ans:x;
	len[++sz]=x;
	memset(son[sz],0,sizeof son[sz]);
	fail[sz]=cnt[sz]=0;
}
void clear()
{
	sz=-1;
	newnode(0);
	newnode(-1);
	last=0;
	fail[0]=1;
}
int getfail(int x)
{
	while (s[tot-len[x]-1]^s[tot]) x=fail[x];
	return x;
}
void insert(char x)
{
	++tot;
	int now=getfail(last);
	if (!son[now][x-'a'])
	{
		newnode(len[now]+2);
		fail[sz]=son[getfail(fail[now])][x-'a'];
		son[now][x-'a']=sz;
	}
	last=son[now][x-'a'];
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%s",s+1);
	clear();
	for (int i=1;s[i];++i) insert(s[i]);
	printf("%d %d",sz-1,ans);
}
