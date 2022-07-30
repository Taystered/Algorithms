#include<cstdio>
#define N 200005
#define mid ((l+r)>>1)
#define max(x,y) (x>y?x:y)
int n,m,T=1;
struct Seg
{
	int cnt,root[N],val[N<<5],ls[N<<5],rs[N<<5];
	void build(int &p,int l,int r)
	{
		p=++cnt;
		if (l==r) return (void)(val[p]=l);
		build(ls[p],l,mid),build(rs[p],mid+1,r);
	}
	void modify(int &p,int q,int l,int r,int x,int v)
	{
		p=++cnt,ls[p]=ls[q],rs[p]=rs[q];
		if (l==r) return (void)(val[p]=v);
		x<=mid?modify(ls[p],ls[q],l,mid,x,v):modify(rs[p],rs[q],mid+1,r,x,v);
	}
	int query(int p,int l,int r,int x)
	{
		if (l==r) return val[p];
		return x<=mid?query(ls[p],l,mid,x):query(rs[p],mid+1,r,x);
	}
} dad,dep;
int get(int x)
{
	int father=dad.query(dad.root[T],1,n,x);
	return father^x?get(father):x;
}
void merge(int x,int y)
{
	int fx=get(x),fy=get(y);
	if (fx==fy) return;
	int	sx=dep.query(dep.root[T],1,n,fx),
		sy=dep.query(dep.root[T],1,n,fy);
	if (sx>sy) fx^=fy^=fx^=fy,sx^=sy^=sx^=sy;
	dad.modify(dad.root[T],dad.root[T-1],1,n,fx,fy);
	if (sx==sy) dep.modify(dep.root[T],dep.root[T-1],1,n,fy,sx+1);
}
int main()
{
	freopen("P3402_5.in","r",stdin);
	freopen("Taystered","w",stdout);
	scanf("%d%d",&n,&m);
	dad.build(dad.root[0],1,n);
	for (int op,x,y;m--;++T)
	{
		dad.root[T]=dad.root[T-1];
		dep.root[T]=dep.root[T-1];
		scanf("%d",&op);
		if (op==1) scanf("%d%d",&x,&y),merge(x,y);
		if (op==2) scanf("%d",&x),
			dad.root[T]=dad.root[x],
			dep.root[T]=dep.root[x];
		if (op==3) scanf("%d%d",&x,&y),puts(get(x)^get(y)?"0":"1");
	}
	return 0;
}
