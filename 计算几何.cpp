#include<bits/stdc++.h>
using namespace std;
const int N=300005;
namespace Basic {
	mt19937 Rand(time(NULL));
	const double eps=1e-8,Pi=acos(-1),INF=1e18;
	double sqr(double x) {return x*x;}
	bool Equal(double x,double y) {return abs(x-y)<eps;}
	bool More(double x,double y) {return x>y+eps;}
	bool Less(double x,double y) {return x<y-eps;}
	bool ge(double x,double y) {return More(x,y) || Equal(x,y);}
	bool le(double x,double y) {return Less(x,y) || Equal(x,y);}
	int Sign(double x) {return Equal(x,0)?0:(x>0?1:-1);}
	bool Rangelr(double l,double x,double r) {return le(l,x) && le(x,r);}
	bool RangelR(double l,double x,double r) {return le(l,x) && Less(x,r);}
	bool RangeLr(double l,double x,double r) {return Less(l,x) && le(x,r);}
	bool RangeLR(double l,double x,double r) {return Less(l,x) && Less(x,r);}
	double max(double x,double y) {return More(x,y)?x:y;}
	double min(double x,double y) {return Less(x,y)?x:y;}
	double max(initializer_list <double> l,double res=-INF) 
		{for (double x:l) res=max(res,x); return res;}
	double min(initializer_list <double> l,double res=INF)
		{for (double x:l) res=min(res,x); return res;}
	double randeps() {return (1.0*Rand()/UINT_MAX-0.5)*eps;}
	double Shake(double &x) {return x+=randeps();}
} 
using namespace Basic;

