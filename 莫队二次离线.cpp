#include<cmath>
#include<tuple>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#define V 16384
#define N 100005
using namespace std;
int vaild[V],cnt[V],pre[N],a[N],l[N],r[N],p[N],belong[N],n,m,k,t,len;
long long ans[N];
vector <tuple<int,int,int,int> > query[N];
int main()
{
	scanf("%d%d%d",&n,&m,&k); len=sqrt(n);
	if (k>14) goto print;
	for (int i=0;i<V;++i) __builtin_popcount(i)==k && (vaild[++t]=i,1);
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		belong[i]=i/len+1;
		pre[i]=cnt[a[i]];
		for (int j=1;j<=t;++j)
			++cnt[a[i]^vaild[j]];
	}
	for (int i=1;i<=m;++i) scanf("%d%d",&l[p[i]=i],&r[i]);
	sort(p+1,p+m+1,[] (int x,int y) {return belong[l[x]]^belong[l[y]]?l[x]<l[y]:r[x]<r[y];});
	for (int i=1,L=1,R=0;i<=m;++i)
	{
		if (L<l[p[i]]) query[R].emplace_back(L,l[p[i]]-1,p[i],-1);
		if (L>l[p[i]]) query[R].emplace_back(l[p[i]],L-1,p[i],1);
		for (;L<l[p[i]];) ans[p[i]]+=pre[L++];
		for (;L>l[p[i]];) ans[p[i]]-=pre[--L];
		if (R<r[p[i]]) query[L-1].emplace_back(R+1,r[p[i]],p[i],-1);
		if (R>r[p[i]]) query[L-1].emplace_back(r[p[i]]+1,R,p[i],1);
		for (;R<r[p[i]];) ans[p[i]]+=pre[++R];
		for (;R>r[p[i]];) ans[p[i]]-=pre[R--];
	}
	memset(cnt,0,sizeof cnt);
	for (int i=1,L,R,id,sig;i<=n;++i)
	{
		for (int j=1;j<=t;++j) ++cnt[a[i]^vaild[j]];
		for (auto &now:query[i])
		{
			tie(L,R,id,sig)=now;
			for (int j=L;j<=R;++j)
				ans[id]+=sig*(cnt[a[j]]-(j<=i && !k));
		}
	}
	for (int i=1;i<=m;++i) ans[p[i]]+=ans[p[i-1]];
	print:for (int i=1;i<=m;++i) printf("%lld\n",ans[i]);
}
