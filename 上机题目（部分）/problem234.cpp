#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int m, n;
  cin >> m >> n;

  vector<int> A(m), B(n);
  for (int i = 0; i < m; i++)
    cin >> A[i];
  for (int i = 0; i < n; i++)
    cin >> B[i];

  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  // Compute n^m
  int total = 1;
  for (int i = 0; i < m; i++)
    total *= n;

  for (int t = 0; t < total; t++) {
    cout << "{";
    // Extract digits for base n, most significant first
    for (int i = 0; i < m; i++) {
      // compute divisor for current position (most significant first)
      int div = 1;
      for (int j = 0; j < m - 1 - i; j++)
        div *= n;
      int digit = (t / div) % n;
      if (i > 0)
        cout << ",";
      cout << "<" << A[i] << "," << B[digit] << ">";
    }
    cout << "}" << endl;
  }

  return 0;
}
