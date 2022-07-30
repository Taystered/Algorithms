#include<cstdio>
#define N 1000005
#define ll long long
int n,q;
namespace BIT
{
	ll f0[N],f1[N];
	void modify(int x,int v0)
	{
		for (ll v1=1ll*v0*x;x<=n;x+=x&-x)
			f0[x]+=v0,f1[x]+=v1;
	}
	void modify(int l,int r,int v)
	{
		modify(l,v),modify(r+1,-v);
	}
	ll query(int x)
	{
		ll res=0;
		for (int v=x;x;x-=x&-x)
			res+=f0[x]*(v+1ll)-f1[x];
		return res;
	}
	ll query(int l,int r)
	{
		return query(r)-query(l-1);
	}
}
using namespace BIT;
int main()
{
//	freopen("2.in","r",stdin);
//	freopen("tree.out","w",stdout);
	scanf("%d%d",&n,&q);
	for (int i=1,x;i<=n;++i)
		scanf("%d",&x),modify(i,i,x);
	for (int op,l,r,x;q--;)
	{
		scanf("%d",&op);
		if (op==1) scanf("%d%d",&l,&x),modify(l,l,x);
		if (op==2) scanf("%d%d",&l,&r),printf("%lld\n",query(l,r));
	}
}
