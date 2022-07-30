#include<cmath>
#include<cstdio>
#include<map>
#define min(x,y) (x<y?x:y)
using namespace std;
map <int,long long> f;
int a,b,p,k,ans=2147483647;
int fastpow(int x,long long y)
{
	int res=1;
	for (;y;y>>=1,x=1ll*x*x%p)
		if (y&1) res=1ll*res*x%p;
	return res;
}
int main()
{
	scanf("%d%d%d",&p,&a,&b);
	k=ceil(sqrt(p));
	for (int i=k;i;--i) 
		f[fastpow(a,1ll*i*k)]=1ll*i*k;
	for (int i=0,t=1;i<k;++i)
	{
		if (f[1ll*t*b%p]) 
			ans=min(ans,f[1ll*t*b%p]-i);
		t=1ll*t*a%p;
	}
	ans<2147483647?printf("%d",ans):puts("no solution");
}
