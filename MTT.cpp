#include<cmath>
#include<cstdio>
#include<algorithm>
#define double long double
using namespace std;
const int N=1e5+5;
const double Pi=acos(-1);
int n,m,mod,limit,c[N<<1],rev[N<<2];
struct complex
{
	double x,y;
	complex(double X=0,double Y=0) : x(X),y(Y) {}
	friend complex operator + (complex x,complex y)
		{return complex(x.x+y.x,x.y+y.y);}
	friend complex operator - (complex x,complex y)
		{return complex(x.x-y.x,x.y-y.y);}
	friend complex operator * (complex x,complex y)
		{return complex(x.x*y.x-x.y*y.y,x.x*y.y+x.y*y.x);}
} a0[N<<2],a1[N<<2],b[N<<2];
void FFT(complex *a,double inv)
{
	for (int i=0;i<limit;++i)
		if (i<rev[i]) swap(a[i],a[rev[i]]);
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
	freopen("P4245_11.in","r",stdin);
	freopen("My.out","w",stdout);
	scanf("%d%d%d",&n,&m,&mod),++n,++m;
	int B=sqrt(mod);
	for (int i=0,x;i<n;++i)
		scanf("%d",&x),x%=mod,a1[i].x=x/B,a0[i].x=x%B;
	for (int i=0,x;i<m;++i)
		scanf("%d",&x),x%=mod,b[i].y=x/B,b[i].x=x%B;
	for (limit=1;limit<n+m;limit<<=1);
	for (int i=0;i<limit;++i) rev[i]=(rev[i>>1]>>1)|(i&1?limit>>1:0);
	FFT(a0,1),FFT(a1,1),FFT(b,1);
	for (int i=0;i<limit;++i) a0[i]=a0[i]*b[i];
	for (int i=0;i<limit;++i) a1[i]=a1[i]*b[i];
	FFT(a0,-1),FFT(a1,-1);
	for (int i=0;i<limit;++i)
		a0[i].x=((long long)(a0[i].x/limit+0.5)%mod+mod)%mod,
		a0[i].y=((long long)(a0[i].y/limit+0.5)%mod+mod)%mod,
		a1[i].x=((long long)(a1[i].x/limit+0.5)%mod+mod)%mod,
		a1[i].y=((long long)(a1[i].y/limit+0.5)%mod+mod)%mod;
	for (int i=0;i<n+m-1;++i)
		printf("%d ",((long long)a0[i].x+(long long)(a0[i].y+a1[i].x)*B%mod+(long long)a1[i].y*B%mod*B%mod)%mod);
}
