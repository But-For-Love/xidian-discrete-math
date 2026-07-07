#include <algorithm>
#include <iostream>
using namespace std;
int m, n, a[10], b[10];
int main() {
  cin >> m >> n;
  for (int i = 0; i < m; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  if (m != n)
    return 0;
  sort(a, a + m);
  sort(b, b + n);
  do {
    cout << '{';
    for (int i = 0; i < m; i++)
      cout << '<' << a[i] << ',' << b[i] << '>' << ",}"[i == m - 1];
    cout << '\n';
  } while (next_permutation(b, b + n));
}
