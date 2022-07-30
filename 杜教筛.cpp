#include<cstdio>
#include<cstring>
#define L 2000001
using namespace std;
int mu[L],prime[L],f[L],T,t;
long long phi[L],g[L],n;
bool vis[L];
long long solvemu(long long x)
{
	if (x<L) return mu[x];
	if (f[n/x]) return f[n/x];
	long long res=1;
	for (int l=2,r;l<=x;l=r+1)
		r=x/(x/l),res-=(r-l+1)*solvemu(x/l);
	return f[n/x]=res;
}
long long solvephi(long long x)
{
	if (x<L) return phi[x];
	if (g[n/x]) return g[n/x];
	long long res=x*(x+1)/2;
	for (int l=2,r;l<=x;l=r+1)
		r=x/(x/l),res-=(r-l+1)*solvephi(x/l);
	return g[n/x]=res;
}
int main()
{
	mu[1]=phi[1]=1;
	for (int i=2;i<L;++i)
	{
		if (!vis[i]) prime[++t]=i,mu[i]=-1,phi[i]=i-1;
		for (int j=1;j<=t && prime[j]*i<L;++j)
		{
			vis[prime[j]*i]=1;
			if (i%prime[j]==0)
			{
				phi[i*prime[j]]=phi[i]*prime[j];
				break;
			}
			else 
			{
				mu[prime[j]*i]=-mu[i];
				phi[prime[j]*i]=phi[prime[j]]*phi[i];
			}	
		}
	}
	for (int i=2;i<L;++i) mu[i]+=mu[i-1],phi[i]+=phi[i-1];
	for (scanf("%d",&T);T--;) 
	{
		scanf("%lld",&n);
		memset(f,0,sizeof(f)),memset(g,0,sizeof(g));
		printf("%lld %lld\n",solvephi(n),solvemu(n));
	}
}
