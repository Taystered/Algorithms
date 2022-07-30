#include<ctime>
#include<cstdio>
#include<cstdlib>
#define N 500005
int root[N],n,tot;
struct treap {int ls,rs,pri,val,size;} t[N<<6];
void update(int x) {t[x].size=t[t[x].ls].size+t[t[x].rs].size+1;}
void newnode(int v) {t[++tot]=(treap){0,0,rand(),v,1};}
void split(int p,int k,int &x,int &y)
{
	if (!p) return (void)(x=y=0);
	t[p].val<=k?
		(t[x=++tot]=t[p],split(t[x].rs,k,t[x].rs,y),update(x)):
		(t[y=++tot]=t[p],split(t[y].ls,k,x,t[y].ls),update(y));
}
int merge(int x,int y)
{
	if (!x || !y) return x+y;
	int p=++tot;
	t[x].pri<t[y].pri?
		(t[p]=t[x],t[p].rs=merge(t[p].rs,y)):
		(t[p]=t[y],t[p].ls=merge(x,t[p].ls));
	update(p);
	return p;
}
int merge(int x,int y,int z) {return merge(merge(x,y),z);}
int X,Y,Z,res;
int kth(int p,int k)
{
	if (t[t[p].ls].size+1==k) return p;
	if (t[t[p].ls].size>=k) return kth(t[p].ls,k);
    return kth(t[p].rs,k-t[t[p].ls].size-1);
}
void insert(int &R,int v)
{
	split(R,v,X,Y);
	newnode(v);
	R=merge(X,tot,Y);
}
void erase(int &R,int v)
{
	split(R,v,X,Z);
	split(X,v-1,X,Y);
	Y=merge(t[Y].ls,t[Y].rs);
	R=merge(X,Y,Z);
}
int rank(int &R,int v)
{
	split(R,v-1,X,Y);
	res=t[X].size+1;
	R=merge(X,Y);
	return res;
}
int pre(int &R,int v)
{
	split(R,v-1,X,Y); 
	res=X?kth(X,t[X].size):(N<<6)-2;
	R=merge(X,Y);
	return res;
}
int suf(int &R,int v)
{
	split(R,v,X,Y);
	res=Y?kth(Y,1):(N<<6)-1;
	R=merge(X,Y);
	return res;
}
int main()
{
	srand(time(NULL));
	scanf("%d",&n);
	t[(N<<6)-1].val=2147483647;
	t[(N<<6)-2].val=-2147483647;
	for (int i=1,op,x,k;i<=n;++i)
	{
		scanf("%d%d%d",&k,&op,&x);
		root[i]=root[k];
		if (op==1) insert(root[i],x);
		if (op==2) erase(root[i],x);
		if (op==3) printf("%d\n",rank(root[i],x));
		if (op==4) printf("%d\n",t[kth(root[i],x)].val);
		if (op==5) printf("%d\n",t[pre(root[i],x)].val);
		if (op==6) printf("%d\n",t[suf(root[i],x)].val);
	}
}
