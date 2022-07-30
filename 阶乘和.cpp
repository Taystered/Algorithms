#include<cstdio>
#define K 1000005
#define P 1000000007
#define ll long long
ll n,k,s,ans,f[K],pl[K],pr[K];
ll pow(ll x,ll y)
{
	ll res=1;
	for (;y;y>>=1,x=x*x%P)
		if (y&1) res=res*x%P;
	return res;
}
int main()
{
	freopen("hey.in","r",stdin);
	scanf("%lld%lld",&n,&k);
	pl[0]=pr[k+3]=f[0]=1;
	for (int i=1;i<=k+2;++i) pl[i]=pl[i-1]*(n-i)%P;
	for (int i=k+2;i;--i) pr[i]=pr[i+1]*(n-i)%P;
	for (int i=1;i<=k+2;++i) f[i]=f[i-1]*i%P;
	for (int i=1;i<=k+2;++i) (s+=pow(i,k))%=P,(ans+=s*pl[i-1]%P*pr[i+1]%P*pow(f[i-1]*f[k-i+2]%P*((k-i)&1?-1:1),P-2))%=P;
	printf("%lld",(ans+P)%P);
}
