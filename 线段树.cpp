namespace Seg
{
	#define ls (p<<1)
	#define rs (ls|1)
	#define mid ((l+r)>>1)
	void update(int p,int v) {}
	void pushdown(int p) {}
	void modify(int p,int l,int r,int x)
	{
		if (l==r) return void();
		x<=mid?modify(ls,l,mid,x):modify(rs,mid+1,r,x);
	}
	void modify(int p,int l,int r,int x,int y)
	{
		if (x<=l && r<=y) return void();
		if (y<=mid) return modify(ls,l,mid,x,y);
		if (mid<x) return modify(rs,mid+1,r,x,y);
		modify(ls,l,mid,x,y),modify(rs,mid+1,r,x,y);
	}
	int query(int p,int l,int r,int x)
	{
		if (l==r) return 0;
		return x<=mid?query(ls,l,mid,x):query(rs,mid+1,r,x);
	}
	int query(int p,int l,int r,int x,int y)
	{
		if (x<=l && r<=y) return 0;
		//pushdown
		if (y<=mid) return query(ls,l,mid,x,y);
		if (x>mid) return query(rs,mid+1,r,x,y);
		return query(ls,l,mid,x,y)+query(rs,mid+1,r,x,y);
	}
	#undef ls
	#undef rs
	#undef mid
}
