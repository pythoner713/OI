#include<bits/stdc++.h>
#define int long long
#define P 1000000007
using namespace std;

int ans, n, m, _2[4000], C[60][60], f[60][60], g[60][60][60], h[60];

int qpow(int A, int B){
	int r = 1;
	while(B){
		if(B & 1) r = (r * A) % P;
		A = (A * A) % P, B >>= 1;
	}
	return r;
}

signed main(){
	cin >> n >> m;
	_2[0] = 1;
	for(int i = 1; i <= 2500; i++) _2[i] = (_2[i - 1] << 1) % P;
	for(int i = 0; i <= 50; C[i++][0] = 1){
		for(int j = 1; j <= i; j++){
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
		}
	}
	h[1] = 1;
	for(int i = 2; i <= n; i++){
		h[i] = _2[i * (i - 1) / 2];
		for(int j = 1; j < i; j++){
			h[i] -= h[j] * C[i - 1][j - 1] % P * _2[(i - j) * (i - j - 1) / 2] % P;
			h[i] = (h[i] % P + P) % P;
		}
	}
	g[0][0][0] = 1;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j < i; j++){
			for(int k = 1; k < i; k++){
				int tmp = 0;
				for(int x = 1; x <= min(i - k, j); x++){
					tmp = (tmp + g[i - k][x][j - x] * qpow(k, x) % P) % P;
				}
				f[i][j] = (f[i][j] + f[k][0] * C[i - 1][k - 1] % P * tmp % P) % P;
			}
		}
		f[i][0] = h[i];
		for(int j = 1; j < i; j++){
			f[i][0] -= f[i][j];
			f[i][0] = (f[i][0] % P + P) % P;
		}
		for(int j = 1; j <= i; j++){
			for(int k = 0; k < i; k++){
				for(int p = 1; p <= i; p++){
					for(int q = 0; q <= k; q++){
						g[i][j][k] = (g[i][j][k] + (f[p][q] * C[i - 1][p - 1] % P * p % P * g[i - p][j - 1][k - q] % P)) % P;
					}
				}
			}
		}
	}
	for(int i = 0; i <= min(m, n); i++){
		ans = (ans + f[n][i]) % P;
	}
	cout << ans;
	return 0;
}
