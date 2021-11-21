#include<bits/stdc++.h>
#define nb 400010
#define int long long
using namespace std;

int _, n, s[nb];
unsigned int B = 131, H1[nb], H2[nb], P[nb] = {1};
struct point{int x, y;}p[nb];

bool check(int l, int r){
    unsigned int h1 = H1[r] - H1[l - 1] * P[r - l + 1];
    unsigned int h2 = H2[l] - H2[r + 1] * P[r - l + 1];
    return h1 == h2;    // 正反哈希值相等说明回文
}

signed main(){
    for(int i = 1; i < nb; i++)
        P[i] = P[i - 1] * B;
    for(cin >> _; _--;){
        cin >> n;
        int ans = 0;
        for(int i = 1; i <= n; i++)
            cin >> p[i].x >> p[i].y;
        for(int i = 1; i <= n; i++){
            int A = i, B = i + 1, C = i + 2;
            B -= (B > n) * n, C -= (C > n) * n;
            s[i * 2 - 1] = pow(p[A].x - p[B].x, 2) + pow(p[A].y - p[B].y, 2);
            s[i * 2] = (p[A].x - p[B].x) * (p[B].y - p[C].y) - (p[A].y - p[B].y) * (p[B].x - p[C].x);
            // s[2i - 1] 和 s[2i] 分别记录边角信息
            // 叉积公式: (a, b) × (c, d) = ad - bc
        }
        for(int i = 1; i <= n * 2; i++) s[i + n * 2] = s[i];          // 断环成链
        for(int i = 1; i <= n * 4; i++) H1[i] = H1[i - 1] * B + s[i]; // 正向哈希
        for(int i = n * 4; i >= 1; i--) H2[i] = H2[i + 1] * B + s[i]; // 反向哈希
        for(int i = 1; i <= n * 2; i++) ans += check(i, i + n * 2);   // 判断回文
        cout << ans / 2 << endl;                                      // 答案除二
    }
    return 0;
}
