#include<cmath>
#include<cstdio>
#include<algorithm>
#define N 140005
using namespace std;
int color[N],belong[N],l[N],r[N],p[N],a[N],b[N],tot[1<<20],last[N],ans[N],n,m,tQ,tR,res;
void swap(int &x,int &y) {x^=y^=x^=y;}
bool cmp(int x,int y)
{
	if (belong[l[x]]^belong[l[y]]) return belong[l[x]]<belong[l[y]];
	if (belong[r[x]]^belong[r[y]]) return belong[r[x]]<belong[r[y]];
	return last[x]<last[y];
}
void inc(int x) {if (++tot[color[x]]==1) ++res;}
void dec(int x) {if (--tot[color[x]]==0) --res;}
void change(int x,int i)
{
	if (l[p[i]]<=a[x] && a[x]<=r[p[i]])
	{
		if (--tot[color[a[x]]]==0) --res;
		if (++tot[b[x]]==1) ++res;
	}
	swap(color[a[x]],b[x]);
}
int main()
{
	freopen("data13.in","r",stdin);
	freopen("data.out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%d",&color[i]);
	scanf("\n");
	for (int i=1;i<=m;++i)
	{
		char ch=getchar();
		if (ch=='Q') last[++tQ]=tR,scanf("%d%d\n",&l[p[tQ]=tQ],&r[tQ]);
		if (ch=='R') ++tR,scanf("%d%d\n",&a[tR],&b[tR]);
	}
	int len=pow(n,2.0/3);
	for (int i=1;i<=n;++i) belong[i]=i/len+1;
	sort(p+1,p+tQ+1,cmp);
	for (int i=1,L=1,R=0,k=0;i<=n;++i)
	{
		while (L<l[p[i]]) dec(L++);
		while (l[p[i]]<L) inc(--L);
		while (R<r[p[i]]) inc(++R);
		while (r[p[i]]<R) dec(R--);
		while (last[p[i]]<k) change(k--,i);
		while (k<last[p[i]]) change(++k,i);
		ans[p[i]]=res;
	}
	for (int i=1;i<=tQ;++i) printf("%d\n",ans[i]);
}
