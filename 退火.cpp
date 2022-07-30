#include<bits/stdc++.h>
#define N 15
#define M 2005
#define y1 kkksc03
#define min(x,y) (x<y?x:y)
#define max(x,y) (x>y?x:y)
using namespace std;
struct Node {int x,y,r;} a[N],b[M];
int n,m,maxR,sumX,sumY,Ans,ans;
double X,Y;
double sqr(double x) {return x*x;}
double dis(double x1,double y1,double x2,double y2) {return sqrt(sqr(x1-x2)+sqr(y1-y2));}
int calc(int x,int y)
{
	int res=0l; double r=maxR;
	for (int i=1;i<=n;++i) r=min(r,dis(x,y,a[i].x,a[i].y)-a[i].r);
	for (int i=1;i<=m;++i) if (dis(x,y,b[i].x,b[i].y)<=r) ++res;
	return res;
}
void SA()
{
	for (double T=3000;T>1e-10;T*=0.998)
	{
		double
			nowx=X+((rand()<<1)-RAND_MAX)*T,
			nowy=Y+((rand()<<1)-RAND_MAX)*T;
		int nowans=calc(nowx,nowy),delta=nowans-ans;
		if (delta>0 || exp(delta/sqrt(T))<rand()/RAND_MAX) X=nowx,Y=nowy,ans=nowans;
		Ans=max(Ans,nowans);
	}
}
int main()
{
//	freopen("boob.in","r",stdin);
	scanf("%d%d%d",&n,&m,&maxR);
	for (int i=1,x,y,r;i<=n;++i) scanf("%d%d%d",&x,&y,&r),a[i]=(Node){x,y,r};
	for (int i=1,x,y;i<=m;++i) scanf("%d%d",&x,&y),b[i]=(Node){x,y,0},sumX+=x,sumY+=y;
	X=sumX/m,Y=sumY/m,Ans=calc(X,Y);
	for (int T=12;T--;) SA();
	printf("%d",Ans);
}
