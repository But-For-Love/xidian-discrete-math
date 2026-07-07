#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<int>> adj(n, vector<int>(n));
  vector<vector<int>> children(n);
  vector<int> indeg(n, 0);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> adj[i][j];
      if (adj[i][j]) {
        children[i].push_back(j);
        indeg[j]++;
      }
    }
  }

  // 找根
  int root = -1;
  for (int i = 0; i < n; ++i) {
    if (indeg[i] == 0) {
      root = i;
      break;
    }
  }

  // BFS 计算层数
  vector<int> depth(n, -1);
  queue<int> q;
  q.push(root);
  depth[root] = 0;

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : children[u]) {
      depth[v] = depth[u] + 1;
      q.push(v);
    }
  }

  // 按字典序输出：即结点0到n-1
  for (int i = 0; i < n; ++i) {
    cout << depth[i] << "\n";
  }

  return 0;
}
