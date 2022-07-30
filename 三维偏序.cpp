#include<cstdio>
#include<algorithm>
#define N 100010
#define get Get
using namespace std;
int a[N],b[N],c[N],p[N],ans[N],s[N],v[N],get[N],f[2*N],n,m,t=1;
bool cmp(int x,int y) {return (a[x]<a[y] || (a[x]==a[y] && (b[x]<b[y] || (b[x]==b[y] && c[x]<c[y]))));}
void modify(int x,int y) {for (;x<=m;x+=x&-x) f[x]+=y;}
int query(int x) {return x?f[x]+query(x-(x&-x)):0;}
void cdq(int l,int r)
{
	if (l==r) return;
	int mid=l+r>>1,i=l,j=mid+1,k=l;
	cdq(l,mid),cdq(mid+1,r);
	while (i<=mid || j<=r)
	{
		if (i<=mid && (j>r || b[p[i]]<=b[p[j]])) modify(c[p[i]],v[p[i]]),get[k++]=p[i++];
		else s[p[j]]+=query(c[p[j]]),get[k++]=p[j++];
	}
	for (int i=l;i<=mid;++i) modify(c[p[i]],-v[p[i]]);
	for (int i=l;i<=r;++i) p[i]=get[i];
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;v[i++]=1) scanf("%d%d%d",&a[i],&b[i],&c[i]),p[i]=i;
	sort(p+1,p+n+1,cmp);
	for (int i=2;i<=n;++i)
	{
        int x=p[i],y=p[t];
        (a[x]^a[y] || b[x]^b[y] || c[x]^c[y])?p[++t]=x:++v[p[t]];
    }
	cdq(1,t);
	for (int i=1;i<=t;++i) ans[s[p[i]]+v[p[i]]-1]+=v[p[i]];
	for (int i=0;i<n;++i) printf("%d\n",ans[i]);
	return 0;
}
