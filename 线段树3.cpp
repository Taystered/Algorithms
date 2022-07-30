#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define ll long long
using namespace std;
const int N=5e5+5;
const ll INF=1e14;
int a[N],n,q;
ll Sec[N<<2],MAX[N<<2],cnt[N<<2],tagMax[N<<2],tagSec[N<<2],Max[N<<2],MaxMax[N<<2],MaxSec[N<<2],sum[N<<2];
void read(int &x)
{
	char ch=getchar(); bool neg=x=0;
	for (;!isdigit(ch);ch=getchar()) ch=='-' && (neg=1,1);
	for (;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
	neg && (x=-x,1);
}
void update(int p,int l,int r,ll vmax,ll vsec,ll maxmax,ll maxsec)
{
	MAX[p]=max(MAX[p],Max[p]+maxmax);
	MaxMax[p]=max(MaxMax[p],tagMax[p]+maxmax);
	MaxSec[p]=max(MaxSec[p],tagSec[p]+maxsec);
	tagMax[p]+=vmax,tagSec[p]+=vsec;
	Max[p]+=vmax,(Sec[p]>-INF) && (Sec[p]+=vsec,1);
	sum[p]+=cnt[p]*vmax+(r-l+1-cnt[p])*vsec;
}
void pushdown(int p,int l,int r)
{
	int MaxVal=max(Max[ls],Max[rs]);
	(MaxVal==Max[ls]?
		update(ls,l,mid,tagMax[p],tagSec[p],MaxMax[p],MaxSec[p]):
		update(ls,l,mid,tagSec[p],tagSec[p],MaxSec[p],MaxSec[p]));
	(MaxVal==Max[rs]?
		update(rs,mid+1,r,tagMax[p],tagSec[p],MaxMax[p],MaxSec[p]):
		update(rs,mid+1,r,tagSec[p],tagSec[p],MaxSec[p],MaxSec[p]));
	tagMax[p]=tagSec[p]=MaxMax[p]=MaxSec[p]=0;
}
void pushup(int p)
{
	sum[p]=sum[ls]+sum[rs];
	Max[p]=max(Max[ls],Max[rs]);
	MAX[p]=max(MAX[ls],MAX[rs]);
	Sec[p]=max(Sec[ls],Sec[rs]),cnt[p]=0;
	Max[ls]==Max[p]?cnt[p]+=cnt[ls]:Sec[p]=max(Sec[p],Max[ls]);
	Max[rs]==Max[p]?cnt[p]+=cnt[rs]:Sec[p]=max(Sec[p],Max[rs]);
}
void build(int p,int l,int r)
{
	if (l==r) return (void)(sum[p]=Max[p]=MAX[p]=a[l],Sec[p]=-INF,cnt[p]=1);
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(p);
}
void modifyAdd(int p,int l,int r,int x,int y,ll v)
{
	if (y<l || r<x) return;
	if (x<=l && r<=y) return update(p,l,r,v,v,v,v);
	pushdown(p,l,r);
	modifyAdd(ls,l,mid,x,y,v);
	modifyAdd(rs,mid+1,r,x,y,v);
	pushup(p);
}
void modifyMin(int p,int l,int r,int x,int y,ll v)
{
	if (y<l || r<x || Max[p]<=v) return;
	if (x<=l && r<=y && Sec[p]<v) return update(p,l,r,v-Max[p],0,0,0);
	pushdown(p,l,r);
	modifyMin(ls,l,mid,x,y,v);
	modifyMin(rs,mid+1,r,x,y,v);
	pushup(p);
}
ll queryS(int p,int l,int r,int x,int y)
{
	if (y<l || r<x) return 0;
	if (x<=l && r<=y) return sum[p];
	pushdown(p,l,r);
	return queryS(ls,l,mid,x,y)+queryS(rs,mid+1,r,x,y);
}
ll queryA(int p,int l,int r,int x,int y)
{
	if (y<l || r<x) return LLONG_MIN;
	if (x<=l && r<=y) return Max[p];
	pushdown(p,l,r);
	return max(queryA(ls,l,mid,x,y),queryA(rs,mid+1,r,x,y));
}
ll queryB(int p,int l,int r,int x,int y)
{
	if (y<l || r<x) return LLONG_MIN;
	if (x<=l && r<=y) return MAX[p];
	pushdown(p,l,r);
	return max(queryB(ls,l,mid,x,y),queryB(rs,mid+1,r,x,y));
}
int main()
{
	freopen("P6242_9.in","r",stdin);
	freopen("Myout.out","w",stdout);
	read(n),read(q);
	for (int i=1;i<=n;++i) read(a[i]);
	build(1,1,n);
	for (int op,x,y,v;q--;)
	{
		scanf("%d",&op);
		if (op==1) read(x),read(y),read(v),modifyAdd(1,1,n,x,y,v);
		if (op==2) read(x),read(y),read(v),modifyMin(1,1,n,x,y,v);
		if (op==3) read(x),read(y),printf("%lld\n",queryS(1,1,n,x,y));
		if (op==4) read(x),read(y),printf("%lld\n",queryA(1,1,n,x,y));
		if (op==5) read(x),read(y),printf("%lld\n",queryB(1,1,n,x,y));
	} 
}
// 分Max，Sec两个标记打 
