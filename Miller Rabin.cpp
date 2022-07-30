#include<cstdio>
#define ll long long
int base[9]={2,3,5,7,11,13,17,19,61};
ll d,x,n;
int t;
ll times(ll x,ll y,ll p)
{
	ll res=0;
	for (;y;y>>=1,x=(x<<1)%p)
		if (y&1) res=(res+x)%p;
	return res;
}
ll pow(ll x,ll y,ll p)
{
	ll res=1;
	for (;y;y>>=1,x=times(x,x,p))
		if (y&1) res=times(res,x,p);
	return res;
}
int main()
{
	while (scanf("%lld",&n)!=EOF)
	{
		for (int i=0;i<9;++i) if (base[i]==n) goto yes;
		if (n==1) goto no;
		d=n-1,t=0;
		while (!(d&1)) ++t,d>>=1;
		for (int i=0;i<9;++i)
		{
			x=pow(base[i],d,n);
			for (int j=1;j<=t;++j)
			{
				if (times(x,x,n)==1 && x!=1 && x!=n-1) goto no;
				x=times(x,x,n);
			}
			if (x!=1) goto no;
		}
		yes:puts("Y");
		continue;
		no:puts("N");
	}
	return 0;
}
