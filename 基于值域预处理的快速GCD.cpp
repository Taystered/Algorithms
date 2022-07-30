#include<cstdio>
#include<cstring>
#define N 5005
#define M 1005
#define P 998244353
int n,t,a[N],b[N],f[(int)1e6+5][3],prime[(int)1e6],gcd[M][M];
bool vis[(int)1e6+5];
void swap(int &x,int &y) {x^=y^=x^=y;}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;++i) scanf("%d",&a[i]);
	for (int i=1;i<=n;++i) scanf("%d",&b[i]);
	f[1][0]=f[1][1]=f[1][2]=1;
	for (int i=2;i<=1e6;++i)
	{
		if (!vis[i]) vis[i]=1,prime[++t]=f[i][2]=i,f[i][0]=f[i][1]=1;
		for (int j=1,x;j<=t && prime[j]*i<=1e6;++j)
		{
			vis[x=prime[j]*i]=1;
			memcpy(f[x],f[i],sizeof f[x]);
			f[x][0]*=prime[j];
			if (f[x][0]>f[x][1]) swap(f[x][0],f[x][1]);
			if (f[x][1]>f[x][2]) swap(f[x][1],f[x][2]);
			if (i%prime[j]==0) break;
		}
	}
	for (int i=1;i<M;++i) gcd[i][0]=i;
	for (int i=1;i<M;++i) for (int j=1;j<=i;++j)
		gcd[i][j]=gcd[j][i]=gcd[j][i%j];
	for (int i=1;i<=n;++i)
	{
		int tot=0;
		for (int j=1,k=1;j<=n;++j)
		{
			k=1ll*k*i%P;
			int x=a[i],y=b[j],ans=1;
			for (int i=0;i<3;++i)
			{
				int now=1;
				if (f[x][i]>=M && y%f[x][i]==0) now=f[x][i];
				if (f[x][i]<M) now=gcd[f[x][i]][y%f[x][i]];
				y/=now,ans=1ll*ans*now%P;
			}
			tot=(tot+1ll*k*ans%P)%P;
		}
		printf("%d\n",tot);
	}
}
