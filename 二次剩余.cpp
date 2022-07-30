#include<bits/stdc++.h>
using namespace std;
int n,mod,T,a,Sqr,Answer;
mt19937 Rand(20060821);
int add(int x,int y) {return (x+=y)>=mod?x-mod:x;}
int mul(int x,int y) {return 1ll*x*y%mod;}
int mul(int x,int y,int z) {return mul(x,mul(y,z));}
struct Complex
{
	int x,y;
	Complex (int X=0,int Y=0) {x=X,y=Y;}
};
Complex mul(Complex x,Complex y)
{
	return Complex(add(mul(x.x,y.x),mul(Sqr,x.y,y.y)),add(mul(x.x,y.y),mul(x.y,y.x)));
}
template <typename Name> Name fastpow(Name x,int y)
{
	auto res=x;
	for (--y;y;y>>=1,x=mul(x,x))
		if (y&1) res=mul(res,x);
	return res;
}
bool check(int x) {return fastpow(x,(mod-1)>>1)==1;}
int main()
{
	freopen("cornelia.in","r",stdin);
	for (scanf("%d",&T);T--;)
	{
		scanf("%d%d",&n,&mod);
		if (n==0)
		{
			puts("0");
			continue;
		}
		if (check(n))
		{
			for (;!(a=Rand()%mod) || check(add(mul(a,a),mod-n)););
			Sqr=add(mul(a,a),mod-n);
			Answer=fastpow(Complex(a,1),(mod+1)>>1).x;
			Answer=min(Answer,mod-Answer);
			printf("%d %d\n",Answer,mod-Answer);
		}
		else puts("Hola!");
	}
}
