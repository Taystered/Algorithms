#include<cstdio>
#include<algorithm>
#define N 1000005
#define mod 998244353
using namespace std;
int a[N<<2],b[N<<2],rev[N<<2],n,m,limit,ilimit;
int add(const int &x,const int &y) {return x+y>=mod?x+y-mod:x+y;}
int sub(const int &x,const int &y) {return x-y<0?x-y+mod:x-y;}
int mul(const int &x,const int &y) {return 1ll*x*y%mod;}
int fastpow(int x,int y)
{
	int res=1;	
	for (;y;y>>=1,x=mul(x,x))
		if (y&1) res=mul(res,x);
	return res;
}
void NTT(int *a,int op)
{
	for (int i=0;i<limit;++i)
		if (i<rev[i]) swap(a[i],a[rev[i]]);
	for (int k=1;k<limit;k<<=1)
	{
		int w=fastpow(3,(mod-1)/(k<<1));
		if (!~op) w=fastpow(w,mod-2);
		for (int i=0;i<limit;i+=k<<1)
			for (int j=0,now=1;j<k;++j)
			{
				int x=a[i+j],y=mul(now,a[i+j+k]);
				a[i+j]=add(x,y),a[i+j+k]=sub(x,y),now=mul(now,w);
			}
	}
	if (!~op) for (int i=0;i<limit;++i) a[i]=mul(a[i],ilimit);
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<=n;++i) scanf("%d",&a[i]);
	for (int i=0;i<=m;++i) scanf("%d",&b[i]);
	for (limit=1;limit<=n+m;limit<<=1); limit<<=1;
	ilimit=fastpow(limit,mod-2);
	for (int i=0;i<limit;++i) rev[i]=(rev[i>>1]>>1)|(i&1?limit>>1:0);
	NTT(a,1),NTT(b,1);
	for (int i=0;i<limit;++i) a[i]=1ll*a[i]*b[i]%mod;
	NTT(a,-1);
}
