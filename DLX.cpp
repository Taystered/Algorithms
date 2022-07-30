#include<bits/stdc++.h>
#define N 5505 // Start Points
using namespace std;
int L[N],R[N],U[N],D[N],size[N],head[N],ans[N],row[N],col[N],n,m,t;
void build(int r,int c)
{
	for (int i=0;i<=c;++i)
		L[i]=i-1,R[i]=i+1,U[i]=D[i]=i;
	L[0]=c,R[c]=0,t=c;
}
void insert(int r,int c)
{
	row[++t]=r,col[t]=c,++size[c];
	D[t]=D[c],U[D[c]]=t,D[c]=t,U[t]=c;
	if (!head[r]) head[r]=t,L[t]=R[t]=t;
	else
	{
		R[t]=R[head[r]],L[R[head[r]]]=t;
		R[head[r]]=t,L[t]=head[r];
	}
}
void remove(int c)
{
	L[R[c]]=L[c],R[L[c]]=R[c];
	for (int i=D[c];i^c;i=D[i])
		for (int j=R[i];j^i;j=R[j])
			U[D[j]]=U[j],D[U[j]]=D[j],--size[col[j]];
}
void recover(int c)
{
	for (int i=D[c];i^c;i=D[i])
		for (int j=R[i];j^i;j=R[j])
			U[D[j]]=D[U[j]]=j,++size[col[j]];
	L[R[c]]=R[L[c]]=c;
}
void print(int x)
{
	for (int i=1;i<x;++i) printf("%d ",ans[i]);
	exit(0);
}
void dance(int dep)
{
	int c=R[0];
	if (!c) print(dep);
	for (int i=R[c];i;i=R[i]) if (size[i]<size[c]) c=i;
	remove(c);
	for (int i=D[c];i^c;i=D[i])
	{
		ans[dep]=row[i];
		for (int j=R[i];j^i;j=R[j]) remove(col[j]);
		dance(dep+1);
		for (int j=L[i];j^i;j=L[j]) recover(col[j]);
	}
	recover(c);
}
int main()
{
	scanf("%d%d",&n,&m);
	build(n,m);
	for (int i=1;i<=n;++i)
		for (int j=1,x;j<=m;++j)
			scanf("%d",&x),x && (insert(i,j),1);
	dance(1);
	puts("No Solution!");
}
