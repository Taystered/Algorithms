#include<cstdio>
#define N 200005
#define P 167772161
int a[N<<2],b[N<<2],fact[N],ifact[N],rev[N<<2],n,limit=1,bit;
int pow(int x,int y)
{
	int res=1;
	for (;y;y>>=1,x=1ll*x*x%P)
		if (y&1) res=1ll*res*x%P;
	return res;
}
void swap(int &x,int &y,int temp=0) {temp=x,x=y,y=temp;}
void NTT(int *a,int op)
{
	for (int i=0;i<limit;++i)
		if (i<rev[i]) swap(a[i],a[rev[i]]);
	for (int k=1;k<limit;k<<=1)
	{
		int E=pow(3,(P-1)/(k<<1));
		if (!~op) E=pow(E,P-2);
		for (int i=0;i<limit;i+=(k<<1))
			for (int j=0,now=1;j<k;++j,now=1ll*now*E%P)
			{
				int x=a[i+j],y=1ll*a[i+j+k]*now%P;
				a[i+j]=(x+y)%P,a[i+j+k]=(x-y+P)%P;
			}
	}
}
int main()
{
	scanf("%d",&n);
	for (int i=fact[0]=1;i<=n;++i) fact[i]=1ll*fact[i-1]*i%P;
	ifact[n]=pow(fact[n],P-2);
	for (int i=n-1;~i;--i) ifact[i]=1ll*ifact[i+1]*(i+1)%P;
	for (int i=0;i<=n;++i)
	{
		a[i]=(i&1?P-1ll:1ll)*ifact[i]%P;
		b[i]=1ll*pow(i,n)*ifact[i]%P;
	}
	while (limit<=n+n) limit<<=1,++bit;
	for (int i=1;i<limit;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	NTT(a,1),NTT(b,1);
	for (int i=0;i<limit;++i) a[i]=1ll*a[i]*b[i]%P;
	NTT(a,-1);
	for (int i=0,I=pow(limit,P-2);i<=n;++i) 
		printf("%lld ",1ll*a[i]*I%P);
}
