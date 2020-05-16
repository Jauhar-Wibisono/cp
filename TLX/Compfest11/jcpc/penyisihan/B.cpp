#include<bits/stdc++.h>
using namespace std;

int n, m;
long long a[100002], ans=0;

int main(){
	cin >> n >> m;
	a[0]=0;
	for (int i=1;i<=n;i++){
		cin >> a[i];
		a[i]+=a[i-1];
	}
	for (int i=m+1;i<=n;i++) ans=max(ans,a[i]-a[i-m-1]);
	cout << ans << "\n";
}
