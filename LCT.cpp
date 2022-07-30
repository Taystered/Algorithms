#include<cstdio>
#define N 300005
#define ls (son[p][0])
#define rs (son[p][1])
int n,m;
namespace LCT
{
	int son[N][2],fa[N],size[N],v[N],st[N];
	bool tag[N];
	bool get(int x) {return x^son[fa[x]][0];}
	bool isrt(int x) {return son[fa[x]][0]^x && son[fa[x]][1]^x;}
	void swap(int &x,int &y) {x^=y^=x^=y;}
	void connect(int x,int y,int op) {son[fa[y]=x][op]=y;}
	void update(int p) {size[p]=size[ls]+size[rs]+1;}
	void pushdown(int p)
	{
		if (tag[p])
			swap(ls,rs),
			tag[ls]^=1,
			tag[rs]^=1,
			tag[p]^=1;
	}
	void rotate(int x)
	{
		int op=get(x),y=fa[x],z=fa[x]=fa[y];
	    if (!isrt(y)) connect(z,x,get(y));
	    connect(y,son[x][op^1],op);
	    connect(x,y,op^1);
	    update(y),update(x);
	}
	void splay(int x)
	{
	    int top=0,y=st[++top]=x;
	    while (!isrt(y)) st[++top]=y=fa[y];
	    while (top) pushdown(st[top--]);
	    for (int y=fa[x];!isrt(x);rotate(x),y=fa[x])
			if (!isrt(y)) rotate(get(x)^get(y)?x:y);
	}
	void access(int p) {for (int x=0;p;p=fa[x=p]) splay(p),rs=x,update(p);}
	int findroot(int p)
	{
	    for (access(p),splay(p),pushdown(p);ls;) pushdown(p),p=ls;
	    return p;
	}
	void makeroot(int x) {access(x),splay(x),tag[x]^=1,pushdown(x);}
	void link(int x,int y) {makeroot(x),(findroot(y)^x) && (fa[x]=y,1);}
	void split(int x,int y) {makeroot(x),access(y),splay(y);}
	void cut(int x,int y)
	{
		makeroot(x);
		if (findroot(y)==x && fa[x]==y && son[y][0]==x && !son[x][1])
			fa[x]=son[y][0]=0,update(y);
	}
	int dis(int x,int y) {split(x,y); return size[y];}
}
using namespace LCT;
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",&v[i]);
	for (int op,x,y;m--;)
	{
		scanf("%d%d%d",&op,&x,&y);
		if (op==0) split(x,y);
        if (op==1) link(x,y);
        if (op==2) cut(x,y);
        if (op==3) splay(x),v[x]=y;
	}
	return 0;
}
