#include<cstdio>
int f(int a,int b,int c,int n)
{
	if (a>=c) return f(a%c,b,c,n)+(a/c)*n*(n+1)/2;
	if (b>=c) return f(a,b%c,c,n)+(b/c)*(n+1);
	if (!a) return 0;
	return (a*n+b)/c*n-f(c,c-b-1,a,(a*n+b)/c-1);
}
int main()
{
	//freopen("similar_gcd.in","r",stdin);
	int a,b,c,n;
	scanf("%d%d%d%d",&a,&b,&c,&n); //ai+b
	printf("%d",f(a,b,c,n));
} 
