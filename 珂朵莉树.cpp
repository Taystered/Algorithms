#include<set>
#include<cstdio>
#include<vector>
#include<algorithm>
#define ll long long
using namespace std;
int n,m,seed,vmax;
struct Node
{
	int l,r;
	mutable ll v;
	Node (int L=0,int R=0,ll V=0) : l(L),r(R),v(V) {}
	bool operator < (const Node &x) const {return l<x.l;}
};
set <Node> s;
int rand()
{
	int ret=seed;
	seed=(seed*7ll+13)%1000000007;
	return ret;
}
int fastpow(int x,int y,int mod)
{
	int res=1;
	for (;y;y>>=1,x=1ll*x*x%mod)
		if (y&1) res=1ll*res*x%mod;
	return res;
}
set<Node>::iterator split(int x)
{
	auto it=s.lower_bound(Node(x));
	if (it!=s.end() && it->l==x) return it;
	--it;
	int l=it->l,r=it->r; ll v=it->v;
	s.erase(it),s.insert(Node(l,x-1,v));
	return s.insert(Node(x,r,v)).first;
}
void assign(int l,int r,int v)
{
	auto itr=split(r+1),itl=split(l);
	s.erase(itl,itr),s.insert(Node(l,r,v));
}
void add(int l,int r,int v)
{
	auto itr=split(r+1),itl=split(l);
	for (auto it=itl;it!=itr;++it) it->v+=v;
}
ll kth(int l,int r,int k)
{
	auto itr=split(r+1),itl=split(l);
	vector <pair<ll,int>> now;
	for (auto it=itl;it!=itr;++it) now.emplace_back(it->v,it->r-it->l+1);
	sort(now.begin(),now.end());
	for (auto x:now) if ((k-=x.second)<=0) return x.first;
}
ll query(int l,int r,int mod,int x)
{
	auto itr=split(r+1),itl=split(l); int res=0;
	for (auto it=itl;it!=itr;++it)
		(res+=1ll*(it->r-it->l+1)*fastpow((it->v)%mod,x,mod)%mod)%=mod;
	return res;
}
int main()
{
	freopen("Chothlly.love","r",stdin);
	scanf("%d%d%d%d",&n,&m,&seed,&vmax);
	for (int i=1;i<=n;++i)
		s.insert(Node(i,i,rand()%vmax+1));
	for (int op,l,r,x,y;m--;)
	{
		op=rand()%4+1,l=rand()%n+1,r=rand()%n+1;
		if (l>r) l^=r^=l^=r;
		if (op==1) add(l,r,rand()%vmax+1);
		if (op==2) assign(l,r,rand()%vmax+1);
		if (op==3) printf("%lld\n",kth(l,r,rand()%(r-l+1)+1));
		if (op==4) printf("%lld\n",query(l,r,rand()%vmax+1,rand()%vmax+1));
	}
} 
