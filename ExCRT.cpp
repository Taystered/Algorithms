#include<cstdio>
#define pp printf
#define ll long long
#define fo(i, x, y) for(int i = x; i <= y; i ++)
using namespace std;

const int N = 1e5 + 5;

int n;
ll m1, m2, c1, c2;

ll mul(ll x, ll y, ll mo) {
	x %= mo; y %= mo;
	ll z = (long double) x * y / mo;
	z = x * y - z * mo;
	if(z < 0) z += mo; else
	if(z > mo) z -= mo;
	return z;
}
ll gcd(ll x, ll y) {
	return !y ? x : gcd(y, x % y);
}
void eg(ll a, ll b, ll &x, ll &y) {
	if(!b) {x = a, y = 0; return;}
	eg(b, a % b, y, x); y = y - (a / b) * x;
}
ll inv(ll v, ll p) {
	ll x, y;
	eg(v, p, x, y);
	x = (x % p + p) % p;
	return x;
}

int main() {
	freopen("EXCRT.in","r",stdin);
	scanf("%d", &n);
	c1 = 0, m1 = 1;
	fo(i, 1, n) {
		scanf("%lld %lld", &m2, &c2);
		ll t = gcd(m1, m2); ll m3 = m2 / t, M = m3 * m1;
		c1 = (mul(mul(inv(m1 / t, m3), (c2 - c1) / t, m3), m1, M) + c1) % M;
		m1 = M; if(c1 < 0) c1 += m1;
	}
	pp("%lld\n", c1);
}
