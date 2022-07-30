#include<cstdio>
#define N 5005
#define ll long long
int n,m;
ll c0[N][N],c1[N][N],c2[N][N],c3[N][N];
void read(int &x)
{
	char ch=getchar(); int sig=1; x=0;
	for (;ch<'0' || '9'<ch;ch=getchar()) if (ch=='-') sig=-1;
	for (;'0'<=ch && ch<='9';x=(x<<1)+(x<<3)+(ch^48),ch=getchar());
	x*=sig;
}
void modify(int X,int Y,ll v0)
{
	ll v1=v0*X,v2=v0*Y,v3=v0*X*Y;
	for (int x=X;x<=n;x+=x&-x)
		for (int y=Y;y<=m;y+=y&-y)
		{
			c0[x][y]+=v0;
			c1[x][y]+=v1;
			c2[x][y]+=v2;
			c3[x][y]+=v3;
		}
}
void modify(int X1,int Y1,int X2,int Y2,int v)
{
	modify(X1,Y1,v);
	modify(X1,Y2+1,-v);
	modify(X2+1,Y1,-v);
	modify(X2+1,Y2+1,v);
}
ll query(int X,int Y)
{
	ll res0=0,res1=0,res2=0,res3=0;
	for (int x=X;x;x-=x&-x)
		for (int y=Y;y;y-=y&-y)
		{
			res0+=c0[x][y];
			res1+=c1[x][y];
			res2+=c2[x][y];
			res3+=c3[x][y];
		}
	return res0*(X+1)*(Y+1)-res1*(Y+1)-res2*(X+1)+res3;
}
ll query(int X1,int Y1,int X2,int Y2)
{
	return query(X2,Y2)-query(X2,Y1-1)-query(X1-1,Y2)+query(X1-1,Y1-1);
}
int main()
{
	read(n),read(m);
	for (int op,X1,Y1,X2,Y2,v;~scanf("%d",&op);)
	{
		if (op==1)
		{
			read(X1),read(Y1),read(X2),read(Y2),read(v);
			modify(X1,Y1,X2,Y2,v);
		}
		if (op==2)
		{
			read(X1),read(Y1),read(X2),read(Y2);
			printf("%lld\n",query(X1,Y1,X2,Y2));
		}
	}
}
