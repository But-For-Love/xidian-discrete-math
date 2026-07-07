#include <algorithm>
#include <iostream>
using namespace std;
int m, n, a[10], b[10], u[10], c[10];
void f(int d) {
  if (d == m) {
    cout << '{';
    for (int i = 0; i < m; i++)
      cout << '<' << a[i] << ',' << c[i] << '>' << ",}"[i == m - 1];
    cout << '\n';
    return;
  }
  for (int i = 0; i < n; i++)
    if (!u[i])
      u[i] = 1, c[d] = b[i], f(d + 1), u[i] = 0;
}
int main() {
  cin >> m >> n;
  for (int i = 0; i < m; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  sort(a, a + m);
  sort(b, b + n);
  f(0);
}
