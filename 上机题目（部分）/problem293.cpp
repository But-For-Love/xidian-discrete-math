#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // 读入整个邻接矩阵（没有给出n，需要从第一行推断）
  vector<vector<int>> matrix;
  string line;

  while (getline(cin, line)) {
    if (line.empty())
      continue;
    vector<int> row;
    istringstream iss(line);
    int val;
    while (iss >> val) {
      row.push_back(val);
    }
    if (!row.empty()) {
      matrix.push_back(row);
    }
  }

  int n = (int)matrix.size();
  if (n == 0) {
    cout << "N\n";
    return 0;
  }

  // 构建子结点列表和入度
  vector<vector<int>> children(n);
  vector<int> indeg(n, 0);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (matrix[i][j]) {
        children[i].push_back(j);
        indeg[j]++;
      }
    }
  }

  // 找根：入度为0的结点
  int root = -1;
  for (int i = 0; i < n; ++i) {
    if (indeg[i] == 0) {
      if (root != -1) {
        cout << "N\n";
        return 0;
      }
      root = i;
    }
  }

  if (root == -1) {
    cout << "N\n";
    return 0;
  }

  // 每个非根结点入度必须为1
  for (int i = 0; i < n; ++i) {
    if (i != root && indeg[i] != 1) {
      cout << "N\n";
      return 0;
    }
  }

  // 统计每个结点的子结点数
  vector<int> child_cnt(n, 0);
  for (int i = 0; i < n; ++i) {
    child_cnt[i] = (int)children[i].size();
  }

  int m = child_cnt[root];
  if (m == 0) {
    // 单结点树
    cout << "Y 0\n";
    return 0;
  }

  // 完全m元树：每个内部结点（有子结点的）必须有恰好m个子结点
  // 叶子可以出现在不同层级
  for (int i = 0; i < n; ++i) {
    if (child_cnt[i] != 0 && child_cnt[i] != m) {
      cout << "N\n";
      return 0;
    }
  }

  cout << "Y " << m << "\n";
  return 0;
}
