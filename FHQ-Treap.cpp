#include<ctime>
#include<cstdio>
#include<cstdlib>
#define N 1100005
int ls[N],rs[N],key[N],val[N],size[N],n,q,t,R,ans;
void update(int x) {size[x]=size[ls[x]]+size[rs[x]]+1;}
void newnode(int v) {size[++t]=1,val[t]=v,key[t]=rand();}
void split(int p,int k,int &x,int &y)
{
	if (!p) return (void)(x=y=0);
	val[p]<=k?
		(x=p,split(rs[p],k,rs[p],y)):
		(y=p,split(ls[p],k,x,ls[p]));
	update(p);
}
int merge(int x,int y)
{
	int p=x;
	if (!x || !y) return x+y;
	key[x]<key[y]?
		rs[p=x]=merge(rs[x],y):
		ls[p=y]=merge(x,ls[y]);
	update(p);
	return p;
}
int merge(int x,int y,int z) {return merge(merge(x,y),z);}
int X,Y,Z,res;
int kth(int p,int k)
{
	if (size[ls[p]]+1==k) return p;
	if (size[ls[p]]>=k) return rank(ls[p],k);
    return rank(rs[p],k-size[ls[p]]-1);
}
void insert(int v)
{
	split(R,v,X,Y);
	newnode(v);
	R=merge(X,t,Y);
}
void erase(int v)
{
	split(R,v,X,Z);
	split(X,v-1,X,Y);
	Y=merge(ls[Y],rs[Y]);
	R=merge(X,Y,Z);
}
int rank(int v)
{
	split(R,v-1,X,Y);
	res=size[X]+1;
	R=merge(X,Y);
	return res;
}
int pre(int v)
{
	split(R,v-1,X,Y);
	res=kth(X,size[X]);
	R=merge(X,Y);
	return res;
}
int suf(int v)
{
	split(R,v,X,Y);
	res=kth(Y,1);
	R=merge(X,Y);
	return res;
}
int main()
{
//	freopen("Treap.in","r",stdin);
	srand(time(NULL));
	scanf("%d%d",&n,&q);
	for (int i=1,x;i<=n;++i) scanf("%d",&x),insert(x);
	for (int op,x,lastans=0;q--;)
	{
		scanf("%d%d",&op,&x);
		x^=lastans;
		if (op==1) insert(x);
		if (op==2) erase(x);
		if (op==3) ans^=lastans=rank(x);
		if (op==4) ans^=lastans=val[rank(R,x)];
		if (op==5) ans^=lastans=val[pre(x)];
		if (op==6) ans^=lastans=val[suf(x)];
	}
	printf("%d",ans);
}
