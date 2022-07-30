#include<cstdio>
#include<algorithm>
#define M 110
#define N 1000005
#define P 998244353
using namespace std; 
int fact[N<<1],ifact[N<<1],a[M],b[M],d[M][M],n,m,T,ans=1;
int inv(int x)
{
	int res=1;
	for (int y=P-2;y;y>>=1,x=1ll*x*x%P)
		if (y&1) res=1ll*res*x%P;
	return res;
}
int C(int x,int y)
{
	return 1ll*fact[x]*ifact[y]%P*ifact[x-y]%P;
}
int main()
{
	for (int i=fact[0]=1;i<N*2;++i) fact[i]=1ll*fact[i-1]*i%P;
	ifact[N*2-1]=inv(fact[N*2-1]);
	for (int i=N*2-1;i;--i) ifact[i-1]=1ll*ifact[i]*i%P;
	for (scanf("%d",&T);T--;ans=1)
	{
		scanf("%d%d",&n,&m);
		for (int i=1;i<=m;++i)
			scanf("%d%d",&a[i],&b[i]);
		for (int i=1;i<=m;++i) for (int j=1;j<=m;++j)
			d[i][j]=a[i]<=b[j]?C(b[j]-a[i]+n-1,n-1):0;
		for (int i=1;i<=m;++i)
		{
			for (int j=i+1;!d[i][i] && j<=m;++j)
				if (d[j][i]) swap(d[i],d[j]);
			for (int j=i+1;j<=m;++j)
			{
				int x=1ll*d[j][i]*inv(d[i][i])%P;
				for (int k=i;k<=m;++k)
					(d[j][k]-=1ll*d[i][k]*x%P-P)%=P;
			}
		}
		for (int i=1;i<=m;++i) ans=1ll*ans*d[i][i]%P;
		printf("%d\n",ans);
	}
}
