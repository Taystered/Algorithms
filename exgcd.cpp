void exgcd(ll a,ll b,ll &x,ll &y)
{
	if (b==0) return (void)(x=1,y=0);
	exgcd(b,a%b,y,x),y-=a/b*x;
}
