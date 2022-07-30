#include<cmath>
#include<cstdio>
#include<algorithm>
#define N 1000005
using namespace std;
double Pi=acos(-1);
int n,m,limit,rev[N<<2];
struct complex
{
	double x,y;
	complex(double X=0,double Y=0) {x=X,y=Y;}
	complex operator + (complex z) {return complex(x+z.x,y+z.y);}
	complex operator - (complex z) {return complex(x-z.x,y-z.y);}
	complex operator * (complex z) {return complex(x*z.x-y*z.y,x*z.y+y*z.x);}
} a[N<<2];
void FFT(complex *a,double inv)
{
	for (int i=0;i<limit;++i)
	{
		rev[i]=(rev[i>>1]>>1)|(i&1?limit>>1:0);
		if (i<rev[i]) swap(a[i],a[rev[i]]);
	}
	for (int k=1;k<limit;k<<=1)
	{
		complex w(cos(Pi/k),inv*sin(Pi/k));
		for (int i=0;i<limit;i+=k<<1)
		{
			complex now(1,0);
			for (int j=0;j<k;++j)
			{
				complex x=a[i|j],y=a[i|j|k]*now;
				a[i|j]=x+y,a[i|j|k]=x-y,now=now*w;
			}
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<=n;++i) scanf("%lf",&a[i].x);
	for (int i=0;i<=m;++i) scanf("%lf",&a[i].y); 
	for (limit=1;limit<=(max(n,m)<<1);limit<<=1);
	FFT(a,1);
	for (int i=0;i<=limit;++i) a[i]=a[i]*a[i];
	FFT(a,-1);
	for (int i=0;i<=n+m;++i) printf("%d ",(int)(a[i].y/limit*0.5+0.5));
}
