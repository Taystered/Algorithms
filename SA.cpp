#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 2000005
int cnt[N],rk[N],sa[N],id[N],n,m=300;
char s[N];
void sort()
{
	memset(cnt,0,sizeof cnt);
	for (int i=1;i<=n;++i) ++cnt[rk[i]];
	for (int i=1;i<=m;++i) cnt[i]+=cnt[i-1];
	for (int i=n;i;--i) sa[cnt[rk[id[i]]]--]=id[i];
}
int main()
{
	scanf("%s",s+1),n=strlen(s+1);
	for (int i=1;s[i];++i) rk[i]=s[i],id[i]=i;
	sort();
	for (int w=1,p=0;p<n && w<=n;w<<=1,m=p,p=0)
	{
		for (int i=n-w+1;i<=n;++i) id[++p]=i;
		for (int i=1;i<=n;++i) if (sa[i]>w) id[++p]=sa[i]-w;
		sort(),std::swap(rk,id),p=0;
		for (int i=1;i<=n;++i)
			rk[sa[i]]=(id[sa[i]]==id[sa[i-1]] && id[sa[i]+w]==id[sa[i-1]+w])?p:++p;
	}
	for (int i=1;i<=n;++i) printf("%d ",sa[i]);
}
