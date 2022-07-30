#include<cstdio>
#define N 100005
#define ll long long
int n;
ll a[N],b[N],M=1,ans;
void exgcd(ll a,ll b,ll &x,ll &y)
{
	if (b==0) return (void)(x=1,y=0);
	exgcd(b,a%b,y,x),y-=a/b*x;
}
int main()
{
	freopen("CRT.in","r",stdin);
	scanf("%d",&n);
	for (int i=1;i<=n;++i) 
		scanf("%lld%lld",&a[i],&b[i]),M*=1ll*a[i];
	for (int i=1;i<=n;++i)
	{
		ll x,y;
		exgcd(M/a[i],a[i],x,y);
		(ans+=M/a[i]*(x<0?x+a[i]:x)*b[i])%=M;
	}
	printf("%lld",ans);
}
