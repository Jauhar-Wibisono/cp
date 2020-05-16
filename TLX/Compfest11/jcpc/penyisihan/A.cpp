#include<bits/stdc++.h>
using namespace std;

long long a, b;

int main(){
	cin >> a >> b;
	if (a%11==0) cout << (a/11)*b << "\n";
	else cout << (b/11)*a << "\n";
}
