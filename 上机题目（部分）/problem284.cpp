#include <iostream>
#include <vector>

using namespace std;

// Bell数 B_n: 大小为n的集合上等价关系个数
// B_{n+1} = Σ_{k=0}^{n} C(n, k) * B_k
// 或者使用 Bell 三角

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  // 使用 Bell 三角计算
  // Bell[0] = 1
  // 三角: T[i][0] = T[i-1][i-1], T[i][j] = T[i][j-1] + T[i-1][j-1]
  // Bell[i] = T[i][0]

  vector<vector<long long>> T(n + 1, vector<long long>(n + 1, 0));
  T[0][0] = 1;

  for (int i = 1; i <= n; ++i) {
    T[i][0] = T[i - 1][i - 1];
    for (int j = 1; j <= i; ++j) {
      T[i][j] = T[i][j - 1] + T[i - 1][j - 1];
    }
  }

  cout << T[n][0] << "\n";

  return 0;
}
