#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
  char label;  // 'r' 或 '0' 或 '1'
  Node *left;  // 0分支
  Node *right; // 1分支
  Node() : label(0), left(nullptr), right(nullptr) {}
};

void insert(Node *root, const string &code) {
  Node *cur = root;
  for (size_t i = 0; i < code.size(); ++i) {
    if (code[i] == '0') {
      if (!cur->left) {
        cur->left = new Node();
        cur->left->label = '0';
      }
      cur = cur->left;
    } else {
      if (!cur->right) {
        cur->right = new Node();
        cur->right->label = '1';
      }
      cur = cur->right;
    }
  }
}

string serialize(Node *node) {
  if (!node)
    return "";
  if (!node->left && !node->right) {
    // 叶结点: [value ]
    string res = "[";
    res += node->label;
    res += " ]";
    return res;
  }
  // 内部结点: [left value right]
  // left后无空格, value后有一个空格
  string res = "[";
  string l = serialize(node->left);
  string r = serialize(node->right);
  res += l;
  res += node->label;
  res += " ";
  res += r;
  res += "]";
  return res;
}

int main() {
  int n;
  cin >> n;
  vector<string> codes(n);
  for (int i = 0; i < n; ++i) {
    cin >> codes[i];
  }

  Node *root = new Node();
  root->label = 'r';

  for (int i = 0; i < n; ++i) {
    insert(root, codes[i]);
  }

  string ans = serialize(root);
  cout << ans << endl;

  return 0;
}
