#include<bits/stdc++.h>
#define min(x,y) (x<y?x:y)
using namespace std;
const int N=1e7+5,SIZE=1e6;
int n,t,prime[N],ans[N];
bool vis[N];
void init(int n)
{
	n=min(n,SIZE);
	prime[++t]=2;
	for (int i=3;i<=n;i+=2)
	{
		if (!vis[i]) prime[++t]=i;
		for (int j=1;j<=t && i*prime[j]<=n;++j)
		{
			vis[i*prime[j]]=1;
			if (i%prime[j]==0) break;
		}
	}
}
bool check(int x)
{
	if (x<2) return 0;
	for (int i=1;i<=t && prime[i]<x;++i)
		if (x%prime[i]==0) return 0;
	return 1;
}
void divide(int x)
{
	int cnt=0;
	for (int i=1;i<=t && prime[i]<=x;++i)
		for (;x%prime[i]==0;x/=prime[i])
			ans[++cnt]=prime[i];
	if (x>1) ans[++cnt]=x;
	printf("Prime Factorization : ");
	for (int i=1;i<cnt;++i) printf("%d*",ans[i]);
	printf("%d\n",ans[cnt]);
}
void sigma(int x)
{
	int res=1,cnt;
	for (int i=1;i<=t && prime[i]<=x;++i) if (x%prime[i]==0)
	{
		for (cnt=0;x%prime[i]==0;x/=prime[i]) ++cnt;
		res*=cnt+1;
	}
	if (x>1) res<<=1;
	printf("The Number of Factors : %d\n",res);
}
void pre(int x)
{
	for (;--x;) if (check(x)) break;
	printf("Previous Prime : %d\n",x);
}
void suf(int x)
{
	for (;++x;) if (check(x)) break;
	printf("Next Prime : %d\n",x);
}
int Num()
{
	
}
int main()
{
	init(1e3);
	int Gap=0;
	for (int i=2;i<=t;++i)
		Gap=max(Gap,prime[i]-prime[i-1]); 
	printf("%d",Gap);
}
