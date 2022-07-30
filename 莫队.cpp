#include<cmath>
#include<cstdio>
#include<algorithm>
#define N 140005
using namespace std;
int color[N],l[N],r[N],p[N],tot[1<<20],ans[N],n,q,B,res;
bool cmp(int x,int y)
{
	return (l[x]/B)^(l[y]/B)?l[x]<l[y]:r[x]<r[y];
}
void inc(int x) {if (++tot[color[x]]==1) ++res;}
void dec(int x) {if (--tot[color[x]]==0) --res;}
int main()
{
	scanf("%d%d",&n,&q); B=sqrt(n);
	for (int i=1;i<=n;++i) scanf("%d",&color[i]);
	for (int i=1;i<=q;++i)
		scanf("%d%d\n",&l[p[i]=i],&r[i]);
	for (int i=1,L=1,R=0;i<=n;++i)
	{
		while (L<l[p[i]]) dec(L++);
		while (L>l[p[i]]) inc(--L);
		while (R<r[p[i]]) inc(++R);
		while (R>r[p[i]]) dec(R--);
		ans[p[i]]=res;
	}
	for (int i=1;i<=q;++i) printf("%d\n",ans[i]);
}
