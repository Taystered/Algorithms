#include<cstdio>
#define N 200005
#define ll long long
#define abs(x) (x>0?x:-(x))
#define max(x,y) (x>y?x:y)
ll a[N],d[N],f[N],res;
int n,T,ans;
void read(int &x)
{
	char ch=getchar(); x=0;
	for (;ch<'0' && '9'<ch;ch=getchar());
	for (;'0'<=ch && ch<='9';x=(x<<1)+(x<<3)+(ch^48),ch=getchar());
}
void read(ll &x)
{
	char ch=getchar(); x=0;
	for (;ch<'0' && '9'<ch;ch=getchar());
	for (;'0'<=ch && ch<='9';x=(x<<1)+(x<<3)+(ch^48),ch=getchar());
}
ll gcd(ll x,ll y) {return y?gcd(y,x%y):x;}
int main()
{
	for (read(T);T--;)
	{
		read(n);
		for (int i=1;i<=n;++i)
			read(a[i]),d[i-1]=abs(a[i]-a[i-1]);
		ans=n>1?d[1]>1:0;
		for (int l=1,r=1,mid=1;mid<n;mid=l=r)
		{
			for (f[l]=d[l];l>1 && f[l]>1;--l,f[l]=gcd(d[l],f[l+1]));
			for (r=mid,res=0;r<n && l<=mid;res=gcd(res,d[++r]))
			{
				for (;l<=mid && gcd(res,f[l])==1;) ++l;
				if (l<=mid) ans=max(ans,r-l+1);
			}
		}
		printf("%d\n",ans+1);
	}
}
