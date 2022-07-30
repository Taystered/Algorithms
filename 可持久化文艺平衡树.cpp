#include<cstdio>
#include<cstdlib>
#define N 200005
#define ll long long
int n,tot,root[N];
ll ans;
struct treap {int ls,rs,key,val,size,tag; ll sum;} t[N<<6];
void update(int x)
{
	t[x].sum=t[t[x].ls].sum+t[t[x].rs].sum+t[x].val;
	t[x].size=t[t[x].ls].size+t[t[x].rs].size+1;
}
void newnode(int v) {t[++tot]=(treap){0,0,rand(),v,1,0,v};}
void pushdown(int x)
{
	if (t[x].tag)
	{
		t[x].ls^=t[x].rs^=t[x].ls^=t[x].rs;
		if (t[x].ls) t[++tot]=t[t[x].ls],t[t[x].ls=tot].tag^=1;
		if (t[x].rs) t[++tot]=t[t[x].rs],t[t[x].rs=tot].tag^=1;
		t[x].tag^=1;
	}
}
void split(int p,int k,int &x,int &y)
{
	if (!p) return (void)(x=y=0);
	pushdown(p);
	t[t[p].ls].size<k?
		(t[x=++tot]=t[p],split(t[x].rs,k-t[t[x].ls].size-1,t[x].rs,y),update(x)):
		(t[y=++tot]=t[p],split(t[y].ls,k,x,t[y].ls),update(y));
}
int merge(int x,int y)
{
	if (!x || !y) return x+y;
	int p;
	pushdown(x),pushdown(y);
	t[x].key<t[y].key?
		(p=x,t[p].rs=merge(t[p].rs,y)):
		(p=y,t[p].ls=merge(x,t[p].ls));
	update(p);
	return p;
}
int merge(int x,int y,int z) {return merge(merge(x,y),z);}
int X,Y,Z;
void insert(int &R,int x,int v)
{
	split(R,x,X,Y);
	newnode(v);
	R=merge(X,tot,Y);
}
void erase(int &R,int x)
{
	split(R,x,X,Y);
	split(X,x-1,X,Z);
	R=merge(X,Y);
}
void reverse(int &R,int l,int r)
{
	split(R,l-1,X,Y);
	split(Y,r-l+1,Y,Z);
	t[Y].tag^=1;
	R=merge(X,Y,Z);
}
ll query(int &R,int l,int r)
{
	split(R,l-1,X,Y);
	split(Y,r-l+1,Y,Z);
	ll res=t[Y].sum;
	R=merge(X,Y,Z);
	return res;
}
int main()
{
	freopen("P5055_1.in","r",stdin);
	freopen("Treap.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
	{
		ll k,op,x,y;
		scanf("%lld%lld",&k,&op);
		root[i]=root[k];
		if (op==1) scanf("%lld%lld",&x,&y),x^=ans,y^=ans,insert(root[i],x,y);
		if (op==2) scanf("%lld",&x),x^=ans,erase(root[i],x);
		if (op==3) scanf("%lld%lld",&x,&y),x^=ans,y^=ans,reverse(root[i],x,y);
		if (op==4) scanf("%lld%lld",&x,&y),x^=ans,y^=ans,printf("%lld\n",ans=query(root[i],x,y));
	}
}
