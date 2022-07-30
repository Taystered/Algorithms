#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int inv2=500000004,inv6=166666668,mod=1000000007,N=200005;
int prime[N],g1[N],g2[N],sp1[N],sp2[N],tP,tV;
ll val[N],n;
bool vis[N];
unordered_map <ll,int> id;
int add(int x,int y) {return (x+=y)>=mod?x-mod:x;}
int sub(int x,int y) {return (x-=y)<0?x+mod:x;}
int mul(int x,int y) {return 1ll*x*y%mod;}
int mul(int x,int y,int z) {return mul(mul(x,y),z);}
int Mod(ll x) {return x>=mod?x%mod:x;}
int S1(ll x) {return x=Mod(x),mul(mul(x,x+1),inv2);}
int S2(ll x) {return x=Mod(x),mul(mul(x,x+1,2*x+1),inv6);}
int S(ll x,int y)
{
	if (prime[y]>=x) return 0;
	int now=id[x],res=sub(sub(g2[now],g1[now]),sub(sp2[y],sp1[y]));
	for (int i=y+1;i<=tP && 1ll*prime[i]*prime[i]<=x;++i)
	{
		ll prod=prime[i];
		for (int j=1;prod<=x;prod*=1ll*prime[i])
			res=add(res,mul(mul(Mod(prod),Mod(prod-1)),add(S(x/prod,i),j!=1))),j=0;
	}
	return res;
}
int main()
{
	scanf("%lld",&n);
	int Sqrt=sqrt(n);
	for (int i=2;i<=Sqrt;++i)
	{
		if (!vis[i])
		{
			prime[++tP]=i;
			sp1[tP]=add(sp1[tP-1],i);
			sp2[tP]=add(sp2[tP-1],mul(i,i));
		}
		for (int j=1;j<=tP && i*prime[j]<=Sqrt;++j)
		{
			vis[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		}
	}
	for (ll i=1;i<=n;i=n/(n/i)+1)
	{
		val[++tV]=n/i,id[n/i]=tV;
		g1[tV]=sub(S1(n/i),1);
		g2[tV]=sub(S2(n/i),1);
	}
	for (int i=1;i<=tP;++i)
		for (int j=1;j<=tV && 1ll*prime[i]*prime[i]<=val[j];++j)
		{
			int now=id[val[j]/prime[i]];
			g1[j]=sub(g1[j],mul(sub(g1[now],sp1[i-1]),prime[i]));
			g2[j]=sub(g2[j],mul(sub(g2[now],sp2[i-1]),prime[i],prime[i]));
		}
	printf("%d",add(S(n,0),1));
}
