#include<bits/stdc++.h>
#define ll long long
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
using namespace std;
const int N=4e5+5,mod=998244353,g=3;
namespace convolution {int limit,len,rev[N<<5];}
namespace IO
{
	template <typename T> void read(T &x)
	{
		char ch=getchar(); x=0;
		for (;ch<'0' || '9'<ch;ch=getchar());
		for (;'0'<=ch && ch<='9';x=(x<<1)+(x<<3)+(ch^48),ch=getchar());
	}
	template <typename T> void readmod(T &x)
	{
		char ch=getchar(); x=0;
		for (;ch<'0' || '9'<ch;ch=getchar());
		for (;'0'<=ch && ch<='9';x=((x<<1)+(x<<3)+(ch^48))%mod,ch=getchar());
	}
	template <typename T> void write(T x)
	{ 
		if (x>9) write(x/10);
		putchar((x%10)|'0');
	}
}
namespace basic
{
	int fact[N<<1],ifact[N<<1],inv[N<<5],Maxinit; //Caution the size
	int add(int x,int y) {return (x+=y)>=mod?x-mod:x;}
	int sub(int x,int y) {return (x-=y)<0?x+mod:x;}
	int mul(int x,int y) {return 1ll*x*y%mod;}
	int mul(int x,int y,int z) {return mul(mul(x,y),z);}
	int mul(list <int> l,int res=1) {for (int x:l) res=mul(res,x); return res;}
	int neg(int x) {return x?mod-x:0;}
	int Mod(ll x) {return (x%mod+mod)%mod;}
	int fastpow(int x,int y)
	{
		int res=1;
		for (;y;y>>=1,x=mul(x,x))
			if (y&1) res=mul(res,x);
		return res;
	}
	int C(int x,int y) {return mul(fact[x],ifact[y],ifact[x-y]);}
	int Inv(int x) {return x<=Maxinit?inv[x]:fastpow(x,mod-2);}
	void init(int n)
	{
		inv[1]=1,Maxinit=n;
		for (int i=2;i<=n;++i) inv[i]=mul(mod-mod/i,inv[mod%i]);
		for (int i=fact[0]=1;i<=n;++i) fact[i]=mul(fact[i-1],i);
		ifact[n]=fastpow(fact[n],mod-2);
		for (int i=n;i;--i) ifact[i-1]=mul(ifact[i],i);
	}
}
using namespace IO;
using namespace basic;
using namespace convolution;
const int i=fastpow(g,(mod-1)/4);
struct Poly
{
	vector <int> f;
	Poly() {}
	Poly(int x) {f.resize(x);}
	Poly(initializer_list <int> x) {f=x;}
	Poly(vector <int> x) {f=x;}
	int & operator [] (int x) {return f[x];}
	int size() {return f.size();}
	void resize(int x) {f.resize(x);}
	void clear() {f.clear();}
	void reverse() {std::reverse(f.begin(),f.end());}
	void read() {for (int &x:f) scanf("%d",&x);}
	void print() {for (int x:f) printf("%d ",x); putchar('\n');}
	void println() {for (int x:f) printf("%d\n",x);}
	void read(int n) {f.resize(n); for (int &x:f) scanf("%d",&x);}
	void print(int n) {f.resize(n); for (int x:f) printf("%d ",x);}
} f;
Poly neg(Poly f) {for (int &x:f.f) x=neg(x); return f;}
Poly resize(Poly f,int n) {f.resize(n); return f;}
Poly operator + (Poly f,int v) {f[0]=add(f[0],v); return f;}
Poly operator - (Poly f,int v) {f[0]=sub(f[0],v); return f;}
Poly operator - (int v,Poly f) {return neg(f)+v;}
Poly operator * (Poly f,int v) {for (int &x:f.f) x=mul(x,v); return f;}
Poly operator * (int v,Poly f) {for (int &x:f.f) x=mul(x,v); return f;}
Poly operator >> (Poly f,int x) {return Poly(vector <int> (f.f.begin()+x,f.f.end()));}
Poly operator << (Poly f,int x) {f.f.insert(f.f.begin(),x,0); return f;}
Poly operator + (Poly f,Poly g)
{
	int n=max(f.size(),g.size());
	f.resize(n),g.resize(n);
	for (int i=0;i<n;++i) f[i]=add(f[i],g[i]);
	return f;
}
Poly operator - (Poly f,Poly g)
{
	int n=max(f.size(),g.size());
	f.resize(n),g.resize(n);
	for (int i=0;i<n;++i) f[i]=sub(f[i],g[i]);
	return f;
}
void NTT(Poly &f,int op,int n=0)
{
	if (n) limit=n;
	for (int i=0;i<limit;++i)
	{
		rev[i]=(rev[i>>1]>>1)|(i&1?limit>>1:0);
		if (i<rev[i]) swap(f[i],f[rev[i]]);
	}
	for (int k=1;k<limit;k<<=1)
	{
		int omega=fastpow(g,(mod-1)/(k<<1));
		if (!~op) omega=Inv(omega);
		for (int i=0;i<limit;i+=(k<<1))
			for (int j=0,now=1;j<k;++j)
			{
				int x=f[i+j],y=mul(now,f[i|j|k]);
				f[i|j]=add(x,y),f[i|j|k]=sub(x,y),now=mul(now,omega);
			}
	}
	if (!~op) f=f*Inv(limit);
}
void DFT(Poly &f) {NTT(f,1);}
void IDFT(Poly &f) {NTT(f,-1);}
Poly operator * (Poly f,Poly g)
{
	int n=f.size()+g.size()-1;
	for (limit=1;limit<n;limit<<=1);
	f.resize(limit),g.resize(limit);
	NTT(f,1),NTT(g,1);
	for (int i=0;i<limit;++i) f[i]=mul(f[i],g[i]);
	NTT(f,-1);
	return resize(f,n); //WARNING!!!
}
Poly Inv(Poly f) // when f[0] is zero there exists no Inv 
{
	int n=f.size();
	Poly g={Inv(f[0])},h;
	for (len=2;len<2*n;len<<=1)
	{
		g=resize(resize(g,len>>1),len<<1);
		h=resize(resize(f,len),len<<1);
		NTT(g,1,len<<1),NTT(h,1,len<<1);
		for (int i=0;i<(len<<1);++i) g[i]=mul(g[i],sub(2,mul(g[i],h[i])));
		NTT(g,-1,len<<1);
	}
	return resize(g,n);
}
pair <Poly,Poly> Div(Poly f,Poly g)
{
	int n=f.size(),m=g.size();
	Poly q,r;
	f.reverse(),g.reverse();
	q=resize(resize(f,n-m+1)*Inv(resize(g,n-m+1)),n-m+1);
	f.reverse(),g.reverse(),q.reverse();
	r=resize(resize(f,m-1)-resize(g*q,m-1),m-1);
	return {q,r};
}
Poly operator / (Poly f,Poly g) {return Div(f,g).first;}
Poly operator % (Poly f,Poly g) {return Div(f,g).second;}
Poly Der(Poly f)
{
	for (int i=1;i<f.size();++i) f[i-1]=mul(f[i],i);
	return resize(f,f.size()-1);
}
Poly Int(Poly f)
{
	f.resize(f.size()+1);
	for (int i=f.size()-1;~i;--i) f[i]=i?mul(f[i-1],Inv(i)):0;
	return f;
}
Poly Sqrt(Poly f)
{
	Poly g={1};
	for (len=2;len<4*f.size();len<<=1)
		g=resize((g+(resize(f,len)*Inv(g)))*Inv(2),len);
	return resize(g,f.size());
}
Poly Ln(Poly f) {return resize(Int(Der(f)*Inv(f)),f.size());}
Poly Exp(Poly f)
{
	Poly g={1};
	for (len=2;len<4*f.size();len<<=1)
		g=resize(g*(1-Ln(g)+resize(f,len)),len);
	return resize(g,f.size());
}
Poly Pow(Poly f,int k0,int k1=0) // f[0] must to be one, or else Inv would be wrong
{
	int shift=0,n=f.size();
	for (;shift<n && !f[shift];) ++shift;
	if (1ll*shift*k1>n) return Poly(vector <int> (n,0));
	int firstval=f[shift];
	f=(f>>shift)*Inv(firstval);
	return resize(Exp(Ln(f)*k0)<<(shift*k1),n)*fastpow(firstval,k1);
}
/*
Poly P[N<<2];
void Eva(int p,int l,int r)
{
	if (l==r) return void(P[p]={Mod(-a[l]),1});
	Eva(ls,l,mid),Eva(rs,mid+1,r);
	if (p>1) P[p]=P[ls]*P[rs];
}
void Eva(Poly f,int p,int l,int r)
{
	if (l==r) return void(b[l]=f[0]);
	Eva(f%P[ls],ls,l,mid);
	Eva(f%P[rs],rs,mid+1,r);
}
void Eva(Poly f,int n) {Eva(1,1,n),Eva(f,1,1,n);}
*/
Poly Sin(Poly f) {return resize((Exp(f*i)-Exp(f*neg(i)))*Inv(i*2),f.size());}
Poly Cos(Poly f) {return resize((Exp(f*i)+Exp(f*neg(i)))*Inv(2),f.size());}
int n,m,t,a[N],b[N];
Poly solveA(int l,int r)
{
	if (l==r) return Poly({1,mod-a[l]});
	Poly res=solveA(l,mid)*solveA(mid+1,r);
	return resize(res,min(res.size(),t+1));
}
Poly solveB(int l,int r)
{
	if (l==r) return Poly({1,mod-b[l]});
	Poly res=solveB(l,mid)*solveB(mid+1,r);
	return resize(res,min(res.size(),t+1));
}	
int main()
{
	freopen("P4705_15.in","r",stdin);
	freopen("My.out","w",stdout);
	read(n),read(m);
	for (int i=1;i<=n;++i) scanf("%d",&a[i]);
	for (int i=1;i<=m;++i) scanf("%d",&b[i]);
	scanf("%d",&t),init(N-5);
	Poly
		A=n-(Der(Ln(resize(solveA(1,n),t+1)))<<1),
		B=m-(Der(Ln(resize(solveB(1,m),t+1)))<<1);
	for (int i=2;i<A.size();++i) A[i]=mul(A[i],ifact[i]);
	for (int i=2;i<B.size();++i) B[i]=mul(B[i],ifact[i]);
	Poly answer=A*B*Inv(n)*Inv(m);
	for (int i=1;i<=t;++i) printf("%d\n",mul(answer[i],fact[i]));
}
