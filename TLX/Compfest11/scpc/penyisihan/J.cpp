#include<bits/stdc++.h>
using namespace std;

// O(n^2logn)
// pake segtree tle, sparse ac lul

const int mod=1e9+7, maxn=2002, logn=12;
int n, m, a[maxn], b[maxn], dp[maxn][maxn], fst[maxn], sparse[logn][maxn], lg2[maxn];

void builds(){
	lg2[1]=0;
	for (int i=2;i<maxn;i++) lg2[i]=lg2[i/2]+1;
	for (int i=0;i<n;i++) sparse[0][i]=a[i];
	for (int i=1;i<logn;i++){
		for (int j=0;j+(1<<i)<=n;j++){
			sparse[i][j]=max(sparse[i-1][j],sparse[i-1][j+(1<<(i-1))]);
		}
	}
}

int querys(int l, int r){
	int lg=lg2[r-l+1];
	return max(sparse[lg][l],sparse[lg][r-(1<<lg)+1]);
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	memset(dp,0,sizeof dp);
	memset(fst,-1,sizeof fst);
	memset(sparse,-1,sizeof sparse);
	cin >> n >> m;
	for (int i=0;i<n;i++) cin >> a[i];
	for (int i=0;i<m;i++) cin >> b[i];
	builds();
	if (m==1){
		if (querys(0,n-1)==b[0]) cout << 1 << "\n";
		else cout << 0 << "\n";
		return 0;
	}
	int mx=0;
	for (int i=0;i<n;i++){
		mx=max(mx,a[i]);
		if (mx==b[0]){
			if (fst[0]==-1) fst[0]=i;
			dp[0][i]=1;
		}
		if (i>0) dp[0][i]+=dp[0][i-1];
	}
	for (int i=1;i<m;i++){
		if (fst[i-1]==-1){
			cout << "0\n";
			return 0;
		}
		for (int j=fst[i-1]+1;j<n;j++){
			int lb=-1, rb=-1;
			// get left border lb
			int l=fst[i-1]+1, r=j;
			while (l<=r){
				int mid=(l+r)/2, tmp=querys(mid,j);
				if (tmp<=b[i]){
					if (tmp==b[i]) lb=mid;
					r=mid-1;
				}
				else l=mid+1;
			}
			// get right border rb
			l=fst[i-1]+1, r=j;
			while (l<=r){
				int mid=(l+r)/2, tmp=querys(mid,j);
				if (tmp>=b[i]){
					if (tmp==b[i]) rb=mid;
					l=mid+1;
				}
				else r=mid-1;
			}
			if (lb==-1) continue;
			if (fst[i]==-1) fst[i]=j;
			dp[i][j]+=dp[i-1][rb-1];
			if (lb>1) dp[i][j]-=dp[i-1][lb-2];
			dp[i][j]+=mod;
			dp[i][j]%=mod;
		}
		if (i<m-1){
			for (int j=1;j<n;j++){
				dp[i][j]+=dp[i][j-1];
				dp[i][j]%=mod;
			}
		}
	}
	cout << dp[m-1][n-1] << "\n";
}
