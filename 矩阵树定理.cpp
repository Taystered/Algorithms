#include<cstdio>
#include<algorithm>
#define N 305
#define P 1000000007
int K[N][N],n,m,op;
void inc(int &x,int v)
{
	x+=v;
	if (x>P) x-=P;
	if (x<0) x+=P;
}
int pow(int x,int y)
{
	int res=1;
	for (;y;y>>=1,x=1ll*x*x%P)
		if (y&1) res=1ll*res*x%P;
	return res;
}
int det(int a[][N])
{
	int res=1;
	for (int i=2;i<=n;++i)
	{
		for (int j=i+1;!a[i][i] && j<=n;++j)
			if (a[j][i]) std::swap(a[i],a[j]),res*=-1;
		int inv=pow(a[i][i],P-2);
		for (int j=i+1;j<=n;++j)	
			for (int k=i,x=1ll*a[j][i]*inv%P;k<=n;++k)
				inc(a[j][k],-1ll*x*a[i][k]%P);
		res=1ll*res*a[i][i]%P;
	}
	return res;
}
int main()
{
	freopen("P6178_1.in","r",stdin);
	scanf("%d%d%d",&n,&m,&op);
	for (int i=1,u,v,w;i<=m;++i)
	{
		scanf("%d%d%d",&u,&v,&w);
		if (op==0) inc(K[u][v],-w),inc(K[v][u],-w),inc(K[u][u],w),inc(K[v][v],w);
		if (op==1) inc(K[u][v],-w),inc(K[v][v],w);
	}
	printf("%d",(det(K)+P)%P);
}
