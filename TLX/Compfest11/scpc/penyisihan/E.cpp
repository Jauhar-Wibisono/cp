#include<bits/stdc++.h>
using namespace std;

int n, k, a[200003];
bool ans=1;

int main(){
	cin >> n >> k;
	for (int i=0;i<2*n;i++) cin >> a[i];
	sort(a,a+2*n);
	for (int i=0;i<2*n;i+=2){
		if (a[i+1]-a[i]>k) ans=0;
	}
	cout << (ans ? "Ya\n" : "Tidak\n");
}