namespace _2D {
	struct V
	{
		double x,y;
		V(void) {}
		V(double X,double Y) {x=X,y=Y;}
		void read() {scanf("%lf %lf",&x,&y);}
		void write() {printf("%lf %lf\n",x,y);}
	};
	double Dis(V x,V y);
	struct L
	{
		V x,e;
		L(void) {}
		L(V X,V E) {x=X,e=E;}
	};
	struct C
	{
		V o; double r;
		C(void) {}
		C(V O,double R) {o=O,r=R;}
		C(V O,V x) {o=O,r=Dis(O,x);}
	};
	V operator + (V x,V y) {return V(x.x+y.x,x.y+y.y);}
	V operator - (V x,V y) {return V(x.x-y.x,x.y-y.y);}
	V operator * (V x,double v) {return V(x.x*v,x.y*v);}
	V operator * (double v,V x) {return V(x.x*v,x.y*v);}
	V operator / (V x,double v) {return V(x.x/v,x.y/v);}
	L operator + (L x,L y) {return L(x.x+y.x,x.e+y.e);}
	L operator - (L x,L y) {return L(x.x-y.x,x.e-y.e);}
	C operator + (C x,C y) {return C(x.o+y.o,x.r+y.r);}
	C operator - (C x,C y) {return C(x.o-y.o,x.r-y.r);}
	bool operator == (V x,V y) {return Equal(x.x,y.x) && Equal(x.y,y.y);}
	bool operator != (V x,V y) {return !Equal(x.x,y.x) || !Equal(x.y,y.y);}
	bool operator == (L x,L y) {return x.x==y.x && x.e==y.e;}
	bool operator != (L x,L y) {return x.x!=y.x || x.e!=y.e;}
	double operator * (V x,V y) {return x.x*y.x+x.y*y.y;}
	double operator ^ (V x,V y) {return x.x*y.y-x.y*y.x;}
	double Len(V x) {return sqrt(sqr(x.x)+sqr(x.y));}
	double Dis(V x,V y) {return Len(x-y);}
	double Angle(double theta) {return theta<0?theta+2*Pi:theta;}
	double Angle(V x) {return Angle(atan2(x.y,x.x));}
	double Angle(V x,V y) {return acos(x*y/Len(x)/Len(y));}
	double Angle(double a,double b,double c) {return acos((sqr(b)+sqr(c)-sqr(a))/(b*c)*0.5);}
	double Angle(V A,V B,V C) {return Angle(Dis(B,C),Dis(A,C),Dis(A,B));}
	double Acute(double theta) {return Less(theta,Pi);}
	double Right(double theta) {return Equal(theta,Pi);}
	double Obtuse(double theta) {return More(theta,Pi);}
	bool Para(V x,V y) {return Equal(x^y,0);}
	bool Para(L x,L y) {return Para(x.e,y.e);}
	bool Vert(V x,V y) {return Equal(x*y,0);}
	bool Vert(L x,L y) {return Vert(x.e,y.e);}
	double Slope(V x) {return !Equal(x.x,0)?x.y/x.x:1e18;}
	double Slope(V x,V y) {return Slope(V(x.x-y.x,x.y-y.y));}
	V Unit(V x) {return x/Len(x);}
	V Midpoint(V x,V y) {return (x+y)*0.5;}
	V TransPoint(double theta,double len=1) {return V(cos(theta),sin(theta))*len;}
	L TransLine(V x,V y) {return L(x,Unit(V(y.x-x.x,y.y-x.y)));}
	pair <L,L> TransLine(pair <V,V> x,pair <V,V> y)
		{return {TransLine(x.first,y.first),TransLine(x.second,y.second)};}
	L Bisector(V x,V y) {return L(V(),(x+y)/Len(x+y));}
	L Bisector(V x,V o,V y) {return Bisector(x-o,y-o)+L(o,V(0,0));}
	V VertPoint(L x,V y) {return x.x+(y-x.x)*x.e*x.e;}
	L VertLine(L x,V y) {return L(VertPoint(x,y),TransPoint(atan(-1.0/Slope(x.e))));}
	L MidVert(V x,V y) {return VertLine(TransLine(x,y),Midpoint(x,y));}
	V Symmetry(L x,V y) {return 2*VertPoint(x,y)-y;}
	double Dis(L x,V y) {return Dis(VertPoint(x,y),y);}
	V CrossPoint(L x,L y) {return x.x+((y.x-x.x)^y.e)/(x.e^y.e)*x.e;}
	V Rotate(V x,double theta)
	{
		double Sin=sin(theta),Cos=cos(theta);
		return V(x.x*Cos-x.y*Sin,x.x*Sin+x.y*Cos);
	}
	L Rotate(L x,double theta) {return L(x.x,Rotate(x.e,theta));}
	C Fix(V x,V y) {return C(Midpoint(x,y),Dis(x,y)*0.5);}
	C Incircle(V x,V y,V z) {C(CrossPoint(Bisector(x,y),Bisector(x,z)),x);}
	C Circumcircle(V x,V y,V z) {return C(CrossPoint(MidVert(x,y),MidVert(x,z)),x);}
	C TransCircle(vector <V> x)
	{
		if (x.size()==1) return C(*x.begin(),0);
		if (x.size()==2) return Fix(*x.begin(),*++x.begin());
		if (x.size()==3) return Circumcircle(*x.begin(),*++x.begin(),*++++x.begin());
	}
	int AngleSign(V o,V x,V y) {return Sign((x-o)^(y-o));}
	bool OnSegment(V a,V b,V x) {return Equal(Dis(a,x)+Dis(x,b),Dis(a,b));}
	bool OffSegment(V a,V b,V x) {return !Equal(Dis(a,x)+Dis(x,b),Dis(a,b));}
	bool OnLine(L x,V y) {return Equal(x.e^(y-x.x),0);}
	bool OffLine(L x,V y) {return !Equal(x.e^(y-x.x),0);}
	bool InPolygon(vector <V> a,V x)
	{
		bool Left=0,Right=0; a.emplace_back(*a.begin());
		for (int i=1;i<a.size();++i)
		{
			V u=a[i-1],v=a[i],now=CrossPoint(TransLine(u,v),L(x,V(1,0)));
			if (OnSegment(u,v,x)) return 1;
			if (Equal(min(u.y,v.y),x.y)) continue;
			(Less(now.x,x.x)?Left:Right)^=OnSegment(u,v,now);
		}
		return Left && Right;
	}
	bool OutPolygon(vector <V> a,V x) {return !InPolygon(a,x);} 
	bool InPlane(L x,V y) {return More(x.e^(y-x.x),0);} // Left Side
	bool OffPlane(L x,V y) {return Less(x.e^(y-x.x),0);}
	bool InCircle(C x,V y) {return Less(Dis(x.o,y),x.r);}
	bool OnCircle(C x,V y) {return Equal(Dis(x.o,y),x.r);}
	bool OutCircle(C x,V y) {return More(Dis(x.o,y),x.r);}
	bool Cross(C x,L y) {return Less(Dis(y,x.o),x.r);}
	bool Tangent(C x,L y) {return Equal(Dis(y,x.o),x.r);}
	bool Separate(C x,L y) {return More(Dis(y,x.o),x.r);}
	bool Cross(C x,C y) {return Less(x.r+y.r,Dis(x.o,y.o));}
	bool Tangent(C x,C y) {return Equal(x.r+y.r,Dis(x.o,y.o));}
	bool Separate(C x,C y) {return More(x.r+y.r,Dis(x.o,y.o));}
	pair <V,V> TangentPoint(C x,V y)
	{
		double d=sqrt(sqr(Dis(x.o,y))-sqr(x.r)),theta=Angle(x.r,Dis(x.o,y),d);
		V e=Unit(x.o-y);
		return {y+Rotate(e,theta)*d,y+Rotate(e,-theta)*d};
	}
	pair <L,L> TangentLine(C x,V y) {return TransLine(TangentPoint(x,y),{y,y});}
	pair <V,V> CrossPoint(C x,L y)
	{
		V Mid=VertPoint(y,x.o);
		double d=sqrt(sqr(x.r)-sqr(Dis(y,x.o)));
		return {Mid-d*y.e,Mid+d*y.e};
	}
	pair <V,V> CrossPoint(C x,C y)
	{
		double theta=Angle(y.r,x.r,Dis(x.o,y.o));
		V Mid=Unit(y.o-x.o)*x.r;
		return {x.o+Rotate(Mid,theta),x.o+Rotate(Mid,-theta)};
	}
	double TriangleArea(double a,double b,double c) 
	{
		double p=(a+b+c)*0.5;
		return sqrt(p*(p-a)*(p-b)*(p-c));
	}
	double TriangleArea(V x,V y,V z) {return fabs((y-x)^(z-x));}
	double RectangleArea(double x,double y) {return x*y;}
	double RectangleArea(V x,V y) {return abs(y.x-x.x)*abs(y.y-x.y);}
	double CircleArea(double r) {return sqr(r)*Pi;}
	double CircleArea(C x) {return sqr(x.r)*Pi;}
	double SectorArea(double l,double r) {return 0.5*l*r;}
	double SectorArea(V o,V x,V y) {return sqr(Dis(o,x))*Angle(o,x,y)*0.5;}
	double PolygonArea(vector <V> a)
	{
		double res=a[0]^a[1];
		for (int i=1;i<a.size();++i) res+=a[i-1]^a[i];
		return res*0.5;
	}
	vector <V> Convex(vector <V> a)
	{
		vector <V> U,D;
		sort(begin(a),end(a),[] (V x,V y) {return !Equal(x.x,y.x)?Less(x.x,y.x):Less(x.y,y.y);});
		for (int i=0;i<a.size();++i)
		{
			if (i>1 && a[i-1]==a[i]) continue;
			for (;U.size()>1 && More(Slope(*++U.rbegin(),a[i]),Slope(*++U.rbegin(),U.back()));) U.pop_back();
			U.emplace_back(a[i]);
		}
		for (int i=0;i<a.size();++i)
		{
			if (i>1 && a[i-1]==a[i]) continue;
			for (;D.size()>1 && Less(Slope(*++D.rbegin(),a[i]),Slope(*++D.rbegin(),D.back()));) D.pop_back();
			D.emplace_back(a[i]);
		}
		vector <V> res;
		res.insert(res.end(),U.begin(),U.end());
		if (U.back()==D.back()) D.pop_back();
		res.insert(res.end(),D.rbegin(),D.rend());
		return res;
	}
	double Diameter(vector <V> a)
	{
		a=Convex(a);
		double res=0;
		for (int i=0,j=3;i<a.size();++i)
		{
			for (;Less(TriangleArea(a[i],a[i+1],a[j]),TriangleArea(a[i],a[i+1],a[j+1]));) ++j==a.size()-1 && (j=0,1);
			res=max({res,Dis(a[0],a[i]),Dis(a[i],a[j]),Dis(a[i+1],a[j])});
		}
		return res;
	}
	void CrossPlane(vector <L> a)
	{
		int l=1,r=0;
		vector <V> qV;
		vector <L> qL;
		sort(begin(a),end(a),[] (L x,L y)
		{
			double Tx=Angle(x.e),Ty=Angle(y.e);
			return Equal(Tx,Ty)?InPlane(y,x.x):Less(Tx,Ty);
		});
		for (auto it=a.begin();it!=a.end();++it)
		{
			if (it!=a.begin() && l<=r && Equal((*--it).e^(*it).e,0)) continue; 
			for (;l<r && OffPlane(*it,qV[r]);) --r;
			for (;l<r && OffPlane(*it,qV[l+1]);) ++l;
			qL[++r]=*it;
			(l<r) && (qV[r]=CrossPoint(qL[r-1],qL[r]),1);
		}
		for (;l<r && OffPlane(qL[l],qV[r]);) --r;
		(l<r) && (qV[r+1]=CrossPoint(qL[l],qL[r]),++r,1);
		printf("%.3f",PolygonArea(vector <V> (qV.begin()+l,qV.begin()+r+1)));
	}
	void CircleCover(vector <V> a)
	{
		shuffle(begin(a),end(a),Rand);
		C res(*a.begin(),0);
		for (int i=1;i<a.size();++i) if (OutCircle(res,a[i]))
		{
			res=C(a[i],0);
			for (int j=0;j<i;++j) if (OutCircle(res,a[j]))
			{
				res=Fix(a[i],a[j]);
				for (int k=0;k<j;++k) if (OutCircle(res,a[k]))
					res=Circumcircle(a[i],a[j],a[k]);
			}
		}
		printf("%.3f",res.r);
	}
	namespace Delaunay
	{
		#define mid ((l+r)>>1)
		void Triangulation(vector <V> a)
		{
			solve(0,a.size()-1,a);
		}
		void solve(int l,int r,vector <V> a)
		{
			if (r-l<=2)
			{
				for (int i=l;i<=r;++i)
					for (int j=l;j<i;++j)
						link(i,j);
				 return;
			}
			solve(l,mid,a),solve(mid+1,r,a);
			int nowl=l,nowr=r;
			for (bool update=1;update)
			{
				for (int i=last[nowl];i;i=next[i])
				{
					V Lpoint=a[nowl],Rpoint=a[nowr],now=a[to[i]];
					int sign=AngleSign(Rpoint,Lpoint,now); 
					if (sign>0 || (sign==0 && dis(now,Rpoint)<dis(Lpoint,Rpoint)))
						{update=1,nowl=to[i]; break;}
				}
				if (update) continue;
				for (int i=last[nowr];i;i=next[i])
				{
					V Lpoint=a[nowl],Rpoint=a[nowr],now=a[to[i]];
					int sign=AngleSign(Lpoint,Rpoint,now);
					if (sign<0 || (sign==0 && dis(now,Lpoint)<dis(Rpoint,Lpoint)))
						{update=1,nowr=to[i]; break;}
				}
			}
			link(nowl,nowr);
			
		}
		#undef mid
	}
	using namespace Delaunay;
}
namespace _3D {
	const int N=205;
	bool vis[N][N];
	struct V
	{
		double x,y,z;
		V(double X=0,double Y=0,double Z=0) {x=X,y=Y,z=Z;}
		void read() {scanf("%lf%lf%lf",&x,&y,&z);}
	};
	vector <V> a;
	struct P
	{
		V x,y,z; int idx,idy,idz;
		P(int X=0,int Y=0,int Z=0)
		{
			x=*(a.begin()+X);
			y=*(a.begin()+Y);
			z=*(a.begin()+Z);
			idx=X,idy=Y,idz=Z;
		}
		P(V X=V(),V Y=V(),V Z=V()) {x=X,y=Y,z=Z;}
	};
	V operator + (V x,V y) {return V(x.x+y.x,x.y+y.y,x.z+y.z);}
	V operator - (V x,V y) {return V(x.x-y.x,x.y-y.y,x.z-y.z);}
	V operator * (V x,double v) {return V(x.x*v,x.y*v,x.z*v);}
	V operator * (double v,V x) {return V(x.x*v,x.y*v,x.z*v);}
	V operator / (V x,double v) {return V(x.x/v,x.y/v,x.z/v);}
	V operator / (double v,V x) {return V(x.x/v,x.y/v,x.z/v);}
	bool operator == (V x,V y) {return Equal(x.x,y.x) && Equal(x.y,y.y) && Equal(x.z,y.z);}
	bool operator != (V x,V y) {return !Equal(x.x,y.x) || !Equal(x.y,y.y) || !Equal(x.z,y.z);}
	double operator * (V x,V y) {return x.x*y.x+x.y*y.y+x.z*y.z;}
	V operator ^ (V x,V y) {return V(x.y*y.z-x.z*y.y,x.z*y.x-x.x*y.z,x.x*y.y-x.y*y.x);}
	double Len(V x) {return sqrt(sqr(x.x)+sqr(x.y)+sqr(x.z));}
	V Normal(P x) {return (x.y-x.x)^(x.z-x.x);}
	double Area(P x) {return Len(Normal(x))*0.5;}
	bool InSpace(P x,V y) {return More((y-x.x)*Normal(x),0);}
	bool OutSpace(P x,V y) {return Less((y-x.x)*Normal(x),0);}
	void Convex(vector <V> a)
	{
		vector <P> ans;
		ans.emplace_back(0,1,2);
		ans.emplace_back(2,1,0);
		for (auto i=3;i<a.size();++i)
		{
			vector <P> now;
			for (P x:ans)
			{
				bool res=InSpace(x,a[i]);
				if (!res) now.emplace_back(x);
				int idx=x.idx,idy=x.idy,idz=x.idz;
				vis[idx][idy]=vis[idy][idz]=vis[idz][idx]=res;
			}
			for (P x:ans)
			{
				int idx=x.idx,idy=x.idy,idz=x.idz;
				if (vis[idx][idy]^vis[idy][idx] && vis[idx][idy]) now.emplace_back(P(i,idx,idy));
				if (vis[idy][idz]^vis[idz][idy] && vis[idy][idz]) now.emplace_back(P(i,idy,idz));
				if (vis[idz][idx]^vis[idx][idz] && vis[idz][idx]) now.emplace_back(P(i,idz,idx));
			}
			ans=now;
		}
		double res=0;
		for (P x:ans) res+=Area(x);
		printf("%.3f",res);
	}
}

int n,T;
using namespace _2D;
int main()
{
	
}
