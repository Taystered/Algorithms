#include<cstdio>
#define N 100005
int son[N][2],fa[N],sz[N],cnt[N],val[N],n,m,rt;
bool tag[N];
bool get(int x) {return x^son[fa[x]][0];}
void update(int x) {sz[x]=sz[son[x][0]]+sz[son[x][1]]+cnt[x];}
void swap(int &x,int &y) {x^=y^=x^=y;}
void rotate(int x)
{
	int y=fa[x],z=fa[y],op=get(x);
	if (z) son[z][get(y)]=x;
	son[y][op]=son[x][op^1];
	fa[son[x][op^1]]=y;
	son[x][op^1]=y;
	fa[x]=z,fa[y]=x;
	update(x),update(y);
}
void pushdown(int p)
{
	if (tag[p])
	{
		tag[p]=0;
		tag[son[p][0]]^=1;
		tag[son[p][1]]^=1;
		swap(son[p][0],son[p][1]);
	}
}
int build(int l,int r,int f)
{
	if (l>r) return 0;
	int mid=l+r>>1;
	val[mid]=mid,cnt[mid]=1,fa[mid]=f;
	son[mid][0]=build(l,mid-1,mid);
	son[mid][1]=build(mid+1,r,mid);
	update(mid);
	return mid;
}
void splay(int x,int y)
{
	for (int f;(f=fa[x])^y;rotate(x))
		if (fa[f]^y) rotate(get(x)^get(f)?f:x);
	rt=y?rt:x;
}
int find(int x,int p=rt)
{
	pushdown(p);
	if (x<=sz[son[p][0]]) return find(x,son[p][0]);
	x-=sz[son[p][0]];
	if (x<=cnt[p]) splay(p,0);
	return x<=cnt[p]?p:find(x-cnt[p],son[p][1]);
}
void reverse(int l,int r)
{
	int x=find(l-1),y=find(r+1);
	splay(x,0),splay(y,x);
	tag[son[son[rt][1]][0]]^=1;
}
void print(int p=rt)
{
	pushdown(p);
	if (son[p][0]) print(son[p][0]);
	if (1<val[p] && val[p]<n+2) printf("%d ",val[p]-1);
	if (son[p][1]) print(son[p][1]);
}
int main()
{
	scanf("%d%d",&n,&m);
	rt=build(1,n+2,0);
	for (int i=1,x,y;i<=m;++i)
		scanf("%d%d",&x,&y),reverse(x+1,y+1);
	print();
	return 0;
}
