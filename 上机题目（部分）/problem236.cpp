#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int m, n;
vector<int> A, B;
vector<vector<pair<int, int>>> results;

void dfs(int idx, vector<int> &assigned, vector<bool> &used, int used_cnt) {
  if (idx == m) {
    if (used_cnt == n) {
      vector<pair<int, int>> relation;
      for (int i = 0; i < m; ++i) {
        relation.push_back({A[i], assigned[i]});
      }
      results.push_back(relation);
    }
    return;
  }

  for (int j = 0; j < n; ++j) {
    // 剪枝：剩余位置不够覆盖未使用的元素
    int remaining = m - idx - 1;
    int need = n - used_cnt - (used[j] ? 0 : 1);
    if (remaining < need)
      continue;

    assigned[idx] = B[j];
    bool was = used[j];
    used[j] = true;
    dfs(idx + 1, assigned, used, used_cnt + (was ? 0 : 1));
    used[j] = was;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> m >> n;
  A.resize(m);
  B.resize(n);
  for (int i = 0; i < m; ++i)
    cin >> A[i];
  for (int i = 0; i < n; ++i)
    cin >> B[i];

  if (m < n) {
    return 0;
  }

  // 对A排序，保持输出的序偶按A中元素升序
  // 题目要求按序偶中元素的字典序
  // 我们保证A是有序的
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  vector<int> assigned(m);
  vector<bool> used(n, false);

  dfs(0, assigned, used, 0);

  // 排序规则：
  // 1. 按基数大小从小到大（基数 = m 固定）
  // 2. 基数相同时按序偶中元素的字典序
  // 序偶集合的比较：先按第一个序偶比，再按第二个...
  // 每个序偶内部：先比第一个元素，再比第二个
  sort(results.begin(), results.end(),
       [](const vector<pair<int, int>> &r1, const vector<pair<int, int>> &r2) {
         for (int i = 0; i < m; ++i) {
           if (r1[i].first != r2[i].first)
             return r1[i].first < r2[i].first;
           if (r1[i].second != r2[i].second)
             return r1[i].second < r2[i].second;
         }
         return false;
       });

  for (auto &r : results) {
    cout << "{";
    for (int i = 0; i < m; ++i) {
      if (i > 0)
        cout << ",";
      cout << "<" << r[i].first << "," << r[i].second << ">";
    }
    cout << "}\n";
  }

  return 0;
}
