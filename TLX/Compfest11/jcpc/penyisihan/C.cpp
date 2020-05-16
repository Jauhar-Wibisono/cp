#include<bits/stdc++.h>
using namespace std;

// sama kayak penyisihan SCPC A

int n;
map<unsigned long long, int>add;
unsigned long long ans=0;

unsigned long long sumn(unsigned long long x){
	return (x*(x+1))/2;
}

int main(){
	cin >> n;
	for (int i=0;i<n;i++){
		unsigned long long l, r;
		cin >> l >> r;
		add[l]++;
		add[r]--;
	}
	int cnt=0, l;
	for (auto u : add){
		if (cnt==0) l=u.first; 
		cnt+=u.second;
		if (cnt==0){
			ans+=sumn(u.first)-sumn(l-1);
		}
	}
	cout << ans << "\n";
}
