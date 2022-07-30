#include<cstdio>
#define N 1000005
int n,m,t,d,mu[N],s[N],prime[100000];
long long ans;
bool vis[N];
int main()
{
//	freopen("gcd.in","r",stdin);
	scanf("%d%d",&n,&m);
	if (n>m) n^=m,m^=n,n^=m;
	mu[1]=s[1]=1;
	for (int i=2;i<=1e6;++i)
	{
		if (!vis[i]) prime[++t]=i,mu[i]=-1;
		for (int j=1;j<=t && prime[j]*i<=1e6;++j)
		{
			vis[prime[j]*i]=1;
			if (i%prime[j]==0) break; 
			else mu[i*prime[j]]=-mu[i];
		}
		s[i]=s[i-1]+mu[i];
	}
	for (int i=1;i<=d;++i)
	{
		int nn=n/d,nm=m/d;
		for (int l=1,r;l<=nn;l=r+1)
		{
			r=min(nn/(nn/l),nm/(nm/l));
			ans=(ans+1ll*(s[r]-s[l-1])*(nn/l)*(nm/l)%mod)%mod;
		}
	}
	printf("%d\n",ans);
	return 0;
}
