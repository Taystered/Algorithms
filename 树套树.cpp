#include<bits/stdc++.h>
#define N 70005
//using namespace std;
int ls[N<<5],rs[N<<5],key[N<<5],val[N<<5],size[N<<5],a[N],n,m,t;
std::mt19937 Rand(time(NULL));
struct Treap
{
	int X,Y,Z,R,res;
	void update(int x) {size[x]=size[ls[x]]+size[rs[x]]+1;}
	void newnode(int v) {size[++t]=1,val[t]=v,key[t]=Rand();}
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
	int kth(int p,int k)
	{
		if (size[ls[p]]+1==k) return p;
		if (size[ls[p]]>=k) return kth(ls[p],k);
	    return kth(rs[p],k-size[ls[p]]-1);
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
		res=X?val[kth(X,size[X])]:-2147483647;
		R=merge(X,Y);
		return res;
	}
	int suf(int v)
	{
		split(R,v,X,Y);
		res=Y?val[kth(Y,1)]:2147483647;
		R=merge(X,Y);
		return res;
	}
	void build(int l,int r)
	{
		for (int i=l;i<=r;++i)
			insert(a[i]);
	}
} f[N<<2];
int max(int x,int y) {return x>y?x:y;}
int min(int x,int y) {return x<y?x:y;}
namespace SegmentTree
{
	#define ls (p<<1)
	#define rs (ls|1)
	#define mid ((l+r)>>1)
	void build(int p,int l,int r)
	{
		f[p].build(l,r);
		if (l^r) build(ls,l,mid),build(rs,mid+1,r);
	}
	void modify(int p,int l,int r,int x,int v0,int v1)
	{
		f[p].insert(v0),f[p].erase(v1);
		if (l==r) return;
		x<=mid?modify(ls,l,mid,x,v0,v1):modify(rs,mid+1,r,x,v0,v1);
	}
	int rank(int p,int l,int r,int x,int y,int v)
	{
		if (y<l || r<x) return 0;
		if (x<=l && r<=y) return f[p].rank(v)-1;
		return rank(ls,l,mid,x,y,v)+rank(rs,mid+1,r,x,y,v);
	}
	int pre(int p,int l,int r,int x,int y,int v)
	{
		if (y<l || r<x) return -2147483647;
		if (x<=l && r<=y) return f[p].pre(v);
		return max(pre(ls,l,mid,x,y,v),pre(rs,mid+1,r,x,y,v));
	}
	int suf(int p,int l,int r,int x,int y,int v)
	{
		if (y<l || r<x) return 2147483647;
		if (x<=l && r<=y) return f[p].suf(v);
		return min(suf(ls,l,mid,x,y,v),suf(rs,mid+1,r,x,y,v));
	}
	#undef ls
	#undef rs
	#undef mid
}
using namespace SegmentTree;
int main()
{
	freopen("P3380_7.in","r",stdin);
//	freopen("Bella.in","r",stdin);
	freopen("Poarch.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",&a[i]);
	build(1,1,n);
	for (int op,x,y,k,ans;m--;ans=0)
	{
		scanf("%d",&op);
		if (op==1) scanf("%d%d%d",&x,&y,&k),printf("%d\n",rank(1,1,n,x,y,k)+1);
		if (op==2)
		{
			scanf("%d%d%d",&x,&y,&k);
			for (int l=1,r=1e8,mid;l<=r;)
				mid=(l+r)>>1,rank(1,1,n,x,y,mid)+1<=k?l=mid+1,ans=mid:r=mid-1;
			printf("%d\n",ans);
		}
		if (op==3) scanf("%d%d",&x,&y),modify(1,1,n,x,y,a[x]),a[x]=y;
		if (op==4) scanf("%d%d%d",&x,&y,&k),printf("%d\n",pre(1,1,n,x,y,k));
		if (op==5) scanf("%d%d%d",&x,&y,&k),printf("%d\n",suf(1,1,n,x,y,k));
	}
	return 0;
}
