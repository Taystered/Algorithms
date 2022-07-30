#include<cstdio>
#include<cstring>
#define P 998244353
int n,a[1<<17],b[1<<17],A[1<<17],B[1<<17];
void in() {memcpy(A,a,sizeof A),memcpy(B,b,sizeof B);}
void get() {for (int i=0;i<n;++i) A[i]=1ll*A[i]*B[i]%P;}
void out(){for (int i=0;i<n;++i) printf("%d ",A[i]);}
int pow(int x,int y)
{
	int res=1;
	for (;y;y>>=1,x=1ll*x*x%P)
		if (y&1) res=1ll*res*x%P;
	return res;
}
int inv=pow(2,P-2);
void Or(int *a,int op)
{
	for (int k=1;k<n;k<<=1)
		for (int i=0;i<n;i+=k<<1)
			for (int j=0;j<k;++j)	
				(a[i+j+k]+=a[i+j]*op+(op<1)*P)%=P;
}
void And(int *a,int op)
{
	for (int k=1;k<n;k<<=1)
		for (int i=0;i<n;i+=k<<1)
			for (int j=0;j<k;++j)
				(a[i+j]+=a[i+j+k]*op+(op<1)*P)%=P;
}
void Xor(int *a,int op)
{
	for (int k=1;k<n;k<<=1)
		for (int i=0;i<n;i+=k<<1)
			for (int j=0;j<k;++j)
			{
				int x=a[i+j],y=a[i+j+k];
				a[i+j]=(x+y)%P,a[i+j+k]=(x-y+P)%P;
				if (op==-1) a[i+j]=1ll*a[i+j]*inv%P,a[i+j+k]=1ll*a[i+j+k]*inv%P;
			}
}
int main()
{
	scanf("%d",&n); n=1<<n;
	for (int i=0;i<n;++i) scanf("%d",&a[i]);
	for (int i=0;i<n;++i) scanf("%d",&b[i]);
	in(),Or(A,1),Or(B,1),get(),Or(A,-1),out(),puts("");
	in(),And(A,1),And(B,1),get(),And(A,-1),out(),puts("");
	in(),Xor(A,1),Xor(B,1),get(),Xor(A,-1),out();
}
