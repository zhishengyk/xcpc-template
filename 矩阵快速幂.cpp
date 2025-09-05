#include <algorithm>
#include <map>
#include<iostream>
#include<string>
#include<set>
#include <vector>
#include <map>
#include <queue>
#include <cstring>
using namespace std;
const int N = 1e6+5;
const int mod = 1e9 + 7;
#define int long long
#define maxn 105
#define ll long long
int n;
struct ahaha{
	ll a[maxn][maxn];     //一定要用long long存矩阵，否则在过程中会爆掉
	ahaha(){
		memset(a,0,sizeof a);
	}
	inline void build(){     //建造单位矩阵
		for(int i=1;i<=n;++i)a[i][i]=1;
	}
}a;
ahaha operator *(const ahaha &x,const ahaha &y){     //重载运算符
	ahaha z;
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j]%mod)%mod;
	return z;
}
int  fastp(int x ,int y ,const int &p){
	int res = 1;
	while(y){
		if(y&1){
			res*=x;
			res%=p;
		}
		y >>=1;
		x=x*x%p;
	}
	return res;
}
int k;
inline void init(){
	cin >> n >> k;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			cin >> a.a[i][j];
}
void solve(){
	init();
	ahaha ans;ans.build();
	while(k){
		if(k&1) ans = ans*a;
		a=a*a;k >>=1;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout << ans.a[i][j] <<" ";
		}
		cout <<"\n";
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0);
	int _ = 1;
//	cin >> _;
	while(_--){
		solve();
	}
	return  0;
}


