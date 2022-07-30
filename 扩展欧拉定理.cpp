#include<cstdio>
int a,b,m,Phi_m;
bool flag;
int GetPhi(int x)
{
	int res=1,v=x;
	for (int i=2;i*i<=v;++i) if (v%i==0)
	{
		res*=i-1,v/=i;
		for (;v%i==0;v/=i) res*=i;
	}
	if (v>1) res*=v-1;
	return res;
}
int fastpow(int x,int y)
{
	int res=1;
	for (;y;y>>=1,x=1ll*x*x%m)
		if (y&1) res=1ll*res*x%m;
	return res;
}
int gcd(int x,int y) {return y?gcd(y,x%y):x;}
int main()
{
	scanf("%d%d",&a,&m);
	Phi_m=GetPhi(m);
	char ch=getchar();
	for (;ch<'0' || '9'<ch;ch=getchar());
	for (;'0'<=ch && ch<='9';ch=getchar())
		b=((b<<1)+(b<<3)+(ch^48)),(b>=Phi_m) && (b%=Phi_m,flag=1);
	if (gcd(a,m)==1) flag=0;
	printf("%d",flag?fastpow(a,b+Phi_m):fastpow(a,b));
} 
