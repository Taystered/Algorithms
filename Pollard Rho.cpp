#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int Base[5]={2,7,13,61,97};
int t,T;
ll n,ans;
mt19937 Rand(time(NULL));
void read(auto &x)
{
	char ch=getchar(); x=0;
	for (;!isdigit(ch);ch=getchar());
	for (;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
}
ll add(ll x,ll y,ll p) {return (x+=y)>=p?x-p:x;}
ll mul(ll x,ll y,ll p) {return ((x*y-(ll)((long double)x*y/p+0.5)*p)%p+p)%p;}
ll fastpow(ll x,ll y,ll p)
{
	ll res=1;
	for (;y;y>>=1,x=mul(x,x,p))
		if (y&1) res=mul(res,x,p);
	return res;
}
bool Miller_Rabin(ll x)
{
	if (x==1) return 0;
	for (int d:Base) if (x%d==0) return d==x;
	ll k=x-1,bit=0;
	for (;!(k&1);k>>=1) ++bit;
	for (int d:Base)
	{
		if (fastpow(d,x-1,x)^1) return 0;
		for (ll T=bit,v=fastpow(d,k,x);T--;v=mul(v,v,x))
			if (mul(v,v,x)==1 && v^1 && v^(x-1)) return 0;
	}
	return 1;
}
ll gcd(ll x,ll y) {return y?gcd(y,x%y):x;}
ll Pollard_rho(ll x)
{
	ll C=Rand()%x,t1=Rand()%x,t2=add(mul(t1,t1,x),C,x),val=abs(t1-t2);
    for (int step=1;val;++step)
	{
		if ((!(step&127) || step<=127) && gcd(val,x)>1)
			return gcd(val,x);
        t1=add(mul(t1,t1,x),C,x);
        t2=add(mul(t2,t2,x),C,x);
		t2=add(mul(t2,t2,x),C,x);
		val=mul(val,abs(t1-t2),x);
    }
    return x;
}
void find(ll x)
{
	if (x==1) return;
	if (Miller_Rabin(x)) return void(ans=max(ans,x));
	for (;;)
	{
		ll v=Pollard_rho(x);
		if (v<x) return find(v),find(x/v);
	}
}
int main()
{
	freopen("P4718_1.in","r",stdin);
	for (read(T);T--;ans=0)
	{
		read(n),find(n);
		ans^n?printf("%lld\n",ans):puts("Prime");
	}
	return 0;
}
