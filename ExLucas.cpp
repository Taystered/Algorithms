#include<cstdio>
#define ll long long
ll n,m,p,t,a[20],b[20];
ll fastpow(ll x,ll y,ll p)
{
	ll res=1;
	for (;y;y>>=1,x=x*x%p)
		if (y&1) res=res*x%p;
	return res;
}
void exgcd(ll a,ll b,ll &x,ll &y)
{
	if (!b) return (void)(x=1,y=0);
	exgcd(b,a%b,y,x),y-=a/b*x;
}
ll inv(ll a,ll p)
{
	ll x,y;
	exgcd(a,p,x,y);
	return (x%p+p)%p;
}
ll fact(ll n,ll p,ll pk)
{
	if (!n) return 1;
	ll res=1;
	for (ll i=1;i<pk;++i) if (i%p) (res*=i)%=pk;
	res=fastpow(res,n/pk,pk);
	for (ll i=1;i<=n%pk;++i) if (i%p) (res*=i)%=pk;
	return res*fact(n/p,p,pk)%pk;
}
ll C(ll n,ll m,ll p,ll pk)
{
	if (n<m) return 0;
	ll f1=fact(n,p,pk),f2=fact(m,p,pk),f3=fact(n-m,p,pk),cnt=0;
	for (ll i=n;i;i/=p) cnt+=i/p;
	for (ll i=m;i;i/=p) cnt-=i/p;
	for (ll i=n-m;i;i/=p) cnt-=i/p;
	return f1*inv(f2,pk)%pk*inv(f3,pk)%pk*fastpow(p,cnt,pk)%pk; 
}
ll CRT()
{
	ll res=0,M=1;
	for (int i=1;i<=t;++i) M*=b[i];
	for (int i=1;i<=t;++i) (res+=a[i]*(M/b[i])*inv(M/b[i],b[i]))%=M;
	return res;
}
int exlucas(ll n,ll m,int p)
{
	int x=p,tmp;
	for (int i=2;i*i<=x;++i) if (x%i==0)
	{
		for (tmp=1;x%i==0;) tmp*=i,x/=i;
		a[++t]=C(n,m,i,tmp),b[t]=tmp;
	}
	if (x>1) a[++t]=C(n,m,x,x),b[t]=x;
	return CRT();
}
int main()
{
	scanf("%lld%lld%d",&n,&m,&p);
	printf("%lld",exlucas(n,m,p));
}
