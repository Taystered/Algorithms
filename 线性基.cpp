#include<cstdio>
#include<algorithm>
#define LogV 60
using namespace std;
int n;
long long a[LogV],ans;
void insert(long long x)
{
	for (int i=50;~i;--i) if (x>>i&1)
		x^=a[i]+=(!a[i])*x;
}
int main()
{
	scanf("%d",&n);
	for (auto i=1ll,x=0ll;i<=n;++i)
		scanf("%lld",&x),insert(x);
	for (int i=50;~i;--i) 
		ans=max(ans,ans^a[i]);
	printf("%lld",ans);
}
