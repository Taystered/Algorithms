#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200005
#define max(x,y) (x>y?x:y)
using namespace std;
int a[N],b[N],l[N],r[N],p[N],bel[N],LLmost[N],LRmost[N],RLmost[N],RRmost[N],ans[N],n,m,q,len;
bool cmp(int x,int y)
{
	return bel[l[x]]^bel[l[y]]?
		bel[l[x]]<bel[l[y]]:r[x]<r[y];
}
int main()
{
	freopen("P5906_1.in","r",stdin);
	freopen("ha.out","w",stdout);
	scanf("%d",&n),m=n;
	for (int i=1;i<=n;++i) scanf("%d",&a[i]);
	scanf("%d",&q),len=sqrt(q);
	for (int i=1;i<=q;++i) scanf("%d%d",&l[p[i]=i],&r[i]);
	for (int i=1;i<=n;++i) bel[i]=i/len;
	memcpy(b,a,sizeof a);
	sort(b+1,b+m+1);
	sort(p+1,p+q+1,cmp);
	m=unique(b+1,b+m+1)-(b+1);
	for (int i=1;i<=n;++i)
		a[i]=lower_bound(b+1,b+m+1,a[i])-b;
	for (int id=0,x=1;id<=n/len;++id)
	{
		int Rbound=(id+1)*len-1,R=Rbound+1,Rres=0;
		for (;x<=q && bel[l[p[x]]]==id;++x)
		{
			if (bel[l[p[x]]]==bel[r[p[x]]])
			{
				for (int i=l[p[x]];i<=r[p[x]];++i)
				{
					if (LLmost[a[i]])
						ans[p[x]]=max(ans[p[x]],i-LLmost[a[i]]);
					else LLmost[a[i]]=i;
				}
				for (int i=l[p[x]];i<=r[p[x]];++i) LLmost[a[i]]=0;
			}
			else
			{
				int Lres=0;
				for (;R<=r[p[x]];++R)
				{
					RRmost[a[R]]=R;
					if (!RLmost[a[R]]) RLmost[a[R]]=R;
					Rres=max(Rres,RRmost[a[R]]-RLmost[a[R]]);
				}
				for (int L=Rbound;L>=l[p[x]];--L)
				{
					LLmost[a[L]]=L;
					if (!LRmost[a[L]]) LRmost[a[L]]=L;
					Lres=max(Lres,LRmost[a[L]]-LLmost[a[L]]);
					Lres=max(Lres,RRmost[a[L]]-LLmost[a[L]]);
				}
				for (int L=Rbound;L>=l[p[x]];--L)
					LLmost[a[L]]=LRmost[a[L]]=0;
				ans[p[x]]=max(Lres,Rres);
			}
		}
		memset(RLmost,0,sizeof RLmost);
		memset(RRmost,0,sizeof RRmost);
	}
	for (int i=1;i<=q;++i) printf("%d\n",ans[i]);
}
