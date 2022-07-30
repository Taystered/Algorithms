#include<cstdio>
#define N 100000
int n,m,next[N];
char a[N],b[N];
int main()
{
	scanf("%d%d%s%s",&n,&m,a+1,b+1);
	for (int i=2,j=0;i<=m;++i)
	{
		for (;j && b[i]^b[j+1];) j=next[j];
		if (b[i]==b[j+1]) ++j;
		next[i]=j;
	}
	for (int i=1,j=0;i<=n;++i)
	{
		for (;j && a[i]^b[j+1];) j=next[j];
		if (a[i]==b[j+1]) ++j;
		if (j==m) printf("%d\n",i-j+1);
	}
}
