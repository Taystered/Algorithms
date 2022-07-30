#include<bits/stdc++.h>
using namespace std;
double a;
double f(double x) {return pow(x,a/x-x);}
double calc(double l,double r) {return (r-l)/6*(f(l)+f(r)+4*f((l+r)*0.5));}
double solve(double l,double r,double Eps)
{
	double mid=(l+r)*0.5,
		now=calc(l,r),
		nowL=calc(l,mid),
		nowR=calc(mid,r);
	if (fabs(now-nowL-nowR)<Eps*15)
		return nowL+nowR+(nowL+nowR-now)/15.0;
	return solve(l,mid,Eps*0.5)+solve(mid,r,Eps*0.5);
}
int main()
{
//	freopen("sleep.in","r",stdin);
	scanf("%lf",&a);
	if (a<0) return puts("orz"),0;
	printf("%.5f",solve(1e-6,15,1e-6));
}
