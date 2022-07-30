int det()
{
	int res=1;
	for (int i=1;i<=n;++i)
	{
		for (int j=i+1;!a[i][i] && j<=n;++j)
			if (a[j][i]) swap(a[i],a[j]),res=mod-res;
		int inv=fastpow(a[i][i],mod-2);
		for (int j=i+1;j<=n;++j)	
			for (int k=i,x=1ll*a[j][i]*inv%mod;k<=n;++k)
				inc(a[j][k],-1ll*x*a[i][k]%mod);
		res=1ll*res*a[i][i]%mod;
	}
	return res;
}
