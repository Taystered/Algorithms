#include<cstdio>
int n,q,t[60];
long long a[60],ans;
void insert(long long x)
{
	for (int i=50;~i;--i) if (x>>i&1)
		x^=a[i]+=(!a[i])*x;
}
void rebuild()
{
	for (int i=50;~i;--i)
		for (int j=i-1;~j;--j)
			if (a[i]>>j&1 && a[j])
				a[i]^=a[j];
	t[0]=a[0]>0;
	for (int i=1;i<=50;++i)
		t[i]=t[i-1]+(a[i]>0);
}
int main()
{
	scanf("%d",&n);
	for (auto i=1ll,x=0ll;i<=n;++i)
		scanf("%lld",&x),insert(x);
	rebuild();
	scanf("%d",&q);
	for (;q--;ans=0)
	{
		long long x;
		scanf("%lld",&x);
		if (t[50]<n) --x;
		if (!x) goto print;
		if ((1ll<<t[50])<=x) ans=-1;
		else for (int i=50;~i;--i)
			if (a[i] && (1ll<<(t[i]-1))<=x) 
				ans^=a[i],x-=(1ll<<(t[i]-1));
		print:printf("%lld\n",ans);
	}
}
