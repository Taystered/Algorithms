#include<cstdio>
#define N 100005
int f[N],ls[N],rs[N],d[N],a[N],n,m;
bool del[N];
void swap(int &x,int &y) {x^=y^=x^=y;}
int get(int x) {return x^f[x]?f[x]=get(f[x]):x;}
int merge(int x,int y)
{
	if (!x || !y) return x+y;
	if (a[x]>a[y]) swap(x,y);
	rs[x]=merge(rs[x],y);
	if (d[ls[x]]<d[rs[x]]) swap(ls[x],rs[x]);
	d[x]=d[rs[x]]+1;
	return x;
}
int main()
{
	freopen("heap.in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",&a[f[i]=i]);
	for (int op,x,y;m--;) scanf("%d",&op),
		(op==1) && (scanf("%d%d",&x,&y),(!del[x] && !del[y] && (x=get(x))^(y=get(y))) && (f[x]=f[y]=merge(x,y),1),1),
		(op==2) && (scanf("%d",&x),del[x]?puts("-1"):(printf("%d\n",a[x=get(x)]),del[x]=1,f[x]=f[ls[x]]=f[rs[x]]=merge(ls[x],rs[x])),1);
}
