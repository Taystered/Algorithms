#include<cstdio>
#define N 100005
int son[N][2],sz[N],fa[N],cnt[N],val[N],rt,tot,n;
bool get(int x) {return x^son[fa[x]][0];}
void clear(int x) {son[x][0]=son[x][1]=sz[x]=val[x]=cnt[x]=fa[x]=0;}
void update(int x) {sz[x]=sz[son[x][0]]+sz[son[x][1]]+cnt[x];}
void connect(int x,int y,int op) {son[fa[y]=x][op]=y;}
void rotate(int x)
{
	int op=get(x),y=fa[x],z=fa[x]=fa[y];
    if (z) connect(z,x,get(y));
    connect(y,son[x][op^1],op);
    connect(x,y,op^1);
    update(y),update(x);
}
void splay(int x)
{
	for (int f;f=fa[x];rotate(x))
		if (fa[f]) rotate(get(x)^get(f)?x:f);
	rt=x;
}
void insert(int x,int p=rt,int f=0)
{
	if (!p) val[++tot]=x,++cnt[tot],
		(fa[tot]=f) && (son[f][val[f]<x]=tot,1),
		rt+=(!rt)*tot,update(tot),update(f),splay(tot);
	else if (val[p]==x)
		++cnt[p],update(p),update(f),splay(p);
	else insert(x,son[p][val[p]<x],p);
}
int xth(int x,int p=rt)
{
	if (x<=sz[son[p][0]]) return xth(x,son[p][0]);
	x-=sz[son[p][0]];
	if (x<=cnt[p]) splay(p);
	return x<=cnt[p]?val[p]:xth(x-cnt[p],son[p][1]);
}
int rank(int x,int p=rt)
{
	if (x<val[p]) return rank(x,son[p][0]);
	int res=sz[son[p][0]];
	if (x==val[p]) splay(p);
	return res+(x^val[p]?cnt[p]+rank(x,son[p][1]):1);
}
int lower(int p=son[rt][0]) {for (;son[p][1];p=son[p][1]); splay(p); return p;}
int upper(int p=son[rt][1]) {for (;son[p][0];p=son[p][0]); splay(p); return p;}
void del(int x)
{
	rank(x);
	if (cnt[rt]>1) --cnt[rt],update(rt);
	else if (!son[rt][0] && !son[rt][1]) clear(rt),rt=0;
	else if (!son[rt][0] || !son[rt][1]) rt=son[rt][!son[rt][0]],clear(fa[rt]),fa[rt]=0;
    else
	{
		int y=rt,z=lower();
	    son[fa[son[y][1]]=rt=z][1]=son[y][1];
	    clear(y),update(rt);
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=1,op,x;i<=n;++i)
	{
		scanf("%d%d",&op,&x);
		if (op==1) insert(x);
		if (op==2) del(x);
		if (op==3) printf("%d\n",rank(x));
		if (op==4) printf("%d\n",xth(x));
		if (op==5) insert(x),printf("%d\n",val[lower()]),del(x);
		if (op==6) insert(x),printf("%d\n",val[upper()]),del(x);
	}
	return 0;
}
