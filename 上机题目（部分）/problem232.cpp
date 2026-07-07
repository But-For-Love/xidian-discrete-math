#include <cstdio>
#include <vector>
#define R                                                                      \
  puts("Nothing found.");                                                      \
  return 0
int n, m[26][26], in[26], out[26], t, s = -1, om, im, c;
std::vector<int> p, k;
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      scanf("%d", &m[i][j]);
      out[i] += m[i][j];
      in[j] += m[i][j];
      t += m[i][j];
    }
  if (!t) {
    R;
  }
  for (int i = 0; i < n; i++) {
    int d = out[i] - in[i];
    if (d == 1) {
      om++;
      s = i;
    } else if (d == -1)
      im++;
    else if (d) {
      R;
    }
  }
  if (!om && !im) {
    c = 1;
    for (int i = 0; i < n; i++)
      if (out[i]) {
        s = i;
        break;
      }
  } else if (om == 1 & im == 1)
    ;
  else {
    R;
  }
  k.push_back(s);
  while (!k.empty()) {
    int v = k.back(), u = -1;
    for (int j = 0; j < n; j++)
      if (m[v][j]) {
        u = j;
        break;
      }
    if (u >= 0) {
      m[v][u]--;
      k.push_back(u);
    } else {
      p.push_back(v);
      k.pop_back();
    }
  }
  if (p.size() != t + 1) {
    R;
  }
  printf("Euler %s found:\n", c ? "circuit" : "path");
  for (int i = p.size() - 1; i >= 0; i--)
    printf("%c%c", 'a' + p[i], i ? ' ' : '\n');
}
