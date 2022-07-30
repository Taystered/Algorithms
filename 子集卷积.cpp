#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+9,N=25;
int n,a[N][1<<21],b[N][1<<21],c[N][1<<20];
int add(int x,int y) {return (x+=y)>=mod?x-mod:x;}
int sub(int x,int y) {return (x-=y)<0?x+mod:x;}
int mul(int x,int y) {return 1ll*x*y%mod;}
void FWT(int *a,int op)
{
	for (int k=1;k<(1<<n);k<<=1)
		for (int i=0;i<(1<<n);i+=k<<1)
			for (int j=0;j<k;++j)
				a[i+j+k]=~op?add(a[i+j+k],a[i+j]):sub(a[i+j+k],a[i+j]);
}
int main()
{
	freopen("P6097_1.in","r",stdin);
	freopen("My.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<(1<<n);++i)
		scanf("%d",&a[__builtin_popcount(i)][i]);
	for (int i=0;i<(1<<n);++i)
		scanf("%d",&b[__builtin_popcount(i)][i]);
	for (int i=0;i<=n;++i) FWT(a[i],1),FWT(b[i],1);
	for (int i=0;i<=n;++i) for (int j=0;j<=n;++j) if (i+j<=n)
		for (int k=0;k<(1<<n);++k) c[i+j][k]=add(c[i+j][k],mul(a[i][k],b[j][k]));
	for (int i=0;i<=n;++i) FWT(c[i],-1);
	for (int i=0;i<(1<<n);++i) printf("%d ",c[__builtin_popcount(i)][i]);
}
