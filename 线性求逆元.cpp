#include<cstdio>
int inv[1<<20],mod;
int main()
{
	scanf("%d",&mod);
	inv[1]=1;
	for (int i=2;i<mod;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
}
