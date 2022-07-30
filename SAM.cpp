#include<cstdio>
#include<cstring>
#define N 2000005
#define max(x,y) (x>y?x:y)
int len[N],father[N],cnt[N],sum[N],id[N],son[N][26],ans,last,t;
char s[N];
void init() {father[last=0]=-1;}
void insert(char c)
{
	int p=last,cur=++t,x=c-'a';
	len[cur]=len[p]+1;
	for (;~p && !son[p][x];son[p][x]=cur,p=father[p]);
	if (!~p) father[cur]=0;
	else
	{
		int q=son[p][x];
		if (len[p]+1==len[q]) father[cur]=q;
		else
		{
			int clone=++t;
			len[clone]=len[p]+1;
			father[clone]=father[q];
			memcpy(son[clone],son[q],sizeof son[q]);
			for (;~p && son[p][x]==q;son[p][x]=clone,p=father[p]);
			father[cur]=father[q]=clone;
		}
	}
	last=cur;
}
int main()
{
	scanf("%s",s+1); init();
	for (int i=1;s[i];++i) insert(s[i]);
	printf("%d",ans);
}
