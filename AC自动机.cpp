#include<cstdio>
#include<cstring>
#include<queue>
#include<cstring>
#define max(x,y) (x>y?x:y)
#define N 200005
using namespace std;
int n,m,tot,T,p,len,son[N*3][26],val[N*3],fail[N*3],in[N*3],pos[N];
char s[N],t[N*10];
queue <int> q;
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;pos[i++]=p)
	{
		scanf("%s",s+1),len=strlen(s+1); p=0;
		for (int j=1;j<=len;++j)
			p=son[p][s[j]-'a']+=son[p][s[j]-'a']?0:++tot;
	}
	for (int i=0;i<26;++i) if (son[0][i]) q.push(son[0][i]);
	while (!q.empty()) 
	{
		p=q.front(),q.pop();
		for (int i=0;i<26;i++) if (son[p][i])
			fail[son[p][i]]=son[fail[p]][i],q.push(son[p][i]);
		else son[p][i]=son[fail[p]][i];
	}
	scanf("%s",t+1),len=strlen(t+1); p=0;
	for (int i=1;i<=len;i++) ++val[p=son[p][t[i]-'a']];
	for (int i=1;i<=tot;++i) ++in[fail[i]];
	for (int i=1;i<=tot;++i) if (!in[i]) q.push(i);
	while (!q.empty())
	{
		int x=q.front(); q.pop();
		val[fail[x]]+=val[x];
		if (!--in[fail[x]]) q.push(fail[x]);
	}
	for (int i=1;i<=n;++i) printf("%d\n",val[pos[i]]);
}
