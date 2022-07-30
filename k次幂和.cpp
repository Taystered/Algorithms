#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7,N=1e6+5;
int fact[N],ifact[N],pre[N],suf[N],power[N],prime[N],n,k,t,T,sum,ans;
bool vis[N];
int add(int x,int y) {return (x+=y)>=mod?x-mod:x;}
int mul(int x,int y) {return 1ll*x*y%mod;}
int mul(list <int> l) {int res=1; for (int x:l) res=mul(res,x); return res;}
int Mod(int x) {return x<0?x+mod:x;}
int fastpow(int x,int y)
{
	int res=1;
	for (;y;y>>=1,x=mul(x,x))
		if (y&1) res=mul(res,x);
	return res;
}
int main()
{
	scanf("%d%d",&n,&k),T=k+2;
	for (int i=2;i<=T;++i)
	{
		if (!vis[i]) prime[++t]=i,power[i]=fastpow(i,k);
		for (int j=1;j<=t && i*prime[j]<=T;++j)
		{
			vis[i*prime[j]]=1;
			power[i*prime[j]]=mul(power[i],power[prime[j]]);
			if (i%prime[j]==0) break;
		}
	}
	fact[0]=pre[0]=suf[T+1]=power[1]=1;
	for (int i=1;i<=T;++i) fact[i]=mul(fact[i-1],i),pre[i]=mul(pre[i-1],n-i);
	ifact[T]=fastpow(fact[T],mod-2);
	for (int i=T;i;--i) ifact[i-1]=mul(ifact[i],i),suf[i]=mul(suf[i+1],n-i);
	for (int i=1;i<=T;++i)
		sum=add(sum,power[i]),ans=add(ans,Mod(mul({sum,pre[i-1],suf[i+1],ifact[i-1],ifact[T-i],(T-i)&1?-1:1})));
	printf("%d",ans);
}
