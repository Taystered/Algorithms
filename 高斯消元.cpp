#include<cstdio>
#include<algorithm>
#define N 110
double d[N][N];
int main()
{
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;++i) 
		for (int j=1;j<=n+1;++j)
			scanf("%lf",&d[i][j]);
	for (int x=1;x<=n;++x)
	{
		for (int i=x+1;!d[i][i] && i<=n;i++)
			if (d[i][x]) swap(d[x],d[i]);
		if (!d[x][x]) return puts("No Solution"),0;
		for (int i=1;i<=n;++i) if (i^x)
			for (int j=n+1;j>=x;--j)
				d[i][j]-=d[x][j]*d[i][x]/d[x][x];
	}
	for (int i=1;i<=n;++i) printf("%.2f\n",d[i][n+1]/d[i][i]);
}
