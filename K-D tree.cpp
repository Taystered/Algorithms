#include<cmath>
#include<cstdio>
#include<algorithm>
#define N 200005
#define mid ((l+r)>>1)
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
#define sqr(x) ((x)*(x))
using namespace std;
int L[N],R[N],D[N],U[N],ls[N],rs[N],n;
long long ans=2e18;
struct node {long long x,y;} a[N];
bool cmpx(node x,node y) {return x.x<y.x;}
bool cmpy(node x,node y) {return x.y<y.y;}
int build(int l,int r)
{
	if (l>=r) return 0;
	double avx=0,avy=0,vax=0,vay=0;
	for (int i=l;i<=r;++i) avx+=1.0*a[i].x,avy+=1.0*a[i].y;
	avx/=1.0*(r-l+1),avy/=1.0*(r-l+1);
	for (int i=l;i<=r;++i)
		vax+=1.0*sqr(a[i].x-avx),
		vay+=1.0*sqr(a[i].y-avy);
	vax>vay?nth_element(a+l,a+mid,a+r+1,cmpx):
			nth_element(a+l,a+mid,a+r+1,cmpy);
	ls[mid]=build(l,mid-1),rs[mid]=build(mid+1,r);
	L[mid]=R[mid]=a[mid].x,D[mid]=U[mid]=a[mid].y;
	if (ls[mid])
		L[mid]=min(L[mid],L[ls[mid]]),R[mid]=max(R[mid],R[ls[mid]]),
		D[mid]=min(D[mid],D[ls[mid]]),U[mid]=max(U[mid],U[ls[mid]]);
	if (rs[mid])
		L[mid]=min(L[mid],L[rs[mid]]),R[mid]=max(R[mid],R[rs[mid]]),
		D[mid]=min(D[mid],D[rs[mid]]),U[mid]=max(U[mid],U[rs[mid]]);
	return mid;
}
long long dis(int x,int y)
{
	long long res=0;
	if (L[y]>a[x].x) res+=sqr(L[y]-a[x].x);
	if (R[y]<a[x].x) res+=sqr(a[x].x-R[y]);
	if (D[y]>a[x].y) res+=sqr(D[y]-a[x].y);
	if (U[y]<a[x].y) res+=sqr(a[x].y-U[y]);
	return res;
}
long long dis(node x,node y) {return sqr(x.x-y.x)+sqr(x.y-y.y);}
void query(int l,int r,int x)
{
	if (l>r) return;
	if (x^mid) ans=min(ans,dis(a[x],a[mid]));
	if (l==r) return;
	long long disl=dis(x,ls[mid]),disr=dis(x,rs[mid]);
	if (disl<ans && disr<ans)
		(disl<disr)?(query(l,mid-1,x),(disr<ans) && (query(mid+1,r,x),1)):
					(query(r,mid+1,x),(disl<ans) && (query(l,mid-1,x),1));
	else (disl<ans) && (query(l,mid-1,x),1),(disr<ans) && (query(mid+1,r,x),1);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;++i) 
		scanf("%lld%lld",&a[i].x,&a[i].y);
	build(1,n);
	for (int i=1;i<=n;++i) query(1,n,i);
	printf("%.4f",sqrt(ans));
}
