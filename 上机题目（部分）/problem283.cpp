#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<int>> R(n, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> R[i][j];
    }
  }

  // 等价关系由自反闭包、对称闭包、传递闭包生成
  // 等价关系 = tsr(R) = 传递闭包(对称闭包(自反闭包(R)))

  // 1. 自反闭包 r(R): R ∪ I
  // 但后面传递闭包会处理自反性，所以我们从自反开始
  for (int i = 0; i < n; ++i) {
    R[i][i] = 1;
  }

  // 2. 对称闭包 s(R): R ∪ R^T
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (R[i][j] || R[j][i]) {
        R[i][j] = R[j][i] = 1;
      }
    }
  }

  // 3. 传递闭包 t(R) = Warshall算法
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (R[i][k] && R[k][j]) {
          R[i][j] = 1;
        }
      }
    }
  }

  // 输出结果矩阵
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j > 0)
        cout << " ";
      cout << R[i][j];
    }
    cout << "\n";
  }

  return 0;
}
